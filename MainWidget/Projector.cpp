#include "Projector.h"
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include "RotateItem.h"

Projector::Projector(QGraphicsItem* parent) :Base(parent)
{
	setFlags(ItemIsMovable | ItemSendsGeometryChanges | ItemSendsScenePositionChanges | ItemIsFocusable);
	//pen width should be 0, or the bounding_rect will return a adjusted rect
	setPen(QPen(Qt::black, 0, Qt::DashLine));
	setBrush(QBrush(QColor(255, 255, 255, 100)));
	setZValue(7);
	setAcceptHoverEvents(true);
}

Projector::~Projector()
{
}

void Projector::updateData()
{
	QPointF pos(this->pos() + rect().topLeft());
	pos = QPointF(positionToValue(Qt::Vertical, pos.x()), positionToValue(Qt::Horizontal, pos.y()));
	QString qspos(QString("%1,%2").arg(int(pos.x() + 0.5)).arg(int(pos.y() + 0.5)));
	m_data.firstChildElement("position").firstChild().setNodeValue(qspos);
	setRotate(rotation() + 0.5);

	emit dataChanged();
}

void Projector::updatePosition()
{
	QString pos = m_data.firstChildElement("position").firstChild().nodeValue();
	QStringList poses = pos.split(',');
	if (poses.count()!=2)
		return;
	
	qreal x = valueToPosition(Qt::Vertical, poses[0].toDouble());
	qreal y = valueToPosition(Qt::Horizontal, poses[1].toDouble());
	qreal width = valueToPosition(Qt::Vertical, m_data.firstChildElement("projectionwidth").firstChild().nodeValue().toInt()) - valueToPosition(Qt::Vertical, 0);
	qreal height = valueToPosition(Qt::Horizontal, m_data.firstChildElement("projectionheight").firstChild().nodeValue().toInt()) - valueToPosition(Qt::Horizontal, 0);

 	setPos(QPointF());
 	setRect(QRectF(x,y,width,height));

	QPointF center = this->rect().center();
	setTransformOriginPoint(center);
	setRotation(rotate());

	if (0 == effectMode())
	{
		restoreBrush();
		setZValue(7);
	}
	else if (1 == effectMode())
	{
		setZValue(brightness());
	}
	else if (2 == effectMode())
	{
		setZValue(pixelDensity());
	}

	//clearfocus so that SizeGrip hide
	clearFocus();
}

void Projector::setData(const QDomElement& data)
{
	m_data = data;
}

QString Projector::index()
{
	return m_data.firstChildElement("index").firstChild().nodeValue();
}

qreal Projector::brightness()
{
	qreal liangdu = m_data.firstChildElement("liangdu").firstChild().nodeValue().toDouble();
	qreal prowidth = m_data.firstChildElement("projectionwidth").firstChild().nodeValue().toDouble();
	qreal proheight = m_data.firstChildElement("projectionheight").firstChild().nodeValue().toDouble();
	if (prowidth < 1 || proheight < 1)
	{
		return 0;
	}
	return liangdu / (prowidth * proheight / 1000000);
}

qreal Projector::pixelDensity()
{
	QString fenbianlv = m_data.firstChildElement("fenbianlv").firstChild().nodeValue();
	QStringList value = fenbianlv.split('x');
	if (value.size() < 1)
	{
		value.push_back("1024");
	}
	qreal width = value[0].toDouble();
	if (qAbs(width) < 0.00001)
	{
		width = 1024;
	}

	qreal prowidth = m_data.firstChildElement("projectionwidth").firstChild().nodeValue().toDouble();
	return prowidth / width;
}

void Projector::restoreBrush()
{
	setBrush(QBrush(QColor(255, 255, 255, 100)));
}

QDomElement Projector::data()
{
	return m_data;
}

void Projector::onRotate(qreal angle)
{
	QPointF center = rect().center();
	setTransformOriginPoint(center);
	setRotation(rotation() + angle);
	
	setRotate(rotation() + 0.5);

	emit dataChanged();
}

QVariant Projector::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == ItemPositionChange && scene() && m_bPressed)
	{
		QPointF newPos = value.toPointF();
		newPos = attached(newPos);
		return newPos;
	}
	else if (change == ItemPositionHasChanged && scene())
	{
	}
	return Base::itemChange(change, value);
}

void Projector::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (0 == effectMode())
	{
		setZValue(8);
	}
	//if is not moving mode, transparent the press event to the central to create mode;
	if (!isMoveMode())
	{
		event->ignore();
	}
	//if is moving mode, you can move it or rotate it
	else
	{
		m_bPressed = true;
		Base::mousePressEvent(event);
		setFocus();
		event->setAccepted(true);
	}
}

void Projector::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Delete && event->modifiers() == Qt::NoModifier)
	{
		emit removeData(m_data);
		dataChanged();
		delete this;
	}
}

