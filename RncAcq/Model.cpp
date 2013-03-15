
#include "Model.h"
#include "MVP.h"
#include "Gps.h"
#include "LogMgr.h"
#include "CtrlCoordenadas.h"
#include "CtrlPontosNotaveis.h"
#include "CtrlMarcoQuilometrico.h"

//-----------------------------------------------------------------------------
Model::Model(IView *view)
{
	mview = view;
	mgps = new Gps(this);
	mlogmgr = LogMgr::GetInstance();
	mctrlCoord = new CtrlCoordenadas(this);
	mctrlPN = new CtrlPontosNotaveis(this);
	mctrlMQ = new CtrlMarcoQuilometrico(this);
	//registra os observers de controle coordenadas
	((CtrlCoordenadas *)mctrlCoord)->RegisterObserver((Observer *)mctrlPN);
	((CtrlCoordenadas *)mctrlCoord)->RegisterObserver((Observer *)mctrlMQ);
}

//-----------------------------------------------------------------------------
void Model::GuiErroGpsFalhaSentenca()
{
	mview->ErroGpsFalhaSentenca();
}

//-----------------------------------------------------------------------------
void Model::GuiErroGpsSentencaInvalida()
{
	//avisa erros do GPS para janela principal
	mview->ErroGpsSentencaInvalida();
}

//-----------------------------------------------------------------------------
void Model::GuiSentencaOk()
{
	mview->SentencaOk();
}

//-----------------------------------------------------------------------------
void Model::GuiErroGps()
{
	//avisa GUI->erro geral
	mview->ErroGps();
}

//-----------------------------------------------------------------------------
void Model::GuiSetHdop(float valor)
{
	//transforma o valor entre 0 e 48->vermelho
	//entre 49 e 75-> amarelo
	//acima de 75->verde

	//hdop entre 0 e 4 -> verde
	//hdop entre 4.1 e 6->amarelo
	//hdop > 6 = vermelho

	int y;

	if(valor < 4)
	{
		//entre 100 e 75 y=100-6.25.x
		y = (int)( 100 - 6.25F * valor );
	}
	else if(valor > 4 && valor < 6)
	{
		//entre 75 e 49 y=127-13x
		y = (int)( 127 - 13.0F * valor );
	}
	else
	{
		//mantenho a mesma reta
		y = (int)( 127 - 13.0F * valor );
		if(y < 0)
		{
			y = 0;
		}
	}

	mview->SetHdop(y);
}

//-----------------------------------------------------------------------------
void Model::GuiSendMsg(const char *msg, int timer)
{
	mview->SendMsg(msg, timer);
}

//-----------------------------------------------------------------------------
void Model::GuiSetDistanciaProximoMarco(int distancia)
{
	mview->SetDistanciaProximoMarco(distancia);
}

//-----------------------------------------------------------------------------
void Model::GuiPlota(COORDENADAS coord)
{
	mview->Plota(coord);
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

void Model::ModelPausarCaptura()
{
}

void Model::ModelTerminarCaptura()
{
	((Gps *)mgps)->Termina();
}


void Model::ModelProcessaPN(PN_DATA pn)
{
	((CtrlPontosNotaveis *)mctrlPN)->ProcessaPN(pn);
}

void Model::ModelProcessaMQ(PN_DATA pn)
{
	((CtrlMarcoQuilometrico *)mctrlMQ)->ProcessaMQ(pn);
}

void Model::ModelSalvaMarcoAtual(int marco)
{
	((CtrlMarcoQuilometrico *)mctrlMQ)->SalvaMarcoAtual(marco);
}

