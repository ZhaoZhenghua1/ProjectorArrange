#include "Central.h"
#include <QPainter>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsLinearLayout>
#include <QTimer>
#include <QtMath>
#include "Projector.h"
#include "GridCover.h"

const int LINEWIDTH = 1;
const int ATTACH_DIS = 7;

class TextItem : public QGraphicsTextItem
{
public:
	using QGraphicsTextItem::QGraphicsTextItem;
protected:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override
	{
		painter->save();

		painter->setRenderHint(QPainter::Antialiasing);
		painter->setPen(Qt::NoPen);
		painter->setBrush(QBrush(QColor(0, 0, 0, 150)));
		painter->drawRoundedRect(boundingRect(), 3, 3);

		painter->restore();
		QGraphicsTextItem::paint(painter, option, widget);
	}
};

class MapItem : public QGraphicsRectItem
{
public:
	using QGraphicsRectItem::QGraphicsRectItem;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * /* = Q_NULLPTR */)override
	{
 		painter->drawPixmap(rect(), m_map, m_map.rect());
	}
	void setPixmap(const QPixmap& map)
	{
		if (!map.isNull())
		{
			m_map = map;
		}
	}
private:
	QPixmap m_map = QPixmap(":/background.jpg");
};

class LineItem : public QGraphicsLineItem
{
public:
	LineItem(Central* central) :QGraphicsLineItem(central),m_central(central) 
	{
		//setPen(QPen(Qt::yellow));
	}
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * widget/* = Q_NULLPTR */)override
	{
		QGraphicsLineItem::paint(painter, option, widget);
	}
private:
	Central* m_central = nullptr;
};

Central::Central()
{
	setAcceptedMouseButtons(Qt::LeftButton);
	setAcceptHoverEvents(true);
	setFlags(QGraphicsItem::ItemIsSelectable);

	m_valueShow = new TextItem(this);
	m_valueShow->setZValue(10000000);
	m_valueShow->setDefaultTextColor(Qt::white);
	m_valueShow->hide();

	m_centralMapItem = new MapItem(this);

	m_line = new LineItem(this);
	m_line->setZValue(10000000);

	m_grid = new GridCover(this);
	connect(m_grid, &GridCover::valueToPosition, this, &Central::valueToPosition);
	connect(m_grid, &GridCover::positionToValue, this, &Central::positionToValue);
}

Central::~Central()
{
}

void Central::setPixmap(const QPixmap& pixmap)
{
	m_centralMapItem->setPixmap(pixmap);
}

void Central::setData(const QDomElement& data)
{
	m_data = data;
	for (QGraphicsItem* item : childItems()) {
		if (Bar* bar = dynamic_cast<Bar*>(item))
			delete bar;
		else if (Projector* area = dynamic_cast<Projector*>(item))
			delete area;
	}

	for (QDomElement elem = data.firstChildElement("projector"); !elem.isNull(); elem = elem.nextSiblingElement("projector"))
	{
		Projector* proj = new Projector(this);
		connect(proj, &Projector::removeData, this, &Central::removeData);
		connect(proj, &Projector::isMoveMode, this, &Central::isMoveMode);
		connect(proj, &Projector::valueToPosition, this, &Central::valueToPosition);
		connect(proj, &Projector::positionToValue, this, &Central::positionToValue);
		connect(proj, &Projector::attached, this, &Central::attached);
		connect(proj, &Projector::mouseTracking, this, &Central::mouseTracking);
		connect(proj, &Projector::hideValue, this, &Central::hideValue);
		connect(proj, &Projector::dataChanged, this, &Central::dataChanged);
		connect(proj, &Projector::setCurrentItemData, this, &Central::setCurrentItemData);
		connect(proj, &Projector::effectMode, this, &Central::effectMode);
		connect(proj, &Projector::getBrightnessGrey, this, &Central::getBrightnessGrey);
		connect(proj, &Projector::getPixdensityHue, this, &Central::getPixdensityHue);
		connect(proj, &Projector::showEffectValue, this, &Central::showValue);
		proj->setData(elem);
		
		proj->updatePosition();
	}
}

void Central::setRatio(unsigned int x, unsigned int y)
{
	m_ratio = QSize(x, y);
}

