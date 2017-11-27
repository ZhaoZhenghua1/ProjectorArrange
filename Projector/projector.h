#ifndef PROJECTOR_H
#define PROJECTOR_H

#include <QtWidgets/QMainWindow>
#include "ui_projector.h"
#include <QVector3D>
#include <array>

class MapWidget;
class DragItem;
class Projector : public QMainWindow
{
	Q_OBJECT

public:
	Projector(QWidget *parent = 0);
	~Projector();
public slots:
void project();
void onDragItemChanged();
private:
	void projectPlane();
	void projectCylinder();
	void projectBall();
private:
	void init();
	//正常投影时的参数
	std::array<QVector3D,4> proPoints();
private:
	Ui::ProjectorClass ui;
	DragItem* m_dragItem = nullptr;
	MapWidget* m_widget = nullptr;
	qreal _A = 0, _B = 0, _C = 0, _D = 0;
	std::array<QVector3D, 4> m_proPoints;
};

#endif // PROJECTOR_H
