#pragma once
#include <QGraphicsRectItem>
#include <QDomElement>

class Bar;
//class SizeGripItem;
class RotateItem;
class Projector :public QObject, public QGraphicsRectItem
{
	Q_OBJECT
		typedef QGraphicsRectItem Base;
public:
	Projector(QGraphicsItem* parent = nullptr);
	~Projector();

	void updateData();
	void updatePosition();

	void setData(const QDomElement& data);

	QString index();
signals:
	qreal positionToValue(Qt::Orientation, qreal);
	qreal valueToPosition(Qt::Orientation, qreal);
	QPointF attached(const QPointF& pos);
	void mouseTracking(const QPointF& location);
	void setSelectArea(QString &index, QRectF& rect);
	void showValue(const QRectF& value);
	void hideValue();
	//limit pos is in the ruler area
	qreal limitPos(const Qt::Edge);

	bool isMoveMode();
	//value changed, update the tab sections
	void dataChanged()const;

	void removeData(const QDomElement& data);
	void setCurrentItemData(const QDomElement& data);
	public slots:
	QDomElement data();
	private slots:
	void onRotate(qreal angle);
protected:
	virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value)override;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void keyPressEvent(QKeyEvent *event)override;
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;
	virtual void focusInEvent(QFocusEvent *event)override;
	virtual void focusOutEvent(QFocusEvent *event)override;
private:
	bool isFreeRotate();
	void setRotate(int rotate);
	int rotate();
private:
	QLineF topLine(const QRectF& rect);
	QLineF leftLine(const QRectF& rect);
	QLineF rightLine(const QRectF& rect);
	QLineF bottomLine(const QRectF& rect);
private:
	QPoint m_point;
	bool m_bPressed = false;
	RotateItem* m_rotateItem = nullptr;
	QDomElement m_data;
};

