#include "Calculator.h"
#include <QtMath>
#include <armadillo>
#include<cv.h>

QVector3D Calculator::intersectLinePlane(const QVector3D& pos1, const QVector3D& pos2, qreal alpha, qreal beta, qreal gamma, qreal dis)
{
	//xcos(α)+xcos(β)+zcos(γ) = distance
	//x/x1 = y/y1 = z/z1 直线方程
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

	qreal matLValue2[3][3] = {
		{ matLValue[0][0],matLValue[1][0],matLValue[2][0] } ,
		{ matLValue[0][1],matLValue[1][1],matLValue[2][1] } ,
		{ matLValue[0][2],matLValue[1][2],matLValue[2][2] } };
	CvMat  *l = cvCreateMat(3, 3, CV_64FC1);
	cvSetData(l, matLValue2, CV_AUTOSTEP);

	CvMat  *r = cvCreateMat(3, 1, CV_64FC1);
	cvSetData(r, matRValue, CV_AUTOSTEP);

	CvMat  *result = cvCreateMat(3, 1, CV_64FC1);

	cvSolve(l, r, result, CV_LU);

	arma::mat Res = arma::solve(L, R);

	QVector3D d1 = QVector3D(result->data.db[0], result->data.db[1], result->data.db[2]);
	cvReleaseMat(&l);
	cvReleaseMat(&r);
	cvReleaseMat(&result);

	QVector3D d2 = QVector3D(Res.at(0, 0), Res.at(1, 0), Res.at(2, 0));
	return d1;
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
		(*ite) -= temp.first();
	}
	//平面法向量
	QVector3D normalVector = QVector3D::crossProduct(temp[1], temp[2]);

	//参考系
	QVector3D corVec[2] = { temp[1]
		,QVector3D::crossProduct(normalVector, temp[1])// { normalVector[1] * l[2] - normalVector[2] * l[1], normalVector[2] * l[0] - normalVector[0] * l[2], normalVector[0] * l[1] - normalVector[1] * l[0] }
	};

	//单位化参考系
	for (QVector3D &point : corVec)
	{
		point /= point.length();
	}

	//在当前参考系下点的坐标值
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
//坐标全部转为正
void Calculator::positivePoints(QVector<QPointF>& points)
{
	qreal minW = 0, minH = 0;
	for (auto ite = points.begin(); ite != points.end(); ++ite)
	{
		if ((*ite).x() < minW)
		{
			minW = (*ite).x();
		}

		if ((*ite).y() < minH)
		{
			minH = (*ite).y();
		}
	}
	//坐标全部转为正
	for (auto ite = points.begin(); ite != points.end(); ++ite)
	{
		if (minW < 0)
			(*ite) += QPointF(-minW,0);

		if (minH < 0)
			(*ite) += QPointF(0,-minH);
	}
}

void Calculator::positivePoints(QVector<QVector3D>& points)
{
	qreal minW = 0, minH = 0, minZ = 0;
	for (auto ite = points.begin(); ite != points.end(); ++ite)
	{
		if ((*ite).x() < minW)
		{
			minW = (*ite).x();
		}

		if ((*ite).y() < minH)
		{
			minH = (*ite).y();
		}

		if ((*ite).z() < minZ)
		{
			minZ = (*ite).z();
		}
	}
	//坐标全部转为正
	for (auto ite = points.begin(); ite != points.end(); ++ite)
	{
		if (minW < 0)
			(*ite) += QVector3D(-minW, 0, 0);

		if (minH < 0)
			(*ite) += QVector3D(0, -minH, 0);

		if (minZ < 0)
			(*ite) += QVector3D(0, 0, -minZ);
	}
}

QSizeF Calculator::size(const QVector<QPointF>& points)
{
	qreal minW = 0, maxW = 0, minH = 0, maxH = 0;
	for (auto ite = points.begin(); ite != points.end(); ++ite)
	{
		if ((*ite).x() > maxW)
		{
			maxW = (*ite).x();
		}
		if ((*ite).x() < minW)
		{
			minW = (*ite).x();
		}

		if ((*ite).y() > maxH)
		{
			maxH = (*ite).y();
		}
		if ((*ite).y() < minH)
		{
			minH = (*ite).y();
		}
	}
	return QSizeF(maxW - minW, maxH - minH);
}
