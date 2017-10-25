#include "ProjectConverter.h"
#include <QtMath>
#include <QMessageBox>

#include<cv.h>
#include<highgui.h>

#include <QGenericMatrix>
#include <armadillo>
using namespace arma;
#include <QVector3D>

#include "Calculator.h"

ProjectConverter::ProjectConverter()
{
	ui.setupUi(this);

	ui.widgetProjector->setPixmap(m_map);
}


ProjectConverter::~ProjectConverter()
{
}

void ProjectConverter::setPixmap(const QString& map)
{
	ui.widgetProjector->setPixmap(map);
	m_map = map;
}
void ProjectConverter::project()
{
	const qreal toRadian = M_PI / 180;

	qreal distance = ui.doubleSpinBoxDistanceToRealScreen->value();
	qreal angleX = ui.doubleSpinBoxRotateX->value() * toRadian;
	qreal angleY = ui.doubleSpinBoxRotateY->value() * toRadian;
	qreal angleZ = ui.doubleSpinBoxRotateZ->value() * toRadian;

	qreal tempValue = qCos(angleX)*qCos(angleX) + qCos(angleY)*qCos(angleY) + qCos(angleZ)*qCos(angleZ);
	if (qAbs(tempValue - 1) > 0.01)
	{
		QMessageBox::information(this, "Error", QString::fromLocal8Bit("α^2 + β^2 + γ^2 == 1"));
		return;
	}

	//plane x*cos(angleX) + y*cos(angleY) + z*cos(angleZ) = distance

	qreal projectorWidth = ui.doubleSpinBoxScreenWidth->value();
	qreal projectorHeight = ui.doubleSpinBoxScreenHeight->value();
	qreal projectorDis = ui.doubleSpinBoxDistanceToScreen->value();
	QRectF projectorRect(-projectorWidth/2, -projectorHeight/2, projectorWidth, projectorHeight);
	//line 
	QVector3D points[4] = { QVector3D(projectorRect.topLeft().x(),projectorRect.topLeft().y(), projectorDis ),
		QVector3D(projectorRect.topRight().x(),projectorRect.topRight().y(),projectorDis ),
		QVector3D(projectorRect.bottomLeft().x(),projectorRect.bottomLeft().y(), projectorDis),
		QVector3D(projectorRect.bottomRight().x(),projectorRect.bottomRight().y(),projectorDis)};

	QVector3D pointsResult[4] = {};
	{
		QVector3D *pointResult = pointsResult;
		//求直线和面的交点
		for (QVector3D&point : points)
		{
			//xcos(α)+xcos(β)+zcos(γ) = distance
			//x/x1 = y/y1 = z/z1 直线方程
			*pointResult = Calculator::intersectLinePlane(QVector3D(), point, angleX, angleY, angleZ, distance);
			pointResult++;
		}
	}

	QString message;
	for (QVector3D&point : pointsResult)
	{
		message += QString("pos x:%1,y:%2,z:%3").arg(point.x()).arg(point.y()).arg(point.z());
		message += '\n';
	}

	//三维平面转换为二维平面
	//一个点作为原点
	pointsResult[3] -= pointsResult[0];
	pointsResult[2] -= pointsResult[0];
	pointsResult[1] -= pointsResult[0];
	pointsResult[0] -= pointsResult[0];

	QVector3D normalVector = QVector3D::crossProduct(pointsResult[1], pointsResult[2]);//{l[1]*r[2] - l[2]*r[1], l[2]*r[0] - l[0]*r[2], l[0]*r[1] - l[1]*r[0]};//平面法向量

	//参考系
	QVector3D corVec[2] = { pointsResult[1]
		,QVector3D::crossProduct(normalVector, pointsResult[1])// { normalVector[1] * l[2] - normalVector[2] * l[1], normalVector[2] * l[0] - normalVector[0] * l[2], normalVector[0] * l[1] - normalVector[1] * l[0] }
	};

	//单位化参考系
	for (QVector3D &point : corVec)
	{
		point /= point.length();
	}

	//在当前参考系下点的坐标值
	QPointF vector2d[4] = { { 0,0 },{ pointsResult[1].length() / corVec[0].length() ,0 },{ 0,0 },{ 0,0 } };
	QPointF*v2d = &vector2d[2];
	for (QVector3D *vector = &pointsResult[2]; vector < &pointsResult[4]; ++vector)//qreal(&vector)[3] : pointsVector)
	{
		qreal matLValue[2][2] = {
			{ corVec[0][0], corVec[0][1] }
			,{ corVec[1][0], corVec[1][1] }
		};
		qreal matRValue[2][1] = { (*vector)[0], (*vector)[1] };
		mat L = mat((qreal *)matLValue, 2, 2);
		mat R = mat((qreal*)matRValue, 2, 1);

		mat Res = solve(L, R);

		*v2d = QPointF(Res.at(0, 0), Res.at(1, 0));
		++v2d;
	}

	//计算像素值
	QPixmap map = ui.widgetProjector->pixmap();

	QSize mapSize = map.size();
//	qreal mm1Width = mapSize.width() / projectorWidth;
	//投影后不同位置对应的宽高对应的像素值不同，这里暂时只考虑宽度对应
//	for (qreal(*vector)[2] = (qreal(*)[2])vector2d[0]; vector < (qreal(*)[2])vector2d[4]; ++vector)
//	{
//		(*vector)[0] *= mm1Width;
//		(*vector)[1] *= mm1Width;
//	}

	CvPoint2D32f srcTri[4], dstTri[4];
	CvMat*       warp_mat = cvCreateMat(3, 3, CV_32FC1);
	IplImage*    dst = NULL;

	QImage image = map.toImage();

	cv::Mat QImage2cvMat(QImage image);
	image.convertToFormat(QImage::Format_RGB32);
	cv::Mat mat = QImage2cvMat(image);
	IplImage src = IplImage(mat);//cvDecodeImage(&mat, 1);
								 // 	src = cvLoadImage("E:\\origpic.png");//("D:\\1.jpg");//("E:\\图像处理\\25.bmp");
	CvSize size;
	{
		qreal minW = 0, maxW = 0, minH = 0, maxH = 0;
		for (QPointF *vector= &vector2d[0]; vector < &vector2d[4]; ++vector)
		{
			if ((*vector).x() > maxW)
				maxW = (*vector).x();
			
			if ((*vector).x() < minW)
				minW = (*vector).x();
			
			if ((*vector).y() > maxH)
				maxH = (*vector).y();
			
			if ((*vector).y() < minH)
				minH = (*vector).y();
		}
		//坐标全部转为正
		for (QPointF *vector = &vector2d[0]; vector < &vector2d[4]; ++vector)
		{
			if (minW < 0)
				(*vector) += QPointF(-minW, 0);
			
			if (minH < 0)
				(*vector) += QPointF(0, -minH);
		}
		
		size = CvSize(maxW - minW, maxH - minH);
	}
	//	size = CvSize(src.width, src.height);
	message += QString("size width:%1,height:%2").arg(size.width).arg(size.height);
	ui.textBrowser->setText(message);

	QRectF srcRect = image.rect();
	srcTri[0].x = srcRect.topLeft().x();
	srcTri[0].y = srcRect.topLeft().y();
	srcTri[1].x = srcRect.topRight().x();
	srcTri[1].y = srcRect.topRight().y();
	srcTri[2].x = srcRect.bottomLeft().x();
	srcTri[2].y = srcRect.bottomLeft().y();
	srcTri[3].x = srcRect.bottomRight().x();
	srcTri[3].y = srcRect.bottomRight().y();


	for (int i = 0; i < 4; ++i)
	{
		dstTri[i].x = vector2d[i].x();//srcTri[i].x;
		dstTri[i].y = vector2d[i].y();//srcTri[i].y;
	}
	while (size.width > 10000 || size.width > 10000)
	{
		size.width /= 10;
		size.height /= 10;
		for (CvPoint2D32f& po : dstTri)
		{
			po.x /= 10;
			po.y /= 10;
		}
	}

	dst = cvCreateImage(size, src.depth, src.nChannels);
	dst->origin = src.origin;
	cvZero(dst);

	cvGetPerspectiveTransform(srcTri, dstTri, warp_mat);
	cvWarpPerspective(&src, dst, warp_mat);

	QImage cvMat2QImage(const cv::Mat& mat);
	QImage imageto = cvMat2QImage(cv::cvarrToMat(dst));
	ui.widget_2->setPixmap(QPixmap::fromImage(imageto));
	update();
}

