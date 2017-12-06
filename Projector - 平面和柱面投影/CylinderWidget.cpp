#include "CylinderWidget.h"
#include <qmath.h>
#include <QGenericMatrix>
#include <QMatrix4x4> 
#include <QGraphicsSceneMouseEvent>
#include<cv.h>
#include<highgui.h>
#include <QPainter>
#include "projector.h"

CylinderWidget::CylinderWidget(Projector* p):m_projector(p)
{
}

CylinderWidget::~CylinderWidget()
{
}

void CylinderWidget::project()
{
	qreal r = m_projector->ui.cyr->value();
	qreal x = m_projector->ui.cyx->value();
	qreal z = m_projector->ui.cyz->value();
	qreal rotateX = m_projector->ui.cyrotateX->value();
	qreal rotateZ = m_projector->ui.cyrotateZ->value();
	qreal rotate = m_projector->ui.rotate->value();
	//旋转X
	QMatrix3x3 rmX;
	//旋转Z
	QMatrix3x3 rmZ;
	//根据旋转角初始化矩阵
	{
		float farrx[] = { 1,0,0,  0,qCos(rotateX*M_PI / 180),qSin(rotateX*M_PI / 180),  0,-qSin(rotateX*M_PI / 180),qCos(rotateX*M_PI / 180) };
		float farrZ[] = { qCos(rotateZ*M_PI / 180),qSin(rotateZ*M_PI / 180),0  ,-qSin(rotateZ*M_PI / 180),qCos(rotateZ*M_PI / 180),0, 0,0,1 };
		rmX = QMatrix3x3(farrx);
		rmZ = QMatrix3x3(farrZ);
	}

	//投影平面四个点
	std::array<QVector3D, 4> proPoints = m_projector->proPoints();

	qreal height = (proPoints[2].y() - proPoints[0].y()) / (proPoints[0].z() / z);
	//生成50份
	QVector<QVector<QVector3D>> points;
	qreal delta = M_PI*r*(1.0 / 50);
	m_dragSize = QSizeF(delta, delta);
	for (qreal theta = 180; theta <= 360; theta += 3.6)
	{
		QVector<QVector3D> temp;
		for (qreal y = height; y >= -2*height; y -= delta)
		{
			QVector3D point(r*qCos(theta*M_PI / 180), y, r*qSin(theta*M_PI / 180));
			float d[] = { point.x(), point.y(), point.z() };
			QMatrix1x3 point13(d);
			//旋转
			QMatrix1x3 ret = rmZ*(rmX*point13);
			point = { ret(0,0), ret(1,0), ret(2,0) };
			//平移
			QVector3D offset(x, 0, z);
			point += offset;
			temp.push_back(point);
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
			temp.push_back(QPointF(po.x() * z / po.z(), po.y()*z / po.z()));
		}
		propoints.push_back(temp);
	}

	m_proRect = QRectF(QPointF(proPoints[0].x(), proPoints[0].y()), QPointF(proPoints[3].x(), proPoints[3].y()));
	m_points = propoints;

	update();
}

