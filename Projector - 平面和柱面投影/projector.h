#ifndef PROJECTOR_H
#define PROJECTOR_H

#include <QtWidgets/QMainWindow>
#include <QSettings>
#include "ui_projector.h"

class PlaneWidget;
class CylinderWidget;
class GraphicsView;
class Projector : public QMainWindow
{
	Q_OBJECT

public:
	Projector(QWidget *parent = 0);
	~Projector();
public slots:
void project();
private:
	void projectPlane();
	void projectCylinder();
	void projectBall();
private:
	void init();
	//正常投影时的参数
	std::array<QVector3D,4> proPoints();
private:
	GraphicsView* m_view = nullptr;
	QSettings* m_settings;
	Ui::ProjectorClass ui;

	PlaneWidget* m_planewidget = nullptr;
	CylinderWidget* m_cylinderWidget = nullptr;

	friend class PlaneWidget;
	friend class CylinderWidget;
};

#endif // PROJECTOR_H
