#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include <QtMath>
#include <QPainter>
#include "RotateItem.h"



RotateItem::RotateItem(QGraphicsItem* parent):Base(parent)
{
	setPen(Qt::NoPen);
	setRect(parent->boundingRect());
}


RotateItem::~RotateItem()
{
}

void RotateItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	Base::mousePressEvent(event);
	event->setAccepted(true);
}

qreal pointAngle(const QPointF& point)
{
	return qAtan2(point.y() , point.x());
}

void RotateItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QPointF center = boundingRect().center();
	qreal angleOld = pointAngle(event->lastPos() - center);
	qreal angleNew = pointAngle(event->pos() - center);
	qreal angle = (angleNew - angleOld) * 180 / 3.141593;
	emit rotate(angle);
	return Base::mouseMoveEvent(event);
}

void RotateItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{
	Base::paint(painter, option, widget);
	painter->drawPixmap(rect(), m_map, m_map.rect());
}
