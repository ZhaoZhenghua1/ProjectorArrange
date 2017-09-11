#pragma once
#include <QGraphicsEllipseItem>

class RotateItem :public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT
	typedef QGraphicsEllipseItem Base;
public:
	RotateItem(QGraphicsItem* parent);
	~RotateItem();
signals:
	void rotate(qreal angle);
protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)override;
private:
	QPixmap m_map = QPixmap(":/rotate.png");
	qreal m_angle = 0;
};

