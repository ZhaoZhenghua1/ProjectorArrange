#include "Ruler.h"
#include <QPainter>
#include <QGraphicsSceneResizeEvent>
#include "Bar.h"

Ruler::Ruler(Qt::Orientation o):m_orient(o)
{
	setAcceptedMouseButtons(Qt::AllButtons);
	setZValue(2);
}


Ruler::~Ruler()
{
}

qreal Ruler::timeToRound(qreal t)const
{
	return t;
	qreal precision =  m_pixSpace/ m_dRulerSpace;
	if (t < precision && t > -precision)
	{
		return 0;
	}
	qreal tmin = t - precision;
	qreal tmax = t + precision;
	int e = 1;
	while (std::ceil(tmin / 10) < (tmax / 10) && tmin > 10)
	{
		tmin = std::ceil(tmin / 10);
		tmax /= 10;
		e *= 10;
	}
	return tmin * e;
}

//根据时间长度和时间轴长度计算时间间距和像素间距
//时间间距为 1/2/5 * 10的幂次方
std::tuple<int, qreal> timeBarRuleStrategy(const unsigned int mappixLength, qreal distance)
{
	//时间轴绘制策略
	qreal timeSpace = mappixLength * 100.0 / distance;
	unsigned int e = pow(10, (int)log10(timeSpace));
	timeSpace /= e;
	if (timeSpace > 0.99999 && timeSpace <= 2.00001)
	{
		timeSpace = 2;
	}
	else if (timeSpace > 2 && timeSpace <= 5)
	{
		timeSpace = 5;
	}
	else
	{
		timeSpace = 10;
	}
	timeSpace *= e;

	qreal pixSpace = distance * timeSpace / mappixLength;

	return{ (int)timeSpace , pixSpace };
}
void Ruler::setRange(unsigned int range)
{
	m_iRulerLength = range;
	updateRuler();
}

qreal Ruler::pixToRuler(qreal timeMS) const
{
	return timeMS * 1.0 * m_iRulerLength/ m_pixSpace * m_dRulerSpace;
}

qreal Ruler::rulerToPix(qreal pos) const
{
	return timeToRound(pos / m_dRulerSpace * m_pixSpace) / m_iRulerLength;
}

void Ruler::resizeEvent(QGraphicsSceneResizeEvent *event)
{
// 	std::tuple<int, qreal> ret = timeBarRuleStrategy(m_iRulerLength, m_orient == Qt::Horizontal ? event->newSize().width() : event->newSize().height());
// 	m_pixSpace = std::get<0>(ret);
// 	m_dRulerSpace = std::get<1>(ret);
	Base::resizeEvent(event);
	updateRuler();
}

void Ruler::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * /* = Q_NULLPTR */)
{

	painter->fillRect(rect(), QColor(35, 35, 35));
//	painter->drawRect(rect());
	qreal w = m_orient == Qt::Horizontal ?  rect().width() : rect().height();
	for (qreal x = 0; x <= w; x += m_dRulerSpace)
	{
		QPoint pos = ((m_orient == Qt::Horizontal) ? QPoint(x, rect().height() - 18) : QPoint(rect().width() - 18,x));

		QString drawStr = QString("%1").arg((int)(rulerToPix(x)*m_iRulerLength + 0.5));

		int fontW = painter->fontMetrics().width(drawStr);
		int fontH = painter->fontMetrics().height();

		pos -= ((m_orient == Qt::Horizontal) ? QPoint(fontW / 2, 0) : QPoint(fontW / 2, 3));
		
		painter->setPen(QPen(QColor(163, 163, 163)));
		painter->drawText(pos, drawStr);

		painter->setPen(QPen(QColor(79, 79, 79)));
		if (m_orient == Qt::Horizontal)
		{
			painter->drawLine(QPointF(x, rect().height() - 13), QPointF(x, rect().height()));
		}
		else
		{
			painter->drawLine(QPointF(rect().width() - 13, x), QPointF(rect().width(), x));
		}

		for (int i = 1; i < 5; ++i)
		{
			if (m_orient == Qt::Horizontal)
			{
				if (rect().width() > x + m_dRulerSpace / 5 * i)
				{
					painter->drawLine(QPointF(x + m_dRulerSpace / 5 * i , rect().height() - 6), QPointF(x + m_dRulerSpace / 5 * i , rect().height()));
				}
			}
			else
			{
				if (rect().height() > x + m_dRulerSpace / 5 * i)
				{
					painter->drawLine(QPointF(rect().width() - 6, x + m_dRulerSpace / 5 * i ), QPointF(rect().width(), x + m_dRulerSpace / 5 * i ));
				}
			}
		}
	}
}

void Ruler::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (m_bPressed && ((m_orient == Qt::Horizontal && event->pos().y() >= boundingRect().bottom()) || 
		(m_orient == Qt::Vertical && event->pos().x() >= boundingRect().right())))
	{
		m_bPressed = false;
		emit createBar(m_orient, event->buttonDownScenePos(Qt::LeftButton));
	}
}

void Ruler::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	Base::mousePressEvent(event);
	if (Bar::dragEnabled())
	{
		event->setAccepted(true);
		m_bPressed = true;
	}
}

void Ruler::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	m_bPressed = false;
	return Base::mouseReleaseEvent(event);
}

void Ruler::updateRuler()
{
	std::tuple<int, qreal> ret = timeBarRuleStrategy(m_iRulerLength, m_orient == Qt::Horizontal ? rect().width() : rect().height());
	m_pixSpace = std::get<0>(ret);
	m_dRulerSpace = std::get<1>(ret);
	update();
}