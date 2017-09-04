#include "SelectionArea.h"
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include "SizeGripItem.h"

bool SelectionArea::m_sbRectEnabled = false;
SelectionArea::SelectionArea(QGraphicsItem* parent):Base(parent)
{
	setFlags(ItemIsMovable | ItemSendsGeometryChanges | ItemSendsScenePositionChanges | ItemIsFocusable);
	//pen width should be 0, or the bounding_rect will return a adjusted rect
	setPen(QPen(Qt::black, 0, Qt::DashLine));
	setBrush(QBrush(QColor(255, 255, 255, 100)));
	setZValue(7);
}


SelectionArea::~SelectionArea()
{
}

void SelectionArea::updateData()
{
	m_data.setAttribute("index", m_index);
	m_data.setAttribute("left", m_points[0].x());
	m_data.setAttribute("right", m_points[1].x());
	m_data.setAttribute("top", m_points[0].y());
	m_data.setAttribute("bottom", m_points[1].y());
}

void SelectionArea::updateValue()
{
	//ruler area
	QRectF limitRect(QPointF(limitPos(Qt::LeftEdge), limitPos(Qt::TopEdge)), QPointF(limitPos(Qt::RightEdge), limitPos(Qt::BottomEdge)));

	QRectF seleArea(pos() + rect().topLeft() - limitRect.topLeft(), rect().size());
	m_points[0].setX(positionToValue(Qt::Vertical, seleArea.left()));
	m_points[1].setX(positionToValue(Qt::Vertical, seleArea.right()));

	m_points[0].setY(positionToValue(Qt::Horizontal, seleArea.top()));
	m_points[1].setY(positionToValue(Qt::Horizontal, seleArea.bottom()));

	updateData();

	emit dataChanged();
}

void SelectionArea::updatePosition()
{
	QRectF limitRect(QPointF(limitPos(Qt::LeftEdge), limitPos(Qt::TopEdge)), QPointF(limitPos(Qt::RightEdge), limitPos(Qt::BottomEdge)));

	qreal x1, y1, x2, y2;
	x1 = valueToPosition(Qt::Vertical, m_points[0].x());
	x2 = valueToPosition(Qt::Vertical, m_points[1].x());
	y1 = valueToPosition(Qt::Horizontal, m_points[0].y());
	y2 = valueToPosition(Qt::Horizontal, m_points[1].y());
	QRectF rect(x1, y1, x2 - x1, y2 - y1);
	rect = QRectF(rect.topLeft() + limitRect.topLeft(), rect.size());
	setPos(QPointF());
	setRect(rect);

	//clearfocus so that SizeGrip hide
	clearFocus();
}

qreal SelectionArea::value(Qt::Edge e)
{
	switch (e)
	{
	case Qt::TopEdge:
		return m_points[0].y();
		break;
	case Qt::LeftEdge:
		return m_points[0].x();
		break;
	case Qt::RightEdge:
		return m_points[1].x();
		break;
	case Qt::BottomEdge:
		return m_points[1].y();
		break;
	}
	return 0;
}

void SelectionArea::setValue(Qt::Edge e, qreal value)
{
	switch (e)
	{
	case Qt::TopEdge:
		m_points[0].setY(value);
		break;
	case Qt::LeftEdge:
		m_points[0].setX(value);
		break;
	case Qt::RightEdge:
		m_points[1].setX(value);
		break;
	case Qt::BottomEdge:
		m_points[1].setY(value);
		break;
	}
}

void SelectionArea::setIndex(const QString& index)
{
	m_index = index;
	emit dataChanged();
}

void SelectionArea::setData(const QDomElement& data)
{
	m_data = data;
	m_index = data.attribute("index");
	
	setValue(Qt::LeftEdge, data.attribute("left").toDouble());
	setValue(Qt::RightEdge, data.attribute("right").toDouble());
	setValue(Qt::TopEdge, data.attribute("top").toDouble());
	setValue(Qt::BottomEdge, data.attribute("bottom").toDouble());
}

QDomElement SelectionArea::data()
{
	return m_data;
}

void SelectionArea::onResizeRect(const QRectF& rect)
{
	if (rect.width() < 1 || rect.height() <1)
	{
		return;
	}
	setRect(rect);
	updateValue();
}

