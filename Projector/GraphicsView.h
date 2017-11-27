#pragma once
#include <QGraphicsView>
class GraphicsView : public QGraphicsView
{
public:
	GraphicsView();
	~GraphicsView();
	void setRootItem(QGraphicsRectItem* item);
protected:
	virtual void resizeEvent(QResizeEvent *event)override;
private:
	QGraphicsRectItem* m_rootitem = nullptr;
};

