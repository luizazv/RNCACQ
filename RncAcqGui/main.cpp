#include "mainwindow.h"
#include <QtWidgets/QApplication>


//#define _WORK_VS2010

#ifdef _WORK_VS2010
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif


int main(int argc, char *argv[])
{
	
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
