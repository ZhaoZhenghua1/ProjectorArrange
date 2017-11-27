#include "DestWidget.h"



DestWidget::DestWidget()
{
	ui.setupUi(this);
}


DestWidget::~DestWidget()
{
}

void DestWidget::setPoints(const QVector<QVector<QPointF>>& points)
{
	ui.widget_2->setPoints(points);
}

void DestWidget::setRatio(const QSizeF& ratio)
{
	ui.widget_2->setRatio(ratio);
}
