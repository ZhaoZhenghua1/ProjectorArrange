#pragma once
#include "ui_ProjectorSettings.h"

class DestWidget;
class Cylinder;
class Ball;
class Plane;
class ProjectConverter : public QWidget
{
	Q_OBJECT
public:
	ProjectConverter();
	~ProjectConverter();
public slots:
	void project();
	void inverseProject();
	void projectPlane();
	void projectRodrigues();
	void invertProjectPlane();
	void innerballpro();
	void outterballpro();
	void projectInnerBall(bool inner = true);
	void inverseballpro();
	void cylinderpro(bool inner = true);
	void innercylinderpro();
	void outtercylinderpro();
	void inversecylinderpro();
	void onComboChanged();
private:
	void setSrc(const QVector<QVector<QVector3D>>& points);
	void setDst(const QVector<QVector<QPointF>>& points);
private:
	Ui::Projector ui;
	DestWidget* m_dstWidget = nullptr;
	QPixmap m_map = QPixmap(":/Resources/origpic.png");
	Cylinder* m_cylinder = nullptr;
	Ball * m_ball = nullptr;
	Plane * m_plane = nullptr;
};

