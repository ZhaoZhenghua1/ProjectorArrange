#pragma once
#include <QGraphicsWidget>


class GridCover : public QGraphicsWidget
{
	Q_OBJECT
		typedef QGraphicsWidget Base;
public:
	using QGraphicsWidget::QGraphicsWidget;
signals:
	qreal valueToPosition(Qt::Orientation o, qreal value);
protected:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)override;
};

