#include "DragItem.h"
#include <QPainter>
#include<cv.h>
#include<highgui.h>
#include <QtMath>

 cv::Mat QImage2cvMat(QImage image)
 {
 	cv::Mat mat;
 	switch (image.format())
 	{
 	case QImage::Format_ARGB32:
 	case QImage::Format_RGB32:
 	case QImage::Format_ARGB32_Premultiplied:
 		mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
 		break;
 	case QImage::Format_RGB888:
 		mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
 		//cv::cvtColor(mat, mat, CV_BGR2RGB);
 		break;
 	case QImage::Format_Indexed8:
 		mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
 		break;
 	}
 	cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC4);
 	int from_to[] = { 0,0, 1,1, 2,2 };
 	cv::mixChannels(&mat, 1, &mat2, 1, from_to, 3);
 	return mat2;
 }

 QImage cvMat2QImage(const cv::Mat& mat)
 {
	 // 8-bits unsigned, NO. OF CHANNELS = 1  
	 if (mat.type() == CV_8UC1)
	 {
		 QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		 // Set the color table (used to translate colour indexes to qRgb values)  
		 image.setColorCount(256);
		 for (int i = 0; i < 256; i++)
		 {
			 image.setColor(i, qRgb(i, i, i));
		 }
		 // Copy input Mat  
		 uchar *pSrc = mat.data;
		 for (int row = 0; row < mat.rows; row++)
		 {
			 uchar *pDest = image.scanLine(row);
			 memcpy(pDest, pSrc, mat.cols);
			 pSrc += mat.step;
		 }
		 return image;
	 }
	 // 8-bits unsigned, NO. OF CHANNELS = 3  
	 else if (mat.type() == CV_8UC3)
	 {
		 // Copy input Mat  
		 const uchar *pSrc = (const uchar*)mat.data;
		 // Create QImage with same dimensions as input Mat  
		 QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		 return image.rgbSwapped();
	 }
	 else if (mat.type() == CV_8UC4)
	 {
		 //qDebug() << "CV_8UC4";
		 // Copy input Mat  
		 const uchar *pSrc = (const uchar*)mat.data;
		 // Create QImage with same dimensions as input Mat  
		 QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		 return image.copy();
	 }
	 else
	 {
		 //qDebug() << "ERROR: Mat could not be converted to QImage.";
		 return QImage();
	 }
 }

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