void Central::updatePosition()
{
	qreal x1 = valueToPosition(Qt::Vertical, 0);
	qreal y1 = valueToPosition(Qt::Horizontal, 0);
	qreal x2 = valueToPosition(Qt::Vertical, m_ratio.width());
	qreal y2 = valueToPosition(Qt::Horizontal, m_ratio.height());
	m_centralMapItem->setRect(x1, y1, x2 - x1, y2 - y1);

	for (QGraphicsItem* item : childItems())
	{
		if (Projector* area = dynamic_cast<Projector*>(item))
		{
			area->updatePosition();
		}
	}
	m_grid->setGeometry(QRectF(0, 0, rect().width(), rect().height()));
}

void Central::resizeEvent(QGraphicsSceneResizeEvent *event)
{
	Base::resizeEvent(event);
	updatePosition();
}

void Central::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
	if (m_projectorRatio == QSize(1, 0))
	{
		setCursor(Qt::ArrowCursor);
	}
	else if (m_projectorRatio.isValid())
	{
		setCursor(Qt::CrossCursor);
	}

	else if (m_projectorRatio.isEmpty())
	{
		setCursor(Qt::PointingHandCursor);
	}
	
	emit mouseTracking(QPointF(positionToValue(Qt::Vertical, event->pos().x() - 7), positionToValue(Qt::Horizontal, event->pos().y() - 7)));
	return Base::hoverMoveEvent(event);
}

Projector* Central::createProjector(const QPointF& pos)
{
	if (m_projectorRatio.isEmpty() || !m_projectorRatio.isValid())
	{
		return nullptr;
	}
	QDomElement proElement = createProjectorNode();
	m_data.appendChild(proElement);
	if (proElement.isNull())
	{
		return nullptr;
	}
	// get a index sequence
	QList<Projector*> selections;
	QList<QGraphicsItem*> items = childItems();
	for (QGraphicsItem* item : items)
	{
		if (Projector* p = dynamic_cast<Projector*>(item))
		{
			selections.push_back(p);
		}
	}
	QVector<int> indexes;
	for (Projector* p : selections)
	{
		indexes.push_back(p->index().toInt());
	}
	indexes.removeAll(0);
	std::sort(indexes.begin(), indexes.end());
	int index = 1;
	for (int i : indexes)
	{
		if (index != i)
		{
			break;;
		}
		++index;
	}
	proElement.firstChildElement("index").firstChild().setNodeValue(QString("%1").arg(index));

	Projector* proj = new Projector(this);
	proj->setData(proElement);

	QPointF value(positionToValue(Qt::Vertical, pos.x()), positionToValue(Qt::Horizontal, pos.y()));
	proElement.firstChildElement("position").firstChild().setNodeValue(QString("%1,%2").arg(value.x()).arg(value.y()));

	connect(proj, &Projector::removeData, this, &Central::removeData);
	connect(proj, &Projector::isMoveMode, this, &Central::isMoveMode);
	connect(proj, &Projector::valueToPosition, this, &Central::valueToPosition);
	connect(proj, &Projector::positionToValue, this, &Central::positionToValue);
	connect(proj, &Projector::attached, this, &Central::attached);
	connect(proj, &Projector::mouseTracking, this, &Central::mouseTracking);
	connect(proj, &Projector::hideValue, this, &Central::hideValue);
	connect(proj, &Projector::dataChanged, this, &Central::dataChanged);
	connect(proj, &Projector::setCurrentItemData, this, &Central::setCurrentItemData);
	connect(proj, &Projector::effectMode, this, &Central::effectMode);
	connect(proj, &Projector::getBrightnessGrey, this, &Central::getBrightnessGrey);
	connect(proj, &Projector::getPixdensityHue, this, &Central::getPixdensityHue);
	connect(proj, &Projector::showEffectValue, this, &Central::showValue);

	return proj;
}

