#include <QPainter>
#include "PlaneWidget.h"
#include <qmath.h>
#include <QGenericMatrix>
#include <QMatrix4x4> 
#include <QGraphicsSceneMouseEvent>

#include<cv.h>
#include<highgui.h>
#include "Projector.h"
#include "ToolS.h"

void PlaneWidget::project()
{
	qreal topleftLen = m_projector->ui.topleftLength->value();
	qreal bottomrightLen = m_projector->ui.bottomrightLength->value();
	qreal bottomleftLen = m_projector->ui.bottomleftLength->value();
	qreal rotate = m_projector->ui.rotate->value();

	//投影平面四个点
	std::array<QVector3D, 4> proPoints = m_projector->proPoints();
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
		m_projector->statusBar()->showMessage("uninvertable");
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
	qreal cosalpha = -A*d / D, cosbeta = -B*d / D, cosgamma = -C*d / D;
	_cosalpha = cosalpha, _cosbeta = cosbeta, _cosgamma = cosgamma;

	//幕投影到斜面上的四角点
	std::array<QVector3D, 4> dstPoints = { destPoint(proPoints[0],A,B,C,D), destPoint(proPoints[1],A,B,C,D),
		destPoint(proPoints[2],A,B,C,D), destPoint(proPoints[3],A,B,C,D) };

	qreal xMin = INT_MAX, xMax = INT_MIN, yMin = INT_MAX, yMax = INT_MIN;
	std::for_each(dstPoints.cbegin(), dstPoints.cend(), [&xMin, &xMax, &yMin, &yMax](const QVector3D& po) {
		xMin > po.x() ? xMin = po.x() : 0; xMax < po.x() ? xMax = po.x() : 0;
		yMin > po.y() ? yMin = po.y() : 0; yMax < po.y() ? yMax = po.y() : 0;
	});

	if (qAbs(C) < 0.000001)
	{
		m_projector->statusBar()->showMessage("wrong C parameter");
		return;
	}
	if (qAbs(xMax - xMin) < 0.0001 || qAbs(yMax - yMin) < 0.0001)
	{
		m_projector->statusBar()->showMessage("projector parameter error");
		return;
	}


	QVector3D k = QVector3D(cosalpha, cosbeta, cosgamma);
	qreal cosTheta = qCos(rotate * M_PI / 180);
	qreal sinTheta = qSin(rotate * M_PI / 180);

	qreal space = qMin(xMax - xMin, yMax - yMin) / 20;
	
	m_dragCentral = QPointF((xMax + xMin) / 2, (yMax + yMin) / 2);
	m_dragSize = QSizeF(1, 1);
	
	qreal centralX = (xMin + xMax) / 2;
	qreal centralY = (yMin + yMax) / 2;
	qreal centralZ = (A*centralX + B*centralY + D) / (-C);
	m_central = QVector3D(centralX, centralY, centralZ);
	QVector3D xVector(space, 0, (A*(centralX + space) + B*centralY + D) / (-C) - centralZ);
	//xVector绕k旋转90°
	QVector3D yVector = QVector3D::dotProduct(k, xVector)*k + QVector3D::crossProduct(k, xVector);

	//旋转rotate°
	//https://baike.baidu.com/item/%E7%BD%97%E5%BE%B7%E9%87%8C%E6%A0%BC%E6%97%8B%E8%BD%AC%E5%85%AC%E5%BC%8F/18878562
	xVector = cosTheta*xVector + (1 - cosTheta)*QVector3D::dotProduct(xVector, k)*k + sinTheta*QVector3D::crossProduct(k, xVector);
	yVector = cosTheta*yVector + (1 - cosTheta)*QVector3D::dotProduct(yVector, k)*k + sinTheta*QVector3D::crossProduct(k, yVector);
	m_xVector = xVector, m_yVector = yVector;

	//生成20个点
	QVector<QVector<QVector3D>> points;
	{
		int count = qSqrt((xMax - xMin)*(xMax - xMin) + (yMax - yMin)*(yMax - yMin)) / space + 2;
		qreal xBase = (xMax + xMin)/2;
		qreal yBase = (yMax + yMin)/2;
		qreal zBase = (A*xBase + B*yBase + D) / (-C);
		QVector3D horBase(xBase, yBase, zBase);
		(horBase -= xVector*(count / 2)) -= yVector*(count / 2);
		for (int i = 0; i < count; ++i)
		{
			QVector<QVector3D> temp;
			for (int j = 0; j < count; ++j)
			{
				temp.push_back(horBase + i*xVector + j*yVector);
			}
			points.push_back(temp);
		}
	}
// 	for (qreal x = xMin - (xMin + xMax); x <= xMax + (xMin + xMax); x += space)
// 	{
// 		QVector<QVector3D> temp;
// 		for (qreal y = yMin - (xMin + xMax); y <= yMax + (xMin + xMax); y += yVector.y())
// 		{
// 			qreal tempx = x - centralX;
// 			qreal tempy = y - centralY;
// 			//Z rotate 
// 			qreal z = (A*x + B*y + D) / (-C) - centralZ;
// 			QVector3D v(tempx, tempy, z);
// 			//https://baike.baidu.com/item/%E7%BD%97%E5%BE%B7%E9%87%8C%E6%A0%BC%E6%97%8B%E8%BD%AC%E5%85%AC%E5%BC%8F/18878562
// 			QVector3D result = cosTheta*v + (1 - cosTheta)*QVector3D::dotProduct(v, k)*k + sinTheta*QVector3D::crossProduct(k, v);
// 			temp.push_back(QVector3D(result.x() + centralX, result.y() + centralY, result.z() + centralZ));
// 		}
// 		points.push_back(temp);
// 	}

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

	setProRect(QRectF(QPointF(proPoints[0].x(), proPoints[0].y()), QPointF(proPoints[3].x(), proPoints[3].y())));
	setPoints(propoints);

	update();
}

