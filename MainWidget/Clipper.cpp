#include "Clipper.h"
#include <QResizeEvent>
#include <QGraphicsScene>
#include <QGraphicsAnchorLayout>
#include <QDialog>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QDebug>
#include <QAction>
#include <QScrollBar>
#include <QMessageBox>
#include <QDomElement>
#include "Ruler.h"
#include "Central.h"
#include "GridCover.h"
#include "ui_BarSet.h"
#include "ui_SelectRectSet.h"

const qreal ZOOM_MULT = 1.1;
class BarSetting : public QDialog
{
public:
	BarSetting(QWidget* parent = nullptr) :QDialog(parent)
	{
		ui.setupUi(this);
	}
	Ui::BarDialog ui;
};

class SelectRectSetting : public QDialog
{
public:
	SelectRectSetting(QWidget* parent = nullptr) :QDialog(parent)
	{
		ui.setupUi(this);
	}
	Ui::SelectAreaDialog ui;

};

Clipper::Clipper(QWidget *parent)
	: QGraphicsView(parent)
{
	setAcceptDrops(false);
	QGraphicsScene* scene = new QGraphicsScene;
	scene->setBackgroundBrush(QBrush(QColor(48,48,48)));
	setScene(scene);
	m_rootWidget = new RootWidget;
	connect(m_rootWidget, &RootWidget::mouseTracking, this, &Clipper::mouseTracking);
	connect(m_rootWidget, &RootWidget::domDocument, this, &Clipper::domDocument);
	connect(m_rootWidget, &RootWidget::setBarValue, this, &Clipper::setBar);
	connect(m_rootWidget, &RootWidget::setSelectArea, this, &Clipper::setSelectArea);
	connect(m_rootWidget, SIGNAL(selectionAreaCreated(Projector*)), this, SIGNAL(selectionAreaCreated(Projector*)));
	connect(this, &Clipper::isIndexValid, m_rootWidget->central(), &Central::isIndexValid);
	connect(m_rootWidget->central(), &Central::dataChanged, this, &Clipper::dataChanged);
	connect(m_rootWidget->central(), &Central::setCurrentItemData, this, &Clipper::setCurrentItemData);
	connect(this, &Clipper::currentItemDataEdited, m_rootWidget->central(), &Central::currentItemDataEdited);
	connect(this, &Clipper::allItemDataEdited, m_rootWidget->central(), &Central::allItemDataEdited);
	connect(this, &Clipper::setSnap, m_rootWidget->central(), &Central::setSnap);
	connect(this, &Clipper::showEffect, m_rootWidget->central(), &Central::showEffect);

	scene->addItem(m_rootWidget);
// 	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
// 	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
// 	setFrameShape(QFrame::NoFrame);

	setRatio(12000, 7500);

	setAutoFillBackground(false);

	setStyleSheet("color:rgb(255,255,255)");

	//setRenderHint(QPainter::Antialiasing, true);
}

Clipper::~Clipper()
{

}

void Clipper::setRatio(unsigned int x, unsigned int y)
{
	m_rootWidget->central()->setRatio(x, y);
	m_data.setAttribute("width", x);
	m_data.setAttribute("height", y);

	x /= 0.6;
	y /= 0.6;
	const unsigned int min = 10;
	x = qMax(x, min);
	y = qMax(y, min);
	m_rootWidget->ruler(Qt::Horizontal)->setRefer(nullptr);
	m_rootWidget->ruler(Qt::Vertical)->setRefer(nullptr);
	m_rootWidget->ruler(Qt::Horizontal)->setRange(x);
	m_rootWidget->ruler(Qt::Vertical)->setRange(y);
	updateSceneRatio();
}

QSize Clipper::ratio()
{
	return QSize(m_rootWidget->ruler(Qt::Horizontal)->range()*0.6 + 0.5, m_rootWidget->ruler(Qt::Vertical)->range()*0.6 + 0.5);
}

void Clipper::setPixmap(const QString& map)
{
	m_rootWidget->central()->setPixmap(QPixmap(map));
}

void Clipper::setData(const QDomElement& data)
{
	m_data = data;
	scene()->setSceneRect(QRectF(QPointF(0, 0), viewport()->size()));

	setRatio(data.attribute("width", "12000").toInt(), data.attribute("height", "7500").toInt());

	m_rootWidget->setData(data);
}

