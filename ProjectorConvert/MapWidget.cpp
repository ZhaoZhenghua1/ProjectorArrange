#include <QPainter>
#include "MapWidget.h"
#include "Calculator.h"

void MapWidget::paintEvent(QPaintEvent *event)
{
// 	QSizeF size = Calculator::size(m_points);
// 	Calculator::positivePoints(m_points);
	QRectF dstRect(0, 0, width(), height());
	if (/*!size.isValid() ||*/ !dstRect.isValid())
	{
		return;
	}
	qreal param = 0;
	QPainter painter(this);

	for (QVector<QPointF>& vec : m_points)
	{
		for (int i = 0; i < vec.size() - 2; i+=2)
		{
			painter.setPen(QPen());
			painter.drawLine(vec[i], vec[i + 2]);
			painter.setPen(QPen(Qt::red,4));
			painter.drawPoint(vec[i]);
			painter.drawPoint(vec[i + 2]);
		}
		for (int i = 1; i < vec.size() - 2; i += 2)
		{ 
			painter.setPen(QPen());
			painter.drawLine(vec[i], vec[i + 2]);
			painter.setPen(QPen(Qt::red, 4));
			painter.drawPoint(vec[i]);
			painter.drawPoint(vec[i + 2]);
		}
		if (!vec.isEmpty())
		{
		//	painter.drawLine(vec.first(), vec.last());
		}
	}
	int maxnum = 0;
	for (QVector<QPointF>& vec : m_points)
	{
		maxnum = vec.size() > maxnum ? vec.size(): maxnum;
	}
	for (int i = 0; i < maxnum ; ++i)
	{
		for (int j = 0 ; j < m_points.size() - 1; ++j)
		{
			if ( (i < m_points[j].size()) && (i < m_points[j+1].size()))
			{
				painter.setPen(QPen());
				painter.drawLine(m_points[j][i], m_points[j+1][i]);
			}
		}
	}
// 	if (width()/height() > size.width()/ size.height())
// 	{
// 		param = size.height() / height();
// 		//use height
// 		dstRect.setWidth(height()*size.width() / size.height());
// 	}
// 	else
// 	{
// 		param = size.width() / width();
// 		dstRect.setHeight(width()*size.height()/ size.width());
// 	}
//	painter.drawPoints(m_points.data(), m_points.size());
// 	QVector<QPointF> lines;
// 	for (int i = 0; i < m_points.size(); ++i)
// 	{
// 		QPointF point = m_points[i];
// 		point /= param;
// 		lines.push_back(point);
// 	}
// 	painter.setRenderHint(QPainter::HighQualityAntialiasing);
// 	painter.drawPoints(lines.data(), lines.size());

// 	QVector<QLineF> lines;
// 	for (int i = 0; i < m_points.size(); ++i)
// 	{
// 		QPointF point = m_points[i];
// 		point /= param;
// 		int col = i % 11;
// 		int row = i / 11;
// 		//draw hor
// 		if (col != 10)
// 		{
// 			QPointF point2 = m_points[i + 1] / param;
// 			lines.push_back(QLineF(QPointF(point.x(), point.y()), point2));
// 		}
// 		//draw ver
// 		if (row != (m_points.size() / 11 - 1))
// 		{
// 			QPointF point2 = m_points[(row + 1) * 11 + col] / param;
// 			lines.push_back(QLineF(QPointF(point.x(), point.y()), point2));
// 		}
// 	}
// 	painter.setRenderHint(QPainter::HighQualityAntialiasing);
// 	painter.drawLines(lines);
}
