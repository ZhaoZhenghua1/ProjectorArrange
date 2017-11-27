#include "ProjectConverter.h"
#include <QtMath>
#include <QMessageBox>
#include <QPainter>

#include<cv.h>
#include<highgui.h>

#include <QGenericMatrix>
#include <armadillo>
using namespace arma;
#include <QVector3D>

#include "Calculator.h"
#include "DestWidget.h"
#include "ui_PlaneSetting.h"
#include "ui_CylinderSettings.h"
#include "ui_BallSettings.h"
#include "StatusPoints.h"

class Plane : public QWidget, public Ui::Plane
{
public:
	Plane(QWidget* parent = nullptr):QWidget(parent)
	{
		setupUi(this);
	}
};

class Cylinder : public QWidget, public Ui::Cylinder
{
public:
	Cylinder(QWidget* parent = nullptr) :QWidget(parent)
	{
		setupUi(this);
	}
};

class Ball : public QWidget, public Ui::Ball
{
public:
	Ball(QWidget* parent = nullptr) :QWidget(parent)
	{
		setupUi(this);
	}
};

typedef QGenericMatrix<1, 3, float> QMatrix1x3;
typedef QGenericMatrix<3, 1, float> QMatrix3x1;

ProjectConverter::ProjectConverter()
{
	ui.setupUi(this);

	QVector<int> aa({ 0,1,0 });

//	ui.widgetProjector->setPixmap(m_map);
	m_dstWidget = new DestWidget;

	m_ball = new Ball;
	m_cylinder = new Cylinder;
	m_plane = new Plane;
	ui.layout->addWidget(m_ball);
	ui.layout->addWidget(m_cylinder);
	ui.layout->addWidget(m_plane);
	m_plane->hide();
//	m_ball->hide();
	m_cylinder->hide();
	void (QComboBox::* chengedSig)(const QString&) = &QComboBox::currentIndexChanged;
	connect(ui.comboBox, chengedSig, this, &ProjectConverter::onComboChanged);

	void (QSpinBox::* spvalueChangedSig)(const QString&) = &QSpinBox::valueChanged;
	void (QDoubleSpinBox::* dspvalueChangedSig)(const QString&) = &QDoubleSpinBox::valueChanged;

	connect(m_cylinder->spinBoxx, spvalueChangedSig, this, &ProjectConverter::inverseProject);
	connect(m_cylinder->spinBoxy, spvalueChangedSig, this, &ProjectConverter::inverseProject);
	connect(m_cylinder->spinBoxz, spvalueChangedSig, this, &ProjectConverter::inverseProject);
	connect(m_cylinder->spinBoxr, spvalueChangedSig, this, &ProjectConverter::inverseProject);
	connect(m_cylinder->spinBoxtheta, spvalueChangedSig, this, &ProjectConverter::inverseProject);
	connect(m_cylinder->spinBoxdelta, spvalueChangedSig, this, &ProjectConverter::inverseProject);
	connect(ui.spinBoxDisBelow, spvalueChangedSig, this, &ProjectConverter::inverseProject);
	connect(ui.spinBoxDisMid, spvalueChangedSig, this, &ProjectConverter::inverseProject);

	connect(m_cylinder->doubleSpinBoxRotateX, dspvalueChangedSig, this, &ProjectConverter::inverseProject);
	connect(m_cylinder->doubleSpinBoxRotateY, dspvalueChangedSig, this, &ProjectConverter::inverseProject);
	connect(m_cylinder->doubleSpinBoxRotateZ, dspvalueChangedSig, this, &ProjectConverter::inverseProject);
	connect(ui.doubleSpinBoxScreenWidth, dspvalueChangedSig, this, &ProjectConverter::inverseProject);
	connect(ui.doubleSpinBoxScreenHeight, dspvalueChangedSig, this, &ProjectConverter::inverseProject);
	connect(ui.doubleSpinBoxDistanceToScreen, dspvalueChangedSig, this, &ProjectConverter::inverseProject);

	connect(m_plane->doubleSpinBoxDistanceToRealScreen, dspvalueChangedSig, this, &ProjectConverter::inverseProject);
	connect(m_plane->doubleSpinBoxRotateX, dspvalueChangedSig, this, &ProjectConverter::inverseProject);
	connect(m_plane->doubleSpinBoxRotateY, dspvalueChangedSig, this, &ProjectConverter::inverseProject);
	connect(m_plane->doubleSpinBoxRotateZ, dspvalueChangedSig, this, &ProjectConverter::inverseProject);
}

ProjectConverter::~ProjectConverter()
{
}

void ProjectConverter::project()
{
	QString text = ui.comboBox->currentText();
	if (text == QString::fromLocal8Bit("平面"))
	{
		projectPlane();
	}
	else if (text == QString::fromLocal8Bit("柱面"))
	{
		cylinderpro(true);
	}
	else if (text == QString::fromLocal8Bit("球面"))
	{
		inversecylinderpro();
	}
}

