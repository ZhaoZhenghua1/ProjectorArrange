#include "projectorconvert.h"
#include "ProjectConverter.h"
#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
#include <QStandardPaths>

ProjectorConvert::ProjectorConvert(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ProjectConverter* converter = new ProjectConverter;
	m_converter = converter;
	setCentralWidget(converter);

	QAction* action = nullptr;// = menuBar()->addAction("set map");
//	connect(action, &QAction::triggered, this, &ProjectorConvert::onSetPixmap);
	
	action = menuBar()->addAction("project");
	connect(action, &QAction::triggered, converter, &ProjectConverter::project);

	action = menuBar()->addAction("inverse project");
	connect(action, &QAction::triggered, converter, &ProjectConverter::invertProject);

	action = menuBar()->addAction("move dst to projector");
	connect(action, &QAction::triggered, converter, &ProjectConverter::swapPixmap);
}

ProjectorConvert::~ProjectorConvert()
{

}

void ProjectorConvert::onSetPixmap()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Set reference picture"), QStandardPaths::writableLocation(QStandardPaths::PicturesLocation), "Images (*.png *.xpm *.jpg);");
	if (!fileName.isEmpty())
	{
		m_converter->setPixmap(fileName);
	}
}
