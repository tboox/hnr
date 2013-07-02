#include <QtGui/QApplication>
#include "mainwindow.h"
//#include <QCleanlooksStyle>
#include <QWindowsXPStyle>

int main(int argc, char *argv[])
{
	//QApplication::setStyle(new QCleanlooksStyle);
	QApplication::setStyle(new QWindowsXPStyle);

    QApplication a(argc, argv);
	qApp->addLibraryPath(qApp->applicationDirPath () + "/plugins");
    MainWindow w;
    w.show();
    return a.exec();
}