void Projector::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QPointF pos = mapToParent(event->pos());
	updateData();
	emit mouseTracking(QPointF(positionToValue(Qt::Vertical, pos.x()), positionToValue(Qt::Horizontal, pos.y())));
	
	Base::mouseMoveEvent(event);
}

void Projector::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	// 	if (m_sbRectEnabled)
	// 	{
	// 		QString oldIndex = m_index;
	// 		QRectF rect(m_points[0], m_points[1]);
	// 		emit setSelectArea(m_index, rect);
	// 		m_points[0] = rect.topLeft();
	// 		m_points[1] = rect.bottomRight();
	// 		updatePosition();
	// 		updateData();
	// 
	// 		emit dataChanged();
	// 	}
	return Base::mouseDoubleClickEvent(event);
}

void Projector::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{
	if (0 == effectMode())
	{
		restoreBrush();
	}
	else if (effectMode() == 1)
	{
		int gray = getBrightnessGrey(brightness());
		setBrush(QBrush(QColor(gray, gray, gray)));
	}
	else if (2 == effectMode())
	{
		int hue = getPixdensityHue(pixelDensity());
		setBrush(QBrush(QColor(hue, 0, 0)));
	}
	painter->save();
	QString index = m_data.firstChildElement("index").firstChild().nodeValue();
	Base::paint(painter, option, widget);

	painter->setRenderHint(QPainter::Antialiasing);
	QFont font = painter->font();
	font.setPixelSize(48);
	painter->setFont(font);
	QPen pen(QBrush(QColor(32, 32, 32)), 2);
	int penwidth = 3;//font.pointSize() * 0.05;
	pen.setWidth(penwidth);
	painter->setPen(pen);

	QFontMetrics metrics(font);
	QPainterPath path;

	int len = metrics.width(index);
	int px = rect().center().x() - len / 2.0;
	//(px,py)是字体基线的起点位置，在qt助手中查找addText函数可以了解到
	int py = rect().center().y() - metrics.height() / 2.0 + metrics.ascent();
	path.addText(px, py, font, index);
	painter->strokePath(path, pen);
	painter->drawPath(path);
	painter->fillPath(path, QBrush(QColor(255, 255, 100)));

	painter->restore();
}

void Projector::focusInEvent(QFocusEvent *event)
{
	if (isMoveMode() && isFreeRotate())
	{
		delete m_rotateItem;
		m_rotateItem = new RotateItem(this);
		connect(m_rotateItem, &RotateItem::rotate, this, &Projector::onRotate);
		if (0 == effectMode())
		{
			setZValue(7);
		}
	}
	if (isMoveMode())
	{
		emit setCurrentItemData(m_data);
	}
	return Base::focusInEvent(event);
}

void Projector::focusOutEvent(QFocusEvent *event)
{
	Base::focusOutEvent(event);
	dataChanged();
	delete m_rotateItem;
	m_rotateItem = nullptr;
	if (0 == effectMode())
	{
		setZValue(6);
	}
	return;
}

void Projector::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
	QString text;
	if (1 == effectMode())
	{
		text = QString("Brightness:%1").arg(brightness(),0, 'f', 1);
	}
	else if (2 == effectMode())
	{
		text = QString("PixDensity:%1").arg(pixelDensity(), 0, 'f', 1);
	}
	if (!text.isEmpty())
	{
		QPointF pos = event->pos();
		pos.setX(pos.x() + 15);
		showEffectValue(mapToParent(pos), text);
	}
	return Base::hoverMoveEvent(event);
}

void Projector::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	if (0 != effectMode())
	{
		hideValue();
	}
	return Base::hoverLeaveEvent(event);
}

void Projector::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (0 == effectMode())
	{
		setZValue(7);
	}
	m_bPressed = false;
	Base::mouseReleaseEvent(event);
	updateData();
	emit hideValue();
}

bool Projector::isFreeRotate()
{
	QString rotate = m_data.firstChildElement("rotate").firstChild().nodeValue();
	QStringList rotateValue = rotate.split(';');
	return rotateValue.size() >=2 ? rotateValue[1].toInt() : false;
}

void Projector::setRotate(int rotate)
{
	while (rotate < 0){
		rotate += 360;
	}
	rotate %= 360;
	QString qsrotate = m_data.firstChildElement("rotate").firstChild().nodeValue();
	QStringList rotateValue = qsrotate.split(';');
	rotateValue[0] = QString("%1").arg(rotate);

	m_data.firstChildElement("rotate").firstChild().setNodeValue(rotateValue.join(';'));
}

int Projector::rotate()
{
	QString rotate = m_data.firstChildElement("rotate").firstChild().nodeValue();
	QStringList rotateValue = rotate.split(';');
	return rotateValue[0].toInt();
}