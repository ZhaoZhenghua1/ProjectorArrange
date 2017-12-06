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
	virtual void wheelEvent(QGraphicsSceneWheelEvent *event)override;
private:
	QVector3D destPoint(const QVector3D& pos);
	void paintDragItem(QPainter *painter);
private:
	QVector<QVector<QPointF>> m_points;//投影点阵
	QRectF m_proRect;//投影矩形


	Projector* m_projector = nullptr;

	QVector3D m_dragCentral;//鼠标拖动图片位置
	QSizeF m_dragSize;//鼠标拖动图片大小
};

