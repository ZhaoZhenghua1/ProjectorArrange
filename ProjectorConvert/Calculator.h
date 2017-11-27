#pragma once
#include <QVector3D>
#include <QVector>
#include <QSizeF>
class Calculator
{
public:
	//ֱ�ߺ�ƽ��Ľ���
	static QVector3D intersectLinePlane(const QVector3D& pos1, const QVector3D& pos2, qreal alpha, qreal beta, qreal gamma, qreal dis);

	static QPair<QVector3D, QVector3D> intersectLineBall(const QVector3D& pos1, const QVector3D& pos2, const QVector3D& posBall, qreal r);

	static QPair<QVector3D, QVector3D> intersectLinecylinder(const QVector3D& pos1, const QVector3D& pos2, const QVector3D& posBall, qreal r);
	//������λ��
	static QVector3D unitRefrence(const QVector3D& vector);
	//�������3d����ת��Ϊ2d����
	static QVector<QPointF> convertToXoYPoints(const QVector<QVector3D>& points3d);
	//����ȫ��תΪ��
	static void positivePoints(QVector<QPointF>& points);
	static void positivePoints(QVector<QVector3D>& points);
	static QSizeF size(const QVector<QPointF>& points);
	static bool isCollinear(const QVector3D& l, const QVector3D& r);
};

