#pragma once
#include <QVector3D>
#include <QVector>
class Calculator
{
public:
	//ֱ�ߺ�ƽ��Ľ���
	static QVector3D intersectLinePlane(const QVector3D& pos1, const QVector3D& pos2, qreal alpha, qreal beta, qreal gamma, qreal dis);
	//������λ��
	static QVector3D unitRefrence(const QVector3D& vector);
	//�������3d����ת��Ϊ2d����
	static QVector<QPointF> convertTo2dPoints(const QVector<QVector3D>& points3d);
};