void Clipper::setBar(Qt::Orientation o, qreal& valueRet)
{
	static BarSetting* pwr = new BarSetting(this);
	pwr->ui.label->setText(o == Qt::Horizontal ? "Y:" : "X:");

	unsigned int e = (int)log10(m_rootWidget->ruler(o)->range());
	void (QDoubleSpinBox::* ptr)(double) = &QDoubleSpinBox::valueChanged;
	pwr->ui.spinboxV->setDecimals(e);
	connect(pwr->ui.spinboxV, ptr, [this,o](double val) {
		QString value = QString("%1").arg(val / 100 * m_rootWidget->ruler(o == Qt::Horizontal ? Qt::Vertical : Qt::Horizontal)->range(), 0, 'f', 1);
		pwr->ui.labelV->setText(value);
	});
	pwr->ui.spinboxV->setValue(valueRet * 100);

	if (QDialog::Accepted == pwr->exec())
	{
		valueRet = pwr->ui.spinboxV->value()/100;
	}
}

void Clipper::setSelectArea(QString& indexRet, QRectF& rectRet)
{
	SelectRectSetting setting(this);
	SelectRectSetting* pwr = &setting;

	QSize ratio(this->ratio());
	unsigned int eH = (int)log10(ratio.width());
	unsigned int eV = (int)log10(ratio.height());
	
	pwr->ui.index->setText(indexRet);
	pwr->ui.spinboxL->setDecimals(eH);
	void (QDoubleSpinBox::* ptr)(double) = &QDoubleSpinBox::valueChanged;
	connect(pwr->ui.spinboxL, ptr, [this, pwr](double val) {
		QString value = QString("%1").arg(val / 100 * m_rootWidget->ruler(Qt::Horizontal)->range(),0,'f',1);
		pwr->ui.labelLValue->setText(value);
	});
	pwr->ui.spinboxL->setValue(rectRet.left() * 100);

	pwr->ui.spinboxT->setDecimals(eV);
	connect(pwr->ui.spinboxT, ptr, [this, pwr](double val) {
		QString value = QString("%1").arg(val / 100 * m_rootWidget->ruler(Qt::Vertical)->range(), 0, 'f', 1);
		pwr->ui.labelTValue->setText(value);
	});
	pwr->ui.spinboxT->setValue(rectRet.top() * 100);
	
	pwr->ui.spinboxR->setDecimals(eH);
	connect(pwr->ui.spinboxR, ptr, [this, pwr](double val) {
		QString value = QString("%1").arg(val / 100 * m_rootWidget->ruler(Qt::Horizontal)->range(), 0, 'f', 1);
		pwr->ui.labelRValue->setText(value);
	});
	pwr->ui.spinboxR->setValue(rectRet.right() * 100);

	pwr->ui.spinboxB->setDecimals(eV);
	connect(pwr->ui.spinboxB, ptr, [this, pwr](double val) {
		QString value = QString("%1").arg(val / 100 * m_rootWidget->ruler(Qt::Vertical)->range(), 0, 'f', 1);
		pwr->ui.labelBValue->setText(value);
	});
	pwr->ui.spinboxB->setValue(rectRet.bottom() * 100);

	QString oldIndex = indexRet;
	if (QDialog::Accepted == pwr->exec())
	{
		QString index = pwr->ui.index->text();
		if (index.isEmpty())
		{
			QMessageBox::information(this, tr("Indexing Empty"), tr("Set failed, please input a valid index!"));
			return;
		}
		//judge whether there is a conflicting index
		if (index != oldIndex && !isIndexValid(index))
		{
			QMessageBox::information(this, tr("Indexing conflict"), tr("Set failed, please input a different index!"));
			return;
		}
		indexRet = index;
		rectRet = QRectF(QPointF(pwr->ui.spinboxL->value() / 100, pwr->ui.spinboxT->value() / 100), 
			QPointF(pwr->ui.spinboxR->value() / 100, pwr->ui.spinboxB->value() / 100));
	}
}

