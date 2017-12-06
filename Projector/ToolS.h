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
//原点到srcPoint的直线，与面ABCD的焦点
QVector3D destPoint(const QVector3D& srcPoint, qreal A, qreal B, qreal C, qreal D);


