#pragma once
#include <QWidget>
#include "ui_PositionWidget.h"

class PositionWidget : public QWidget, public Ui::PositionWidget
{
	Q_OBJECT
public:
	PositionWidget(QWidget* parent = nullptr);
	~PositionWidget();
	void setData(const QString& data);
	QString data();
signals:
	void dataChanged();
};

