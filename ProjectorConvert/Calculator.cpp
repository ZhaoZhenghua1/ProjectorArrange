#include "Calculator.h"
#include <QtMath>
#include <armadillo>

QVector3D Calculator::intersectLinePlane(const QVector3D& pos1, const QVector3D& pos2, qreal alpha, qreal beta, qreal gamma, qreal dis)
{
	//xcos(��)+xcos(��)+zcos(��) = distance
	//x/x1 = y/y1 = z/z1 ֱ�߷���
	qreal matLValue[3][3] = {
		{ qCos(alpha), pos2.y() - pos1.y(), 0 } ,
		{ qCos(beta), -(pos2.x() - pos1.x()), -(pos2.z() - pos1.z()) } ,
		{ qCos(gamma), 0, pos2.y() - pos1.y() } };
	if (qAbs(pos1.y() - pos2.y()) < 0.00001)
	{
		matLValue[0][1] = pos2.z() - pos1.z();
		matLValue[1][1] = 0;
		matLValue[2][1] = -(pos2.x() - pos1.x());

		matLValue[0][2] = 0;
		matLValue[1][2] = 1;
		matLValue[2][2] = pos1.y();
	}
	qreal matRValue[3] = { dis, (pos2.y() - pos1.y())*pos1.x() - (pos2.x() - pos1.x())*pos1.y(), (pos2.y() - pos1.y())*pos1.z() - (pos2.z() - pos1.z())*pos1.y() };
	arma::mat L = arma::mat((qreal *)matLValue, 3, 3);
	arma::mat R = arma::mat((qreal*)matRValue, 3, 1);

	arma::mat Res = arma::solve(L, R);

	return QVector3D(Res.at(0, 0),Res.at(1, 0), Res.at(2, 0));
}

QVector3D Calculator::unitRefrence(const QVector3D& vector)
{
	qreal length = vector.length();
	return vector / length;
}

QVector<QPointF> Calculator::convertTo2dPoints(const QVector<QVector3D>& points3d)
{
	if (points3d.size() < 3)
	{
		return{};
	}
	QVector<QVector3D> temp = points3d;
	for (auto ite = temp.rbegin(); ite != temp.rend(); ++ite)
	{
		(*ite) -= temp.first;
	}
	//ƽ�淨����
	QVector3D normalVector = QVector3D::crossProduct(temp[1], temp[2]);

	//�ο�ϵ
	QVector3D corVec[2] = { temp[1]
		,QVector3D::crossProduct(normalVector, temp[1])// { normalVector[1] * l[2] - normalVector[2] * l[1], normalVector[2] * l[0] - normalVector[0] * l[2], normalVector[0] * l[1] - normalVector[1] * l[0] }
	};

	//��λ���ο�ϵ
	for (QVector3D &point : corVec)
	{
		point /= point.length();
	}

	//�ڵ�ǰ�ο�ϵ�µ������ֵ
	QVector<QPointF> vector2d = { QPointF(0,0), QPointF(temp[1].length() / corVec[0].length() ,0) };
	
	for (auto ite = temp.begin() + 2; ite != temp.end(); ++ite)
	{
		qreal matLValue[2][2] = {
			{ corVec[0][0], corVec[0][1] }
			,{ corVec[1][0], corVec[1][1] }
		};
		qreal matRValue[2] = { (*ite)[0], (*ite)[1] };
		arma::mat L = arma::mat((qreal *)matLValue, 2, 2);
		arma::mat R = arma::mat(matRValue, 2, 1);

		arma::mat Res = arma::solve(L, R);

		vector2d.push_back(QPointF(Res.at(0, 0), Res.at(1, 0)));
	}
	return vector2d;
}
