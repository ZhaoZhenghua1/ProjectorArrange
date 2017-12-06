#include "DragItem.h"
#include <QPainter>
#include<cv.h>
#include<highgui.h>
#include <QtMath>
#include "ToolS.h"

void DragItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{
//	QGraphicsRectItem::paint(painter, option, widget);
	QPainterPath path;
	path.addRect(rect());
//	painter->setClipPath(path);
	static QPixmap map(":/Projector/Resources/origpic.png");
//	painter->drawPixmap(rect(), map, map.rect());
	if (m_proRect.width() < 0.0001 || !m_proRect.isValid())
	{
		return;
	}
	std::array<QPointF, 4> tempPoints = m_points;
	QPointF topleft = m_proRect.topLeft();
	qreal xmmpix = rect().width() / m_proRect.width();
	qreal ymmpix = rect().height() / m_proRect.height();
	for (QPointF& po : tempPoints) 
	{
		po -= topleft;
		po.setX(po.x()*xmmpix);
		po.setY(po.y()*ymmpix);
//		po *= xmmpix;
		po += rect().topLeft();
	}
// 	painter->drawLine(tempPoints[0], tempPoints[1]);
// 	painter->drawLine(tempPoints[0], tempPoints[2]);
// 	painter->drawLine(tempPoints[1], tempPoints[3]);
// 	painter->drawLine(tempPoints[2], tempPoints[3]);
// 	
// 	return;
	QSize mapSize = map.size();

	QImage image = map.toImage();
	image.convertToFormat(QImage::Format_ARGB32);
	cv::Mat mat = QImage2cvMat(image);
	IplImage src = IplImage(mat);

	CvPoint2D32f srcTri[4] = { CvPoint2D32f(0,0),CvPoint2D32f(src.width,0),CvPoint2D32f(0,src.height),CvPoint2D32f(src.width, src.height)};

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
	qreal width = 2*qSqrt((xMax - xMin)*(xMax - xMin));
	if (width > 9999)
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
		painter->drawPixmap(tempPoints[0], map);
	}
}

QVariant DragItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	QVariant ret = QGraphicsRectItem::itemChange(change, value);
	if (change == ItemPositionHasChanged && scene())
	{
		emit positionChanged();
	}
	return ret;
}
