#include "Central.h"
#include <QPainter>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsLinearLayout>
#include "SelectionArea.h"

const int LINEWIDTH = 1;
const int ATTACH_DIS = 7;

class TextItem : public QGraphicsTextItem
{
public:
	using QGraphicsTextItem::QGraphicsTextItem;
protected:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override
	{
		painter->save();

		painter->setRenderHint(QPainter::Antialiasing);
		painter->setPen(Qt::NoPen);
		painter->setBrush(QBrush(QColor(0, 0, 0, 150)));
		painter->drawRoundedRect(boundingRect(), 3, 3);

		painter->restore();
		QGraphicsTextItem::paint(painter, option, widget);
	}
};

class MapItem : public QGraphicsWidget
{
public:
	using QGraphicsWidget::QGraphicsWidget;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * /* = Q_NULLPTR */)override
	{
 		painter->drawPixmap(rect(), m_map, m_map.rect());
	}
	void setPixmap(const QPixmap& map)
	{
		if (!map.isNull())
		{
			m_map = map;
		}
	}
private:
	QPixmap m_map = QPixmap(":/background.jpg");
};

Central::Central()
{
	setAcceptedMouseButtons(Qt::LeftButton);
	setAcceptHoverEvents(true);

	m_valueShow = new TextItem(this);
	m_valueShow->setZValue(10);
	m_valueShow->setDefaultTextColor(Qt::white);
	m_valueShow->hide();

	m_centralMapItem = new MapItem;
	QGraphicsLinearLayout* layout = new QGraphicsLinearLayout;
	layout->setContentsMargins(ATTACH_DIS, ATTACH_DIS, ATTACH_DIS, ATTACH_DIS);
	setLayout(layout);
	layout->addItem(m_centralMapItem);
}

Central::~Central()
{
}

void Central::setPixmap(const QPixmap& pixmap)
{
	m_centralMapItem->setPixmap(pixmap);
//	m_map = pixmap;
}

bool Central::rectEnabled()
{
	return SelectionArea::rectEnabled();
}

void Central::setRectEnabled(bool b)
{
	SelectionArea::setRectEnabled(b);

	for (QGraphicsItem* item : childItems())
	{
		if (SelectionArea* bar = dynamic_cast<SelectionArea*>(item))
		{
			bar->setAcceptedMouseButtons(b ? Qt::LeftButton : Qt::NoButton);
		}
	}
}

void Central::setData(const QDomElement& data)
{
	m_data = data;
	for (QGraphicsItem* item : childItems()){
		if (Bar* bar = dynamic_cast<Bar*>(item))
			delete bar;
		else if (SelectionArea* area = dynamic_cast<SelectionArea*>(item))
			delete area;
	}

	for (QDomElement elem = data.firstChildElement("bar"); !elem.isNull(); elem = elem.nextSiblingElement("bar"))
	{
		Bar* bar = new Bar(Qt::Horizontal, this);
		bar->setData(elem);
		connect(bar, &Bar::removeData, this, &Central::removeData);
		connect(bar, &Bar::valueToPosition, this, &Central::valueToPosition);
		connect(bar, &Bar::positionToValue, this, &Central::positionToValue);
		connect(bar, &Bar::attached, this, &Central::attached);
		connect(bar, &Bar::mouseTracking, this, &Central::mouseTracking);
		connect(bar, &Bar::setBarValue, this, &Central::setBarValue);
		connect(bar, &Bar::showValue, this, &Central::showBarValue);
		connect(bar, &Bar::hideValue, this, &Central::hideValue);
		connect(bar, &Bar::limitPos, this, &Central::limitPos);
		bar->updatePosition();
	}

	for (QDomElement elem = data.firstChildElement("area"); !elem.isNull(); elem = elem.nextSiblingElement("area"))
	{
		SelectionArea* selection = new SelectionArea(this);
		selection->setData(elem);
		connect(selection, &SelectionArea::removeData, this, &Central::removeData);
		connect(selection, &SelectionArea::valueToPosition, this, &Central::valueToPosition);
		connect(selection, &SelectionArea::positionToValue, this, &Central::positionToValue);
		connect(selection, &SelectionArea::attached, this, &Central::attached);
		connect(selection, &SelectionArea::mouseTracking, this, &Central::mouseTracking);
		connect(selection, &SelectionArea::setSelectArea, this, &Central::setSelectArea);
		connect(selection, &SelectionArea::showValue, this, &Central::showSelectAreaValue);
		connect(selection, &SelectionArea::hideValue, this, &Central::hideValue);
		connect(selection, &SelectionArea::limitPos, this, &Central::limitPos);
		selection->updatePosition();


		emit selectionAreaCreated(selection);
	}
}