QDomElement Central::createProjectorNode()
{
	const QStringList strElems = {"index", "position", "fenbianlv","liangdu","rotate","projectionwidth", "projectionheight","projectorratio"/*, "prodis"*/ };
	QDomElement proElement = domDocument().createElement("projector");
	for (const QString& elem : strElems)
	{
		QDomElement nodeElement = domDocument().createElement(elem);
		proElement.appendChild(nodeElement);
		nodeElement.appendChild(domDocument().createTextNode(""));
	}

	proElement.firstChildElement("projectorratio").firstChild().setNodeValue("1.5");
	proElement.firstChildElement("liangdu").firstChild().setNodeValue("5000");
	proElement.firstChildElement("rotate").firstChild().setNodeValue(QString("%1").arg(m_projectorRotate));
	proElement.firstChildElement("fenbianlv").firstChild().setNodeValue(QString("%1x%2").arg(m_projectorRatio.width()).arg(m_projectorRatio.height()));
	double onePixWidth = 4000 / 1920.0;
	proElement.firstChildElement("projectionwidth").firstChild().setNodeValue(QString("%1").arg(int(m_projectorRatio.width()*onePixWidth + 0.5)));
	proElement.firstChildElement("projectionheight").firstChild().setNodeValue(QString("%1").arg(int(m_projectorRatio.height()*onePixWidth + 0.5)));

	return proElement;
}

QPixmap Central::createBrightnessMap()
{
	QPixmap map(rect().width(), rect().height());
	map.fill(Qt::black);
	QPainter painter(&map);

	QList<Projector*> projectors;
	QList<QGraphicsItem*> childItems = this->childItems();
	for (QGraphicsItem* item : childItems)
	{
		if (Projector* pro = dynamic_cast<Projector*>(item))
			projectors.push_back(pro);
	}
	if (!projectors.isEmpty())
	{
		std::sort(projectors.begin(), projectors.end(), [](Projector* l, Projector* r) {return l->brightness() < r->brightness();});
		qreal minBrightness = projectors.first()->brightness();
		qreal maxBrightness = projectors.last()->brightness();
		qreal demarcation = 128;
		qreal k1 = 128 / (200 - minBrightness);
		qreal b1 = 128 - 200 * k1;

		qreal k2 = (255 - 128) / (maxBrightness - 200);
		qreal b2 = 255 - maxBrightness * k2;

		for (Projector* pro : projectors)
		{
			pro->setZValue(pro->brightness());
// 			QPolygonF points({ pro->mapToParent(pro->rect().topLeft()), pro->mapToParent(pro->rect().topRight()) ,
// 				pro->mapToParent(pro->rect().bottomRight()), pro->mapToParent(pro->rect().bottomLeft()) });

			qreal brightness = pro->brightness();

			qreal gray;
			if (qAbs(brightness - 200) < 0.00001)
			{
				gray = 128;
			}
			else if (brightness < 200)
			{
				gray = k1*brightness + b1;
			}
			else
			{
				gray = k2*brightness + b2;
			}
			pro->setBrush(QBrush(QColor(gray, gray, gray)));
//			QPainterPath path;
//			path.addPolygon(points);
//			painter.fillPath(path, QBrush(QColor(gray, gray, gray)));
		}
	}

	return map;
}

QPixmap Central::createPixDensityMap()
{
	QPixmap map(rect().width(), rect().height());
	map.fill(Qt::black);
	QPainter painter(&map);

	QList<Projector*> projectors;
	QList<QGraphicsItem*> childItems = this->childItems();
	for (QGraphicsItem* item : childItems)
	{
		if (Projector* pro = dynamic_cast<Projector*>(item))
			projectors.push_back(pro);
	}
	if (!projectors.isEmpty())
	{
		std::sort(projectors.begin(), projectors.end(), [](Projector* l, Projector* r) {return l->brightness() < r->brightness();});
		qreal minBrightness = projectors.first()->brightness();
		qreal maxBrightness = projectors.first()->brightness();
		qreal demarcation = 128;
		qreal k1 = 128 / (200 - minBrightness);
		qreal b1 = 128 - 200 * k1;

		qreal k2 = (255 - 128) / (maxBrightness - 200);
		qreal b2 = 255 - maxBrightness * k2;

		for (Projector* pro : projectors)
		{
			QPolygonF points({ pro->mapToParent(pro->rect().topLeft()), pro->mapToParent(pro->rect().topRight()) ,
				pro->mapToParent(pro->rect().bottomRight()), pro->mapToParent(pro->rect().bottomLeft()) });

			qreal brightness = pro->brightness();

			qreal gray;
			if (qAbs(brightness - 200) < 0.00001)
			{
				gray = 128;
			}
			else if (brightness < 200)
			{
				gray = k1*brightness + b1;
			}
			else
			{
				gray = k2*brightness + b2;
			}
			QPainterPath path;
			path.addPolygon(points);
			painter.fillPath(path, QBrush(QColor(gray, gray, gray)));
		}
	}

	return map.copy(m_centralMapItem->rect().toRect());
}

