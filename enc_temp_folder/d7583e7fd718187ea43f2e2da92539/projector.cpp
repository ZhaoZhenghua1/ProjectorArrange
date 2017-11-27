#include "projector.h"
#include <qmath.h>
#include <QGenericMatrix>
#include <QMatrix4x4> 
#include "MapWidget.h"
#include "GraphicsView.h"
#include "DragItem.h"
#include "SizeGripItem.h"

class RectResizer : public SizeGripItem::Resizer
{
public:
	virtual void operator()(QGraphicsItem* item, const QRectF& rect)
	{
		DragItem* rectItem =
			dynamic_cast<DragItem*>(item);

		if (rectItem)
		{
			rectItem->setRect(rect);
			rectItem->positionChanged();
		}
	}
};

//原点到srcPoint的直线，与面ABCD的焦点
QVector3D destPoint(const QVector3D& srcPoint, qreal A, qreal B, qreal C, qreal D)
{
	qreal x = (-D*srcPoint.x()) / (A*srcPoint.x() + B*srcPoint.y() + C*srcPoint.z());
	qreal y = (-D*srcPoint.y()) / (A*srcPoint.x() + B*srcPoint.y() + C*srcPoint.z());
	qreal z = (-D*srcPoint.z()) / (A*srcPoint.x() + B*srcPoint.y() + C*srcPoint.z());
	return QVector3D(x, y, z);
}

Projector::Projector(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	init();

	m_widget = new MapWidget;
	m_widget->setBrush(QBrush(QColor(0, 100, 100)));
	DragItem* dragItem = new DragItem(m_widget);
	connect(dragItem, &DragItem::positionChanged, this, &Projector::onDragItemChanged);

	m_dragItem = dragItem;
	m_dragItem->setBrush(QBrush(QColor(153, 217, 234, 150)));
	dragItem->setRect(QRectF(0, 0, 50, 50));
	dragItem->setFlag(QGraphicsItem::ItemIsMovable );
	dragItem->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
	new SizeGripItem(new RectResizer, dragItem);

	GraphicsView * view = new GraphicsView;
	view->show();
	view->setRootItem(m_widget);
}

void Projector::init()
{
	void (QSpinBox::* spvalueChangedSig)(const QString&) = &QSpinBox::valueChanged;

	connect(ui.topleftLength, spvalueChangedSig, this, &Projector::project);
	connect(ui.bottomrightLength, spvalueChangedSig, this, &Projector::project);
	connect(ui.bottomleftLength, spvalueChangedSig, this, &Projector::project);
	connect(ui.rotate, spvalueChangedSig, this, &Projector::project);
//	connect(ui.bottomrightLength , spvalueChangedSig, this, &Projector::project);
}              

Projector::~Projector()
{

}

void Projector::project()
{
	switch(ui.tabWidget->currentIndex())
	{
	case 0:
		projectPlane();
		break;
	case 1:
		projectCylinder();
		break;
	case 2:
		projectBall();
		break;
	}
}

