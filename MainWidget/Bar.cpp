#include "Bar.h"
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QPainter>
#include <QGraphicsLineItem>
#include <QCursor>

bool Bar::m_sbEnabled = true;
Bar::Bar(Qt::Orientation o, QGraphicsItem* parent ):m_o(o), Base(parent)
{
	m_line = new QGraphicsLineItem(this);
	m_line->setPen(QPen(QColor(74, 255, 255), 1));
	setFlags(ItemIsMovable | ItemSendsGeometryChanges | ItemSendsScenePositionChanges | ItemIsFocusable);
	setAcceptHoverEvents(true);
	setZValue(4);
}


Bar::~Bar()
{
}

void Bar::updatePosition()
{
	QRectF limitRect(QPointF(limitPos(Qt::LeftEdge), limitPos(Qt::TopEdge)), QPointF(limitPos(Qt::RightEdge), limitPos(Qt::BottomEdge)));
	qreal pos = emit valueToPosition(m_o, value());
	QSizeF size = (orient() == Qt::Horizontal ? QSizeF(limitRect.width(), rect().height()) : QSizeF(rect().width(), limitRect.height()));
	QPointF posi = (orient() == Qt::Horizontal ? QPointF(limitRect.left(), limitRect.top() + pos - rect().height() / 2) : QPointF(limitRect.left() + pos - rect().width() / 2, limitRect.top()));
	setPos(QPointF());
	setGeometry(QRectF(posi, size));
}

void Bar::updateData()
{
	m_data.setAttribute("o", m_o);
	m_data.setAttribute("value", m_value);
}

void Bar::updateValue()
{
	//ruler area
	QRectF limitRect(QPointF(limitPos(Qt::LeftEdge), limitPos(Qt::TopEdge)), QPointF(limitPos(Qt::RightEdge), limitPos(Qt::BottomEdge)));
	//central area to ruler area
	QPointF pos = this->pos() + rect().center() - limitRect.topLeft();
	m_value = emit positionToValue(m_o, m_o == Qt::Horizontal ? pos.y() : pos.x());

	updateData();
}

void Bar::setData(const QDomElement& data)
{
	m_data = data;
	m_o = (Qt::Orientation)data.attribute("o").toInt();
	m_value = data.attribute("value").toDouble();
}

QDomElement Bar::data()
{
	return m_data;
}

QVariant Bar::itemChange(GraphicsItemChange change, const QVariant &value)
{
 	if (change == ItemPositionChange && scene())
 	{
		QRectF limitRect(QPointF(limitPos(Qt::LeftEdge), limitPos(Qt::TopEdge)), QPointF(limitPos(Qt::RightEdge), limitPos(Qt::BottomEdge)));
		QPointF newPos = value.toPointF();
		//bar can be anywhere if you drag
		//²»Ô½½ç
// 		if (!m_bNewCreateFlag)
// 		{
// 			if (newPos.y() < limitRect.top())
// 			{
// 				newPos.setY(limitRect.top());
// 			}
// 			if (newPos.x() < limitRect.left())
// 			{
// 				newPos.setX(limitRect.left());
// 			}
// 
// 			if (m_o == Qt::Horizontal && newPos.y() > limitRect.bottom())
// 			{
// 				newPos.setY(limitRect.bottom());
// 			}
// 			if (m_o == Qt::Vertical && newPos.x() > limitRect.right())
// 			{
// 				newPos.setX(limitRect.right());
// 			}
// 		}

		qreal width = ((m_o == Qt::Horizontal) ? rect().height() : rect().width()) / 2;
		qreal value = ((m_o == Qt::Horizontal) ? newPos.y() : newPos.x()) + width;
		if (m_bDragging)
		{
			value = attached(m_o, value);
		}

 		return m_o == Qt::Horizontal ? QPointF(limitRect.left(), value - width) : QPointF(value - width, limitRect.top());
 	}
 	else if (change == ItemPositionHasChanged && scene())
 	{
 		if (parentItem()->boundingRect().contains(mapToParent(value.toPointF())))
 		{
			m_state = Green;////Grey;
 		}
 	}
	return Base::itemChange(change, value);
}

void Bar::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Delete && event->modifiers() == Qt::NoModifier)
	{
		removeData(m_data);
		delete this;
	}
}

void Bar::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (m_sbEnabled)
	{
		setFocus();
	}
	m_bDragging = true;
	return Base::mousePressEvent(event);
}

void Bar::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	ungrabMouse();
	m_state = Green;
	updateValue();
	//	QPointF releasePos = mapToParent(event->pos());// +((m_o == Qt::Horizontal) ? QPointF(0, rect().height() / 2) : QPointF(rect().width() / 2, 0));
//	m_value = emit positionToValue(m_o, attached(m_o, m_o == Qt::Horizontal ? releasePos.y() : releasePos.x()));
//	updatePosition();
//	update();
	m_bDragging = false;
	m_bNewCreateFlag = false;
	emit hideValue();
	return Base::mouseReleaseEvent(event);
}

void Bar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{
	return Base::paint(painter, option, widget);
	painter->save();

	QColor color = m_state == Grey ? Qt::gray : Qt::green;
	painter->setPen(QPen(color, 1));

	QPointF pos1, pos2;
	QRectF rect = this->rect();
	if (m_o == Qt::Horizontal)
	{
		pos1 = (rect.topLeft() + rect.bottomLeft()) / 2;
		pos2 = (rect.topRight() + rect.bottomRight()) / 2;
	}
	else
	{
		pos1 = (rect.topLeft() + rect.topRight()) / 2;
		pos2 = (rect.bottomLeft() + rect.bottomRight()) / 2;
	}
	painter->drawLine(pos1, pos2);

	painter->restore();
}

void Bar::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QPointF pos = mapToParent(event->pos());
	//7 is black border width
	emit mouseTracking(QPointF(positionToValue(Qt::Vertical, pos.x() - 7), positionToValue(Qt::Horizontal, pos.y() - 7)));
	if (m_sbEnabled)
	{
		updateValue();
		emit showValue(m_o, m_value);
		Base::mouseMoveEvent(event);
	}
}

void Bar::resizeEvent(QGraphicsSceneResizeEvent *event)
{
	Base::resizeEvent(event);
	QRectF rect = this->rect();
	QPointF pos1 = (rect.topLeft() + (m_o == Qt::Horizontal ? rect.bottomLeft() : rect.topRight())) / 2;
	QPointF pos2 = (rect.bottomRight() + (m_o == Qt::Horizontal ? rect.topRight() : rect.bottomLeft())) / 2;
	m_line->setLine(QLineF(pos1, pos2));
}

void Bar::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
	if (m_sbEnabled)
	{
		setCursor(QCursor((m_o == Qt::Horizontal) ? Qt::SplitVCursor : Qt::SplitHCursor));
	}
	return Base::hoverMoveEvent(event);
}

void Bar::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	setCursor(Qt::ArrowCursor);
	return Base::hoverLeaveEvent(event);
}

void Bar::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	if (m_sbEnabled)
	{
		emit setBarValue(m_o, m_value);
		updateData();
		updatePosition();
	}
	return Base::mouseDoubleClickEvent(event);
}
