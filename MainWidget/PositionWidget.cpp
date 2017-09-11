#include "PositionWidget.h"



PositionWidget::PositionWidget(QWidget* parent):QWidget(parent)
{
	setupUi(this);
	void (QSpinBox::* pSpinboxDataChanged)(int) = &QSpinBox::valueChanged;
	connect(spinBoxx, pSpinboxDataChanged, this, &PositionWidget::dataChanged);
	connect(spinBoxy, pSpinboxDataChanged, this, &PositionWidget::dataChanged);
}


PositionWidget::~PositionWidget()
{
}

void PositionWidget::setData(const QString& data)
{
	QStringList positions = data.split(',');
	while (positions.size() < 2)
		positions.push_back("0");
	spinBoxx->setValue(positions[0].toInt());
	spinBoxy->setValue(positions[1].toInt());
}

QString PositionWidget::data()
{
	return QString("%1,%2").arg(spinBoxx->value()).arg(spinBoxy->value());
}
