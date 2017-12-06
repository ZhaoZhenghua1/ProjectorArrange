#pragma once

#include<cv.h>
#include<highgui.h>
#include <QImage>
#include <QVector3D>
#include <QGenericMatrix>

typedef QGenericMatrix<1, 3, float> QMatrix1x3;
typedef QGenericMatrix<3, 1, float> QMatrix3x1;

cv::Mat QImage2cvMat(QImage image);
QImage cvMat2QImage(const cv::Mat& mat);
//ԭ�㵽srcPoint��ֱ�ߣ�����ABCD�Ľ���
QVector3D destPoint(const QVector3D& srcPoint, qreal A, qreal B, qreal C, qreal D);