void PlaneWidget::setPoints(const QVector<QVector<QPointF>>& ps)
{
	m_points = ps;
}

void PlaneWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /*= Q_NULLPTR*/)
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

QVariant PlaneWidget::itemChange(GraphicsItemChange change, const QVariant &value)
{
	QVariant ret = QGraphicsRectItem::itemChange(change, value);
	if (change == ItemPositionHasChanged && scene())
	{
		emit positionChanged();
	}
	return ret;
}

void PlaneWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	m_dragStatus = eOutRect;

	std::array<QVector3D, 4> proPoints = m_projector->proPoints();
	QPointF pos = event->pos();

	QVector3D central(m_dragCentral.x(), m_dragCentral.y(), (_A*m_dragCentral.x() + _B*m_dragCentral.y() + _D) / (-_C));
	std::array<QVector3D, 4> dragRect = { central - m_dragSize.width()*m_xVector - m_dragSize.height()*m_yVector, 
		central + m_dragSize.width()*m_xVector - m_dragSize.height()*m_yVector,
		central - m_dragSize.width()*m_xVector + m_dragSize.height()*m_yVector, 
		central + m_dragSize.width()*m_xVector + m_dragSize.height()*m_yVector };
	{
		//转换为与XoY平行的幕的交点
		std::array<QPointF, 4> tempPoints;
		auto ite = tempPoints.begin();
		for (const QVector3D& po : dragRect)
		{
			qreal z = m_proPoints[0].z();
			*ite++ = QPointF(po.x() * z / po.z(), po.y()*z / po.z());
		}

		QPointF topleft = m_proRect.topLeft();
		qreal xmmpix = rect().width() / m_proRect.width();
		qreal ymmpix = rect().height() / m_proRect.height();
		for (QPointF& po : tempPoints)
		{
			po -= topleft;
			po.setX(po.x()*xmmpix);
			po.setY(po.y()*ymmpix);
			po += rect().topLeft();
		}
		QPainterPath path(tempPoints[0]);
		path.lineTo(tempPoints[1]);
		path.lineTo(tempPoints[3]);
		path.lineTo(tempPoints[2]);
		path.moveTo(tempPoints[0]);
		if (path.contains(pos))
		{
			m_dragStatus = eInRect;
		}
	}
}

void PlaneWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (m_dragStatus == eInRect)
	{
		std::array<QVector3D, 4> proPoints = m_projector->proPoints();
		QPointF pos = event->pos();
		qreal prox = proPoints[0].x() + (proPoints[1].x() - proPoints[0].x())*(pos.x() / rect().width());
		qreal proy = proPoints[0].y() + (proPoints[2].y() - proPoints[0].y())*(pos.y() / rect().height());
		QVector3D destPoint = ::destPoint(QVector3D(prox, proy, proPoints[0].z()), _A, _B, _C, _D);

		m_dragCentral = QPointF(destPoint.x(), destPoint.y());
		update();
	}
}

void PlaneWidget::wheelEvent(QGraphicsSceneWheelEvent *event)
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

