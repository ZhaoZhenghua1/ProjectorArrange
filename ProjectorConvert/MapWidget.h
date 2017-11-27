#pragma once
#include <QWidget>
class MapWidget : public QWidget
{
public:
	using QWidget::QWidget;
public:
	void setPoints(const QVector<QVector<QPointF>>& ps) { m_points = ps; }
	void setRatio(const QSizeF& ratio) { m_ratio = ratio; }
	QVector<QVector<QPointF>> points() { return m_points; }
protected:
	virtual void paintEvent(QPaintEvent *event)override;
private:
	QVector<QVector<QPointF>> m_points;
	QSizeF m_ratio;
};