void ProjectConverter::project2()
{
	const qreal toRadian = M_PI / 180;

	qreal distance = ui.doubleSpinBoxDistanceToRealScreen->value();
	qreal angleX = ui.doubleSpinBoxRotateX->value();
	qreal angleY = ui.doubleSpinBoxRotateY->value();
	qreal angleZ = ui.doubleSpinBoxRotateZ->value();

	qreal tempValue = qCos(angleX * toRadian)*qCos(angleX * toRadian) + qCos(angleY * toRadian)*qCos(angleY * toRadian) + qCos(angleZ * toRadian)*qCos(angleZ * toRadian);
	if (qAbs(tempValue - 1) > 0.01)
	{
		QMessageBox::information(this, "Error", QString::fromLocal8Bit("α^2 + β^2 + γ^2 == 1"));
		return;
	}

	//plane x*cos(angleX) + y*cos(angleY) + z*cos(angleZ) = distance

	qreal projectorWidth = ui.doubleSpinBoxScreenWidth->value();
	qreal projectorHeight = ui.doubleSpinBoxScreenHeight->value();
	qreal projectorDis = ui.doubleSpinBoxDistanceToScreen->value();
	QRectF projectorRect(-projectorWidth / 2, -projectorHeight / 2, projectorWidth, projectorHeight);
	//line 
	qreal points[4][3] = { { projectorRect.topLeft().x(),projectorRect.topLeft().y(), projectorDis },
	{ projectorRect.topRight().x(),projectorRect.topRight().y(),projectorDis },
	{ projectorRect.bottomLeft().x(),projectorRect.bottomLeft().y(), projectorDis },
	{ projectorRect.bottomRight().x(),projectorRect.bottomRight().y(),projectorDis },
	};

	// 	QGenericMatrix<1, 3, qreal> 3drect1 = QGenericMatrix<1, 3, qreal>();
	// 	QGenericMatrix<1, 3, qreal> 3drect1 = QGenericMatrix<1, 3, qreal>();
	// 	QGenericMatrix<1, 3, qreal> 3drect1 = QGenericMatrix<1, 3, qreal>();
	// 	QGenericMatrix<1, 3, qreal> 3drect1 = QGenericMatrix<1, 3, qreal>();


	qreal pointsResult[4][3] = { 0 };
	qreal(*pointResult)[3] = (qreal(*)[3])pointsResult[0];
	//求直线和面的交点
	for (qreal(&point)[3] : points)
	{
		//xcos(α)+xcos(β)+zcos(γ) = distance
		//x/x1 = y/y1 = z/z1 直线方程
		qreal matLValue[3][3] = {
			{ qCos(angleX * toRadian), point[1], 0 } ,
			{ qCos(angleY * toRadian), -point[0], point[2] } ,
			{ qCos(angleZ * toRadian), 0, -point[1] } };
		qreal matRValue[3][1] = { distance, 0, 0 };
		mat L = mat((qreal *)matLValue, 3, 3);
		mat R = mat((qreal*)matRValue, 3, 1);

		mat Res = solve(L, R);

		(*pointResult)[0] = Res.at(0, 0);
		(*pointResult)[1] = Res.at(1, 0);
		(*pointResult)[2] = Res.at(2, 0);
		pointResult++;
	}

	QString message;
	for (qreal(&point)[3] : pointsResult)
	{
		message += QString("pos x:%1,y:%2,z:%3").arg(point[0]).arg(point[1]).arg(point[2]);
		message += '\n';
	}

	//三维平面转换为二维平面
	qreal(&R)[4][3] = pointsResult;
	//一个点作为原点
	qreal pointsVector[4][3] = { { 0 }
		,{ R[1][0] - R[0][0], R[1][1] - R[0][1], R[1][2] - R[0][2] }
		,{ R[2][0] - R[0][0], R[2][1] - R[0][1], R[2][2] - R[0][2] }
		,{ R[3][0] - R[0][0], R[3][1] - R[0][1], R[3][2] - R[0][2] }
	};
	qreal(&l)[3] = pointsVector[1];
	qreal(&r)[3] = pointsVector[2];
	qreal normalVector[3] = { l[1] * r[2] - l[2] * r[1], l[2] * r[0] - l[0] * r[2], l[0] * r[1] - l[1] * r[0] };//平面法向量
																												//r = normalVector; //why this is error? todo

																												//参考系
	qreal corVec[2][3] = { { l[0], l[1], l[2] }
		,{ normalVector[1] * l[2] - normalVector[2] * l[1], normalVector[2] * l[0] - normalVector[0] * l[2], normalVector[0] * l[1] - normalVector[1] * l[0] }
	};

	//单位化参考系
	for (qreal(&point)[3] : corVec)
	{
		qreal length = qSqrt(point[0] * point[0] + point[1] * point[1] + point[2] * point[2]);
		point[0] /= length;
		point[1] /= length;
		point[2] /= length;
	}

	//在当前参考系下点的坐标值
	qreal vector2d[4][2] = { { 0 },{ qSqrt(l[0] * l[0] + l[1] * l[1] + l[2] * l[2]) / qSqrt(corVec[0][0] * corVec[0][0] + corVec[0][1] * corVec[0][1] + corVec[0][2] * corVec[0][2]) ,0 },{ 0 },{ 0 } };
	qreal(*v2d)[2] = (qreal(*)[2])vector2d[2];
	for (qreal(*vector)[3] = (qreal(*)[3])pointsVector[2]; vector < (qreal(*)[3])pointsVector[4]; ++vector)//qreal(&vector)[3] : pointsVector)
	{
		qreal matLValue[2][2] = {
			{ corVec[0][0], corVec[0][1] }
			,{ corVec[1][0], corVec[1][1] }
		};
		qreal matRValue[2][1] = { (*vector)[0], (*vector)[1] };
		mat L = mat((qreal *)matLValue, 2, 2);
		mat R = mat((qreal*)matRValue, 2, 1);

		mat Res = solve(L, R);

		(*v2d)[0] = Res.at(0, 0);
		(*v2d)[1] = Res.at(1, 0);
		++v2d;
	}

	//计算像素值
	QPixmap map = ui.widgetProjector->pixmap();

	QSize mapSize = map.size();
	qreal mm1Width = mapSize.width() / projectorWidth;
	//投影后不同位置对应的宽高对应的像素值不同，这里暂时只考虑宽度对应
	for (qreal(*vector)[2] = (qreal(*)[2])vector2d[0]; vector < (qreal(*)[2])vector2d[4]; ++vector)
	{
		(*vector)[0] *= mm1Width;
		(*vector)[1] *= mm1Width;
	}

	CvPoint2D32f srcTri[4], dstTri[4];
	CvMat*       warp_mat = cvCreateMat(3, 3, CV_32FC1);
	//	IplImage*    src = NULL;
	IplImage*    dst = NULL;

	QImage image = map.toImage();

	cv::Mat QImage2cvMat(QImage image);
	image.convertToFormat(QImage::Format_RGB32);
	cv::Mat mat = QImage2cvMat(image);
	IplImage src = IplImage(mat);//cvDecodeImage(&mat, 1);
								 // 	src = cvLoadImage("E:\\origpic.png");//("D:\\1.jpg");//("E:\\图像处理\\25.bmp");
	CvSize size;
	{
		qreal minW = 0, maxW = 0, minH = 0, maxH = 0;
		for (qreal(*vector)[2] = (qreal(*)[2])vector2d[0]; vector < (qreal(*)[2])vector2d[4]; ++vector)
		{
			if ((*vector)[0] > maxW)
			{
				maxW = (*vector)[0];
			}
			if ((*vector)[0] < minW)
			{
				minW = (*vector)[0];
			}

			if ((*vector)[1] > maxH)
			{
				maxH = (*vector)[1];
			}
			if ((*vector)[1] < minH)
			{
				minH = (*vector)[1];
			}
		}
		//坐标全部转为正
		if (minW < 0)
		{
			for (qreal(*vector)[2] = (qreal(*)[2])vector2d[0]; vector < (qreal(*)[2])vector2d[4]; ++vector)
			{
				(*vector)[0] += -minW;
			}
		}
		if (minH < 0)
		{
			for (qreal(*vector)[2] = (qreal(*)[2])vector2d[0]; vector < (qreal(*)[2])vector2d[4]; ++vector)
			{
				(*vector)[1] += -minH;
			}
		}
		size = CvSize(maxW - minW, maxH - minH);
	}
	//	size = CvSize(src.width, src.height);
	message += QString("size width:%1,height:%2").arg(size.width).arg(size.height);
	ui.textBrowser->setText(message);

	QRectF srcRect = image.rect();
	srcTri[0].x = srcRect.topLeft().x();
	srcTri[0].y = srcRect.topLeft().y();
	srcTri[1].x = srcRect.topRight().x();
	srcTri[1].y = srcRect.topRight().y();
	srcTri[2].x = srcRect.bottomLeft().x();
	srcTri[2].y = srcRect.bottomLeft().y();
	srcTri[3].x = srcRect.bottomRight().x();
	srcTri[3].y = srcRect.bottomRight().y();


	for (int i = 0; i < 4; ++i)
	{
		dstTri[i].x = vector2d[i][0];//srcTri[i].x;
		dstTri[i].y = vector2d[i][1];//srcTri[i].y;
	}
	while (size.width > 10000 || size.width > 10000)
	{
		size.width /= 10;
		size.height /= 10;
		for (CvPoint2D32f& po : dstTri)
		{
			po.x /= 10;
			po.y /= 10;
		}
	}

	dst = cvCreateImage(size, src.depth, src.nChannels);
	dst->origin = src.origin;
	cvZero(dst);

	cvGetPerspectiveTransform(srcTri, dstTri, warp_mat);
	cvWarpPerspective(&src, dst, warp_mat);

	QImage cvMat2QImage(const cv::Mat& mat);
	QImage imageto = cvMat2QImage(cv::cvarrToMat(dst));
	ui.widget_2->setPixmap(QPixmap::fromImage(imageto));
	update();
}