void Central::setLineEnabled(bool b)
{
	Bar::setDragEnabled(b);

	for (QGraphicsItem* item : childItems())
	{
		if (Bar* bar = dynamic_cast<Bar*>(item))
		{
			bar->setAcceptedMouseButtons(b ? Qt::LeftButton : Qt::NoButton);
		}
	}
}

void Central::resizeEvent(QGraphicsSceneResizeEvent *event)
{
	Base::resizeEvent(event);
	for (QGraphicsItem* item : childItems())
	{
		if (Bar* bar = dynamic_cast<Bar*>(item))
		{
			bar->updatePosition();
		}
		else if (SelectionArea* area = dynamic_cast<SelectionArea*>(item))
		{
			area->updatePosition();
		}
	}
}

void Central::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
	emit mouseTracking(QPointF(positionToValue(Qt::Vertical, event->pos().x() - 7), positionToValue(Qt::Horizontal, event->pos().y() - 7)));
	return Base::hoverMoveEvent(event);
}

qreal Central::attached(Qt::Orientation o, qreal pos)
{
	//attach to border
	if ((o == Qt::Horizontal))
	{
		qreal topValue = m_centralMapItem->geometry().top();
		qreal bottomValue = m_centralMapItem->geometry().bottom();
		if (qAbs(topValue - pos) <= ATTACH_DIS)
		{
			return topValue;
		}
		else if (qAbs(bottomValue - pos) <= ATTACH_DIS)
		{
			return bottomValue;
		}
	}
	else
	{
		qreal leftValue = m_centralMapItem->geometry().left();
		qreal rightValue = m_centralMapItem->geometry().right();
		if (qAbs(leftValue - pos) <= ATTACH_DIS)
		{
			return leftValue;
		}
		else if (qAbs(rightValue - pos) <= ATTACH_DIS)
		{
			return rightValue;
		}
	}

	qreal edge = limitPos(Qt::LeftEdge);
	//attach to other items
	for (QGraphicsItem* item : childItems())
	{
		if (Bar* bar = dynamic_cast<Bar*>(item))
		{
			//bar not attached to bars
			if (bar != sender() && !qobject_cast<Bar*>(sender()))
			{
				qreal val = valueToPosition(bar->orient(), bar->value()) + edge;
				if (qAbs(val - pos) <= ATTACH_DIS)
				{
					return val;
				}
			}
		}
		else if (SelectionArea* select = dynamic_cast<SelectionArea*>(item))
		{
			if (select != sender())
			{
				if ((o == Qt::Horizontal))
				{
					qreal topValue = valueToPosition(o, select->value(Qt::TopEdge)) + edge;
					qreal bottomValue = valueToPosition(o, select->value(Qt::BottomEdge)) + edge;
					if (qAbs(topValue - pos) <= ATTACH_DIS)
					{
						return topValue;
					}
					else if (qAbs(bottomValue - pos) <= ATTACH_DIS)
					{
						return bottomValue;
					}
				}
				else
				{
					qreal leftValue = valueToPosition(o, select->value(Qt::LeftEdge)) + edge;
					qreal rightValue = valueToPosition(o, select->value(Qt::RightEdge)) + edge;
					if (qAbs(leftValue - pos) <= ATTACH_DIS)
					{
						return leftValue;
					}
					else if (qAbs(rightValue - pos) <= ATTACH_DIS)
					{
						return rightValue;
					}
				}
			}
		}
	}
	return pos;
}

void Central::showBarValue(Qt::Orientation o, qreal value)
{
	QPoint gloPos = QCursor::pos();
	QGraphicsView* view = scene()->views().first();
	QPoint viewPos = view->viewport()->mapFromGlobal(gloPos);
	QPointF scenePos = view->mapToScene(viewPos);
	QPointF pos = mapFromScene(scenePos) + QPointF(10, -30);
	m_valueShow->setPos(pos);
	QString text = QString("%1:%2").arg(o == Qt::Horizontal ? 'Y' : 'X').arg(emit ratioValue(o == Qt::Horizontal ? Qt::Vertical : Qt::Horizontal, value));
	m_valueShow->setPlainText(text);
	m_valueShow->update();
	m_valueShow->show();
}