//计算两平行直线间的距离
qreal distance(const QLineF& l, const QLineF& r)
{
	if (qAbs(l.angleTo(r)) < 0.1 || qAbs(l.angleTo(r) - 360) < 0.1 || qAbs(l.angleTo(r) - 180) < 0.1)
	{
		if (qAbs(l.angle() - 90) < 0.1 || qAbs(l.angle() - 270) < 0.1)
		{
			return qAbs(r.x1() - l.x1());
		}
		qreal k = (r.p2().y() - r.p1().y()) / (r.p2().x() - r.p1().x());//k=(y2-y1)/(x2-x1)
		qreal b1 = l.y1() - k*l.x1();
		qreal b2 = r.y1() - k*r.x1();
		return qAbs(b2 - b1) / qSqrt(1 + k*k);
	}
	return INT_MAX;
}

//make line x1 < x2, y1 < y2
QLineF normalLine(const QLineF& line)
{
	QPointF p1 = line.p1();
	QPointF p2 = line.p2();
	if (qAbs(p1.x() - p2.x()) < 0.01)
	{
		return p1.y() < p2.y() ? QLineF(p1, p2) : QLineF(p2, p1);
	}
	else
	{
		return p1.x() < p2.x() ? QLineF(p1, p2) : QLineF(p2, p1);
	}
}

//计算点到直线间的距离
qreal distance(const QPointF& l, const QLineF& to)
{
	qreal toangle = to.angle();
	if (qAbs(toangle) < 0.1 || qAbs(toangle - 180) < 0.1 || qAbs(toangle - 360) < 0.1)
	{
		if ((l.x() < (to.p1().x() - 7)) || (l.x() > (to.p2().x() + 7)))
		{
			return INT_MAX;
		}
		return qAbs(l.y() - to.p1().y());
	}
	else if (qAbs(toangle - 90) < 0.1 || qAbs(toangle - 270) < 0.1)
	{
		if ((l.y() < (to.p1().y() - 7)) || (l.y() > (to.p2().y() + 7)))
		{
			return INT_MAX;
		}
		return qAbs(l.x() - to.p1().x());
	}
	else
	{
		if ((l.x() < (to.p1().x() - 7)) || (l.x() > (to.p2().x() + 7)))
		{
			return INT_MAX;
		}
		qreal k = (to.p2().y() - to.p1().y()) / (to.p2().x() - to.p1().x());//k=(y2-y1)/(x2-x1)
		qreal b2 = -to.y1() + k*to.x1();
		return qAbs(l.y() - k*l.x() + b2) / qSqrt(1 + k*k);
	}
}

//from直线投影到to上，得到投影直线
QLineF projectorTo(const QLineF& from, const QLineF& to)
{
	if (qAbs(from.angleTo(to)) < 0.1 || qAbs(from.angleTo(to) - 180) < 0.1 || qAbs(from.angleTo(to) - 360) < 0.1)
	{
		if (qAbs(from.angle() - 90) < 0.1 || qAbs(from.angle() - 270) < 0.1)
		{
			return QLineF(QPointF(to.x1(), from.y1()), QPointF(to.x1(), from.y2()));
		}
		else if (qAbs(from.angle()) < 0.1 || qAbs(from.angle() - 180) < 0.1)
		{
			return QLineF(QPointF(from.x1(), to.y1()), QPointF(from.x2(), to.y1()));
		}
		else
		{
			qreal k = (from.p2().y() - from.p1().y()) / (from.p2().x() - from.p1().x());
			qreal x1 = (from.y1() - to.y1() + k*to.x1() + 1 / k*from.x1()) / (k + 1 / k);
			qreal y1 = k*(x1 - to.x1()) + to.y1();

			qreal x2 = (from.y1() - to.y2() + k*to.x2() + 1 / k*from.x1()) / (k + 1 / k);
			qreal y2 = k*(x1 - to.x2()) + to.y2();

			return QLineF(QPointF(x1, y1), QPointF(x2, y2));
		}
	}
	return from;
}
//点投影到直线上
QPointF projectorTo(const QPointF& from, const QLineF& to)
{
	qreal toangle = to.angle();
	if (qAbs(toangle) < 0.1 || qAbs(toangle - 180) < 0.1 || qAbs(toangle - 360) < 0.1)
	{
		return QPointF(from.x(), to.p1().y());
	}
	else if (qAbs(toangle - 90) < 0.1 || qAbs(toangle - 270) < 0.1)
	{
		return QPointF(to.p1().x(), from.y());
	}
	else
	{
		qreal k = (to.p2().y() - to.p1().y()) / (to.p2().x() - to.p1().x());
		qreal x1 = (from.y() - to.y1() + k*to.x1() + 1 / k*from.x()) / (k + 1 / k);
		qreal y1 = k*(x1 - to.x1()) + to.y1();

		return{ x1,y1 };
	}
}

