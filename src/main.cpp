#include <QApplication>
#include "mainwindow.h"
#include <QTranslator>
#include <QFile>

int main(int argc, char** argv)
{
	QApplication app(argc,argv);

	QTranslator tslator;
	if (tslator.load("HostDetector_zh_CN.qm",QString("%1/translations").arg(QCoreApplication::applicationDirPath())))
	{
		app.installTranslator(&tslator);
	}

	MainWindow m;
	m.show();

	return app.exec();
}