QVariant SelectionArea::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == ItemPositionChange && scene() && m_bPressed)
	{
		QRectF limitRect(QPointF(limitPos(Qt::LeftEdge), limitPos(Qt::TopEdge)), QPointF(limitPos(Qt::RightEdge), limitPos(Qt::BottomEdge)));
		QPointF newPos = value.toPointF() + rect().topLeft();

		qreal x = newPos.x();
		x = attached(Qt::Vertical, x);
		if (qAbs(newPos.x() - x) <= 0.1)
		{
			//x not attached
			qreal width = rect().width();
			qreal x2 = x + width;
			x2 = attached(Qt::Vertical, x2);
			x = x2 - width;
		}

		qreal y = newPos.y();
		y = attached(Qt::Horizontal, y);
		if (qAbs(newPos.y() - y) <= 0.1)
		{
			//y not attached
			qreal height = rect().height();
			qreal y2 = y + height;
			y2 = attached(Qt::Horizontal, y2);
			y = y2 - height;
		}

		newPos = QPointF(x, y);
		if (newPos.y() < limitRect.top())
		{
			newPos.setY(limitRect.top());
		}
		if (newPos.x() < limitRect.left())
		{
			newPos.setX(limitRect.left());
		}
		QPointF bottomRight = newPos + QPointF(rect().width(), rect().height());
		if (bottomRight.x() > limitRect.right())
		{
			newPos.setX(limitRect.right() - rect().width());
		}
		if (bottomRight.y() > limitRect.bottom())
		{
			newPos.setY(limitRect.bottom() - rect().height());
		}

		return newPos - rect().topLeft();
	}
	return Base::itemChange(change, value);
}

void SelectionArea::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (m_sbRectEnabled)
	{
		m_bPressed = true;
		Base::mousePressEvent(event);
		setFocus();
		event->setAccepted(true);
//		emit showValue(QRectF(m_points[0], m_points[1]));
	}
}

void SelectionArea::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Delete && event->modifiers() == Qt::NoModifier)
	{
		emit removeData(m_data);
		delete this;
	}
}

void SelectionArea::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QPointF pos = mapToParent(event->pos());
	updateValue();
	emit mouseTracking(QPointF(positionToValue(Qt::Vertical, pos.x() - 7), positionToValue(Qt::Horizontal, pos.y() - 7)));
	emit showValue(QRectF(m_points[0], m_points[1]));
	if (m_sbRectEnabled)
	{
		Base::mouseMoveEvent(event);
	}
}

void SelectionArea::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	if (m_sbRectEnabled)
	{
		QString oldIndex = m_index;
		QRectF rect(m_points[0], m_points[1]);
		emit setSelectArea(m_index, rect);
		m_points[0] = rect.topLeft();
		m_points[1] = rect.bottomRight();
		updatePosition();
		updateData();

		emit dataChanged();
	}
	return Base::mouseDoubleClickEvent(event);
}

void SelectionArea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{
	painter->save();

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
	
	int len = metrics.width(m_index);
	int px = rect().center().x() - len / 2.0;
	//(px,py)是字体基线的起点位置，在qt助手中查找addText函数可以了解到
	int py = rect().center().y() - metrics.height() / 2.0 + metrics.ascent();
	path.addText(px, py, font, m_index);
	painter->strokePath(path, pen);
	painter->drawPath(path);
	painter->fillPath(path, QBrush(QColor(255, 255, 100)));

	painter->restore();
}

void SelectionArea::focusInEvent(QFocusEvent *event)
{
	if (m_sbRectEnabled)
	{
		delete m_sizeGrip;
		m_sizeGrip = new SizeGripItem(this);
		connect(m_sizeGrip, &SizeGripItem::resizeItem, this, &SelectionArea::onResizeRect);
		connect(m_sizeGrip, &SizeGripItem::attached, this, &SelectionArea::attached);
		connect(m_sizeGrip, &SizeGripItem::limitPos, this, &SelectionArea::limitPos);
		setZValue(7);
	}
	return Base::focusInEvent(event);
}

void SelectionArea::focusOutEvent(QFocusEvent *event)
{
	delete m_sizeGrip;
	m_sizeGrip = nullptr;
	setZValue(6);
	return Base::focusOutEvent(event);
}

void SelectionArea::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	m_bPressed = false;
	Base::mouseReleaseEvent(event);
	updateValue();
	emit hideValue();
}
