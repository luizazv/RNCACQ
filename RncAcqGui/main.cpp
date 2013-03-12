#include "mainwindow.h"
#include <QtWidgets/QApplication>

#include "c:/dados/projetos daiken/rncacq/rncacq/Model.h"

//#define _WORK_VS2010

#ifdef _EXECUTANDO_VS2010
//elimina a janela do console
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif


int main(int argc, char *argv[])
{
	
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
