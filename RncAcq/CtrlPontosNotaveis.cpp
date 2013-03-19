

#include "CtrlPontosNotaveis.h"
#include "LogMgr.h"
#include <istream>
#include <string>
#include <boost/timer/timer.hpp>

//---------------------------------------------------------------------------
CtrlPontosNotaveis::CtrlPontosNotaveis(Model *model)
{
	mmodel = model;
	mdadoGpsNovo = false;
}

//---------------------------------------------------------------------------
void CtrlPontosNotaveis::Notify(Subject *p)
{
	boost::lock_guard<boost::mutex> guard (gpsMutex);
	((CtrlCoordenadas *)p)->GetCoordenadas(mgpsData);
	mdadoGpsNovo = true;
}

//---------------------------------------------------------------------------
void CtrlPontosNotaveis::ProcessaPN(PN_DATA pnData)
{
	mpnData = pnData;

	switch(mpnData.pntipo)
	{
	case PN_INICIOPONTE:
		//deve estar parado
		if(mgpsData.velocidade != 0)
		{
			mmodel->GuiSendMsg("Velocidade Deve Ser Zero para Marcar Ponte!");
		}
		else
		{
			//marcar ponte no log durante 20 segundos leituras de gps
			mmodel->GuiSendMsg("Aguarde! Gravando Inicio de Ponte", TEMPO_LEITURA_DE_PONTO_NOTAVEL * 1000);
			boost::thread(Thread, this);  
		}
	break;

	case PN_FIMPONTE:
		//deve estar parado
		if(mgpsData.velocidade != 0)
		{
			mmodel->GuiSendMsg("Velocidade Deve Ser Zero para Marcar Ponte!");
		}
		else
		{
			//marcar ponte no log durante 20 segundos leituras de gps
			mmodel->GuiSendMsg("Aguarde! Gravando Fim de Ponte", TEMPO_LEITURA_DE_PONTO_NOTAVEL * 1000);
			boost::thread(Thread, this);  
		}
	break;


	case PN_INICIOTUNEL:
		//deve estar parado
		if(mgpsData.velocidade != 0)
		{
			mmodel->GuiSendMsg("Velocidade Deve Ser Zero para Marcar Tunel!");
		}
		else
		{
			//marcar ponte no log durante 20 segundos leituras de gps
			mmodel->GuiSendMsg("Aguarde! Gravando Inicio de tunel", TEMPO_LEITURA_DE_PONTO_NOTAVEL * 1000);
			boost::thread(Thread, this);  
		}
	break;


	case PN_FIMTUNEL:
		//deve estar parado
		if(mgpsData.velocidade != 0)
		{
			mmodel->GuiSendMsg("Velocidade Deve Ser Zero para Marcar Tunel!");
		}
		else
		{
			//marcar ponte no log durante 20 segundos leituras de gps
			mmodel->GuiSendMsg("Aguarde! Gravando Fim de Tunel", TEMPO_LEITURA_DE_PONTO_NOTAVEL * 1000);
			boost::thread(Thread, this);  
		}
	break;

	case PN_INICIOSB:
		//recebe dados da sb
		//deve estar parado
		if(mgpsData.velocidade != 0)
		{
			mmodel->GuiSendMsg("Velocidade deve ser zero para marcar SB!");
		}
		else
		{
			//marcar ponte no log durante 20 segundos leituras de gps
			mmodel->GuiSendMsg("Aguarde! Gravando Inicio de SB", TEMPO_LEITURA_DE_PONTO_NOTAVEL * 1000 );
			//dispara thread para marcaçao das coordenadas
			boost::thread(Thread, this);  

		}
	break;

	case PN_FIMSB:
		//deve estar parado
		if(mgpsData.velocidade != 0)
		{
			mmodel->GuiSendMsg("Velocidade deve ser zero para marcar ponte!");
		}
		else
		{
			//marcar ponte no log durante 20 segundos leituras de gps
			mmodel->GuiSendMsg("Aguarde! Gravando fim de SB", TEMPO_LEITURA_DE_PONTO_NOTAVEL * 1000);
			boost::thread(Thread, this);  
		}
	break;

	case PN_PASSAGEMNIVEL:
		SetPassagemNivel();
		mmodel->GuiSendMsg("Aguarde! Gravando Passagem de Nivel", 3000);
	break;
	}
}