QPointF minPoint(const QLineF& line)
{
	QPointF p1 = line.p1();
	QPointF p2 = line.p2();
	if (qAbs(p1.x() - p2.x()) < 0.01)
	{
		return p1.x() < p2.x() ? p1 : p2;
	}
	else
	{
		return p1.y() < p2.y() ? p1 : p2;
	}
}

QPointF Central::attached(const QPointF& newPos)
{
	if (!m_bSnap)
	{
		return newPos;
	}
	QPointF offset;

	if (Projector* sender = qobject_cast<Projector*>(this->sender()))
	{
		QPointF posoffset = newPos - sender->pos();

		QPointF origPoints[4] = { sender->mapToParent(sender->rect().topLeft()) + posoffset , sender->mapToParent(sender->rect().topRight()) + posoffset , sender->mapToParent(sender->rect().bottomLeft()) + posoffset , sender->mapToParent(sender->rect().bottomRight()) + posoffset };
		QLineF lineFromHor[2] = { QLineF(origPoints[0], origPoints[1]), QLineF(origPoints[2], origPoints[3]) };
		QLineF lineFromVer[2] = { QLineF(origPoints[0], origPoints[2]), QLineF(origPoints[1], origPoints[3]) };

		bool horSetted = false, verSetted = false;

		QList<QGraphicsRectItem*> attachItems;
		attachItems.push_back(m_centralMapItem);

		QList<QGraphicsItem*> childItems = this->childItems();
		for (QGraphicsItem* item : childItems)
		{
			if (Projector* pro = dynamic_cast<Projector*>(item))
				if (pro != sender)
					attachItems.push_back(pro);
		}

		for (QGraphicsRectItem* pro : attachItems)
		{
			if (horSetted && verSetted)
			{
				break;
			}

			QPointF points[4] = { pro->mapToParent(pro->rect().topLeft()), pro->mapToParent(pro->rect().topRight()) ,pro->mapToParent(pro->rect().bottomLeft()), pro->mapToParent(pro->rect().bottomRight()) };
			QLineF lineToHor[2];
			QLineF lineToVer[2];
			int rotationDif = qAbs(pro->rotation() - sender->rotation()) + 0.5;
			if (rotationDif % 180 == 0)
			{
				lineToHor[0] = QLineF(points[0], points[1]);
				lineToHor[1] = QLineF(points[2], points[3]);

				lineToVer[0] = QLineF(points[0], points[2]);
				lineToVer[1] = QLineF(points[1], points[3]);
			}
			else if (rotationDif % 90 == 0)
			{
				lineToHor[0] = QLineF(points[0], points[2]);
				lineToHor[1] = QLineF(points[1], points[3]);

				lineToVer[0] = QLineF(points[0], points[1]);
				lineToVer[1] = QLineF(points[2], points[3]);
			}
			else
			{
				continue;
			}

			if (!horSetted)
			{
				for (QLineF lineF : lineFromHor)
				{
					lineF = normalLine(lineF);
					bool finished = false;
					for (QLineF lineT : lineToHor)
					{
						lineT = normalLine(lineT);
						if (distance(lineF, lineT) <= 7)
						{
							QLineF proLine = projectorTo(lineF, lineT);
							QPointF pointF = minPoint(lineF);
							QPointF pointP = minPoint(proLine);
							offset += (pointP - pointF);
							finished = true;
							horSetted = true;
							break;
						}
					}
					if (finished)
					{
						break;
					}
				}
			}

			if (!verSetted)
			{
				for (QLineF lineF : lineFromVer)
				{
					lineF = normalLine(lineF);
					bool finished = false;
					for (QLineF lineT : lineToVer)
					{
						lineT = normalLine(lineT);
						if (distance(lineF, lineT) <= 7)
						{
							QLineF proLine = projectorTo(lineF, lineT);
							QPointF pointF = minPoint(lineF);
							QPointF pointP = minPoint(proLine);
							offset += (pointP - pointF);
							finished = true;
							verSetted = true;
							break;
						}
					}
					if (finished)
					{
						break;
					}
				}
			}
		}
	}
	return newPos + offset;
}

