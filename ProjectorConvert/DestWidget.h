#pragma once
#include <QWidget>
#include "ui_RealScreen.h"
class DestWidget : public QWidget
{
public:
	DestWidget();
	~DestWidget();

public:
	void setPoints(const QVector<QVector<QPointF>>& points);
	void setRatio(const QSizeF& ratio);
private:
	Ui::RealScreen ui;
};