void Projector::onDragItemChanged()
{
	qreal proWidth = m_proPoints[1].x() - m_proPoints[0].x();
	qreal proHeight = m_proPoints[2].y() - m_proPoints[0].y();
	qreal width = m_dragItem->rect().width() / m_widget->rect().width() * proWidth;
	qreal height = m_dragItem->rect().height() / m_widget->rect().height() * proHeight;
	qreal x = (m_dragItem->pos().x() + m_dragItem->rect().left()) / m_widget->rect().width()*proWidth + m_proPoints[0].x();
	qreal y = (m_dragItem->pos().y() + m_dragItem->rect().top()) / m_widget->rect().height()*proHeight + m_proPoints[0].y();
	qreal z = m_proPoints[0].z();
	qreal rotate = ui.rotate->value();
	std::array<QVector3D, 4> proPoints = { QVector3D(x,y,z),QVector3D(x+width,y,z), QVector3D(x,y+height,z), QVector3D(x+width, y+height,z)};
	//幕投影到斜面上的四角点
	std::array<QVector3D, 4> dstPoints = { destPoint(proPoints[0],_A,_B,_C,_D), destPoint(proPoints[1],_A,_B,_C,_D),
		destPoint(proPoints[2],_A,_B,_C,_D), destPoint(proPoints[3],_A,_B,_C,_D) };

	qreal xMin = INT_MAX, xMax = INT_MIN, yMin = INT_MAX, yMax = INT_MIN;
	std::for_each(dstPoints.cbegin(), dstPoints.cend(), [&xMin, &xMax, &yMin, &yMax](const QVector3D& po) {
		xMin > po.x() ? xMin = po.x() : 0; xMax < po.x() ? xMax = po.x() : 0;
		yMin > po.y() ? yMin = po.y() : 0; yMax < po.y() ? yMax = po.y() : 0;
	});

	if (qAbs(_C) < 0.000001)
	{
		statusBar()->showMessage("wrong C parameter");
		return;
	}
	if (qAbs(xMax - xMin) < 0.0001 || qAbs(yMax - yMin) < 0.0001)
	{
		statusBar()->showMessage("projector parameter error");
		return;
	}
	//生成4个点
	std::array<QVector3D, 4> points;
	int i = 0;
	qreal cosTheta = qCos(rotate*M_PI / 180);
	qreal sinTheta = qSin(rotate*M_PI / 180);
	float data4x4[] = { cosTheta, sinTheta, 0, 0,
		-sinTheta, cosTheta, 0,0,
		0, 0, 1,0,
		0,0,0,1
	};
	QMatrix4x4 m4x4(data4x4);

	for (qreal y = yMin; y <= yMax; y += yMax - yMin)
	{
		for (qreal x = xMin; x <= xMax; x += xMax - xMin)
		{
			//qreal tempy = y - (x - xMin)*qTan(rotate*M_PI / 360);
			//Z rotate
			qreal tempx = x - (xMax + xMin) / 2;
			qreal tempy = y - (yMax + yMin) / 2;
			qreal z = (_A*tempx + _B*tempy + _D) / (-_C);

			QVector4D v(tempx, tempy, z, 1);
			QVector4D result = m4x4*v;

			points[i++] = QVector3D(result.x() + (xMax + xMin) / 2, result.y() + (yMax + yMin) / 2, result.z());
		}
	}

	//转换为与XoY平行的幕的交点
	std::array<QPointF, 4> propoints;
	i = 0;
	for (const QVector3D& po : points)
	{
		qreal z = proPoints[0].z();
		propoints[i++] = QPointF(po.x() * z / po.z(), po.y()*z / po.z());
	}

	m_dragItem->setProRect(QRectF(QPointF(proPoints[0].x(), proPoints[0].y()), QPointF(proPoints[3].x(), proPoints[3].y())));
	m_dragItem->setPoints(propoints);
	m_widget->update();
}

std::array<QVector3D, 4> Projector::proPoints()
{
	qreal topleftLen = ui.protopleftLength->value();
	qreal toprightLen = ui.protoprightLength->value();
	qreal horWidth = ui.prohorWidth->value();
	qreal x = (toprightLen*toprightLen - topleftLen*topleftLen - horWidth*horWidth) / (2 * horWidth);
	
	qreal bottomleftLen = ui.probottomleftLength->value();
	qreal verWidth = ui.proverWidth->value();
	qreal y = (bottomleftLen*bottomleftLen - topleftLen*topleftLen - verWidth*verWidth) / (2 * verWidth);

	qreal z = qSqrt(topleftLen*topleftLen - x*x - y*y);

	return{ QVector3D(x,y,z), QVector3D(x + horWidth, y, z), 
		QVector3D(x, y + verWidth, z), QVector3D(x + horWidth,y + verWidth,z) };
}

