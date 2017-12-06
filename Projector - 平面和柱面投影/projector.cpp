#include <QtMath>
#include "projector.h"
#include "PlaneWidget.h"
#include "GraphicsView.h"
#include "DragItem.h"
#include "CylinderWidget.h"

Projector::Projector(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_settings = new QSettings("projector.ini", QSettings::IniFormat, this);

	ui.protopleftLength->setValue(m_settings->value("Projector/protopleftLength").toInt());
	ui.protoprightLength->setValue(m_settings->value("Projector/protoprightLength").toInt());
	ui.prohorWidth->setValue(m_settings->value("Projector/prohorWidth").toInt());
	ui.probottomleftLength->setValue(m_settings->value("Projector/probottomleftLength").toInt());
	ui.rotate->setValue(m_settings->value("Projector/rotate").toInt());
	ui.proverWidth->setValue(m_settings->value("Projector/proverWidth").toInt());

	init();

	m_planewidget = new PlaneWidget(this);
	m_planewidget->setBrush(QBrush(QColor(0, 100, 100)));

	m_cylinderWidget = new CylinderWidget(this);
	m_cylinderWidget->init();
	m_cylinderWidget->setBrush(QBrush(QColor(0, 100, 100)));

	m_view= new GraphicsView;
	m_view->show();

	connect(ui.protopleftLength, &QAbstractSpinBox::editingFinished, [this]() {
		m_settings->setValue("Projector/protopleftLength", ui.protopleftLength->value());
	});
	connect(ui.protoprightLength, &QAbstractSpinBox::editingFinished, [this]() {
		m_settings->setValue("Projector/protoprightLength", ui.protoprightLength->value());
	});
	connect(ui.prohorWidth, &QAbstractSpinBox::editingFinished, [this]() {
		m_settings->setValue("Projector/prohorWidth", ui.prohorWidth->value());
	});
	connect(ui.probottomleftLength, &QAbstractSpinBox::editingFinished, [this]() {
		m_settings->setValue("Projector/probottomleftLength", ui.probottomleftLength->value());
	});
	connect(ui.rotate, &QAbstractSpinBox::editingFinished, [this]() {
		m_settings->setValue("Projector/rotate", ui.rotate->value());
	});
	connect(ui.proverWidth, &QAbstractSpinBox::editingFinished, [this]() {
		m_settings->setValue("Projector/proverWidth", ui.proverWidth->value());
	});
}

void Projector::init()
{
	ui.topleftLength->setValue(m_settings->value("Plane/topleftLength").toInt());
	ui.bottomrightLength->setValue(m_settings->value("Plane/bottomrightLength").toInt());
	ui.bottomleftLength->setValue(m_settings->value("Plane/bottomleftLength").toInt());

	void (QSpinBox::* spvalueChangedSig)(const QString&) = &QSpinBox::valueChanged;
	connect(ui.topleftLength, spvalueChangedSig, this, &Projector::project);
	connect(ui.bottomrightLength, spvalueChangedSig, this, &Projector::project);
	connect(ui.bottomleftLength, spvalueChangedSig, this, &Projector::project);
	connect(ui.rotate, spvalueChangedSig, this, &Projector::project);

	connect(ui.topleftLength, &QAbstractSpinBox::editingFinished, [this]() {
		m_settings->setValue("Plane/topleftLength", ui.topleftLength->value());
	});
	connect(ui.bottomrightLength, &QAbstractSpinBox::editingFinished, [this]() {
		m_settings->setValue("Plane/bottomrightLength", ui.bottomrightLength->value());
	});
	connect(ui.bottomleftLength, &QAbstractSpinBox::editingFinished, [this]() {
		m_settings->setValue("Plane/bottomleftLength", ui.bottomleftLength->value());
	});
}              

Projector::~Projector()
{

}

void Projector::project()
{
	statusBar()->clearMessage();
	switch(ui.tabWidget->currentIndex())
	{
	case 0:
		projectPlane();
		break;
	case 1:
		projectCylinder();
		break;
	case 2:
		projectBall();
		break;
	}
}

std::array<QVector3D, 4> Projector::proPoints()
{
	qreal topleftLen = ui.protopleftLength->value();
	qreal toprightLen = ui.protoprightLength->value();
	qreal horWidth = ui.prohorWidth->value();
	qreal x = (toprightLen*toprightLen - topleftLen*topleftLen - horWidth*horWidth) / (2 * horWidth);

	qreal bottomleftLen = ui.probottomleftLength->value();
	qreal verWidth = ui.proverWidth->value();
	qreal y = (bottomleftLen*bottomleftLen - topleftLen*topleftLen - verWidth*verWidth) / (2 * verWidth);

	qreal z = qSqrt(topleftLen*topleftLen - x*x - y*y);

	return{ QVector3D(x,y,z), QVector3D(x + horWidth, y, z),
		QVector3D(x, y + verWidth, z), QVector3D(x + horWidth,y + verWidth,z) };
}

void Projector::projectPlane()
{
	m_view->setRootItem(m_planewidget);

	m_planewidget->project();
}

void Projector::projectCylinder()
{
	m_view->setRootItem(m_cylinderWidget);
	m_cylinderWidget->project();
}

void Projector::projectBall()
{

}