//---------------------------------------------------------------------------
void CtrlPontosNotaveis::SetPassagemNivel()
{
	stringstream strgpsdado;

	COORDENADAS gpsData;
	
	if(GetCoordenadas(gpsData))
	{
		strgpsdado << "LATITUDE: " << gpsData.latitude << ", LONGITUDE: " << gpsData.longitude << ", ALTITUDE: " << gpsData.altitude;
	}
	else
	{
		strgpsdado << "COORDENADAS NAO DISPONIVEIS";
	}
	
	std::string header;

	header = strgpsdado.str();

	PN_DATA data;

	data.pntipo = PN_PASSAGEMNIVEL;

	mmodel->GuiPlota(gpsData, data);

	LogMgr::GetInstance()->Escreve("PN_PASSAGEMNIVEL", header);

}


//---------------------------------------------------------------------------
bool CtrlPontosNotaveis::GetCoordenadas(COORDENADAS &coordenadas)
{
	bool retval = false;

	boost::lock_guard<boost::mutex> guard (gpsMutex);
	if(mdadoGpsNovo)
	{
		retval = true;
		mdadoGpsNovo = false;
		coordenadas = mgpsData;
	}

	return retval;
}

//---------------------------------------------------------------------------
void CtrlPontosNotaveis::Thread(CtrlPontosNotaveis *p)
{
	p->Run();
}

//---------------------------------------------------------------------------
void CtrlPontosNotaveis::Run()
{
	stringstream strdado;
	string tag;
	COORDENADAS gpsData;

	switch(mpnData.pntipo)
	{
		case PN_INICIOSB:
			strdado << "SB: " << mpnData.Sb\
			<< ", INICIO TIPO: " << ((mpnData.pntipoinicio == PN_INICIO_MARCO) ? "PN_INICIO_MARCO" : ((mpnData.pntipoinicio == PN_DESVIO_ESQUERDA) ? "PN_DESVIO_ESQUERDA" : "PN_DESVIO_DIREITA"))\
			<< ", SENTIDO: " << ((mpnData.pnsentido == PN_CRESCENTE) ? "PN_CRESCENTE" : "PN_DECRESCENTE")\
			<< ", MARCO: " << mpnData.Marco << ", ";

			tag = "PN_INICIOSB";
		break;

		case PN_FIMSB:
			strdado << "SB: " << mpnData.Sb << ((mpnData.pnchave == PN_CHAVE_A_FRENTE) ? ", CHAVE: PN_CHAVE_A_FRENTE, " : "CHAVE: PN_SEM_CHAVE, ");
			tag = "PN_FIMSB";
		break;

		case PN_INICIOPONTE:
			tag = "PN_INICIOPONTE";
		break;

		case PN_FIMPONTE:
			tag = "PN_FIMPONTE";
		break;

		case PN_INICIOTUNEL:
			tag = "PN_INICIOTUNEL";
		break;
	
		case PN_FIMTUNEL:
			tag = "PN_FIMTUNEL";
		break;
	}

	std::string header1;

	header1 = strdado.str();


    boost::posix_time::ptime t1 = boost::posix_time::second_clock::local_time();

	mterminateThread = false;

	while(!mterminateThread)
	{
		if(mdadoGpsNovo)
		{
			if(GetCoordenadas(gpsData))
			{
				stringstream strgpsdado;
				strgpsdado << string("LATITUDE: ") << gpsData.latitude << ", LONGITUDE: " << gpsData.longitude << ", ALTITUDE: " << gpsData.altitude;

				std::string header2 = strgpsdado.str();

				LogMgr::GetInstance()->Escreve(tag, header1 + header2);
			}
		}

		//verifica se ultrapassou 20 segundos
	    boost::posix_time::ptime t2 = boost::posix_time::second_clock::local_time();
		boost::posix_time::time_duration diff = t2 - t1;

		if( diff.total_seconds() > TEMPO_LEITURA_DE_PONTO_NOTAVEL)
		{
			mterminateThread = true;
			//mostra ponto notavel na tela
			mmodel->GuiPlota(gpsData, mpnData);

		}
		else
		{
			//delay loop principal da thread
			boost::this_thread::sleep(boost::posix_time::milliseconds(600));
		}
	}
}