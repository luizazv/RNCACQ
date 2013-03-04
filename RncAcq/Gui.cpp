
#include "Gui.h"
#include "Gps.h"

#include "boost\thread.hpp"

//-----------------------------------------------------------------------------
Gui::Gui()
{
	//cria message queue com GPS
	mgpsQueue.InitProdutor(sizeof(GPSDATA), string(NOME_GPS_QUEUE));
}

//-----------------------------------------------------------------------------
Gui::~Gui()
{
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
		//para teste pode executar outras atividades aqui
		boost::this_thread::sleep(boost::posix_time::milliseconds(2000));
	}
}

