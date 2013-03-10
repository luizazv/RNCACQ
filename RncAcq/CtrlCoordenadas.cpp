
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
	//n�o necessita sincronismo->as chamadas s�o em sequencia pelo
	//m�todo NotifyObservers()
	dados = mdadosCoordenadas;
}

//---------------------------------------------------------------------------
void CtrlCoordenadas::ExecutaProcessamento()
{
	//processa estrutura GPSDATA

	//verifica se as senten�as est�o presentes
	if(mgpsData.ParserGGA == true && mgpsData.ParserRMC == true)
	{
		//verifica se os dados da senten�a RMC est�o v�lidos
		if(mgpsData.receiverWarning == 'A')
		{
			//dados v�lidos
			mdadosCoordenadas.latitude = mgpsData.latitude.valor;
			mdadosCoordenadas.longitude = mgpsData.longitude.valor;
			mdadosCoordenadas.velocidade = mgpsData.velocidade;
		}
		else
		{
			//avisa interface gr�fica que est� sem sinal
		}
	}
	else
	{
		//avisa interface gr�fica que n�o recebeu as senten�as 
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
