#pragma once
#include <QGraphicsWidget>
#include <QPointer>
#include <QVector>
#include <QDomElement>
#include "Bar.h"

class QGraphicsTextItem;
class MapItem;
class SelectionArea;
class Central : public QGraphicsWidget
{
	Q_OBJECT
	typedef QGraphicsWidget Base;
public:
	Central();
	~Central();
	
	void setPixmap(const QPixmap& pixmap);
	bool rectEnabled();
	void setRectEnabled(bool b);
	void setData(const QDomElement& data);
	void setLineEnabled(bool b);
signals:
	qreal valueToPosition(Qt::Orientation o, qreal value);
	qreal positionToValue(Qt::Orientation o, qreal value);
	void mouseTracking(const QPointF& location);
	void setBarValue(Qt::Orientation, qreal&);
	void setSelectArea(QString &index, QRectF& rect);
	int ratioValue(Qt::Orientation, qreal);

	void selectionAreaCreated(SelectionArea*);
	QDomElement createElement(const QString& name);
public slots:
	void createBar(Qt::Orientation o, const QPointF& scenePos);
	qreal attached(Qt::Orientation o, qreal pos);
	void showBarValue(Qt::Orientation, qreal);
	void showSelectAreaValue(const QRectF& value);
	void hideValue();
	qreal limitPos(const Qt::Edge e);
	void removeData(const QDomElement& data);
	bool isIndexValid(const QString& index);
protected:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)override;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void resizeEvent(QGraphicsSceneResizeEvent *event)override;
	virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event)override;
private:
	SelectionArea* m_currentSelection = nullptr;
	bool m_bPressed = false;
	QGraphicsTextItem* m_valueShow = nullptr;
	MapItem* m_centralMapItem = nullptr;
	QDomElement m_data;
};

