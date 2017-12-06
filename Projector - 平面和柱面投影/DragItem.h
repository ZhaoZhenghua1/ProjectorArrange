#pragma once
#include <QGraphicsRectItem>
#include <QObject>
#include <array>

class DragItem :public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public:
	using QGraphicsRectItem::QGraphicsRectItem;
signals:
	void positionChanged();
public:
	void setPoints(const std::array<QPointF, 4>& ps) { m_points = ps; }
	void setProRect(const QRectF& ratio) { m_proRect = ratio; }
protected:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;
	virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
private:
	std::array<QPointF,4> m_points;
	QRectF m_proRect;
};

