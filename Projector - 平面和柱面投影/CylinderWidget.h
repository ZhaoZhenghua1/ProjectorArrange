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
	QVector<QVector<QPointF>> m_points;//ͶӰ����
	QRectF m_proRect;//ͶӰ����


	Projector* m_projector = nullptr;

	QVector3D m_dragCentral;//����϶�ͼƬλ��
	QSizeF m_dragSize;//����϶�ͼƬ��С
};

