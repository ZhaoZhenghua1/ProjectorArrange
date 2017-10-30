#pragma once
#include <QWidget>
#include "ui_RealScreen.h"
class DestWidget : public QWidget
{
public:
	DestWidget();
	~DestWidget();

public:
	void setPixmap(const QPixmap& map);
private:
	Ui::RealScreen ui;
};

