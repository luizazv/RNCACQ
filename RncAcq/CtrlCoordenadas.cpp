
//---------------------------------------------------------------------------


#include "CtrlCoordenadas.h"
#include <boost/thread/thread.hpp> 

//---------------------------------------------------------------------------
CtrlCoordenadas::CtrlCoordenadas()
{
	//abre queue message do GPS para receber dados de GPS
//	mGpsQueue.InitConsumidor(NOME_CTRL_COORDENADAS_QUEUE);
}

//---------------------------------------------------------------------------
void CtrlCoordenadas::SentencaGps(string sentenca)
{

}

void CtrlCoordenadas::GetCoordenadas(COORDENADAS &dados)
{
	//não necessita sincronismo->as chamadas são em sequencia pelo
	//método NotifyObservers()
	dados = mdadosCoordenadas;
}

//---------------------------------------------------------------------------
void CtrlCoordenadas::ExecutaProcessamento()
{
	//processa estrutura GPSDATA

	//verifica se as sentenças estão presentes
	if(mgpsData.ParserGGA == true && mgpsData.ParserRMC == true)
	{
		//verifica se os dados da sentença RMC estão válidos
		if(mgpsData.receiverWarning == 'A')
		{
			//dados válidos
			mdadosCoordenadas.latitude = mgpsData.latitude.valor;
			mdadosCoordenadas.longitude = mgpsData.longitude.valor;
			mdadosCoordenadas.velocidade = mgpsData.velocidade;
		}
		else
		{
			//avisa interface gráfica que está sem sinal
		}
	}
	else
	{
		//avisa interface gráfica que não recebeu as sentenças 
	}
}

//---------------------------------------------------------------------------
bool CtrlCoordenadas::RecebeDadosGps()
{
	bool retval = false;

	//verifica se chegou algo no message queue do GPS
//	if(mGpsQueue.Receive(&mgpsData))
	{
		retval = true;
	}

	return retval;
}

void CtrlCoordenadas::Executa()
{
	mThread = boost::thread(Thread, this);  
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
			ExecutaProcessamento();
			//notifica observers
			NotifyObservers();
		}

		boost::this_thread::sleep(boost::posix_time::milliseconds(200));
	}
}
