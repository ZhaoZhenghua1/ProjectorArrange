#pragma once
#include <QPointF>
#include <QVector3D>

template<class Point>
struct NetNode
{
	Point point3d;
	NetNode* l = nullptr, *t = nullptr, *r = nullptr, *b = nullptr;
};

typedef NetNode<QPointF> PointFNode;
typedef NetNode<QVector3D> Vector3dNode;