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
	if (m_rootitem == item)
	{
		return;
	}
	if (m_rootitem)
	{
		scene()->removeItem(m_rootitem);
	}
	m_rootitem = item;
	scene()->addItem(item);
	item->setRect(QRectF(QPointF(), rect().size()));
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
