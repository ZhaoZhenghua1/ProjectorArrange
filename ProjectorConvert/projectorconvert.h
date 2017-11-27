#ifndef PROJECTORCONVERT_H
#define PROJECTORCONVERT_H

#include <QtWidgets/QMainWindow>
#include "ui_projectorconvert.h"

class ProjectConverter;
class ProjectorConvert : public QMainWindow
{
	Q_OBJECT

public:
	ProjectorConvert(QWidget *parent = 0);
	~ProjectorConvert();

private:
	Ui::ProjectorConvertClass ui;
	ProjectConverter* m_converter = nullptr;
};

#endif // PROJECTORCONVERT_H
