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

void Ruler::setRefer(Ruler* referTo)
{
	m_referTo = referTo;
	if (referTo)
	{
		referTo->m_referTo = nullptr;
	}
	updateRuler();
}

qreal Ruler::rulerToPix(qreal ruler) const
{
	qreal width = (m_orient == Qt::Horizontal) ? rect().width() : rect().height();
	return ruler / m_pixSpace * m_dRulerSpace + width * m_dZeroPoint;
}

qreal Ruler::pixToRuler(qreal pix) const
{
	qreal width = (m_orient == Qt::Horizontal) ? rect().width() : rect().height();
	return (pix - width * m_dZeroPoint) / m_dRulerSpace * m_pixSpace;
}

void Ruler::resizeEvent(QGraphicsSceneResizeEvent *event)
{
	Base::resizeEvent(event);
	updateRuler();
}

void Ruler::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * /* = Q_NULLPTR */)
{

	painter->fillRect(rect(), QColor(35, 35, 35));
	qreal w = m_orient == Qt::Horizontal ?  rect().width() : rect().height();
	qreal begin = -((int(m_dZeroPoint*w / m_dRulerSpace) + 1)*m_dRulerSpace - m_dZeroPoint*w);
	for (qreal x = begin; x <= w; x += m_dRulerSpace)
	{
		QPoint pos = ((m_orient == Qt::Horizontal) ? QPoint(x, rect().height() - 18) : QPoint(rect().width() - 18,x));

		qreal ruler = pixToRuler(x);
		QString drawStr = QString("%1").arg((int)(ruler + ((ruler > 0) ? 0.5 : -0.5)));

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
	if (m_referTo)
	{
		m_pixSpace = m_referTo->m_pixSpace;
		m_dRulerSpace = m_referTo->m_dRulerSpace;
	}
	else
	{
		std::tuple<int, qreal> ret = timeBarRuleStrategy(m_iRulerLength, m_orient == Qt::Horizontal ? rect().width() : rect().height());
		m_pixSpace = std::get<0>(ret);
		m_dRulerSpace = std::get<1>(ret);
	}

	update();
}