void CylinderWidget::init()
{
	m_projector->ui.cyr->setValue(m_projector->m_settings->value("Cylinder/cyr").toInt());
	m_projector->ui.cyx->setValue(m_projector->m_settings->value("Cylinder/cyx").toInt());
	m_projector->ui.cyz->setValue(m_projector->m_settings->value("Cylinder/cyz").toInt());
	m_projector->ui.cyrotateX->setValue(m_projector->m_settings->value("Cylinder/cyrotateX").toInt());
	m_projector->ui.cyrotateZ->setValue(m_projector->m_settings->value("Cylinder/cyrotateZ").toInt());


	void (QSpinBox::* spvalueChangedSig)(const QString&) = &QSpinBox::valueChanged;
	connect(m_projector->ui.cyr, spvalueChangedSig, m_projector, &Projector::project);
	connect(m_projector->ui.cyx, spvalueChangedSig, m_projector, &Projector::project);
	connect(m_projector->ui.cyz, spvalueChangedSig, m_projector, &Projector::project);
	connect(m_projector->ui.cyrotateX, spvalueChangedSig, m_projector, &Projector::project);
	connect(m_projector->ui.cyrotateZ, spvalueChangedSig, m_projector, &Projector::project);

	connect(m_projector->ui.cyr, &QAbstractSpinBox::editingFinished, [this]() {
		m_projector->m_settings->setValue("Cylinder/cyr", m_projector->ui.cyr->value());
	});
	connect(m_projector->ui.cyx, &QAbstractSpinBox::editingFinished, [this]() {
		m_projector->m_settings->setValue("Cylinder/cyx", m_projector->ui.cyx->value());
	});
	connect(m_projector->ui.cyz, &QAbstractSpinBox::editingFinished, [this]() {
		m_projector->m_settings->setValue("Cylinder/cyz", m_projector->ui.cyz->value());
	});
	connect(m_projector->ui.cyrotateX, &QAbstractSpinBox::editingFinished, [this]() {
		m_projector->m_settings->setValue("Cylinder/cyrotateX", m_projector->ui.cyrotateX->value());
	});
	connect(m_projector->ui.cyrotateZ, &QAbstractSpinBox::editingFinished, [this]() {
		m_projector->m_settings->setValue("Cylinder/cyrotateZ", m_projector->ui.cyrotateZ->value());
	});
}

void CylinderWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /*= Q_NULLPTR*/)
{
	QGraphicsRectItem::paint(painter, option, widget);
	QPainterPath path;
	path.addRect(rect());
	painter->setClipPath(path);

	QPointF topleft = m_proRect.topLeft();
	qreal xmmpix = rect().width() / m_proRect.width();
	qreal ymmpix = rect().height() / m_proRect.height();
	QVector<QVector<QPointF>> tempPoints = m_points;
	for (QVector<QPointF>& vec : tempPoints)
	{
		for (QPointF& po : vec)
		{
			po -= topleft;
			po.setX(po.x()*xmmpix);
			po.setY(po.y()*ymmpix);
			po += rect().topLeft();
		}
	}

	qreal param = 0;

	for (QVector<QPointF>& vec : tempPoints)
	{
		for (int i = 0; i < vec.size() - 2; i += 2)
		{
			painter->setPen(QPen());
			painter->drawLine(vec[i], vec[i + 2]);
			painter->setPen(QPen(Qt::red, 4));
			painter->drawPoint(vec[i]);
			painter->drawPoint(vec[i + 2]);
		}
		for (int i = 1; i < vec.size() - 2; i += 2)
		{
			painter->setPen(QPen());
			painter->drawLine(vec[i], vec[i + 2]);
			painter->setPen(QPen(Qt::red, 4));
			painter->drawPoint(vec[i]);
			painter->drawPoint(vec[i + 2]);
		}
		if (!vec.isEmpty())
		{
			//	painter.drawLine(vec.first(), vec.last());
		}
	}
	int maxnum = 0;
	for (QVector<QPointF>& vec : tempPoints)
	{
		maxnum = vec.size() > maxnum ? vec.size() : maxnum;
	}
	for (int i = 0; i < maxnum; ++i)
	{
		for (int j = 0; j < tempPoints.size() - 1; ++j)
		{
			if ((i < tempPoints[j].size()) && (i < tempPoints[j + 1].size()))
			{
				painter->setPen(QPen());
				painter->drawLine(tempPoints[j][i], tempPoints[j + 1][i]);
			}
		}
	}
	paintDragItem(painter);
}

void CylinderWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	std::array<QVector3D, 4> proPoints = m_projector->proPoints();
	QPointF pos = event->pos();
	qreal prox = proPoints[0].x() + (proPoints[1].x() - proPoints[0].x())*(pos.x() / rect().width());
	qreal proy = proPoints[0].y() + (proPoints[2].y() - proPoints[0].y())*(pos.y() / rect().height());
	m_dragCentral = destPoint(QVector3D(prox, proy, proPoints[0].z()));

	update();
}

void CylinderWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void CylinderWidget::wheelEvent(QGraphicsSceneWheelEvent *event)
{
	int delta = event->delta();
	if (delta > 0)
	{
		m_dragSize *= 1.1;
	}
	if (delta < 0)
	{
		m_dragSize /= 1.1;
	}
	update();
	return QGraphicsRectItem::wheelEvent(event);
}

