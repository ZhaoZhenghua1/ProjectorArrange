#include <QPainter>
#include "MapWidget.h"

void MapWidget::setPoints(const QVector<QVector<QPointF>>& ps)
{
	m_points = ps;
}

void MapWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /*= Q_NULLPTR*/)
{
	QGraphicsRectItem::paint(painter, option, widget);
	QPainterPath path;
	path.addRect(rect());
	painter->setClipPath(path);

	QPointF topleft = m_proRect.topLeft();
	qreal xmmpix = rect().width() / m_proRect.width();
	qreal ymmpix = rect().height() / m_proRect.height();
	QVector<QVector<QPointF>> tempPoints = m_points;
	for (QVector<QPointF>& vec : tempPoints)
	{
		for (QPointF& po : vec)
		{
			po -= topleft;
			po.setX(po.x()*xmmpix);
			po.setY(po.y()*ymmpix);
			po += rect().topLeft();
		}
	}

	qreal param = 0;

	for (QVector<QPointF>& vec : tempPoints)
	{
		for (int i = 0; i < vec.size() - 2; i += 2)
		{
			painter->setPen(QPen());
			painter->drawLine(vec[i], vec[i + 2]);
			painter->setPen(QPen(Qt::red, 4));
			painter->drawPoint(vec[i]);
			painter->drawPoint(vec[i + 2]);
		}
		for (int i = 1; i < vec.size() - 2; i += 2)
		{
			painter->setPen(QPen());
			painter->drawLine(vec[i], vec[i + 2]);
			painter->setPen(QPen(Qt::red, 4));
			painter->drawPoint(vec[i]);
			painter->drawPoint(vec[i + 2]);
		}
		if (!vec.isEmpty())
		{
			//	painter.drawLine(vec.first(), vec.last());
		}
	}
	int maxnum = 0;
	for (QVector<QPointF>& vec : tempPoints)
	{
		maxnum = vec.size() > maxnum ? vec.size() : maxnum;
	}
	for (int i = 0; i < maxnum; ++i)
	{
		for (int j = 0; j < tempPoints.size() - 1; ++j)
		{
			if ((i < tempPoints[j].size()) && (i < tempPoints[j + 1].size()))
			{
				painter->setPen(QPen());
				painter->drawLine(tempPoints[j][i], tempPoints[j + 1][i]);
			}
		}
	}
}

QVariant MapWidget::itemChange(GraphicsItemChange change, const QVariant &value)
{
	QVariant ret = QGraphicsRectItem::itemChange(change, value);
	if (change == ItemPositionHasChanged && scene())
	{
		emit positionChanged();
	}
	return ret;
}