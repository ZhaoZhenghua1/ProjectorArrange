#pragma once
#include <QWidget>
class MapWidget : public QWidget
{
public:
	using QWidget::QWidget;
public:
	void setPixmap(const QPixmap& map) { m_map = map; }
	QPixmap pixmap() { return m_map; }
protected:
	virtual void paintEvent(QPaintEvent *event)override;
private:
	QPixmap m_map;
};

