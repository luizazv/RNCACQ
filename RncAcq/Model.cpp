
#include "Model.h"
#include "MVP.h"
#include "Gps.h"

//-----------------------------------------------------------------------------
Model::Model()
{
	mgps = new Gps();
}

//-----------------------------------------------------------------------------
void Model::ModelIniciaGps(std::string InterfaceSerial)
{
	//neste primeiro momento a GUI apenas configura a serial
	SERIALDATA gpsSerialData;

	gpsSerialData.acao = gpsSerialData.serOpen;
	gpsSerialData.baudrate = 4800;

	//testar OS-> se Windows = "COMX", outros "/tty...
	//esta versão é para windows
	//retira numero da serial
	unsigned int pos = InterfaceSerial.find(' ');

	if(pos != string::npos)
	{
		//retira numero da serial
		string Numero = InterfaceSerial.substr(pos + 1);
		string com = "COM";
		com += Numero;

		((Gps *)mgps)->Inicia(com);
	}

}

void Model::ModelIniciarCaptura()
{
}

void Model::ModelPausarCaptura()
{
}

void Model::ModelTerminarCaptura()
{
}
