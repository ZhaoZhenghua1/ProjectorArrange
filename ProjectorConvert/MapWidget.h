#pragma once
#include <QWidget>
class MapWidget : public QWidget
{
public:
	using QWidget::QWidget;
public:
	void setPixmap(const QPixmap& map) { m_map = map; }
	QPixmap pixmap() { return m_map; }

	void setPoints(const QVector<QPointF>& ps) { m_points = ps; }
	QVector<QPointF> points() { return m_points; }
protected:
	virtual void paintEvent(QPaintEvent *event)override;
private:
	QPixmap m_map;
	QVector<QPointF> m_points;
};