//求向量l和向量r夹角向量
const float ZERO = 0.00001;
QPointF getVector(const QPointF& l, const QPointF& r)
{
	if (qAbs(l.x()) > ZERO && qAbs(l.y()) > ZERO &&qAbs(r.x()) > ZERO &&qAbs(r.y()) > ZERO)
	{
		qreal k1 = -l.x() / l.y();
		qreal k2 = -r.x() / r.y();
		if (qAbs(k1 - k2) < ZERO)
		{
			return l;
		}

		qreal x = (l.y() - r.y() - k1*l.x() + k2*r.x()) / (k2 - k1);
		qreal y = k1*(x - l.x()) + l.y();
		return{ x,y };
	}
	//zero vector
	else if (l.manhattanLength() < ZERO)
	{
		return r;
	}
	else if (r.manhattanLength() < ZERO)
	{
		return l;
	}
	else if ((qAbs(l.x()) < ZERO && qAbs(r.x()) < ZERO) ||(qAbs(l.y()) < ZERO && qAbs(r.y()) < ZERO))
	{
		return l;
	}
	//坐标轴向量
	else if (qAbs(l.x()) < ZERO && qAbs(r.y()) < ZERO)
	{
		return{r.x(), l.y()};
	}
	else if (qAbs(l.y()) < ZERO && qAbs(r.x()) < ZERO)
	{
		return{l.x(), r.y()};
	}
	else if (qAbs(l.x()) < ZERO)
	{
		qreal k = -r.x() / r.y();
		if (qAbs(k) < ZERO)
		{
			return r;
		}
		return{(l.y() - r.y())/k + r.x() ,l.y() };
	}
	else if (qAbs(r.x()) < ZERO)
	{
		qreal k = -l.x() / l.y();
		if (qAbs(k) < ZERO)
		{
			return l;
		}
		return{ (r.y() - l.y()) / k + l.x() ,r.y() };
	}
	else if (qAbs(l.y()) < ZERO)
	{
		qreal k = -r.x() / r.y();
		if (qAbs(k) < ZERO)
		{
			return r;
		}
		return{ l.x(), k*(l.x() - r.x()) + r.y() };
	}
	else if (qAbs(r.y()) < ZERO)
	{
		qreal k = -l.x() / l.y();
		if (qAbs(k) < ZERO)
		{
			return l;
		}
		return{ r.x(), k*(r.x() - l.x()) + l.y() };
	}
	else
	{
		return l;
	}
}

QPointF Central::attachedPos(const QPointF& newPos)
{
	if (!m_bSnap)
	{
		return newPos;
	}
	QPointF offsetHor, offsetVer;

	QList<QGraphicsRectItem*> attachItems;
	attachItems.push_back(m_centralMapItem);
	QList<QGraphicsItem*> childItems = this->childItems();
	for (QGraphicsItem* item : childItems)
	{
		if (Projector* pro = dynamic_cast<Projector*>(item))
			attachItems.push_back(pro);
	}

	bool horSetted = false, verSetted = false;
	for (QGraphicsRectItem* pro : attachItems)
	{
		if (horSetted && verSetted)
		{
			break;
		}

		QPointF points[4] = { pro->mapToParent(pro->rect().topLeft()), pro->mapToParent(pro->rect().topRight()) ,pro->mapToParent(pro->rect().bottomLeft()), pro->mapToParent(pro->rect().bottomRight()) };
		QLineF lineToHor[2] = {QLineF(points[0], points[1]), QLineF(points[2], points[3])};
		QLineF lineToVer[2] = {QLineF(points[0], points[2]), QLineF(points[1], points[3])};

		if (!horSetted)
		{
			for (QLineF lineT : lineToHor)
			{
				lineT = normalLine(lineT);
				if (distance(newPos, lineT) <= 7)
				{
					QPointF pointP = projectorTo(newPos, lineT);
					offsetHor += (pointP - newPos);
					horSetted = true;
					break;
				}
			}
		}

		if (!verSetted)
		{
			for (QLineF lineT : lineToVer)
			{
				lineT = normalLine(lineT);
				if (distance(newPos, lineT) <= 7)
				{
					QPointF pointP = projectorTo(newPos, lineT);
					offsetVer += (pointP - newPos);
					verSetted = true;
					break;
				}
			}
		}
	}

	return newPos + getVector(offsetHor, offsetVer);
}

