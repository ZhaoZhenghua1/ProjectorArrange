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
#include "Projector.h"

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

class MapItem : public QGraphicsWidget
{
public:
	using QGraphicsWidget::QGraphicsWidget;
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

Central::Central()
{
	setAcceptedMouseButtons(Qt::LeftButton);
	setAcceptHoverEvents(true);

	m_valueShow = new TextItem(this);
	m_valueShow->setZValue(10);
	m_valueShow->setDefaultTextColor(Qt::white);
	m_valueShow->hide();

	m_centralMapItem = new MapItem(this);
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
	for (QGraphicsItem* item : childItems()){
		//delete item;
	}

	for (QDomElement elem = data.firstChildElement("bar"); !elem.isNull(); elem = elem.nextSiblingElement("bar"))
	{
		Bar* bar = new Bar(Qt::Horizontal, this);
		bar->setData(elem);
		connect(bar, &Bar::removeData, this, &Central::removeData);
		connect(bar, &Bar::valueToPosition, this, &Central::valueToPosition);
		connect(bar, &Bar::positionToValue, this, &Central::positionToValue);
		connect(bar, &Bar::attached, this, &Central::attached);
		connect(bar, &Bar::mouseTracking, this, &Central::mouseTracking);
		connect(bar, &Bar::showValue, this, &Central::showBarValue);
		connect(bar, &Bar::hideValue, this, &Central::hideValue);
		bar->updatePosition();
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
	m_centralMapItem->setGeometry(x1, y1, x2 - x1, y2 - y1);
}

void Central::resizeEvent(QGraphicsSceneResizeEvent *event)
{
	Base::resizeEvent(event);
	updatePosition();

	for (QGraphicsItem* item : childItems())
	{
		if (Bar* bar = dynamic_cast<Bar*>(item))
		{
			bar->updatePosition();
		}
		else if (Projector* area = dynamic_cast<Projector*>(item))
		{
			area->updatePosition();
		}
	}
}

void Central::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
	emit mouseTracking(QPointF(positionToValue(Qt::Vertical, event->pos().x() - 7), positionToValue(Qt::Horizontal, event->pos().y() - 7)));
	return Base::hoverMoveEvent(event);
}

Projector* Central::createProjector(const QPointF& pos)
{
	if (m_projectorRatio.isEmpty())
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
		if (Projector* p = qgraphicsitem_cast<Projector*>(item))
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

	return proj;
}

QDomElement Central::createProjectorNode()
{
	const QStringList strElems = {"index", "position", "fenbianlv","liangdu","rotate","projectionwidth", "projectionheight","projectorratio", "prodis" };
	QDomElement proElement = domDocument().createElement("projector");
	for (const QString& elem : strElems)
	{
		QDomElement nodeElement = domDocument().createElement(elem);
		proElement.appendChild(nodeElement);
		nodeElement.appendChild(domDocument().createTextNode(""));
	}
	proElement.firstChildElement("rotate").firstChild().setNodeValue(QString("%1").arg(m_projectorRotate));
	proElement.firstChildElement("fenbianlv").firstChild().setNodeValue(QString("%1x%2").arg(m_projectorRatio.width()).arg(m_projectorRatio.height()));
	double onePixWidth = 4000 / 1920.0;
	proElement.firstChildElement("projectionwidth").firstChild().setNodeValue(QString("%1").arg(int(m_projectorRatio.width()*onePixWidth + 0.5)));
	proElement.firstChildElement("projectionheight").firstChild().setNodeValue(QString("%1").arg(int(m_projectorRatio.height()*onePixWidth + 0.5)));

	return proElement;
}

QLineF Central::attached(Qt::Orientation o, const QLineF& line)
{
	//attach to border
// 	if ((o == Qt::Horizontal))
// 	{
// 		qreal topValue = m_centralMapItem->geometry().top();
// 		qreal bottomValue = m_centralMapItem->geometry().bottom();
// 		if (qAbs(topValue - pos) <= ATTACH_DIS)
// 		{
// 			return topValue;
// 		}
// 		else if (qAbs(bottomValue - pos) <= ATTACH_DIS)
// 		{
// 			return bottomValue;
// 		}
// 	}
// 	else
// 	{
// 		qreal leftValue = m_centralMapItem->geometry().left();
// 		qreal rightValue = m_centralMapItem->geometry().right();
// 		if (qAbs(leftValue - pos) <= ATTACH_DIS)
// 		{
// 			return leftValue;
// 		}
// 		else if (qAbs(rightValue - pos) <= ATTACH_DIS)
// 		{
// 			return rightValue;
// 		}
// 	}

//	qreal edge = limitPos(Qt::LeftEdge);
	//attach to other items
//	for (QGraphicsItem* item : childItems())
	{
// 		if (Bar* bar = dynamic_cast<Bar*>(item))
// 		{
// 			//bar not attached to bars
// 			if (bar != sender() && !qobject_cast<Bar*>(sender()))
// 			{
// 				qreal val = valueToPosition(bar->orient(), bar->value()) + edge;
// 				if (qAbs(val - pos) <= ATTACH_DIS)
// 				{
// 					return val;
// 				}
// 			}
// 		}
// 		else if (SelectionArea* select = dynamic_cast<SelectionArea*>(item))
// 		{
// 			if (select != sender())
// 			{
// 				if ((o == Qt::Horizontal))
// 				{
// 					qreal topValue = valueToPosition(o, select->value(Qt::TopEdge)) + edge;
// 					qreal bottomValue = valueToPosition(o, select->value(Qt::BottomEdge)) + edge;
// 					if (qAbs(topValue - pos) <= ATTACH_DIS)
// 					{
// 						return topValue;
// 					}
// 					else if (qAbs(bottomValue - pos) <= ATTACH_DIS)
// 					{
// 						return bottomValue;
// 					}
// 				}
// 				else
// 				{
// 					qreal leftValue = valueToPosition(o, select->value(Qt::LeftEdge)) + edge;
// 					qreal rightValue = valueToPosition(o, select->value(Qt::RightEdge)) + edge;
// 					if (qAbs(leftValue - pos) <= ATTACH_DIS)
// 					{
// 						return leftValue;
// 					}
// 					else if (qAbs(rightValue - pos) <= ATTACH_DIS)
// 					{
// 						return rightValue;
// 					}
// 				}
// 			}
// 		}
 	}
	return line;
}

void Central::showBarValue(Qt::Orientation o, qreal value)
{
	QPoint gloPos = QCursor::pos();
	QGraphicsView* view = scene()->views().first();
	QPoint viewPos = view->viewport()->mapFromGlobal(gloPos);
	QPointF scenePos = view->mapToScene(viewPos);
	QPointF pos = mapFromScene(scenePos) + QPointF(10, -30);
	m_valueShow->setPos(pos);
	QString text = QString("%1:%2").arg(o == Qt::Horizontal ? 'Y' : 'X').arg(emit ratioValue(o == Qt::Horizontal ? Qt::Vertical : Qt::Horizontal, value));
	m_valueShow->setPlainText(text);
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

QDomElement Central::currentItemData() const
{
	if (QGraphicsItem* focusItem = this->focusItem())
	{
		if (Projector* sa = qgraphicsitem_cast<Projector*>(focusItem))
		{
			return sa->data();
		}
	}
	return QDomElement();
}

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

bool Central::isMoveMode()
{
	return m_projectorRatio.isEmpty();
}

void Central::removeData(const QDomElement& data)
{
	m_data.removeChild(data);
}

void Central::createBar(Qt::Orientation o, const QPointF& scenePos)
{
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
	connect(bar, &Bar::showValue, this, &Central::showBarValue);
	connect(bar, &Bar::hideValue, this, &Central::hideValue);

	bar->resize(bar->orient() == Qt::Horizontal ? QSizeF(rect().width(), LINEWIDTH) : QSizeF(LINEWIDTH, rect().height()));

	QPointF itemPos = mapFromScene(scenePos);

	bar->setPos(bar->orient() == Qt::Horizontal ? QPointF(m_centralMapItem->pos().x(), -LINEWIDTH/2 + itemPos.y()) : QPointF(-LINEWIDTH/2 + itemPos.x(), m_centralMapItem->pos().y()));
	
	bar->grabMouse();
}

void Central::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * /* = Q_NULLPTR */)
{
	painter->fillRect(rect(), Qt::black);//QColor(35, 35, 35)
}

void Central::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QPointF pressedPos = event->pos();
//	pressedPos = QPointF(attached(Qt::Vertical, pressedPos.x()), attached(Qt::Horizontal, pressedPos.y()));

	if (Projector* pro = createProjector(pressedPos))
	{
		pro->updatePosition();
	}
	Base::mousePressEvent(event);
}

void Central::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	hideValue();
	return Base::mouseReleaseEvent(event);
}

void Central::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	emit mouseTracking(QPointF(positionToValue(Qt::Vertical, event->pos().x()), positionToValue(Qt::Horizontal, event->pos().y())));
	return Base::mouseMoveEvent(event);
}
