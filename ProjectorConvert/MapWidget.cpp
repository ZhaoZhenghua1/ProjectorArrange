#include "MapWidget.h"
#include <QPainter>

void MapWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawPixmap(QRect(0,0,width(), height()), m_map, m_map.rect());
}
