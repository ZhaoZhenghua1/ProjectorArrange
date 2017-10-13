#include "GridCover.h"
#include <QPainter>

void GridCover::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{
	painter->save();
	painter->setPen(QPen(QBrush(QColor(70, 70, 70)), 1));
	QVector<QLineF> lines;
	for (int i = 0;; i+=1000)
	{
		qreal value = valueToPosition(Qt::Vertical, i);
		if (value > rect().width())
		{
			break;
		}
		lines.push_back(QLineF(value, 0, value, rect().height()));
	}
	for (int i = -1000;;i-=1000)
	{
		qreal value = valueToPosition(Qt::Vertical, i);
		if (value < 0)
		{
			break;
		}
		lines.push_back(QLineF(value, 0, value, rect().height()));
	}

	for (int i = 0;; i += 1000)
	{
		qreal value = valueToPosition(Qt::Horizontal, i);
		if (value > rect().height())
		{
			break;
		}
		lines.push_back(QLineF(0,value, rect().width(), value));
	}
	for (int i = -1000;;i -= 1000)
	{
		qreal value = valueToPosition(Qt::Horizontal, i);
		if (value < 0)
		{
			break;
		}
		lines.push_back(QLineF(0, value, rect().width(), value));
	}
	
	painter->drawLines(lines);
	painter->restore();
}
