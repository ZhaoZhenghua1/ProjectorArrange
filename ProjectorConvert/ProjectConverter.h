#pragma once
#include "ui_projectorconverter.h"

class ProjectConverter : public QWidget
{
	Q_OBJECT
public:
	ProjectConverter();
	~ProjectConverter();
public slots:
	void setPixmap(const QString& map);
	void project2();
	void project();
	void invertProject();
	void swapPixmap();
private:
	void setSrc(const QVector<QVector3D>& points);
private:
	Ui::ProjectorConverter ui;
	QPixmap m_map = QPixmap(":/Resources/origpic.png");
};