void Clipper::updateSceneRatio()
{
	QSize size = this->ratio();
	double ratio = size.width()*1.0 / size.height();
	QSizeF viewSize = m_rootWidget->central()->size();
	double viewRatio = viewSize.width()*1.0 / viewSize.height();
	if (ratio < viewRatio)
	{
		//use height
		m_rootWidget->ruler(Qt::Horizontal)->setRefer(m_rootWidget->ruler(Qt::Vertical));
	}
	else
	{
		//use width
		m_rootWidget->ruler(Qt::Vertical)->setRefer(m_rootWidget->ruler(Qt::Horizontal));
	}

	m_rootWidget->central()->updatePosition();
}

qreal Clipper::borderWidth()
{
	return m_rootWidget->rect().width() - m_rootWidget->central()->rect().width();//35 + 7*2
}

void Clipper::resizeEvent(QResizeEvent *event)
{
	QRectF rec(QPointF(0, 0), event->size());

	scene()->setSceneRect(rec);
	m_rootWidget->setGeometry(rec);
	updateSceneRatio();

	return Base::resizeEvent(event);
}

class ScopeUpdateEnable
{
public:
	ScopeUpdateEnable(QWidget* w) :m_widget(w) { w->setUpdatesEnabled(false); }
	~ScopeUpdateEnable() { m_widget->setUpdatesEnabled(true); }
private:
	QWidget* m_widget;
};

void Clipper::wheelEvent(QWheelEvent *event)
{
	return Base::wheelEvent(event);

	//control + wheel , zoom_in and zoom_out
	if (event->modifiers()&Qt::ControlModifier)
	{
		{
			ScopeUpdateEnable sb(this);
			QPoint viewPos = event->pos();
			QPointF scenePos = mapToScene(viewPos);
			QPointF rootPos = m_rootWidget->mapFromScene(scenePos);
			QRectF sceneRect1 = this->sceneRect();
			int delt = event->delta();
			
			if (delt > 0)
			{
				zoomIn();
				rootPos *= ZOOM_MULT;
			}
			else
			{	
				zoomOut();
				rootPos /= ZOOM_MULT;
			}
			//locate to where the cursor is by setting the scrollbar value
			QRectF sceneRect2 = this->sceneRect();
			//already maximumed or minimumed
			if (sceneRect2.size() == sceneRect1.size())
			{
				return;
			}
			
			//(sceneLength - pageStep)*value/range = left.  so that i can get the value of scrollbar
			QPointF scenePos2 = m_rootWidget->mapToScene(rootPos);
			QPointF topleft(scenePos2 - viewPos);
			QScrollBar* hBar = horizontalScrollBar();
			int hrange = hBar->maximum() - hBar->minimum();
			hBar->setValue(topleft.x() * hrange / (sceneRect2.width() - hBar->pageStep()));
			QScrollBar* vBar = verticalScrollBar();
			vBar->setValue(topleft.y()*(vBar->maximum() - vBar->minimum()) / (sceneRect2.height() - vBar->pageStep()));
		}
		update();
	}
	else
	{
		return Base::wheelEvent(event);
	}
}

void Clipper::zoomIn()
{
	return;
	QRectF sceneRect = this->sceneRect();
	sceneRect.setWidth(sceneRect.width() * ZOOM_MULT);
	sceneRect.setHeight(sceneRect.height()* ZOOM_MULT);

	QSizeF maxSize(m_rootWidget->ruler(Qt::Horizontal)->range() + borderWidth(), m_rootWidget->ruler(Qt::Vertical)->range() + borderWidth());
	QSizeF minSize(viewport()->size());
	if (maxSize.width() < minSize.width())
	{
		maxSize.setWidth(minSize.width());
	}
	if (maxSize.height() < minSize.height())
	{
		maxSize.setHeight(minSize.height());
	}
	
	if (sceneRect.width() > maxSize.width())
	{
		sceneRect.setWidth(maxSize.width());
	}
	if (sceneRect.height() > maxSize.height())
	{
		sceneRect.setHeight(maxSize.height());
	}
	scene()->setSceneRect(sceneRect);
	updateSceneRatio();
}

void Clipper::zoomOut()
{
	return;
	QRectF sceneRect = this->sceneRect();
	QSizeF minSize(viewport()->size());
	sceneRect.setWidth(sceneRect.width() / ZOOM_MULT);
	sceneRect.setHeight(sceneRect.height()/ ZOOM_MULT);
	if (sceneRect.width() < minSize.width())
	{
		sceneRect.setWidth(minSize.width());
	}
	if (sceneRect.height() < minSize.height())
	{
		sceneRect.setHeight(minSize.height());
	}
	scene()->setSceneRect(sceneRect);
	updateSceneRatio();
}

