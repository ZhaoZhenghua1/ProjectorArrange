#include "GraphicsView.h"
#include <QResizeEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

GraphicsView::GraphicsView()
{
	QGraphicsScene* scene = new QGraphicsScene;
	setScene(scene);
}


GraphicsView::~GraphicsView()
{
}

void GraphicsView::setRootItem(QGraphicsRectItem* item)
{
	m_rootitem = item;
	scene()->addItem(item);
}

void GraphicsView::resizeEvent(QResizeEvent *event)
{
	QRectF rec(QPointF(0, 0), event->size());

	if (m_rootitem)
	{
		m_rootitem->setRect(rec);
	}
	scene()->setSceneRect(rec);
	return QGraphicsView::resizeEvent(event);
}
