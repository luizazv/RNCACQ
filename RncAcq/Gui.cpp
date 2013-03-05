
#include "Gui.h"
#include "Gps.h"

#include "boost\thread.hpp"

//-----------------------------------------------------------------------------
Gui::Gui(CtrlCoordenadas *ctrl1, CtrlMarcoQuilometrico *ctrl2, CtrlPontosNotaveis *ctrl3)
{
	mctrlCoordenadas = ctrl1;
	mctrlMarcoQuilometrico = ctrl2;
	mctrlPontosNotaveis = ctrl3;

	//cria message queue com GPS
	mgpsQueue.InitProdutor(sizeof(GPSDATA), string(NOME_GPS_QUEUE));
}

//-----------------------------------------------------------------------------
Gui::~Gui()
{
}

//-----------------------------------------------------------------------------
int Gui::EventoQt()
{
	return -1;
}

//-----------------------------------------------------------------------------
void Gui::Run()
{
	//neste primeiro momento a GUI apenas configura a serial
	SERIALDATA gpsSerialData;

	gpsSerialData.acao = gpsSerialData.serOpen;
	gpsSerialData.baudrate = 4800;
	gpsSerialData.devName = "COM1";

	mgpsQueue.Send((char *)&gpsSerialData);

	while(1)
	{
		//verifica evento QT
		switch(EventoQt())
		{
		case 0:
			//evento para controle de coordenadas
		break;

		case 1:
			//evento para controle de marco quilometrico
			mctrlMarcoQuilometrico->EventoSalvarMarcoManual();
			break;
		case 2:
			break;
		}

		boost::this_thread::sleep(boost::posix_time::milliseconds(100));
	}
}