void Central::showSelectAreaValue(const QRectF& value)
{
	QPoint gloPos = QCursor::pos();
	QGraphicsView* view = scene()->views().first();
	QPoint viewPos = view->viewport()->mapFromGlobal(gloPos);
	QPointF scenePos = view->mapToScene(viewPos);
	QPointF pos = mapFromScene(scenePos) + QPointF(10, -70);
	m_valueShow->setPos(pos);

	QSize ratio(emit ratioValue(Qt::Horizontal, 1), emit ratioValue(Qt::Vertical, 1));
	unsigned int eH = (int)log10(ratio.width());
	unsigned int eV = (int)log10(ratio.height());
	QString text = QString("%1:%2%\n%3:%4%\n%5:%6%\n%7:%8%").arg('L').arg(value.left()*100, 0, 'f', eH)
		.arg('R').arg(value.right()*100, 0,  'f', eH)
		.arg('T').arg(value.top() * 100, 0, 'f', eV)
		.arg('B').arg(value.bottom() * 100, 0, 'f', eV);
	m_valueShow->setPlainText(text);
	m_valueShow->show();
}

void Central::hideValue()
{
	m_valueShow->hide();
}

qreal Central::limitPos(const Qt::Edge e)
{
	QRectF imageRect = m_centralMapItem->rect();
	imageRect = QRectF(imageRect.topLeft() + m_centralMapItem->pos(), imageRect.size());
	switch (e)
	{
	case Qt::LeftEdge:
		return imageRect.left();
	case Qt::RightEdge:
		return imageRect.right();
	case Qt::TopEdge:
		return imageRect.top();
	case Qt::BottomEdge:
		return imageRect.bottom();
		break;
	}
	return 0;
}

bool Central::isIndexValid(const QString& index)
{
	for (QGraphicsItem* item : childItems())
	{
		if (SelectionArea* select = dynamic_cast<SelectionArea*>(item))
		{
			if (select->index() == index)
			{
				return false;
			}	
		}
	}
	return true;
}

void Central::removeData(const QDomElement& data)
{
	m_data.removeChild(data);
}

void Central::createBar(Qt::Orientation o, const QPointF& scenePos)
{
	Bar* bar = new Bar(o, this);
	connect(bar, &Bar::removeData, this, &Central::removeData);
	QDomElement barElement = createElement("bar");
	m_data.appendChild(barElement);
	barElement.setAttribute("o", o);
	bar->setData(barElement);
	connect(bar, &Bar::valueToPosition, this, &Central::valueToPosition);
	connect(bar, &Bar::positionToValue, this, &Central::positionToValue);
	connect(bar, &Bar::attached, this, &Central::attached);
	connect(bar, &Bar::mouseTracking, this, &Central::mouseTracking);
	connect(bar, &Bar::setBarValue, this, &Central::setBarValue);
	connect(bar, &Bar::showValue, this, &Central::showBarValue);
	connect(bar, &Bar::hideValue, this, &Central::hideValue);
	connect(bar, &Bar::limitPos, this, &Central::limitPos);

	bar->resize(bar->orient() == Qt::Horizontal ? QSizeF(m_centralMapItem->size().width(), LINEWIDTH) : QSizeF(LINEWIDTH, m_centralMapItem->size().height()));

	QPointF itemPos = mapFromScene(scenePos);

	bar->setPos(bar->orient() == Qt::Horizontal ? QPointF(m_centralMapItem->pos().x(), -LINEWIDTH/2 + itemPos.y()) : QPointF(-LINEWIDTH/2 + itemPos.x(), m_centralMapItem->pos().y()));
	
	bar->grabMouse();
}

void Central::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * /* = Q_NULLPTR */)
{
// 	if (m_map.isNull())
// 	{
// 		static QPixmap map(":/background.jpg");
// 		painter->drawPixmap(rect(), map, map.rect());
// 	}
// 	else
// 	{
// 		painter->drawPixmap(rect(), m_map, m_map.rect());
// 	}
	painter->fillRect(rect(), Qt::black);//QColor(35, 35, 35)
}

void Central::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (SelectionArea::rectEnabled())
	{
		m_bPressed = true;
		Base::mousePressEvent(event);
		event->setAccepted(true);
	}
	else
	{
		Base::mousePressEvent(event);
	}
}

void Central::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	m_bPressed = false;
	//create selection finished
	if (m_currentSelection)
	{
		//set focus so that you can press delete
		m_currentSelection->setFocus();
		m_currentSelection->updateValue();
		//notify,so that the TransCoder can create corresponding tab
		emit selectionAreaCreated(m_currentSelection);
		m_currentSelection = nullptr;
	}
	hideValue();
	return Base::mouseReleaseEvent(event);
}

