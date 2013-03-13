

#include "CtrlPontosNotaveis.h"
#include "LogMgr.h"
#include <istream>
#include <string>
#include <boost/timer/timer.hpp>

//---------------------------------------------------------------------------
CtrlPontosNotaveis::CtrlPontosNotaveis(Model *model)
{
	mmodel = model;
}

//---------------------------------------------------------------------------
void CtrlPontosNotaveis::Notify(Subject *p)
{
	//processamento de pontos notaveis
	((CtrlCoordenadas *)p)->GetCoordenadas(mgpsData);
}

//---------------------------------------------------------------------------
void CtrlPontosNotaveis::ProcessaPN(PN_DATA pnData)
{
	mpnData = pnData;

	switch(mpnData.pntipo)
	{
	case PN_INICIOPONTE:
	case PN_FIMPONTE:
		//deve estar parado
		if(mgpsData.velocidade != 0)
		{
			mmodel->SendMsg("Velocidade deve ser zero para marcar ponte!");
		}
		else
		{
			//marcar ponte no log durante 20 segundos leituras de gps
			mmodel->SendMsg("Aguarde! Marcando ponte");
		}
	break;

	case PN_INICIOTUNEL:
	case PN_FIMTUNEL:
		//deve estar parado
		if(mgpsData.velocidade != 0)
		{
			mmodel->SendMsg("Velocidade deve ser zero para marcar tunel!");
		}
		else
		{
			//marcar ponte no log durante 20 segundos leituras de gps
			mmodel->SendMsg("Aguarde! Marcando tunel");
		}
	break;

	case PN_INICIOSB:
		//recebe dados da sb
		//deve estar parado
		if(mgpsData.velocidade != 0)
		{
			mmodel->SendMsg("Velocidade deve ser zero para marcar ponte!");
		}
		else
		{
			//marcar ponte no log durante 20 segundos leituras de gps
			mmodel->SendMsg("Aguarde! Marcando ponte");
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
			mmodel->SendMsg("Aguarde! Marcando ponte");
		}
	break;

	case PN_MARCO:
	break;
	}
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
	stringstream strgpsdado;
	string tag;

	switch(mpnData.pntipo)
	{
		case PN_INICIOSB:
			strdado << "SB: " << mpnData.Sb
			<< "INICIO TIPO: " << ((mpnData.pntipoinicio == PN_INICIO_MARCO) ? "PN_INICIO_MARCO" : "PN_INICIO_CHAVE")
			<< "SENTIDO: " << ((mpnData.pnsentido == PN_CRESCENTE) ? "PN_CRESCENTE" : "PN_DECRESCENTE")
			<< " DESVIO:" << ((mpnData.pndesvio == PN_DESVIO_DIREITA) ? "PN_DESVIO_DIREITA" : "PN_DESVIO_ESQUERDA")
			<< "MARCO:" << mpnData.Marco;

			tag = "INICIOSB";
		break;

		case PN_FIMSB:
			strdado << "SB: " << mpnData.Sb << (mpnData.pnchave == PN_CHAVE_A_FRENTE) ? "PN_CHAVE_A_FRENTE" : "PN_SEM_CHAVE";
			tag = "FIMSB";
		break;

		case PN_INICIOPONTE:
			strdado << "PN_INICIOPONTE";
			tag = "PONTE";
		break;

		case PN_FIMPONTE:
			strdado << "PN_FIMPONTE";
			tag = "PONTE";
		break;

		case PN_INICIOTUNEL:
			strdado << "PN_INICIOTUNEL";
			tag = "TUNEL";
		break;
	
		case PN_FIMTUNEL:
			strdado << "PN_FIMTUNEL";
			tag = "TUNEL";
		break;
	}

	std::string header1;

	strdado >> header1;

	using boost::timer::cpu_timer;
	using boost::timer::cpu_times;
	using boost::timer::nanosecond_type;

	nanosecond_type const vinte_segundos(20 * 1000000000LL);
	cpu_timer timer;


	mterminateThread = false;

	while(!mterminateThread)
	{
		strgpsdado << string("LATITUDE:") << mgpsData.latitude << "LONGITUDE:" << mgpsData.longitude << endl;

		std::string header2;

		strgpsdado >> header2;

		LogMgr::GetInstance()->Escreve("PNINICIOSB", header1 + header2);

		//verifica se ultrapassou 20 segundos
		cpu_times const elapsed_times(timer.elapsed());
		nanosecond_type const elapsed(elapsed_times.system + elapsed_times.user);
		if (elapsed >= vinte_segundos)
		{
			mterminateThread = true;
		}
	}
}