void PlaneWidget::paintDragItem(QPainter *painter)
{
	if (!rect().isValid())
	{
		return;
	}
	
	QVector3D central(m_dragCentral.x(), m_dragCentral.y(), (_A*m_dragCentral.x() + _B*m_dragCentral.y() + _D) / (-_C));
	std::array<QVector3D, 4> dragRect = { central - m_dragSize.width()*m_xVector - m_dragSize.height()*m_yVector,
		central + m_dragSize.width()*m_xVector - m_dragSize.height()*m_yVector,
		central - m_dragSize.width()*m_xVector + m_dragSize.height()*m_yVector,
		central + m_dragSize.width()*m_xVector + m_dragSize.height()*m_yVector };

	//转换为与XoY平行的幕的交点
	std::array<QPointF,4> tempPoints;
	auto ite = tempPoints.begin();
	for (const QVector3D& po : dragRect)
	{
		qreal z = m_proPoints[0].z();
		*ite++ = QPointF(po.x() * z / po.z(), po.y()*z / po.z());
	}

	QPointF topleft = m_proRect.topLeft();
	qreal xmmpix = rect().width() / m_proRect.width();
	qreal ymmpix = rect().height() / m_proRect.height();
	for (QPointF& po : tempPoints)
	{
		po -= topleft;
		po.setX(po.x()*xmmpix);
		po.setY(po.y()*ymmpix);
		po += rect().topLeft();
	}

	static QPixmap map(":/Projector/Resources/origpic.png");
	if (m_proRect.width() < 0.0001 || !m_proRect.isValid())
	{
		return;
	}

	QImage image = map.toImage();
	image.convertToFormat(QImage::Format_ARGB32);
	cv::Mat mat = QImage2cvMat(image);
	IplImage src = IplImage(mat);

	CvPoint2D32f srcTri[4] = { CvPoint2D32f(0,0),CvPoint2D32f(src.width,0),CvPoint2D32f(0,src.height),CvPoint2D32f(src.width, src.height) };

	std::array<QPointF, 4> temp = tempPoints;
	for (auto ite = temp.rbegin(); ite != temp.rend(); ++ite)
	{
		*ite -= temp[0];
	}

	CvSize size;
	qreal xMin = INT_MAX, xMax = INT_MIN, yMin = INT_MAX, yMax = INT_MIN;
	std::for_each(temp.cbegin(), temp.cend(), [&xMin, &xMax, &yMin, &yMax](const QPointF& po) {
		xMin > po.x() ? xMin = po.x() : 0; xMax < po.x() ? xMax = po.x() : 0;
		yMin > po.y() ? yMin = po.y() : 0; yMax < po.y() ? yMax = po.y() : 0;
	});
	for (QPointF& po : temp)
	{
		xMin < 0 ? po.setX(po.x() - xMin) : 0;
		yMin < 0 ? po.setY(po.y() - yMin) : 0;
	}

	CvPoint2D32f dstTri[4] = { CvPoint2D32f(temp[0].x(), temp[0].y()),CvPoint2D32f(temp[1].x(), temp[1].y()),CvPoint2D32f(temp[2].x(), temp[2].y()),CvPoint2D32f(temp[3].x(), temp[3].y()) };
	qreal width = 2 * qSqrt((xMax - xMin)*(xMax - xMin));
	if (width > 9999 || width < 1)
	{
		return;
	}
	size = CvSize(width, width);

	IplImage*    dst = cvCreateImage(size, src.depth, src.nChannels);
	dst->origin = src.origin;
	cvZero(dst);

	CvMat*       warp_mat = cvCreateMat(3, 3, CV_32FC1);
	cvGetPerspectiveTransform(srcTri, dstTri, warp_mat);
	cvWarpPerspective(&src, dst, warp_mat);
	cvNamedWindow("Perspective warp");
	cvShowImage("Perspective warp", dst);
	//	CV_INTER_NN
	QImage imageto = cvMat2QImage(cv::cvarrToMat(dst));

	{
		QPixmap map = QPixmap::fromImage(imageto);
		painter->drawPixmap(tempPoints[0] + QPointF(xMin, yMin), map);
	}
	painter->drawLine(tempPoints[0], tempPoints[1]);
	painter->drawLine(tempPoints[0], tempPoints[2]);
	painter->drawLine(tempPoints[2], tempPoints[3]);
	painter->drawLine(tempPoints[1], tempPoints[3]);
}


