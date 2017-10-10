#include "GridCover.h"
#include <QPainter>

void GridCover::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{
	painter->fillRect(rect(), QColor(48, 0, 48, 125));
}
