#pragma once
#include <QGraphicsRectItem>
#include <QObject>
#include <QVector3D>
#include <array>
#include "ToolS.h"

class Projector;
class CylinderWidget:public QObject ,public QGraphicsRectItem
{
	Q_OBJECT
public:
	CylinderWidget(Projector* p);
	~CylinderWidget();
public slots:
	void project();
public:
	void init();
protected:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR)override;
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
private:
	QVector3D destPoint(const QVector3D& pos);
	void paintDragItem(QPainter *painter);
private:
	QVector<QVector<QPointF>> m_points;
	QRectF m_proRect;


	Projector* m_projector = nullptr;

	QVector3D m_dragCentral;
	QSizeF m_dragSize;
private:
	//Ðý×ªX
	QMatrix3x3 m_rmX;
	//Ðý×ªZ
	QMatrix3x3 m_rmZ;
};

