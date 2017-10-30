#pragma once
#include <QVector3D>
#include <QVector>
#include <QSizeF>
class Calculator
{
public:
	//直线和平面的交点
	static QVector3D intersectLinePlane(const QVector3D& pos1, const QVector3D& pos2, qreal alpha, qreal beta, qreal gamma, qreal dis);
	//向量单位化
	static QVector3D unitRefrence(const QVector3D& vector);
	//将共面的3d坐标转换为2d坐标
	static QVector<QPointF> convertTo2dPoints(const QVector<QVector3D>& points3d);
	//坐标全部转为正
	static void positivePoints(QVector<QPointF>& points);
	static void positivePoints(QVector<QVector3D>& points);
	static QSizeF size(const QVector<QPointF>& points);
};