void ProjectConverter::inverseProject()
{
	QString text = ui.comboBox->currentText();
	if (text == QString::fromLocal8Bit("平面"))
	{
		projectRodrigues();
	}
	else if (text == QString::fromLocal8Bit("柱面"))
	{
		inversecylinderpro();
	}
	else if (text == QString::fromLocal8Bit("球面"))
	{
		inverseballpro();
	}
}

void ProjectConverter::onComboChanged()
{
	QString text = ui.comboBox->currentText();
	m_plane->hide();
	m_ball->hide();
	m_cylinder->hide();
	if (text == QString::fromLocal8Bit("平面"))
	{
		m_plane->show();
	}
	else if (text == QString::fromLocal8Bit("柱面"))
	{
		m_cylinder->show();
	}
	else if (text == QString::fromLocal8Bit("球面"))
	{
		m_ball->show();
	}
}

void ProjectConverter::setSrc(const QVector<QVector<QVector3D>>& pointsC)
{
	QVector<QVector<QPointF>> points2d;
	for (const QVector<QVector3D>& vecs : pointsC)
	{
		QVector<QPointF> temp;
		for (const QVector3D& po : vecs)
		{
			temp.push_back({ po.x(), po.y() });
		}
		points2d.push_back(temp);
	}
	ui.widgetProjector->setPoints(points2d);
	ui.widgetProjector->update();
}

void ProjectConverter::setDst(const QVector<QVector<QPointF>>& pointsC)
{
	qreal projectorWidth = ui.doubleSpinBoxScreenWidth->value();
	qreal projectorHeight = ui.doubleSpinBoxScreenHeight->value();
	qreal projectorDis = ui.doubleSpinBoxDistanceToScreen->value();
	qreal projectorBelow = ui.spinBoxDisBelow->value();
	qreal projectorMid = ui.spinBoxDisMid->value();
	QRectF projectorRect(-projectorWidth / 2 + projectorMid,  projectorBelow - projectorHeight, projectorWidth, projectorHeight);

	QVector<QVector<QPointF>> result;
	for (const QVector<QPointF>& vec : pointsC)
	{
		QVector<QPointF> temp;
		for (const QPointF& po : vec)
		{
//			if (projectorRect.contains(po))
			{
				temp.push_back(po - projectorRect.topLeft());
			}
		}
		if (!temp.isEmpty())
		{
			result.push_back(temp);
		}
	}

	m_dstWidget->setRatio(QSizeF(projectorWidth, projectorHeight));
	m_dstWidget->setPoints(result);
	m_dstWidget->show();
	m_dstWidget->update();
}