void Projector::projectPlane()
{
	statusBar()->clearMessage();

	qreal topleftLen = ui.topleftLength->value();
	qreal bottomrightLen = ui.bottomrightLength->value();
	qreal bottomleftLen = ui.bottomleftLength->value();
	qreal rotate = ui.rotate->value();

	//投影平面四个点
	std::array<QVector3D, 4> proPoints = this->proPoints();
	m_proPoints = proPoints;

	//生成
	float data4x4[] = { proPoints[0].x(), proPoints[0].y(), proPoints[0].z(),1,
		proPoints[2].x(), proPoints[2].y(), proPoints[2].z(),1,
		proPoints[3].x(), proPoints[3].y(), proPoints[3].z(),1,
		0,0,0,1
	};
	QMatrix4x4 m4x4(data4x4);

	QVector4D v(-proPoints[0].length() / topleftLen, -proPoints[2].length() / bottomleftLen,
		-proPoints[3].length() / bottomrightLen, 0);

	//求逆矩阵
	bool invertable = false;
	QMatrix4x4 invertresult = m4x4.inverted(&invertable);

	if (!invertable)
	{
		statusBar()->showMessage("uninvertable");
		return;
	}

	//Ax=B, x=A^(-1)*B
	QVector4D result1x4 = invertresult*v;

	//求得平面方程
	qreal A = result1x4.x(), B = result1x4.y(), C = result1x4.z(), D = 1;
	_A = A, _B = B, _C = C, _D = D;

	//原点到平面的距离
	qreal d = qAbs(D) / qSqrt(A*A + B*B + C*C);
	//标准式获取方向余弦
	qreal cosalpha = -A*d/D, cosbeta = -B*d/D, cosgamma = -C*d/D;

	//幕投影到斜面上的四角点
	std::array<QVector3D, 4> dstPoints = { destPoint(proPoints[0],A,B,C,D), destPoint(proPoints[1],A,B,C,D), 
		destPoint(proPoints[2],A,B,C,D), destPoint(proPoints[3],A,B,C,D) };

	qreal xMin = INT_MAX, xMax = INT_MIN, yMin = INT_MAX, yMax = INT_MIN;
	std::for_each(dstPoints.cbegin(), dstPoints.cend(), [&xMin,&xMax,&yMin,&yMax](const QVector3D& po) {
		xMin > po.x() ? xMin = po.x() : 0; xMax < po.x() ? xMax = po.x() : 0;
		yMin > po.y() ? yMin = po.y() : 0; yMax < po.y() ? yMax = po.y() : 0;
	});

	if (qAbs(C) < 0.000001)
	{
		statusBar()->showMessage("wrong C parameter");
		return;
	}
	if (qAbs(xMax - xMin) < 0.0001 || qAbs(yMax - yMin) < 0.0001)
	{
		statusBar()->showMessage("projector parameter error");
		return;
	}
	//生成20个点
	QVector<QVector<QVector3D>> points;
	qreal cosTheta = qCos(rotate*M_PI / 180);
	qreal sinTheta = qSin(rotate*M_PI / 180);
	float rdata4x4[] = { cosTheta, sinTheta, 0, 0,
		-sinTheta, cosTheta, 0,0,
		0, 0, 1,0,
		0,0,0,1
	};
	QMatrix4x4 rm4x4(rdata4x4);
//	m_dragItem->setMatrix(QMatrix(cosTheta, -sinTheta, sinTheta, cosTheta,0,0));

	qreal space = (xMax - xMin) > (yMax - yMin) ? (yMax - yMin) / 20 : (xMax - xMin) / 20;
	for (qreal x = xMin - (xMin + xMax); x <= xMax+ (xMin + xMax); x+= space)
	{
		QVector<QVector3D> temp;
		for (qreal y = yMin - (xMin + xMax); y<= yMax + (xMin + xMax); y+= space)
		{
			qreal tempx = x - (xMin + xMax) / 2;
			qreal tempy = y - (yMin + yMax) / 2;
			//Z rotate
			qreal z = (A*tempx + B*tempy + D) / (-C);
			QVector4D v(tempx, tempy,z,1);
			QVector4D result = rm4x4*v;
//			qreal tempy = y - (x - xMin)*qTan(rotate*M_PI / 360);
			temp.push_back(QVector3D(result.x() + (xMin + xMax) / 2, result.y() + (yMin + yMax) / 2, result.z()));
		}
		points.push_back(temp);
	}

	//转换为与XoY平行的幕的交点
	QVector<QVector<QPointF>> propoints;
	for (const QVector<QVector3D>& vec : points)
	{
		QVector<QPointF> temp;
		qreal z = proPoints[0].z();
		for (const QVector3D& po : vec)
		{
			temp.push_back(QPointF(po.x() * z/po.z(), po.y()*z/po.z()));
		}
		propoints.push_back(temp);
	}

	m_widget->setProRect(QRectF(QPointF(proPoints[0].x(), proPoints[0].y()),QPointF(proPoints[3].x(), proPoints[3].y())));
	m_widget->setPoints(propoints);

	onDragItemChanged();
	m_widget->update();
}

void Projector::projectCylinder()
{

}

void Projector::projectBall()
{

}
