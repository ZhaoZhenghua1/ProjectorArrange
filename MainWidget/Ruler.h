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
	void setZeroPoint(qreal zero) { m_dZeroPoint = zero; }

	void setRefer(Ruler* referTo);
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
	void updateRuler();
private:
	unsigned int m_iRulerLength = 10;
	unsigned int m_pixSpace = 1;
	qreal m_dRulerSpace = 1;
	qreal m_dZeroPoint = 0.2;
	Qt::Orientation m_orient;
	bool m_bPressed = false;

	Ruler* m_referTo = nullptr;
};

