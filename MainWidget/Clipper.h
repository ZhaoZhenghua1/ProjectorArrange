#ifndef CLIPPER_H
#define CLIPPER_H

#include <QGraphicsView>
#include <QGraphicsWidget>
#include <QDomElement>

class Ruler;
class Central;
class Projector;
class RootWidget : public QGraphicsWidget
{
	Q_OBJECT
public:
	RootWidget();
	Ruler* ruler(Qt::Orientation o);
	Central* central();

	void setData(const QDomElement& data);
signals:
	void mouseTracking(const QPoint& location);
	void setBarValue(Qt::Orientation, qreal&);
	void setSelectArea(QString &index, QRectF& rect);

	void selectionAreaCreated(Projector*);

	QDomDocument domDocument();
public slots:
	qreal valueToPosition(Qt::Orientation o, qreal value);
	qreal positionToValue(Qt::Orientation o, qreal postion);
	void onMouseTracking(const QPointF& location);
	int ratioValue(Qt::Orientation o,  qreal);
protected:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)override;
private:
	Ruler* m_rulers[2];
	Central* m_central;
};

class Clipper : public QGraphicsView
{
	Q_OBJECT
public:
	typedef QGraphicsView Base;
public:
	Clipper(QWidget *parent = 0);
	~Clipper();
	void setRatio(unsigned int x, unsigned int y);
	void setPixmap(const QString& map);
	void setData(const QDomElement& data);

	void setProRatio(const QSize& ratio);
	QSize projectorRatio();
	void setProRotate(unsigned int rotate);
signals:
	void mouseTracking(const QPoint& location);
	void selectionAreaCreated(Projector*);

	bool isIndexValid(const QString& index);

	QDomDocument domDocument();

	void setCurrentItemData(const QDomElement&);
	void currentItemDataEdited() const;
	void allItemDataEdited()const;
	void dataChanged()const;
public slots:
	QSize ratio();

	//show a dialog, setting the double clicked line bar, valueRet is the input and output
	void setBar(Qt::Orientation o, qreal& valueRet);
	//so as the setBar
	void setSelectArea(QString& indexRet,QRectF& rectRet);
	//ctrl+plus zoomin
	void zoomIn();
	//ctrl+minus zoomout
	void zoomOut();

private slots:
private:
	void updateSceneRatio();
	qreal borderWidth();
protected:
	virtual void resizeEvent(QResizeEvent *event)override;
	virtual void wheelEvent(QWheelEvent *event)override;
//	virtual void keyPressEvent(QKeyEvent *event)override;
private:
	RootWidget* m_rootWidget = nullptr;
	bool m_bDisablePaint = false;
	QDomElement m_data;
};

#endif // CLIPPER_H