void Clipper::setProRatio(const QSize& ratio)
{
	m_rootWidget->central()->setProRatio(ratio);
}

QSize Clipper::projectorRatio()
{
	return m_rootWidget->central()->projectorRatio();
}

void Clipper::setProRotate(unsigned int rotate)
{
	m_rootWidget->central()->setProRotate(rotate);
}

RootWidget::RootWidget()
{
	QGraphicsAnchorLayout* layout = new QGraphicsAnchorLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	setLayout(layout);
	Ruler* rulerTop = new Ruler(Qt::Horizontal);
	Ruler* rulerLeft = new Ruler(Qt::Vertical);
	Central* central = new Central;
	connect(central, &Central::mouseTracking, this, &RootWidget::onMouseTracking);
	connect(central, &Central::domDocument, this, &RootWidget::domDocument);
	connect(central, &Central::positionToValue, this, &RootWidget::positionToValue);
	connect(central, &Central::valueToPosition, this, &RootWidget::valueToPosition);
	connect(central, &Central::ratioValue, this, &RootWidget::ratioValue);

	connect(rulerTop, &Ruler::createBar, central, &Central::createBar);
	connect(rulerLeft, &Ruler::createBar, central, &Central::createBar);
	layout->addAnchor(rulerTop, Qt::AnchorTop, layout, Qt::AnchorTop);
	layout->addAnchor(rulerTop, Qt::AnchorBottom, layout, Qt::AnchorTop)->setSpacing(35);
	layout->addAnchor(rulerTop, Qt::AnchorLeft, layout, Qt::AnchorLeft)->setSpacing(37);
	layout->addAnchor(rulerTop, Qt::AnchorRight, layout, Qt::AnchorRight);

	layout->addAnchor(rulerLeft, Qt::AnchorLeft, layout, Qt::AnchorLeft);
	layout->addAnchor(rulerLeft, Qt::AnchorRight, layout, Qt::AnchorLeft)->setSpacing(37);
	layout->addAnchor(rulerLeft, Qt::AnchorTop, layout, Qt::AnchorTop)->setSpacing(35);
	layout->addAnchor(rulerLeft, Qt::AnchorBottom, layout, Qt::AnchorBottom);

	layout->addAnchor(central, Qt::AnchorTop, rulerTop, Qt::AnchorBottom);
	layout->addAnchor(central, Qt::AnchorLeft, rulerLeft, Qt::AnchorRight);
	layout->addAnchor(central, Qt::AnchorRight, layout, Qt::AnchorRight);
	layout->addAnchor(central, Qt::AnchorBottom, layout, Qt::AnchorBottom);

	m_central = central;
	m_rulers[0] = rulerTop;
	m_rulers[1] = rulerLeft;
}

Ruler* RootWidget::ruler(Qt::Orientation o)
{
	if (o == Qt::Horizontal)
	{
		return m_rulers[0];
	}
	else
	{
		return m_rulers[1];
	}
}

Central* RootWidget::central()
{
	return m_central;
}

void RootWidget::setData(const QDomElement& data)
{
	m_central->setData(data);
}

qreal RootWidget::valueToPosition(Qt::Orientation o, qreal value)
{
	if (o == Qt::Horizontal)
	{
		return m_rulers[1]->rulerToPix(value);
	}
	else
	{
		return m_rulers[0]->rulerToPix(value);
	}
}

qreal RootWidget::positionToValue(Qt::Orientation o, qreal postion)
{
	if (o == Qt::Horizontal)
	{
		return m_rulers[1]->pixToRuler(postion);
	}
	else
	{
		return m_rulers[0]->pixToRuler(postion);
	}
}

void RootWidget::onMouseTracking(const QPointF& location)
{
	emit mouseTracking(QPoint(location.x() + 0.5, location.y() + 0.5 ));
}

int RootWidget::ratioValue(Qt::Orientation o, qreal value)
{
	return ruler(o)->range()*value + 0.5;
}

void RootWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * /* = Q_NULLPTR */)
{
	painter->fillRect(rect(),QColor(35, 35, 35));
}
