#include "Projector.h"
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include "RotateItem.h"
//#include "SizeGripItem.h"

Projector::Projector(QGraphicsItem* parent) :Base(parent)
{
	setFlags(ItemIsMovable | ItemSendsGeometryChanges | ItemSendsScenePositionChanges | ItemIsFocusable);
	//pen width should be 0, or the bounding_rect will return a adjusted rect
	setPen(QPen(Qt::black, 0, Qt::DashLine));
	setBrush(QBrush(QColor(255, 255, 255, 100)));
	setZValue(7);
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
// 
// 	//clearfocus so that SizeGrip hide
// 	clearFocus();
}

// qreal Projector::value(Qt::Edge e)
// {
// 	switch (e)
// 	{
// 	case Qt::TopEdge:
// 		return m_points[0].y();
// 		break;
// 	case Qt::LeftEdge:
// 		return m_points[0].x();
// 		break;
// 	case Qt::RightEdge:
// 		return m_points[1].x();
// 		break;
// 	case Qt::BottomEdge:
// 		return m_points[1].y();
// 		break;
// 	}
// 	return 0;
// }

// void Projector::setValue(Qt::Edge e, qreal value)
// {
// 	switch (e)
// 	{
// 	case Qt::TopEdge:
// 		m_points[0].setY(value);
// 		break;
// 	case Qt::LeftEdge:
// 		m_points[0].setX(value);
// 		break;
// 	case Qt::RightEdge:
// 		m_points[1].setX(value);
// 		break;
// 	case Qt::BottomEdge:
// 		m_points[1].setY(value);
// 		break;
// 	}
// }

void Projector::setData(const QDomElement& data)
{
	m_data = data;
}

QString Projector::index()
{
	return m_data.firstChildElement("index").firstChild().nodeValue();
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
		QRectF sceneRect = rect();
		QPointF newPos = value.toPointF() + rect().topLeft() + pos();
		sceneRect.setTopLeft(newPos);

// 		qreal x = newPos.x();
// 		x = attached(Qt::Vertical, x);
// 		if (qAbs(newPos.x() - x) <= 0.1)
// 		{
// 			//x not attached
// 			qreal width = rect().width();
// 			qreal x2 = x + width;
// 			x2 = attached(Qt::Vertical, x2);
// 			x = x2 - width;
// 		}
// 
// 		qreal y = newPos.y();
// 		y = attached(Qt::Horizontal, y);
// 		if (qAbs(newPos.y() - y) <= 0.1)
// 		{
// 			//y not attached
// 			qreal height = rect().height();
// 			qreal y2 = y + height;
// 			y2 = attached(Qt::Horizontal, y2);
// 			y = y2 - height;
// 		}

//		newPos = QPointF(x, y);

		return newPos - rect().topLeft();
	}
	return Base::itemChange(change, value);
}

void Projector::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
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
		setZValue(7);
	}
	return Base::focusInEvent(event);
}

void Projector::focusOutEvent(QFocusEvent *event)
{
	Base::focusOutEvent(event);
	dataChanged();
	delete m_rotateItem;
	m_rotateItem = nullptr;
	setZValue(6);
	return;
}

void Projector::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
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