//原点与pos点的连线与圆柱的交点
QVector3D CylinderWidget::destPoint(const QVector3D& pos)
{
	qreal r = m_projector->ui.cyr->value();
	qreal x = m_projector->ui.cyx->value();
	qreal z = m_projector->ui.cyz->value();

	QVector3D pos1 = QVector3D(), pos2 = pos;

	//逆平移
	pos1 -= QVector3D(x, 0, z);
	pos2 -= QVector3D(x, 0, z);

	//逆旋转
	qreal rotateX = -m_projector->ui.cyrotateX->value();
	qreal rotateZ = -m_projector->ui.cyrotateZ->value();
	//旋转X
	QMatrix3x3 rmX;
	//旋转Z
	QMatrix3x3 rmZ;
	//根据旋转角初始化矩阵
	{
		float farrx[] = { 1,0,0,  0,qCos(rotateX*M_PI / 180),qSin(rotateX*M_PI / 180),  0,-qSin(rotateX*M_PI / 180),qCos(rotateX*M_PI / 180) };
		float farrZ[] = { qCos(rotateZ*M_PI / 180),qSin(rotateZ*M_PI / 180),0  ,-qSin(rotateZ*M_PI / 180),qCos(rotateZ*M_PI / 180),0, 0,0,1 };
		rmX = QMatrix3x3(farrx);
		rmZ = QMatrix3x3(farrZ);
	}

	//计算旋转后的点
	{
		QVector3D* v[2] = {&pos1, &pos2};
		for (QVector3D* pos : v)
		{
			float d[] = { pos->x(), pos->y(), pos->z() };
			QMatrix1x3 point13(d);
			QMatrix1x3 ret = rmX*(rmZ*point13);
			*pos = { ret(0,0), ret(1,0), ret(2,0) };
		}
	}
	//直线方程 x-x1/x2-x1=y-y1/y2-y1=z-z1/z2-z1 x1,y1,z1,x2,y2,z2 = pos1,pos2
	//圆柱方程 x^2 + z^2 = r^2; (z < 0)     联立解得z
	//解方程解得与圆柱交点
	qreal cyx = 0, cyy = 0, cyz = 0;
	{
		qreal z2mz1 = pos2.z() - pos1.z();
		qreal x2mx1 = pos2.x() - pos1.x();
		qreal a = x2mx1*x2mx1 / (z2mz1*z2mz1) + 1;
		qreal b = 2 * (pos1.x() - x2mx1 / z2mz1*pos1.z())*x2mx1 / z2mz1;
		qreal c = (pos1.x() - x2mx1 / z2mz1*pos1.z())*(pos1.x() - x2mx1 / z2mz1*pos1.z()) - r*r;
		//a*z^2 + b*z + c = 0;
		qreal delta = b*b - 4 * a*c;
		//z的两个解
		qreal zs[2] = {0,0};
		if (delta >= 0){
			zs[0] = (-b + qSqrt(delta)) / (2*a);
			zs[1] = (-b - qSqrt(delta)) / (2*a);
		}
		//取z<0的解
		cyz = zs[0] < 0 ? zs[0] : zs[1];
		cyx = (cyz - pos1.z()) / z2mz1*x2mx1 + pos1.x();
		cyy = (cyz - pos1.z()) / z2mz1*(pos2.y() - pos1.y()) + pos1.y();
	}
	return QVector3D(cyx, cyy, cyz);
	//旋转，平移得到最终交点
// 	{
// 		//旋转
// 		qreal rotateX = m_projector->ui.cyrotateX->value();
// 		qreal rotateZ = m_projector->ui.cyrotateZ->value();
// 		float farrx[] = { 1,0,0,  0,qCos(rotateX*M_PI / 180),qSin(rotateX*M_PI / 180),  0,-qSin(rotateX*M_PI / 180),qCos(rotateX*M_PI / 180) };
// 		float farrZ[] = { qCos(rotateZ*M_PI / 180),qSin(rotateZ*M_PI / 180),0  ,-qSin(rotateZ*M_PI / 180),qCos(rotateZ*M_PI / 180),0, 0,0,1 };
// 		rmX = QMatrix3x3(farrx);
// 		rmZ = QMatrix3x3(farrZ);
// 
// 		float d[] = { cyx, cyy, cyz };
// 		QMatrix1x3 point13(d);
// 		QMatrix1x3 ret = rmZ*(rmX*point13);
// 		return QVector3D(ret(0, 0) + x, ret(1, 0), ret(2, 0) + z);
// 	}
}

