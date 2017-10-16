

#include <QtWidgets/QApplication>
#include <QTranslator>
#include "MainWidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setWindowIcon(QPixmap(":/ProjectionSketch2D.ico"));
//	QTranslator* translator = new QTranslator;
//	bool loaded = translator->load(":/clipper_zh_CN.qm");
//	bool ret = a.installTranslator(translator);
	a.setFont(QFont(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"), 10));//Î¢ÈíÑÅºÚ 
	MainWidget view(argc > 1 ? argv[1] : "");
	view.show();
	

	return a.exec();
}
