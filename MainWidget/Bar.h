#pragma once
#include <QGraphicsWidget>
#include <QGraphicsRectItem>
#include <QDomElement>

class Bar :public QGraphicsWidget
{
	Q_OBJECT
	typedef  QGraphicsWidget Base;
public:
	enum State
	{
		Grey,Green
	};
	Bar(Qt::Orientation o, QGraphicsItem* parent = nullptr);
	~Bar();

	Qt::Orientation orient() { return m_o; }
	qreal value() { return m_value; }
	void setValue(qreal value) { m_value = value; }
	qreal position();
	void updatePosition();
	void updateValue();
	void updateData();
	
	void setData(const QDomElement& data);
	QDomElement data();

	static bool dragEnabled() { return m_sbEnabled; }
	static void setDragEnabled(bool b) { m_sbEnabled = b; }
signals:
	qreal positionToValue(Qt::Orientation, qreal);
	qreal valueToPosition(Qt::Orientation, qreal);
	QPointF attached(const QPointF& pos);
	void mouseTracking(const QPointF& location);
	void setBarValue(Qt::Orientation, qreal&);
	void showValue(Qt::Orientation,qreal );
	void hideValue();
	//limit pos is in the ruler area
	qreal limitPos(const Qt::Edge);
	void removeData(const QDomElement& data);
public slots:

protected:
	virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value)override;
	virtual void keyPressEvent(QKeyEvent *event)override;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)override;
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void resizeEvent(QGraphicsSceneResizeEvent *event)override;
	virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event)override;
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event)override;
	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)override;
private:
	Qt::Orientation m_o;
	State m_state = Grey;
	qreal m_value = 0;
	static bool m_sbEnabled;
	QGraphicsLineItem* m_line = nullptr;
	bool m_bDragging = true;
	bool m_bNewCreateFlag = true;
	QDomElement m_data;
};