void ProjectConverter::projectPlane()
{
	//plane x*cos(angleX) + y*cos(angleY) + z*cos(angleZ) = distance
	qreal projectorWidth = ui.doubleSpinBoxScreenWidth->value();
	qreal projectorHeight = ui.doubleSpinBoxScreenHeight->value();
	qreal projectorDis = ui.doubleSpinBoxDistanceToScreen->value();
	qreal projectorBelow = ui.spinBoxDisBelow->value();
	qreal projectorMid = ui.spinBoxDisMid->value();
	QRectF projectorRect(-projectorWidth / 2 + projectorMid, projectorHeight - projectorBelow, projectorWidth, projectorHeight);
	//line 
	QVector<QVector<QVector3D>> points;
	for (qreal x = projectorRect.left(); x <= projectorRect.right(); x += projectorRect.width() / 10.0)
	{
		QVector<QVector3D> temp;
		for (qreal y = projectorRect.top(); y <= projectorRect.bottom(); y += projectorRect.height() / 10.0)
		{
			temp.push_back(QVector3D(x, y, projectorDis));
		}
		points.push_back(temp);
	}
	setSrc(points);

	const qreal toRadian = M_PI / 180;
	qreal distance = m_plane->doubleSpinBoxDistanceToRealScreen->value();
	qreal angleX = m_plane->doubleSpinBoxRotateX->value() * toRadian;
	qreal angleY = m_plane->doubleSpinBoxRotateY->value() * toRadian;
	qreal angleZ = m_plane->doubleSpinBoxRotateZ->value() * toRadian;
	qreal tempValue = qCos(angleX)*qCos(angleX) + qCos(angleY)*qCos(angleY) + qCos(angleZ)*qCos(angleZ);
	if (qAbs(tempValue - 1) > 0.01)
	{
		QMessageBox::information(this, "Error", QString::fromLocal8Bit("α^2 + β^2 + γ^2 == 1"));
		return;
	}

	QVector<QVector<QVector3D>> pointsResult;
	//求直线和面的交点
	for (QVector<QVector3D>& vec : points)
	{
		QVector<QVector3D> temp;
		for (QVector3D&point : vec)
		{
			//xcos(α)+xcos(β)+zcos(γ) = distance
			//x/x1 = y/y1 = z/z1 直线方程
			temp.push_back(Calculator::intersectLinePlane(QVector3D(), point, angleX, angleY, angleZ, distance));
		}
		pointsResult.push_back(temp);
	}

	

// 	QString message;
// 	for (QVector3D&point : pointsResult)
// 	{
// 		message += QString("pos x:%1,y:%2,z:%3").arg(point.x()).arg(point.y()).arg(point.z());
// 		message += '\n';
// 	}
	QVector3D v1 = QVector3D(0, 0, 1);
	QVector3D v2 = QVector3D(qCos(angleX), qCos(angleY), qCos(angleZ));

	QVector3D k = QVector3D::crossProduct(v1, v2);
	//k is not zero
	if (qAbs(qAbs(k.x()) + qAbs(k.y()) + qAbs(k.z())) > 0.00001)
	{
		k /= k.length();

		qreal costheta = QVector3D::dotProduct(v1, v2) / (v1.length()*v2.length());
		qreal sintheta = qSqrt(1 - costheta*costheta);

		static const float d[9] = { 1.0, 0.0, 0.0 , 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
		static const QMatrix3x3 unitMatrix(d);
		const float kd[] = { k.x(), k.y(), k.z() };
		const float kd33[] = { 0, k.z(), -k.y(), -k.z(), 0, k.x(), k.y(), -k.x(), 0 };
		QMatrix3x3 R = (float)costheta * unitMatrix + (float)(1 - costheta)*QMatrix1x3(kd)*QMatrix3x1(kd) + (float)sintheta*QMatrix3x3(kd33);

		for (QVector<QVector3D>& vec : pointsResult)
		{
			for (QVector3D&point : vec)
			{
				QMatrix1x3 po = R*QMatrix1x3(&point[0]);
				point = QVector3D(po(0, 0), po(1, 0), po(2, 0));
			}
		}
	}

	QVector<QVector<QPointF>> vector2d;
	for (QVector<QVector3D>& vec : pointsResult)
	{
		vector2d.push_back(Calculator::convertToXoYPoints(vec));
	}
	

//	QSize size = Calculator::size(vector2d).toSize();
	
	//	size = CvSize(src.width, src.height);
//	message += QString("size width:%1,height:%2").arg(size.width()).arg(size.height());
//	ui.textBrowser->setText(message);

	setDst(vector2d);
}

//https://baike.baidu.com/item/%E7%BD%97%E5%BE%B7%E9%87%8C%E6%A0%BC%E6%97%8B%E8%BD%AC%E5%85%AC%E5%BC%8F/18878562?fr=aladdin
void ProjectConverter::projectRodrigues()
{
	//plane x*cos(angleX) + y*cos(angleY) + z*cos(angleZ) = distance
	qreal projectorWidth = ui.doubleSpinBoxScreenWidth->value();
	qreal projectorHeight = ui.doubleSpinBoxScreenHeight->value();
	qreal projectorDis = ui.doubleSpinBoxDistanceToScreen->value();
	qreal projectorBelow = ui.spinBoxDisBelow->value();
	qreal projectorMid = ui.spinBoxDisMid->value();
	QRectF projectorRect(-projectorWidth / 2 + projectorMid, projectorHeight - projectorBelow, projectorWidth, projectorHeight);
	//line 
	qreal distance = m_plane->doubleSpinBoxDistanceToRealScreen->value();
	QVector<QVector<QVector3D>> points;
	for (qreal x = projectorRect.left(); x <= projectorRect.right(); x += projectorRect.width() / 10.0)
	{
		QVector<QVector3D> temp;
		for (qreal y = projectorRect.top(); y <= projectorRect.bottom(); y += projectorRect.height() / 10.0)
		{
			temp.push_back(QVector3D(x, y, distance));
		}
		points.push_back(temp);
	}
	setSrc(points);

	const qreal toRadian = M_PI / 180;
//	qreal distance = ui.doubleSpinBoxDistanceToRealScreen->value();
	qreal angleX = m_plane->doubleSpinBoxRotateX->value() * toRadian;
	qreal angleY = m_plane->doubleSpinBoxRotateY->value() * toRadian;
	qreal angleZ = m_plane->doubleSpinBoxRotateZ->value() * toRadian;
	qreal tempValue = qCos(angleX)*qCos(angleX) + qCos(angleY)*qCos(angleY) + qCos(angleZ)*qCos(angleZ);
	if (qAbs(tempValue - 1) > 0.01)
	{
		QMessageBox::information(this, "Error", QString::fromLocal8Bit("α^2 + β^2 + γ^2 == 1"));
		return;
	}

	QVector3D v1 = QVector3D(0, 0, 1);
	QVector3D v2 = QVector3D(qCos(angleX), qCos(angleY), qCos(angleZ));

	QVector3D k = QVector3D::crossProduct(v2, v1);
	//k is not zero
	if (qAbs(qAbs(k.x()) + qAbs(k.y()) + qAbs(k.z())) > 0.00001)
	{
		k /= k.length();

		qreal costheta = QVector3D::dotProduct(v1, v2) / (v1.length()*v2.length());
		qreal sintheta = qSqrt(1 - costheta*costheta);

		static const float d[9] = { 1.0, 0.0, 0.0 , 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
		static const QMatrix3x3 unitMatrix(d);
		const float kd[] = { k.x(), k.y(), k.z() };
		const float kd33[] = { 0, k.z(), -k.y(), -k.z(), 0, k.x(), k.y(), -k.x(), 0 };
		QMatrix3x3 R = (float)costheta * unitMatrix + (float)(1 - costheta)*QMatrix1x3(kd)*QMatrix3x1(kd) + (float)sintheta*QMatrix3x3(kd33);

		for (QVector<QVector3D>& vec : points)
		{
			for (QVector3D&point : vec)
			{
				QMatrix1x3 po = R*QMatrix1x3(&point[0]);
				point = QVector3D(po(0, 0), po(1, 0), po(2, 0));
			}
		}
	}


	QVector<QVector<QVector3D>> pointsResult;
	//求直线和面的交点
	for (QVector<QVector3D>& vec : points)
	{
		QVector<QVector3D> temp;
		for (QVector3D&point : vec)
		{
			//xcos(α)+xcos(β)+zcos(γ) = distance
			//x/x1 = y/y1 = z/z1 直线方程
			temp.push_back(Calculator::intersectLinePlane(QVector3D(), point, M_PI / 2, M_PI / 2, 0, projectorDis));
		}
		pointsResult.push_back(temp);
	}



// 	QString message;
// 	for (QVector3D&point : pointsResult)
// 	{
// 		message += QString("pos x:%1,y:%2,z:%3").arg(point.x()).arg(point.y()).arg(point.z());
// 		message += '\n';
// 	}

	QVector<QVector<QPointF>> vector2d;
	for (QVector<QVector3D>& vec : pointsResult)
	{
		QVector<QPointF> temp = Calculator::convertToXoYPoints(vec);
		vector2d.push_back(temp);
	}

//	QSize size = Calculator::size(vector2d).toSize();

	//	size = CvSize(src.width, src.height);
//	message += QString("size width:%1,height:%2").arg(size.width()).arg(size.height());
//	ui.textBrowser->setText(message);

	setDst(vector2d);
	//	ui.widget_2->setPixmap(QPixmap::fromImage(imageto));
	//	update();
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

void ProjectConverter::invertProjectPlane()
{
	const qreal toRadian = M_PI / 180;

	qreal distance = m_plane->doubleSpinBoxDistanceToRealScreen->value();
	qreal angleX = m_plane->doubleSpinBoxRotateX->value()* toRadian;
	qreal angleY = m_plane->doubleSpinBoxRotateY->value()* toRadian;
	qreal angleZ = m_plane->doubleSpinBoxRotateZ->value()* toRadian;

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
	qreal projectorBelow = ui.spinBoxDisBelow->value();
	qreal projectorMid = ui.spinBoxDisMid->value();
	QRectF projectorRect(-projectorWidth / 2 + projectorMid, projectorHeight - projectorBelow, projectorWidth, projectorHeight);
	//line 
	QVector3D points[2] = { QVector3D(projectorRect.topLeft().x(),projectorRect.topLeft().y(), projectorDis )
		,QVector3D(projectorRect.topRight().x(),projectorRect.topRight().y(), projectorDis)};

	QVector<QVector3D> topPoints;
	//求直线和面的交点
	for (QVector3D&point : points)
	{
		//xcos(α)+xcos(β)+zcos(γ) = distance
		//x/x1 = y/y1 = z/z1 直线方程
		topPoints.push_back(Calculator::intersectLinePlane(QVector3D(), point, angleX, angleY, angleZ, distance));
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
	qreal horLineLength = horLine.length();
	qreal verLineLength = horLineLength * ui.doubleSpinBoxScreenHeight->value() / ui.doubleSpinBoxScreenWidth->value();

	verLine[0] *= verLineLength;
	verLine[1] *= verLineLength;
	verLine[2] *= verLineLength;
	
	QVector<QVector3D> bottomPoints = { topPoints[0] + verLine, topPoints[1] + verLine };

	QVector<QVector3D> proPoints = { { points[0] },{ points[1]}};
	//求直线和面的交点
	for (QVector3D&point : bottomPoints)
	{
		//xcos(α)+xcos(β)+zcos(γ) = distance
		//x/x1 = y/y1 = z/z1 直线方程
		proPoints.push_back(Calculator::intersectLinePlane(QVector3D(), point, M_PI / 2, M_PI / 2, 0, projectorDis));
	}

	QString message;
	for (QVector3D&point : proPoints)
	{
		message += QString("pos x:%1,y:%2,z:%3").arg(point[0]).arg(point[1]).arg(point[2]);
		message += '\n';
	}
	QVector<QPointF> pro2dPoints = Calculator::convertToXoYPoints(proPoints);
	Calculator::positivePoints(pro2dPoints);

//	qreal mm1Width = mapSize.width() / projectorWidth;
	//投影后不同位置对应的宽高对应的像素值不同，这里暂时只考虑宽度对应
//	for (qreal(*vector)[3] = (qreal(*)[3])proPoints[0]; vector < (qreal(*)[3])proPoints[4]; ++vector)
//	{
//		(*vector)[0] *= mm1Width;
//		(*vector)[1] *= mm1Width;
//	}
	QVector<QVector3D> srcPoints;
	srcPoints.append(topPoints);
	srcPoints.append(bottomPoints);
	QVector<QPointF> src2dPoints = Calculator::convertToXoYPoints(srcPoints);
	Calculator::positivePoints(src2dPoints);
	QSizeF src2dSize = Calculator::size(src2dPoints);

	CvPoint2D32f dstToScreen[4];
	QSizeF pro2dSize = Calculator::size(pro2dPoints);
	{
		for (int i = 0; i < 4; ++i)
		{
			dstToScreen[i].x = pro2dPoints[i].x();//srcTri[i].x;
			dstToScreen[i].y = pro2dPoints[i].y();//srcTri[i].y;
		}
		CvSize size = CvSize(pro2dSize.width() + 0.5, pro2dSize.height() + 0.5);
		while (size.width > 10000 || size.width > 10000)
		{
			size.width /= 10;
			size.height /= 10;
			for (CvPoint2D32f& po : dstToScreen)
			{
				po.x /= 10;
				po.y /= 10;
			}
		}
	}
}


void ProjectConverter::innerballpro()
{
	projectInnerBall();
}

void ProjectConverter::outterballpro()
{
	projectInnerBall(false);
}

void ProjectConverter::projectInnerBall(bool inner)
{
	qreal x1 = m_ball->spinBoxx->value();
	qreal y1 = m_ball->spinBoxy->value();
	qreal z1 = m_ball->spinBoxz->value();
	qreal r = m_ball->spinBoxr->value();

	qreal projectorWidth = ui.doubleSpinBoxScreenWidth->value();
	qreal projectorHeight = ui.doubleSpinBoxScreenHeight->value();
	qreal projectorDis = ui.doubleSpinBoxDistanceToScreen->value();
	qreal projectorBelow = ui.spinBoxDisBelow->value();
	qreal projectorMid = ui.spinBoxDisMid->value();
	QRectF projectorRect(-projectorWidth / 2 + projectorMid,  - projectorBelow, projectorWidth, projectorHeight);
	//line 
	QVector<QVector3D> points;
	for (qreal x = projectorRect.left(); x <= projectorRect.right(); x += projectorRect.width() / 10.0)
	{
		for (qreal y = projectorRect.top(); y <= projectorRect.bottom(); y += projectorRect.height() / 10.0)
		{
			points.push_back(QVector3D(x, y, projectorDis));
		}
	}
//	setSrc(points);

	const qreal toRadian = M_PI / 180;

	QVector<QVector3D> pointsResult;
	//求直线和面的交点
	for (QVector3D&point : points)
	{
		//xcos(α)+xcos(β)+zcos(γ) = distance
		//x/x1 = y/y1 = z/z1 直线方程
		QPair<QVector3D, QVector3D> collide = Calculator::intersectLineBall(QVector3D(), point, QVector3D(x1, y1, z1), r);
		pointsResult.push_back(inner ? collide.second : collide.first);
	}


	QString message;
	for (QVector3D&point : pointsResult)
	{
		message += QString("pos x:%1,y:%2,z:%3").arg(point.x()).arg(point.y()).arg(point.z());
		message += '\n';
	}
// 	QVector3D v1 = QVector3D(0, 0, 1);
// 	QVector3D v2 = QVector3D(qCos(angleX), qCos(angleY), qCos(angleZ));
// 
// 	QVector3D k = QVector3D::crossProduct(v1, v2);
// 	//k is not zero
// 	if (qAbs(qAbs(k.x()) + qAbs(k.y()) + qAbs(k.z())) > 0.00001)
// 	{
// 		k /= k.length();
// 
// 		qreal costheta = QVector3D::dotProduct(v1, v2) / (v1.length()*v2.length());
// 		qreal sintheta = qSqrt(1 - costheta*costheta);
// 
// 		static const float d[9] = { 1.0, 0.0, 0.0 , 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
// 		static const QMatrix3x3 unitMatrix(d);
// 		const float kd[] = { k.x(), k.y(), k.z() };
// 		const float kd33[] = { 0, k.z(), -k.y(), -k.z(), 0, k.x(), k.y(), -k.x(), 0 };
// 		QMatrix3x3 R = (float)costheta * unitMatrix + (float)(1 - costheta)*QMatrix1x3(kd)*QMatrix3x1(kd) + (float)sintheta*QMatrix3x3(kd33);
// 
// 		for (QVector3D&point : pointsResult)
// 		{
// 			QMatrix1x3 po = R*QMatrix1x3(&point[0]);
// 			point = QVector3D(po(0, 0), po(1, 0), po(2, 0));
// 		}
// 	}

	QVector<QPointF> vector2d = Calculator::convertToXoYPoints(pointsResult);

	QSize size = Calculator::size(vector2d).toSize();

	//	size = CvSize(src.width, src.height);
	message += QString("size width:%1,height:%2").arg(size.width()).arg(size.height());
//	ui.textBrowser->setText(message);

//	setDst(vector2d);
}

//生成单位球半球点阵
const qreal DIS = 5;
QVector<QVector<QVector3D>> createHalfBallPoints()
{
	//θ(-90~90) ，φ(0~180),r=1
	const qreal r = 1;
	const qreal toRadian = M_PI / 180;
	const qreal span = 2 * M_PI * r * DIS / 360;
	QVector<QVector<QVector3D>> ret;
	for (qreal thetaZ = 0; thetaZ <= 90; thetaZ += DIS)
	{
		qreal sinThetaZ = qSin(thetaZ * toRadian);
		qreal cosThetaZ = qCos(thetaZ * toRadian);

		QVector<QVector3D> temp;
		for (qreal thetaY = 0; thetaY <= 180; thetaY += DIS)
		{
			qreal sinThetaY = qSin(thetaY * toRadian);
			qreal cosThetaY = qCos(thetaY * toRadian);

			qreal sp = cosThetaZ*cosThetaZ + cosThetaY*cosThetaY;
			if (sp <= 1)
			{
				qreal posiX = qSqrt(1 - cosThetaZ*cosThetaZ - cosThetaY*cosThetaY);
				qreal nagaX = -posiX;

				temp.push_back(QVector3D(posiX, cosThetaY, cosThetaZ));
				temp.push_back(QVector3D(nagaX, cosThetaY, cosThetaZ));
			}
		}
		if (!temp.isEmpty())
		{
			ret.push_back(temp);
		}
	}
	return ret;
}

// QVector<QVector<QVector3D>> createHalfBallPoints()
// {
// 	//θ(-90~90) ，φ(0~180),r=1
// 	const qreal toRadian = M_PI / 180;
// 	const qreal span = 2 * M_PI*DIS / 360;
// 	QVector<QVector<QVector3D>> ret;
// 	for (qreal theta = 0; theta <= 90; theta += DIS)
// 	{
// 		qreal sinTheta = qSin(theta * toRadian);
// 		qreal cosTheta = qCos(theta * toRadian);
// 
// 		qreal rPhi = qAbs(sinTheta * 1);
// 		qreal phispan = span / (2 * M_PI*rPhi) * 360;
// 		QVector<QVector3D> temp;
// 		//for (qreal phi = 0; phi <= 360; phi += phispan)
// 		for (int n = 0; n < 360/phispan/2; ++n)
// 		{
// 			int arr[] = { 1,-1 };
// 			for (int a : arr)
// 			{
// 				qreal phi = 180 + a*n*phispan;
// 				qreal sinPhi = qSin(phi * toRadian);
// 				qreal cosPhi = qCos(phi * toRadian);
// 
// 				qreal x = sinTheta*cosPhi;
// 				qreal y = sinTheta*sinPhi;
// 				qreal z = cosTheta;
// 				temp.push_back(QVector3D(x, y, z));
// 				if (n == 0)
// 				{
// 					break;
// 				}
// 			}
// 
// 		}
// 		ret.push_back(temp);
// 	}
// 	return ret;
// }

void unitTo(QVector<QVector3D>& points, qreal radius)
{
	for (QVector3D& p : points)
	{
		p *= radius;
	}
}

void moveTo(QVector<QVector3D>& points, const QVector3D& pos)
{
	for (QVector3D& p : points)
	{
		p += pos;
	}
}

//http://blog.csdn.net/csxiaoshui/article/details/65446125
//将(0，0，1)旋转到vector
void rotate(QVector<QVector3D>& points, const QVector3D& vector)
{
	//绕Y轴旋转
	qreal lenY = qSqrt(vector.x()*vector.x() + vector.y()*vector.y() + vector.z()*vector.z());
	qreal cosThetaY = qSqrt(vector.y()*vector.y() + vector.z()*vector.z()) / lenY;
	qreal sinThetaY = -vector.x() / lenY;
	float rotateY[] = { cosThetaY,0, -sinThetaY,0,1,0,sinThetaY,0,cosThetaY };
	QMatrix3x3 ry(rotateY);

	//绕X轴旋转
	qreal lenX = qSqrt(vector.y()*vector.y() + vector.z()*vector.z());
	qreal cosThetaX = vector.z() / lenX;
	qreal sinThetaX = -vector.y() / lenX;
	float rotateX[] = { 1,0,0,0,cosThetaX,-sinThetaX,0,sinThetaX,cosThetaX };
	QMatrix3x3 rx(rotateX);
	for (QVector3D& point : points)
	{
		float pd[] = { point.x(), point.y(), point.z() };
		QMatrix1x3 point13(pd);
		QMatrix1x3 ret = rx*ry*point13;
		point = { ret(0,0), ret(1,0), ret(2,0) };
	}
}
enum ROTATETYPE
{
	eX,eY,eZ
};
void rotate(QVector<QVector3D>& points, ROTATETYPE t, const qreal angle)
{
	QMatrix3x3 rm;
	switch (t)
	{
	case eX:
	{
		float farr[] = { 1,0,0,  0,qCos(angle),qSin(angle),  0,-qSin(angle),qCos(angle) };
		rm = QMatrix3x3(farr);
		break;
	}
	case eY:
	{
		float farr[] = { qCos(angle),0,-qSin(angle) ,0,1,0,  qSin(angle),0,qCos(angle) };
		rm = QMatrix3x3(farr);
		break;
	}
	case eZ:
	{
		float farr[] = { qCos(angle),qSin(angle),0  ,-qSin(angle),qCos(angle),0, 0,0,1 };
		rm = QMatrix3x3(farr);
		break;
	}
	default:
		return;
	}
	for (QVector3D& point : points)
	{
		float pd[] = { point.x(), point.y(), point.z() };
		QMatrix1x3 point13(pd);
		QMatrix1x3 ret = rm*point13;
		point = { ret(0,0), ret(1,0), ret(2,0) };
	}
}

void ProjectConverter::inverseballpro()
{
	const qreal toRadian = M_PI / 180;
	qreal x1 = m_ball->spinBoxx->value();
	qreal y1 = m_ball->spinBoxy->value();
	qreal z1 = m_ball->spinBoxz->value();
	qreal r = m_ball->spinBoxr->value();
	qreal theta = m_ball->spinBoxtheta->value()*toRadian;
	qreal phi = m_ball->spinBoxphi->value()*toRadian;
	qreal delta = m_ball->spinBoxdelta->value()*toRadian;
	
//	{

	//创建所有半球点阵
	QVector<QVector<QVector3D>> points = createHalfBallPoints();
	for (QVector<QVector3D>& t : points)
	{
		unitTo(t, r);
		moveTo(t, QVector3D(x1, y1, z1));
		rotate(t, QVector3D(x1, y1, z1));
	}
//	}

// 	QVector<QVector3D> points;
// 	for (int i = 0; i <= 10; ++i)
// 	{
// 		qreal costheta = qCos(theta + i * delta);
// 		for (int j = 0; j <= 10 ; ++j)
// 		{
// 			qreal tanphi = qTan(phi + j*delta);
// 			qreal z = costheta*r;
// 			qreal x = -qSqrt((r*r - z*z) / (1 + tanphi*tanphi));
// 			qreal y = tanphi*x;
// 			points.push_back(QVector3D(x + x1, y + y1, z + z1));
// 		}
// 	}
	//line 

	setSrc(points);

	//求直线和面的交点
	for (QVector<QVector3D>& vec : points)
	{
		for (QVector3D&point : vec)
		{
			//xcos(α)+xcos(β)+zcos(γ) = distance
			//x/x1 = y/y1 = z/z1 直线方程
			point = Calculator::intersectLinePlane(QVector3D(), point, M_PI / 2, M_PI / 2, 0, ui.doubleSpinBoxDistanceToScreen->value());
		}
	}


	QVector<QVector<QPointF>> vector2d;
	for (QVector<QVector3D>& vec : points)
	{
		QVector<QPointF> vec2d = Calculator::convertToXoYPoints(vec);
		vector2d.push_back(vec2d);
	}
	

//	QSize size = Calculator::size(vector2d).toSize();

	//	size = CvSize(src.width, src.height);
//	message += QString("size width:%1,height:%2").arg(size.width()).arg(size.height());
//	ui.textBrowser->setText(message);

	setDst(vector2d);
}

void ProjectConverter::cylinderpro(bool inner)
{
	qreal x1 = m_cylinder->spinBoxx->value();
	qreal y1 = m_cylinder->spinBoxy->value();
	qreal z1 = m_cylinder->spinBoxz->value();
	qreal r = m_cylinder->spinBoxr->value();

	qreal projectorWidth = ui.doubleSpinBoxScreenWidth->value();
	qreal projectorHeight = ui.doubleSpinBoxScreenHeight->value();
	qreal projectorDis = ui.doubleSpinBoxDistanceToScreen->value();
	qreal projectorBelow = ui.spinBoxDisBelow->value();
	qreal projectorMid = ui.spinBoxDisMid->value();
	QRectF projectorRect(-projectorWidth / 2 + projectorMid, -projectorBelow, projectorWidth, projectorHeight);
	//line 
	QVector<QVector3D> points;
	for (qreal x = projectorRect.left(); x <= projectorRect.right(); x += projectorRect.width() / 10.0)
	{
		for (qreal y = projectorRect.top(); y <= projectorRect.bottom(); y += projectorRect.height() / 10.0)
		{
			points.push_back(QVector3D(x, y, projectorDis));
		}
	}
//	setSrc(points);

	const qreal toRadian = M_PI / 180;

	QVector<QVector3D> pointsResult;
	//求直线和面的交点
	for (QVector3D&point : points)
	{
		//xcos(α)+xcos(β)+zcos(γ) = distance
		//x/x1 = y/y1 = z/z1 直线方程
		QPair<QVector3D, QVector3D> collide = Calculator::intersectLinecylinder(QVector3D(), point, QVector3D(x1, y1, z1), r);
		pointsResult.push_back(inner ? collide.second : collide.first);
	}


	QString message;
	for (QVector3D&point : pointsResult)
	{
		message += QString("pos x:%1,y:%2,z:%3").arg(point.x()).arg(point.y()).arg(point.z());
		message += '\n';
	}

	QVector<QPointF> vector2d = Calculator::convertToXoYPoints(pointsResult);

	QSize size = Calculator::size(vector2d).toSize();

	//	size = CvSize(src.width, src.height);
	message += QString("size width:%1,height:%2").arg(size.width()).arg(size.height());
//	ui.textBrowser->setText(message);

//	setDst(vector2d);
}

void ProjectConverter::innercylinderpro()
{
	cylinderpro(true);
}

void ProjectConverter::outtercylinderpro()
{
	cylinderpro(false);
}

void ProjectConverter::inversecylinderpro()
{
	const qreal toRadian = M_PI / 180;
	qreal x1 = m_cylinder->spinBoxx->value();
	qreal y1 = m_cylinder->spinBoxy->value();
	qreal z1 = m_cylinder->spinBoxz->value();
	qreal r = m_cylinder->spinBoxr->value();
	qreal theta = m_cylinder->spinBoxtheta->value()*toRadian;
	qreal delta = m_cylinder->spinBoxdelta->value()*toRadian;


	QVector<QVector<QVector3D>> points;
	for (int i = 0; i <= 10; ++i)
	{
		qreal costheta = qCos(theta + i * delta);
		qreal sintheta = qSin(theta + i*delta);
		qreal deltay = delta / (M_PI*2) * 2 * M_PI*r;
		qreal x = r*costheta;
		qreal z = r*sintheta;

		QVector<QVector3D> temp;
		for (int j = 0; j <= 10; ++j)
		{
			qreal y = j*deltay;
			temp.push_back(QVector3D(x , y , z ));
		}
		points.push_back(temp);
	} 

	qreal angleX = m_cylinder->doubleSpinBoxRotateX->value() * toRadian;
	qreal angleY = m_cylinder->doubleSpinBoxRotateY->value() * toRadian;
	qreal angleZ = m_cylinder->doubleSpinBoxRotateZ->value() * toRadian;
	for (QVector<QVector3D>& vec : points)
	{
		if (qAbs(angleX) > 0.1)
		{
			rotate(vec, eX, angleX);
		}
		if (qAbs(angleY) > 0.1)
		{
			rotate(vec, eY, angleY);
		}
		if (qAbs(angleZ) > 0.1)
		{
			rotate(vec, eZ, angleZ);
		}
	}
	for (QVector<QVector3D>& vec : points)
	{
		moveTo(vec, QVector3D(x1, y1, z1));
	}

	//line 

	setSrc(points);

	QVector<QVector<QVector3D>> pointsResult;
	//求直线和面的交点
	for (QVector<QVector3D>& vec : points)
	{
		QVector<QVector3D> temp;
		for (QVector3D&point : vec)
		{
			//xcos(α)+xcos(β)+zcos(γ) = distance
			//x/x1 = y/y1 = z/z1 直线方程
			QVector3D collide = Calculator::intersectLinePlane(QVector3D(), point, M_PI / 2, M_PI / 2, 0, ui.doubleSpinBoxDistanceToScreen->value());
			temp.push_back(collide);
		}
		pointsResult.push_back(temp);
	}



// 	QString message;
// 	for (QVector3D&point : pointsResult)
// 	{
// 		message += QString("pos x:%1,y:%2,z:%3").arg(point.x()).arg(point.y()).arg(point.z());
// 		message += '\n';
// 	}


	QVector<QVector<QPointF>> vector2d;
	for (QVector<QVector3D>& vec : pointsResult)
	{
		QVector<QPointF> temp = Calculator::convertToXoYPoints(vec);

		vector2d.push_back(temp);
	}
	

	//	size = CvSize(src.width, src.height);
//	message += QString("size width:%1,height:%2").arg(size.width()).arg(size.height());
//	ui.textBrowser->setText(message);

	setDst(vector2d);
}
