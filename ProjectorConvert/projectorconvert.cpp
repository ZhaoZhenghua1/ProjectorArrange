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
	connect(action, &QAction::triggered, converter, &ProjectConverter::inverseProject);

// 	action = menuBar()->addAction("inner ball pro");
// 	connect(action, &QAction::triggered, converter, &ProjectConverter::innerballpro);
// 
// 	action = menuBar()->addAction("out ball pro");
// 	connect(action, &QAction::triggered, converter, &ProjectConverter::outterballpro);
// 
// 	action = menuBar()->addAction("inverse ball pro");
// 	connect(action, &QAction::triggered, converter, &ProjectConverter::inverseballpro);
// 
// 	action = menuBar()->addAction("inner cylinder pro");
// 	connect(action, &QAction::triggered, converter, &ProjectConverter::innercylinderpro);
// 
// 	action = menuBar()->addAction("out cylinder pro");
// 	connect(action, &QAction::triggered, converter, &ProjectConverter::outtercylinderpro);
// 	
// 	action = menuBar()->addAction("inversecylinderpro");
// 	connect(action, &QAction::triggered, converter, &ProjectConverter::inversecylinderpro);
}

ProjectorConvert::~ProjectorConvert()
{

}