#pragma once
#include <QGraphicsWidget>
#include <QPointer>
#include <QVector>
#include <QDomElement>
#include "Bar.h"

class QGraphicsTextItem;
class MapItem;
class Projector;
class Central : public QGraphicsWidget
{
	Q_OBJECT
	typedef QGraphicsWidget Base;
public:
	Central();
	~Central();
	
	void setPixmap(const QPixmap& pixmap);
	void setData(const QDomElement& data);
	void setRatio(unsigned int x, unsigned int y);

	void setProRatio(const QSize& ratio) { m_projectorRatio = ratio; }
	QSize projectorRatio() { return m_projectorRatio; }
	void setProRotate(unsigned int rotate) { m_projectorRotate = rotate; }

	void updatePosition();
signals:
	qreal valueToPosition(Qt::Orientation o, qreal value);
	qreal positionToValue(Qt::Orientation o, qreal value);
	void mouseTracking(const QPointF& location);

	int ratioValue(Qt::Orientation, qreal);
	QDomDocument domDocument();
	void dataChanged()const;

	void setCurrentItemData(const QDomElement& data);
public slots:
	void createBar(Qt::Orientation o, const QPointF& scenePos);
	QLineF attached(const QLineF& line);
	void showBarValue(Qt::Orientation, qreal);
	void hideValue();
	void removeData(const QDomElement& data);
	bool isIndexValid(const QString& index);
	void currentItemDataEdited() const;
	void allItemDataEdited()const;
	bool isMoveMode();
protected:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)override;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void resizeEvent(QGraphicsSceneResizeEvent *event)override;
	virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event)override;
private:
	Projector* createProjector(const QPointF& pos);
	QDomElement createProjectorNode();
private:
	QGraphicsTextItem* m_valueShow = nullptr;
	MapItem* m_centralMapItem = nullptr;
	QDomElement m_data;
	QSize m_ratio;
	QSize m_projectorRatio;
	unsigned int m_projectorRotate = 0;
};