void Central::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	emit mouseTracking(QPointF(positionToValue(Qt::Vertical, event->pos().x() - 7), positionToValue(Qt::Horizontal, event->pos().y() - 7)));

	//mouse pressed and move, if there is no selection, create one
	if (!m_currentSelection)
	{
		// get a index sequence
		QList<SelectionArea*> selections;
		QList<QGraphicsItem*> items = childItems();
		for (QGraphicsItem* item : items)
		{
			if (SelectionArea* p = qgraphicsitem_cast<SelectionArea*>(item))
			{
				selections.push_back(p);
			}
		}
		QVector<int> indexes;
		for (SelectionArea* p : selections)
		{
			indexes.push_back(p->index().toInt());
		}
		indexes.removeAll(0);
		std::sort(indexes.begin(), indexes.end());
		int index = 1;
		for (int i : indexes)
		{
			if (index != i)
			{
				break;;
			}
			++index;
		}

		//create selection
		m_currentSelection = new SelectionArea(this);
		connect(m_currentSelection, &SelectionArea::removeData, this, &Central::removeData);
		QDomElement area = createElement("area");
		Q_ASSERT(!area.isNull());
		Q_ASSERT(!m_data.isNull());
		m_data.appendChild(area);
		m_currentSelection->setData(area);

		m_currentSelection->setIndex(QString("%1").arg(index));
		connect(m_currentSelection, &SelectionArea::valueToPosition, this, &Central::valueToPosition);
		connect(m_currentSelection, &SelectionArea::positionToValue, this, &Central::positionToValue);
		connect(m_currentSelection, &SelectionArea::attached, this, &Central::attached);
		connect(m_currentSelection, &SelectionArea::mouseTracking, this, &Central::mouseTracking);
		connect(m_currentSelection, &SelectionArea::setSelectArea, this, &Central::setSelectArea);
		connect(m_currentSelection, &SelectionArea::showValue, this, &Central::showSelectAreaValue);
		connect(m_currentSelection, &SelectionArea::hideValue, this, &Central::hideValue);
		connect(m_currentSelection, &SelectionArea::limitPos, this, &Central::limitPos);
	}

	QRectF limitRect(QPointF(limitPos(Qt::LeftEdge), limitPos(Qt::TopEdge)), QPointF(limitPos(Qt::RightEdge), limitPos(Qt::BottomEdge)));

	//set to the mouse select area
	QPointF pressedPos = event->buttonDownPos(Qt::LeftButton);
	pressedPos = QPointF(m_currentSelection->attached(Qt::Vertical, pressedPos.x()), m_currentSelection->attached(Qt::Horizontal, pressedPos.y()));
	if (pressedPos.x() < limitRect.left())
	{
		pressedPos.setX(limitRect.left());
	}
	if (pressedPos.y() < limitRect.top())
	{
		pressedPos.setY(limitRect.top());
	}

	QPointF movePos = event->pos();
	movePos = QPointF(m_currentSelection->attached(Qt::Vertical, movePos.x()), m_currentSelection->attached(Qt::Horizontal, movePos.y()));
	if (movePos.x() > limitRect.right())
	{
		movePos.setX(limitRect.right());
	}
	if (movePos.y() > limitRect.bottom())
	{
		movePos.setY(limitRect.bottom());
	}

	qreal x = pressedPos.x() > movePos.x() ? movePos.x() : pressedPos.x();
	qreal y = pressedPos.y() > movePos.y() ? movePos.y() : pressedPos.y();
	qreal width = qAbs(pressedPos.x() - movePos.x());
	qreal x2 = x + width;
	qreal height = qAbs(pressedPos.y() - movePos.y());
	qreal y2 = y + height;

	m_currentSelection->setRect(x, y, x2 - x, y2 - y);
	m_currentSelection->updateValue();

	//show values in the black window
	showSelectAreaValue(QRectF(QPointF(m_currentSelection->value(Qt::LeftEdge), m_currentSelection->value(Qt::TopEdge)),
		QPointF(m_currentSelection->value(Qt::RightEdge), m_currentSelection->value(Qt::BottomEdge))));

	if (m_currentSelection->rect().isEmpty())
	{
		m_currentSelection->removeData(m_currentSelection->data());
		delete m_currentSelection;
		m_currentSelection = nullptr;
	}
	return Base::mouseMoveEvent(event);
}
