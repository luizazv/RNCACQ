
//---------------------------------------------------------------------------


#include "CtrlCoordenadas.h"
#include <boost/thread/thread.hpp> 

//---------------------------------------------------------------------------
CtrlCoordenadas::CtrlCoordenadas(Model *model)
{
	mmodel = model;
	//abre queue message do GPS para receber dados de GPS
	mgpsQueue.InitConsumidor(NOME_CTRL_COORDENADAS_QUEUE);

	mThread = boost::thread(Thread, this);
}

//---------------------------------------------------------------------------
void CtrlCoordenadas::GetCoordenadas(COORDENADAS &dados)
{
	//não necessita sincronismo->as chamadas são em sequencia pelo
	//método NotifyObservers()
	dados = mdadosCoordenadas;
}

//---------------------------------------------------------------------------
bool CtrlCoordenadas::ExecutaProcessamento()
{
	bool retval = false;

	//processa estrutura GPSDATA

	//verifica se as sentenças estão presentes
	if(mgpsData.ParserGGA == true && mgpsData.ParserRMC == true)
	{
		//dados válidos
		mdadosCoordenadas.latitude = mgpsData.latitude.valor;
		mdadosCoordenadas.longitude = mgpsData.longitude.valor;
		mdadosCoordenadas.velocidade = mgpsData.velocidade;
		mdadosCoordenadas.altitude = mgpsData.altitude;

		retval = true;
	}

	return retval;
}

//---------------------------------------------------------------------------
bool CtrlCoordenadas::RecebeDadosGps()
{
	bool retval = false;

	//verifica se chegou algo no message queue do GPS
	message_queue mq(open_only, NOME_CTRL_COORDENADAS_QUEUE);

	size_t recvdSize;
	unsigned int prioridade;

	try
	{
		mq.receive(&mgpsData, sizeof(GPSDATA), recvdSize, prioridade);

		if(recvdSize > 0)
		{
			retval = true;
		}
	}
	catch(...)
	{
		retval = false;
	}

	return retval;
}

//---------------------------------------------------------------------------------
void CtrlCoordenadas::Thread(CtrlCoordenadas *p)
{
	p->Run();
}

//---------------------------------------------------------------------------
void CtrlCoordenadas::Run()
{
	//thread principal do controle de coordenadas
	while(1)
	{
		//executa processamento
		//verifica se recebeu dados de GPS
		if(RecebeDadosGps())
		{
			if(ExecutaProcessamento())
			{
				//plota na tela principal
				PN_DATA pn;
				pn.pntipo = PN_COORDENADAS;

				mmodel->GuiPlota(mdadosCoordenadas, pn);

				//notifica observers
				NotifyObservers();
			}
		}

		boost::this_thread::sleep(boost::posix_time::milliseconds(200));
	}
}
