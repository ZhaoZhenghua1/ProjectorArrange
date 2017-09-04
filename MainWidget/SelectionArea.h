#pragma once
#include <QGraphicsRectItem>
#include <QDomElement>

class Bar;
class SizeGripItem;
class SelectionArea :public QObject, public QGraphicsRectItem
{
	Q_OBJECT
	typedef QGraphicsRectItem Base;
public:
	SelectionArea(QGraphicsItem* parent = nullptr);
	~SelectionArea();
	void updateValue();
	void updateData();
	void updatePosition();
	static bool rectEnabled() { return m_sbRectEnabled; }
	static void setRectEnabled(bool b) { m_sbRectEnabled = b; }
	qreal value(Qt::Edge e);
	void setValue(Qt::Edge e, qreal value);
	QString index() { return m_index; }
	void setIndex(const QString& index);

	void setData(const QDomElement& data);
signals:
	qreal positionToValue(Qt::Orientation, qreal);
	qreal valueToPosition(Qt::Orientation, qreal);
	qreal attached(Qt::Orientation o, qreal pos);
	void mouseTracking(const QPointF& location);
	void setSelectArea(QString &index, QRectF& rect);
	void showValue(const QRectF& value);
	void hideValue();
	//limit pos is in the ruler area
	qreal limitPos(const Qt::Edge);

	//value changed, update the tab sections
	void dataChanged();
	
	void removeData(const QDomElement& data);
public slots:
	QDomElement data();
private slots:
	void onResizeRect(const QRectF& rect);
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
	QPointF m_points[2];//top, left ,right, bottom
	bool m_bPressed = false;
	static bool m_sbRectEnabled;
	QString m_index;
	SizeGripItem* m_sizeGrip = nullptr;
	QDomElement m_data;
};

