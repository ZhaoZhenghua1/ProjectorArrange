#include "DestWidget.h"



DestWidget::DestWidget()
{
	ui.setupUi(this);
}


DestWidget::~DestWidget()
{
}

void DestWidget::setPixmap(const QPixmap& map)
{
	ui.widget_2->setPixmap(map);
}
