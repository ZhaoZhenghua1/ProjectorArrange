#include "projector.h"
#include <QtWidgets/QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Projector w;
	w.show();
//	MainWindow mw;
//	mw.show();
	return a.exec();
}
