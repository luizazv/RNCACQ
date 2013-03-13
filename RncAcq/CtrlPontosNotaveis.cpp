

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
			mmodel->SendMsg("Velocidade Deve Ser Zero para Marcar Ponte!");
		}
		else
		{
			//marcar ponte no log durante 20 segundos leituras de gps
			mmodel->SendMsg("Aguarde! Marcando Inicio de Ponte", TEMPO_LEITURA_DE_PONTO_NOTAVEL * 1000);
			boost::thread(Thread, this);  
		}
	break;

	case PN_FIMPONTE:
		//deve estar parado
		if(mgpsData.velocidade != 0)
		{
			mmodel->SendMsg("Velocidade Deve Ser Zero para Marcar Ponte!");
		}
		else
		{
			//marcar ponte no log durante 20 segundos leituras de gps
			mmodel->SendMsg("Aguarde! Marcando Fim de Ponte", TEMPO_LEITURA_DE_PONTO_NOTAVEL * 1000);
			boost::thread(Thread, this);  
		}
	break;


	case PN_INICIOTUNEL:
		//deve estar parado
		if(mgpsData.velocidade != 0)
		{
			mmodel->SendMsg("Velocidade Deve Ser Zero para Marcar Tunel!");
		}
		else
		{
			//marcar ponte no log durante 20 segundos leituras de gps
			mmodel->SendMsg("Aguarde! Marcando Inicio de tunel", TEMPO_LEITURA_DE_PONTO_NOTAVEL * 1000);
			boost::thread(Thread, this);  
		}
	break;


	case PN_FIMTUNEL:
		//deve estar parado
		if(mgpsData.velocidade != 0)
		{
			mmodel->SendMsg("Velocidade Deve Ser Zero para Marcar Tunel!");
		}
		else
		{
			//marcar ponte no log durante 20 segundos leituras de gps
			mmodel->SendMsg("Aguarde! Marcando Fim de Tunel", TEMPO_LEITURA_DE_PONTO_NOTAVEL * 1000);
			boost::thread(Thread, this);  
		}
	break;

	case PN_INICIOSB:
		//recebe dados da sb
		//deve estar parado
		if(mgpsData.velocidade != 0)
		{
			mmodel->SendMsg("Velocidade deve ser zero para marcar SB!");
		}
		else
		{
			//marcar ponte no log durante 20 segundos leituras de gps
			mmodel->SendMsg("Aguarde! Marcando Inicio de SB", TEMPO_LEITURA_DE_PONTO_NOTAVEL * 1000 );
			//dispara thread para marcaçao das coordenadas
			boost::thread(Thread, this);  

		}
	break;

	case PN_FIMSB:
		//deve estar parado
		if(mgpsData.velocidade != 0)
		{
			mmodel->SendMsg("Velocidade deve ser zero para marcar ponte!");
		}
		else
		{
			//marcar ponte no log durante 20 segundos leituras de gps
			mmodel->SendMsg("Aguarde! Marcando fim de SB", TEMPO_LEITURA_DE_PONTO_NOTAVEL * 1000);
			boost::thread(Thread, this);  
		}
	break;

	case PN_MARCO:
		SetMarco();
		mmodel->SendMsg("Marcando Marco", 4);
	break;

	case PN_MARCOAUTOMATICO:
		SetMarco();
		mmodel->SendMsg("Marcando Marco Automatico", 4);
	break;
	case PN_PASSAGEMNIVEL:
		SetPassagemNivel();
		mmodel->SendMsg("Marcando Passagem de Nivel", 4);
	}
}

//---------------------------------------------------------------------------
void CtrlPontosNotaveis::SetMarco()
{
	stringstream strgpsdado;
	COORDENADAS gpsData = GetDadosGps();

	strgpsdado << string("LATITUDE:") << gpsData.latitude << "LONGITUDE:" << gpsData.longitude;

	std::string header;

	strgpsdado >> header;

	LogMgr::GetInstance()->Escreve(mpnData.pntipo == PN_MARCOAUTOMATICO ? "PN_MARCOAUTOMATICO" : "PN_MARCO", header);
}

//---------------------------------------------------------------------------
void CtrlPontosNotaveis::SetPassagemNivel()
{
	stringstream strgpsdado;
	COORDENADAS gpsData = GetDadosGps();

	strgpsdado << string("LATITUDE:") << gpsData.latitude << "LONGITUDE:" << gpsData.longitude;

	std::string header;

	strgpsdado >> header;

	LogMgr::GetInstance()->Escreve(mpnData.pntipo == PN_MARCOAUTOMATICO ? "PN_MARCOAUTOMATICO" : "PN_MARCO", header);
}


//---------------------------------------------------------------------------
COORDENADAS CtrlPontosNotaveis::GetDadosGps()
{
	boost::lock_guard<boost::mutex> guard (gpsMutex);
	mdadoGpsNovo = false;
	return mgpsData;
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

	switch(mpnData.pntipo)
	{
		case PN_INICIOSB:
			strdado << "SB: " << mpnData.Sb\
			<< ", INICIO TIPO: " << ((mpnData.pntipoinicio == PN_INICIO_MARCO) ? "PN_INICIO_MARCO" : "PN_INICIO_CHAVE")\
			<< ", SENTIDO: " << ((mpnData.pnsentido == PN_CRESCENTE) ? "PN_CRESCENTE" : "PN_DECRESCENTE")\
			<< ", DESVIO: " << ((mpnData.pndesvio == PN_DESVIO_DIREITA) ? "PN_DESVIO_DIREITA" : "PN_DESVIO_ESQUERDA")\
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
			COORDENADAS gpsData = GetDadosGps();

			stringstream strgpsdado;
			strgpsdado << string("LATITUDE: ") << gpsData.latitude << ", LONGITUDE: " << gpsData.longitude;

			std::string header2 = strgpsdado.str();

			LogMgr::GetInstance()->Escreve(tag, header1 + header2);
		}

		//verifica se ultrapassou 20 segundos
	    boost::posix_time::ptime t2 = boost::posix_time::second_clock::local_time();
		boost::posix_time::time_duration diff = t2 - t1;
		if( diff.total_seconds() > TEMPO_LEITURA_DE_PONTO_NOTAVEL)
		{
			mterminateThread = true;
		}
		else
		{
			//delay loop principal da thread
			boost::this_thread::sleep(boost::posix_time::milliseconds(600));
		}
	}
}