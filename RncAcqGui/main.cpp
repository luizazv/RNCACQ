#include "mainwindow.h"
#include <QtWidgets/QApplication>


#define _RNCVS2010

#ifdef _RNCVS2010
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

void mainrnc();
#endif


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

#ifdef _RNCVS2010
//    mainrnc();
#endif

    return a.exec();
}
