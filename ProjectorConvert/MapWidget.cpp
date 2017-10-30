#include "MapWidget.h"
#include <QPainter>

void MapWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QRectF dstRect(0, 0, width(), height());
	if (!dstRect.isValid() || !m_map.rect().isValid())
	{
		return;
	}
	if (width()/height() > m_map.rect().width()/m_map.rect().height())
	{
		//use height
		dstRect.setWidth(height()*m_map.rect().width() / m_map.rect().height());
	}
	else
	{
		dstRect.setHeight(width()*m_map.rect().height()/m_map.rect().width());
	}
	painter.drawPixmap(dstRect, m_map, m_map.rect());
}