// cv::Mat QImage2cvMat(QImage image)
// {
// 	cv::Mat mat;
// 	qDebug() << image.format();
// 	switch (image.format())
// 	{
// 	case QImage::Format_ARGB32:
// 	case QImage::Format_RGB32:
// 	case QImage::Format_ARGB32_Premultiplied:
// 		mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
// 		break;
// 	case QImage::Format_RGB888:
// 		mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
// 		//cv::cvtColor(mat, mat, CV_BGR2RGB);
// 		break;
// 	case QImage::Format_Indexed8:
// 		mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
// 		break;
// 	}
// 	cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3);
// 	int from_to[] = { 0,0, 1,1, 2,2 };
// 	cv::mixChannels(&mat, 1, &mat2, 1, from_to, 3);
// 	return mat2;
// }

void ProjectConverter::invertProject()
{
	const qreal toRadian = M_PI / 180;

	qreal distance = ui.doubleSpinBoxDistanceToRealScreen->value();
	qreal angleX = ui.doubleSpinBoxRotateX->value()* toRadian;
	qreal angleY = ui.doubleSpinBoxRotateY->value()* toRadian;
	qreal angleZ = ui.doubleSpinBoxRotateZ->value()* toRadian;

	qreal tempValue = qCos(angleX)*qCos(angleX) + qCos(angleY)*qCos(angleY) + qCos(angleZ)*qCos(angleZ);
	if (qAbs(tempValue - 1) > 0.01)
	{
		QMessageBox::information(this, "Error", QString::fromLocal8Bit("α^2 + β^2 + γ^2 == 1"));
		return;
	}

	//plane x*cos(angleX) + y*cos(angleY) + z*cos(angleZ) = distance

	qreal projectorWidth = ui.doubleSpinBoxScreenWidth->value();
	qreal projectorHeight = ui.doubleSpinBoxScreenHeight->value();
	qreal projectorDis = ui.doubleSpinBoxDistanceToScreen->value();
	QRectF projectorRect(-projectorWidth / 2, -projectorHeight / 2, projectorWidth, projectorHeight);
	//line 
	QVector3D points[2] = { QVector3D(projectorRect.topLeft().x(),projectorRect.topLeft().y(), projectorDis )
		,QVector3D(projectorRect.topRight().x(),projectorRect.topRight().y(), projectorDis)};

	QVector3D topPoints[2] = {};
	{
		QVector3D*pointResult = &topPoints[0];
		//求直线和面的交点
		for (QVector3D&point : points)
		{
			//xcos(α)+xcos(β)+zcos(γ) = distance
			//x/x1 = y/y1 = z/z1 直线方程
			*pointResult = Calculator::intersectLinePlane(QVector3D(), point, angleX, angleY, angleZ, distance);
			pointResult++;
		}
	}

	//投影直线向量
	QVector3D horLine = topPoints[1] - topPoints[0];
	//平面法向量
	QVector3D vecPlane = QVector3D(qCos(angleX ) , qCos(angleY), qCos(angleZ));
	//向量叉乘得垂直直线向量
	QVector3D verLine = QVector3D::crossProduct(vecPlane, horLine);
	//{vecPlane[1] * horLine[2] - vecPlane[2] * horLine[1],vecPlane[2] * horLine[0] - vecPlane[0] * horLine[2],vecPlane[0] * horLine[1] - vecPlane[1] * horLine[0] };

	//单位化
	verLine /= verLine.length();
	
	//计算垂直向量
	QPixmap map = ui.widgetProjector->pixmap();
	QSize mapSize = map.size();
	qreal horLineLength = horLine.length();
	qreal verLineLength = horLineLength * mapSize.height() / mapSize.width();

	verLine[0] *= verLineLength;
	verLine[1] *= verLineLength;
	verLine[2] *= verLineLength;
	
	QVector3D bottomPoints[2] = { topPoints[0] + verLine, topPoints[1] + verLine };

	QVector3D proPoints[4] = { { points[0] },{ points[1]},{},{} };
	//求直线和面的交点
	{
		QVector3D*pointResult = &proPoints[2];
		for (QVector3D&point : bottomPoints)
		{
			//xcos(α)+xcos(β)+zcos(γ) = distance
			//x/x1 = y/y1 = z/z1 直线方程
			*pointResult = Calculator::intersectLinePlane(QVector3D(), point, M_PI/2, M_PI / 2, 0, projectorDis);
			pointResult++;
		}
	}


	QString message;
	for (QVector3D&point : proPoints)
	{
		message += QString("pos x:%1,y:%2,z:%3").arg(point[0]).arg(point[1]).arg(point[2]);
		message += '\n';
	}

//	qreal mm1Width = mapSize.width() / projectorWidth;
	//投影后不同位置对应的宽高对应的像素值不同，这里暂时只考虑宽度对应
//	for (qreal(*vector)[3] = (qreal(*)[3])proPoints[0]; vector < (qreal(*)[3])proPoints[4]; ++vector)
	{
//		(*vector)[0] *= mm1Width;
//		(*vector)[1] *= mm1Width;
	}
	qreal srcPoints[4][3] = { {}, {}, {}, {} };

	CvPoint2D32f srcTri[4], dstTri[4];
	CvMat*       warp_mat = cvCreateMat(3, 3, CV_32FC1);
	//	IplImage*    src = NULL;
	IplImage*    dst = NULL;

//	map = ui.widget_2->pixmap();
	QImage image = map.toImage();

	cv::Mat QImage2cvMat(QImage image);
	image.convertToFormat(QImage::Format_RGB32);
	cv::Mat mat = QImage2cvMat(image);
	IplImage src = IplImage(mat);//cvDecodeImage(&mat, 1);
								 // 	src = cvLoadImage("E:\\origpic.png");//("D:\\1.jpg");//("E:\\图像处理\\25.bmp");
	CvSize size;
	{
		qreal minW = 0, maxW = 0, minH = 0, maxH = 0;
		for (QVector3D*vector = &proPoints[0]; vector < &proPoints[4]; ++vector)
		{
			if ((*vector)[0] > maxW)
			{
				maxW = (*vector)[0];
			}
			if ((*vector)[0] < minW)
			{
				minW = (*vector)[0];
			}

			if ((*vector)[1] > maxH)
			{
				maxH = (*vector)[1];
			}
			if ((*vector)[1] < minH)
			{
				minH = (*vector)[1];
			}
		}
		//坐标全部转为正

		for (QVector3D*vector = &proPoints[0]; vector < &proPoints[4]; ++vector)
		{
			if (minW < 0)
				(*vector)[0] += -minW;

			if (minH < 0)
				(*vector)[1] += -minH;
		}
		
		size = CvSize(maxW - minW, maxH - minH);
	}
	//	size = CvSize(src.width, src.height);
	message += QString("size width:%1,height:%2").arg(size.width).arg(size.height);
	ui.textBrowser->setText(message);

	QRectF srcRect = image.rect();
	srcTri[0].x = srcRect.topLeft().x();//topPoints[0][0];//
	srcTri[0].y = srcRect.topLeft().y();//topPoints[0][1];//
	srcTri[1].x = srcRect.topRight().x();//topPoints[1][0];//
	srcTri[1].y = srcRect.topRight().y();//topPoints[1][1];//
	srcTri[2].x = srcRect.bottomLeft().x();//bottomPoints[0][0];//
	srcTri[2].y = srcRect.bottomLeft().y();//bottomPoints[0][1];//
	srcTri[3].x = srcRect.bottomRight().x();//bottomPoints[1][0];//
	srcTri[3].y = srcRect.bottomRight().y();//bottomPoints[1][1];//


	for (int i = 0; i < 4; ++i)
	{
		dstTri[i].x = proPoints[i][0];//srcTri[i].x;
		dstTri[i].y = proPoints[i][1];//srcTri[i].y;
	}
	while (size.width > 10000 || size.width > 10000)
	{
		size.width /= 10;
		size.height /= 10;
		for (CvPoint2D32f& po : dstTri)
		{
			po.x /= 10;
			po.y /= 10;
		}
	}

	dst = cvCreateImage(size, src.depth, src.nChannels);
	dst->origin = src.origin;
	cvZero(dst);

	cvGetPerspectiveTransform(srcTri, dstTri, warp_mat);
	cvWarpPerspective(&src, dst, warp_mat);

	QImage cvMat2QImage(const cv::Mat& mat);
	QImage imageto = cvMat2QImage(cv::cvarrToMat(dst));
	ui.widget_2->setPixmap(QPixmap::fromImage(imageto));
	update();
}

void ProjectConverter::swapPixmap()
{
	ui.widgetProjector->setPixmap(ui.widget_2->pixmap());
	ui.widget_2->setPixmap(QPixmap());
	update();
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
		qDebug() << "CV_8UC4";
		// Copy input Mat  
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat  
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}
}
cv::Mat QImage2cvMat(QImage image)
{
	cv::Mat mat;
	qDebug() << image.format();
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
	return mat;
}