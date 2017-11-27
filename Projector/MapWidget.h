#pragma once
#include <QGraphicsRectItem>
#include <QObject>

class MapWidget :public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public:
	using QGraphicsRectItem::QGraphicsRectItem;
signals:
	void positionChanged();
public:
	void setPoints(const QVector<QVector<QPointF>>& ps);
	void setProRect(const QRectF& ratio) { m_proRect = ratio; }
	QVector<QVector<QPointF>> points() { return m_points; }
protected:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR)override;
	virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
private:
	QVector<QVector<QPointF>> m_points;
	QRectF m_proRect;
};