void Central::showTapeLineValue(Qt::Orientation o, qreal value)
{
	QPoint gloPos = QCursor::pos();
	QGraphicsView* view = scene()->views().first();
	QPoint viewPos = view->viewport()->mapFromGlobal(gloPos);
	QPointF scenePos = view->mapToScene(viewPos);
	QPointF pos = mapFromScene(scenePos) + QPointF(10, -30);
	QString text = QString("Length:%1mm").arg(int(value + 0.5));
	showValue(pos, text);
}

void Central::showValue(const QPointF& pos, const QString& value)
{
	m_valueShow->setPos(pos);
	m_valueShow->setPlainText(value);
	m_valueShow->update();
	m_valueShow->show();
}

void Central::hideValue()
{
	m_valueShow->hide();
}

bool Central::isIndexValid(const QString& index)
{
// 	for (QGraphicsItem* item : childItems())
// 	{
// 		if (SelectionArea* select = dynamic_cast<SelectionArea*>(item))
// 		{
// 			if (select->index() == index)
// 			{
// 				return false;
// 			}	
// 		}
// 	}
	return true;
}

// QDomElement Central::setCurrentItemData() const
// {
// 	if (QGraphicsItem* focusItem = this->focusItem())
// 	{
// 		if (Projector* sa = qgraphicsitem_cast<Projector*>(focusItem))
// 		{
// 			return sa->data();
// 		}
// 	}
// 	return QDomElement();
// }

void Central::currentItemDataEdited() const
{
	if (QGraphicsItem* focusItem = this->focusItem())
	{
		if (Projector* sa = qgraphicsitem_cast<Projector*>(focusItem))
		{
			return sa->updatePosition();
		}
	}
}

void Central::allItemDataEdited()const
{
	QList<QGraphicsItem*> items = childItems();
	for (QGraphicsItem* item : items)
	{
		if (Projector* sa = qgraphicsitem_cast<Projector*>(item))
		{
			sa->updatePosition();
		}
	}
}

bool Central::isMoveMode()
{
	return m_projectorRatio.isEmpty() && !m_projectorRatio.isValid();
}

void Central::setSnap(bool b)
{
	m_bSnap = b;
}

void Central::showEffect(int type)
{
	m_effectMode = type;
	if (0 == type)
	{
		m_centralMapItem->setPixmap(QPixmap(":/background.jpg"));
	}
	if (1 == type)
	{
		QPixmap map(m_centralMapItem->rect().width(), m_centralMapItem->rect().height());
		map.fill(Qt::black);
		m_centralMapItem->setPixmap(map);
	}
	else if (2 == type)
	{
		QPixmap map(m_centralMapItem->rect().width(), m_centralMapItem->rect().height());
		map.fill(QColor(0,110,160));
		m_centralMapItem->setPixmap(map);
	}

	QList<QGraphicsItem*> childItems = this->childItems();
	for (QGraphicsItem* item : childItems)
	{
		if (Projector* pro = dynamic_cast<Projector*>(item))
			pro->updatePosition();
	}
	
	update();
}

int Central::effectMode()
{
	return m_effectMode;
}

int Central::getBrightnessGrey(int brightness)
{
	QList<Projector*> projectors;
	QList<QGraphicsItem*> childItems = this->childItems();
	for (QGraphicsItem* item : childItems)
	{
		if (Projector* pro = dynamic_cast<Projector*>(item))
			projectors.push_back(pro);
	}
	if (!projectors.isEmpty())
	{
		std::sort(projectors.begin(), projectors.end(), [](Projector* l, Projector* r) {return l->brightness() < r->brightness();});
		qreal minBrightness = projectors.first()->brightness();
		qreal maxBrightness = projectors.last()->brightness();
		qreal demarcation = 128;
		qreal k1 = (128 - 32) / (200 - minBrightness);
		qreal b1 = 128 - 200 * k1;

		qreal k2 = (255 - 128) / (maxBrightness - 200);
		qreal b2 = 255 - maxBrightness * k2;

		qreal gray;
		if (qAbs(brightness - 200) < 0.00001)
		{
			gray = 128;
		}
		else if (brightness < 200)
		{
			gray = k1*brightness + b1;
		}
		else
		{
			gray = k2*brightness + b2;
		}
		
		return gray;
	}
	return 0;
}

