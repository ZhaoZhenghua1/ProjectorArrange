#pragma once
#include <QGraphicsRectItem>
#include <QObject>
#include <QVector3D>
#include <array>

class Projector;
class PlaneWidget :public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public:
	PlaneWidget(Projector* p):m_projector(p){}
signals:
	void positionChanged();
public:
	void project();
public:
	void setPoints(const QVector<QVector<QPointF>>& ps);
	void setProRect(const QRectF& ratio) { m_proRect = ratio; }
	QVector<QVector<QPointF>> points() { return m_points; }
protected:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR)override;
	virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void wheelEvent(QGraphicsSceneWheelEvent *event)override;
private:
	void paintDragItem(QPainter *painter);
private:
	qreal _A = 0, _B = 0, _C = 0, _D = 0;
	qreal _cosalpha = 0, _cosbeta = 0, _cosgamma = 0;
	std::array<QVector3D, 4> m_proPoints;
	QVector3D m_central;

	QVector3D m_xVector;
	QVector3D m_yVector;
private:
	QVector<QVector<QPointF>> m_points;
	QRectF m_proRect;

	QPointF m_dragCentral;
	QSizeF m_dragSize;
	enum DragStatus
	{
		eOutRect, eInRect, eAtBorder,
	};
	DragStatus m_dragStatus = eOutRect;
	Projector* m_projector;
};