void CylinderWidget::paintDragItem(QPainter *painter)
{
	if (!rect().isValid() || m_dragCentral.isNull())
	{
		return;
	}
	qreal r = m_projector->ui.cyr->value();
	qreal x = m_projector->ui.cyx->value();
	qreal z = m_projector->ui.cyz->value();
	//鼠标拖动不在柱子上
	if (qAbs(r*r - (m_dragCentral.x()*m_dragCentral.x() + m_dragCentral.z()*m_dragCentral.z())) > 0.1)
	{
		return;
	}
	//柱面坐标角度
	qreal theta = qAsin(m_dragCentral.z() / r);
	theta = m_dragCentral.x() < 0 ? M_PI - theta : 2 * M_PI + theta;
	//距中心点宽度角度
	qreal delta = m_dragSize.width() / r;

	//初始化旋转矩阵
	QMatrix3x3 rmX, rmZ;
	{
		//旋转
		qreal rotateX = m_projector->ui.cyrotateX->value();
		qreal rotateZ = m_projector->ui.cyrotateZ->value();
		float farrx[] = { 1,0,0,  0,qCos(rotateX*M_PI / 180),qSin(rotateX*M_PI / 180),  0,-qSin(rotateX*M_PI / 180),qCos(rotateX*M_PI / 180) };
		float farrZ[] = { qCos(rotateZ*M_PI / 180),qSin(rotateZ*M_PI / 180),0  ,-qSin(rotateZ*M_PI / 180),qCos(rotateZ*M_PI / 180),0, 0,0,1 };
		rmX = QMatrix3x3(farrx);
		rmZ = QMatrix3x3(farrZ);
	}
	static QPixmap map(":/Projector/Resources/origpic.png");
	//src image
	QImage image = map.toImage();
	//调整大小
	image.scaled(m_dragSize.toSize() * 2);

	//目的图片
	QImage imageDst(rect().size().toSize(), QImage::Format_ARGB32);
	imageDst.fill(QColor(0, 0, 0, 0));
	//屏幕
	std::array<QVector3D, 4> proPoints = m_projector->proPoints();
	qreal proZ = proPoints[0].z();
	qreal pixdel = 1 / r;
	int i = 0;
	qreal xmmpix = rect().width() / (proPoints[1].x() - proPoints[0].x());
	qreal ymmpix = rect().height() / (proPoints[2].y() - proPoints[0].y());
	//柱子上的图片映射到投影面
	for (qreal the = theta - delta; the < theta + delta; the += pixdel)
	{
		qreal tx = r*qCos(the);
		qreal tz = r*qSin(the);
		int j = 0;
		for (int ty = m_dragCentral.y() - m_dragSize.height(); ty < m_dragCentral.y() + m_dragSize.height(); ++ty)
		{
			float d[] = { tx,ty,tz };
			QMatrix1x3 point13(d);
			QMatrix1x3 ret = rmZ*(rmX*point13);
			QVector3D po = QVector3D(ret(0, 0) + x, ret(1, 0), ret(2, 0) + z);
			//转换为与XoY平行的幕的交点
			QPointF pos = QPointF(po.x() * proZ / po.z(), po.y()*proZ / po.z());
			pos -= QPointF(proPoints[0].x(), proPoints[0].y());
			pos.setX(pos.x() * xmmpix);
			pos.setY(pos.y()*ymmpix);
			pos += rect().topLeft();
			if (rect().contains(pos))
			{
				imageDst.setPixelColor(pos.toPoint(), image.pixelColor(i, j));
			}
			
			++j;
		}
		++i;
	}

	
	painter->drawImage(QPointF(), imageDst);
}
