#pragma once
#include <QGraphicsWidget>


class Bar;
class Ruler : public QGraphicsWidget
{
	Q_OBJECT

	typedef QGraphicsWidget Base;
public:
	Ruler(Qt::Orientation o);
	~Ruler();
	void setRange(unsigned int range);
	unsigned int range() { return m_iRulerLength; }
public slots:
	qreal pixToRuler(qreal timeMS) const;
	qreal rulerToPix(qreal pos) const;
signals:
	void createBar(Qt::Orientation o, const QPointF& pos);
protected:
	virtual void resizeEvent(QGraphicsSceneResizeEvent *event)override;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)override;
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
private:
	qreal timeToRound(qreal t)const;
	void updateRuler();
private:
	unsigned int m_iRulerLength = 10;
	unsigned int m_pixSpace = 1;
	qreal m_dRulerSpace = 1;
	Qt::Orientation m_orient;
	bool m_bPressed = false;
};