int Central::getPixdensityHue(qreal pixdensity)
{
	QList<Projector*> projectors;
	QList<QGraphicsItem*> childItems = this->childItems();
	for (QGraphicsItem* item : childItems)
	{
		if (Projector* pro = dynamic_cast<Projector*>(item))
			projectors.push_back(pro);
	}
	if (!projectors.isEmpty())
	{
		std::sort(projectors.begin(), projectors.end(), [](Projector* l, Projector* r) {return l->pixelDensity() < r->pixelDensity();});
		qreal minBrightness = projectors.first()->pixelDensity();
		qreal maxBrightness = projectors.last()->pixelDensity();
		
		if (qAbs(minBrightness - maxBrightness) < 0.1)
		{
			return 255;
		}

		qreal k = (255 - 32) / (maxBrightness - minBrightness);
		qreal b = 32 - minBrightness * k;

		return k*pixdensity + b;
	}
	return 0;
}

void Central::removeData(const QDomElement& data)
{
	m_data.removeChild(data);
}

void Central::createBar(Qt::Orientation o, const QPointF& scenePos)
{
	return;
	Bar* bar = new Bar(o, this);
	connect(bar, &Bar::removeData, this, &Central::removeData);
	QDomElement barElement = domDocument().createElement("bar");
	m_data.appendChild(barElement);
	barElement.setAttribute("o", o);
	bar->setData(barElement);
	connect(bar, &Bar::valueToPosition, this, &Central::valueToPosition);
	connect(bar, &Bar::positionToValue, this, &Central::positionToValue);
	connect(bar, &Bar::attached, this, &Central::attached);
	connect(bar, &Bar::mouseTracking, this, &Central::mouseTracking);
	connect(bar, &Bar::showValue, this, &Central::showTapeLineValue);
	connect(bar, &Bar::hideValue, this, &Central::hideValue);

	bar->resize(bar->orient() == Qt::Horizontal ? QSizeF(rect().width(), LINEWIDTH) : QSizeF(LINEWIDTH, rect().height()));

	QPointF itemPos = mapFromScene(scenePos);

	bar->setPos(bar->orient() == Qt::Horizontal ? QPointF(m_centralMapItem->pos().x(), -LINEWIDTH/2 + itemPos.y()) : QPointF(-LINEWIDTH/2 + itemPos.x(), m_centralMapItem->pos().y()));
	
	bar->grabMouse();
}

void Central::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * /* = Q_NULLPTR */)
{
	painter->fillRect(rect(), QColor(48, 48, 48));
}

void Central::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QPointF pressedPos = event->pos();
//	pressedPos = QPointF(attached(Qt::Vertical, pressedPos.x()), attached(Qt::Horizontal, pressedPos.y()));

	if (Projector* pro = createProjector(pressedPos))
	{
		pro->updatePosition();
	}

	if (m_projectorRatio == QSize(1,0))
	{
		QPointF pos = attachedPos(event->pos());
		m_line->setLine(QLineF(pos, pos));
		m_line->show();
	}
	Base::mousePressEvent(event);
}

void Central::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	hideValue();
	m_line->hide();
	return Base::mouseReleaseEvent(event);
}

void Central::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (m_projectorRatio == QSize(1, 0))
	{
		QPointF pos = attachedPos(event->pos());
		m_line->setLine(QLineF(m_line->line().p1(), pos));
		showTapeLineValue(Qt::Horizontal, positionToValue(Qt::Horizontal, valueToPosition(Qt::Horizontal,0) + m_line->line().length()));
	}
	emit mouseTracking(QPointF(positionToValue(Qt::Vertical, event->pos().x()), positionToValue(Qt::Horizontal, event->pos().y())));
	return Base::mouseMoveEvent(event);
}
