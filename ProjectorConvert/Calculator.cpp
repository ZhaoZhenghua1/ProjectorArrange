#include "Calculator.h"
#include <QtMath>
#include <armadillo>
#include<cv.h>

QPair<QVector3D, QVector3D> Calculator::intersectLineBall(const QVector3D& pos1, const QVector3D& pos2, const QVector3D& posBall, qreal r)
{
	qreal xtp = pos2.x() - pos1.x();
	qreal ytp = pos2.y() - pos1.y();
	qreal ztp = pos2.z() - pos1.z();

	qreal x1 = pos1.x() - posBall.x();
	qreal y1 = pos1.y() - posBall.y();
	qreal z1 = pos1.z() - posBall.z();

	qreal sq = xtp*xtp + ytp*ytp + ztp*ztp;
	qreal eq = 2*xtp*x1 + 2*ytp*y1 + 2*ztp*z1;
	qreal co = x1*x1 + y1*y1 + z1*z1 - r*r;
	//直线与球无交点
	if (eq*eq - 4*sq*co < 0)
	{
		return{};
	}
	else
	{
		qreal t1 = (-eq - qSqrt(eq*eq - 4*sq*co))/(2*sq);
		qreal t2 = (-eq + qSqrt(eq*eq - 4 * sq*co)) / (2 * sq);
		QVector3D pos1(xtp*t1 + pos1.x(), ytp*t1 + pos1.y(), ztp*t1 + pos1.z());
		QVector3D pos2(xtp*t2 + pos1.x(), ytp*t2 + pos1.y(), ztp*t2 + pos1.z());
		return QPair<QVector3D, QVector3D>( pos1,pos2 );
	}
}

QPair<QVector3D, QVector3D> Calculator::intersectLinecylinder(const QVector3D& pos1, const QVector3D& pos2, const QVector3D& posBall, qreal r)
{
	qreal xtp = pos2.x() - pos1.x();
	qreal ytp = pos2.y() - pos1.y();
	qreal ztp = pos2.z() - pos1.z();

	qreal x1 = pos1.x() - posBall.x();
	qreal y1 = pos1.y() - posBall.y();
	qreal z1 = pos1.z() - posBall.z();

	qreal sq = xtp*xtp + ztp*ztp;
	qreal eq = 2 * xtp*x1 + 2 * ztp*z1;
	qreal co = x1*x1 + z1*z1 - r*r;
	//直线与球无交点
	if (eq*eq - 4 * sq*co < 0)
	{
		return{};
	}
	else
	{
		qreal t1 = (-eq - qSqrt(eq*eq - 4 * sq*co)) / (2 * sq);
		qreal t2 = (-eq + qSqrt(eq*eq - 4 * sq*co)) / (2 * sq);
		QVector3D pos1(xtp*t1 + pos1.x(), ytp*t1 + pos1.y(), ztp*t1 + pos1.z());
		QVector3D pos2(xtp*t2 + pos1.x(), ytp*t2 + pos1.y(), ztp*t2 + pos1.z());
		return QPair<QVector3D, QVector3D>(pos1, pos2);
	}
}

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
	return d2;
}

QVector3D Calculator::unitRefrence(const QVector3D& vector)
{
	qreal length = vector.length();
	return vector / length;
}

QVector<QPointF> Calculator::convertToXoYPoints(const QVector<QVector3D>& points3d)
{
// 	if (points3d.size() < 3)
// 	{
// 		return{};
// 	}
 	QVector<QVector3D> temp = points3d;
// 	for (auto ite = temp.rbegin(); ite != temp.rend(); ++ite)
// 	{
// 		(*ite) -= temp.first();
// 	}
	//平面法向量
// 	auto vector2 = temp.begin() + 2;
// 	while (isCollinear(temp[1], *vector2))
// 	{
// 		++vector2;
// 	}
//	QVector3D normalVector = QVector3D::crossProduct(temp[1], *vector2);

	//参考系
//	QVector3D vec2 = QVector3D::crossProduct(normalVector, temp[1]);
	QVector3D corVec[3] = { QVector3D(1,0,0), QVector3D(0,1,0), QVector3D(0,0,1) };
//	{ temp[1]
//		,vec2// { normalVector[1] * l[2] - normalVector[2] * l[1], normalVector[2] * l[0] - normalVector[0] * l[2], normalVector[0] * l[1] - normalVector[1] * l[0] }
//		,QVector3D::crossProduct(temp[1], vec2)
//	};

// 	//单位化参考系
// 	for (QVector3D &point : corVec)
// 	{
// 		point /= point.length();
// 	}

	//在当前参考系下点的坐标值
	QVector<QVector3D> vector3d;// = { QVector3D(0,0,0), QVector3D(temp[1].length() / corVec[0].length() ,0,0) };

	for (auto ite = temp.begin()/* + 2*/; ite != temp.end(); ++ite)
	{
		qreal matLValue[3][3] = {
			{ corVec[0][0], corVec[0][1], corVec[0][2] }
			,{ corVec[1][0], corVec[1][1], corVec[1][2] }
			,{ corVec[2][0], corVec[2][1], corVec[2][2] }
		};
		qreal matRValue[3] = { (*ite)[0], (*ite)[1], (*ite)[2] };
		arma::mat L = arma::mat((qreal *)matLValue, 3, 3);
		arma::mat R = arma::mat(matRValue, 3, 1);

		arma::mat Res = arma::solve(L, R);

		vector3d.push_back(QVector3D(Res.at(0, 0), Res.at(1, 0), Res.at(2, 0)));
	}
// 	QVector3D average;
// 	for (const QVector3D& point : vector3d)
// 	{
// 		average += QVector3D(qAbs(point.x()), qAbs(point.y()), qAbs(point.z()));
// 	}
// 	average /= vector3d.size();
// 	int castoff = (average[0] < average[1])? ((average[2] > average[0]) ? 0 : 2): ((average[2] > average[1]) ? 1 : 2);


	QVector<QPointF> ret;
	for (const QVector3D& point: vector3d)
	{
// 		switch (castoff)
// 		{
// 		case 0:
// 			ret.push_back(QPointF(point[1], point[2]));
// 			break;
// 		case 1:
// 			ret.push_back(QPointF(point[0], point[2]));
// 			break;
// 		case 2:
			ret.push_back(QPointF(point[0], point[1]));
//			break;
//		}
	}
	return ret;
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

bool Calculator::isCollinear(const QVector3D& l, const QVector3D& r)
{
	QVector3D k = QVector3D::crossProduct(l, r);
	if (qAbs(qAbs(k.x()) + qAbs(k.y()) + qAbs(k.z())) > 0.00001)
	{
		return false;
	}
	return true;
}
