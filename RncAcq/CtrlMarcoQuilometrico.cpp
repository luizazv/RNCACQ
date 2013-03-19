//---------------------------------------------------------------------------
#include <boost/thread/thread.hpp> 
#include <boost/lexical_cast.hpp>
#include "CtrlMarcoQuilometrico.h"
#include "CtrlCoordenadas.h"
#include "LogMgr.h"
#include <fstream>

//-----------------------------------------------------------------------------
CtrlMarcoQuilometrico::CtrlMarcoQuilometrico(Model *model)
{
	mmodel = model;
	mmarcoAtual = 0;
	mmarcoAnterior = mmarcoAtual;
	mmarcoInicialGravado = false;
	mdistanciaMarcoAnterior = 0;
	mdistancia10Km = 0;
//	mthread = boost::thread(Thread, this);
}

//-----------------------------------------------------------------------------
void CtrlMarcoQuilometrico::SalvaMarcoAtual(int marco)
{
	mmarcoAtual = marco;
}

//-----------------------------------------------------------------------------
double CtrlMarcoQuilometrico::ConverteGrausParaRadianos (double graus)
{
	return (graus * GRAUSTORAD);
}

//-----------------------------------------------------------------------------
// Calcula distancia entre 2 pontos usando a fórmula de Haversine.
// Coordenadas devem ser passadas em décimos de segundo.
// ponto1 - coordenadas em décimo de segundo de grau do primeiro ponto
// ponto2 - coordenadas em décimo de segundo de grau do segundo ponto
// retval - distancia entre os dois pontos em metros.
double CtrlMarcoQuilometrico::CalculaDistanciaHaversine(COORDENADAS ponto1, COORDENADAS ponto2)
{
	// Converte coordenadas para décimos de grau.
	double	lat1, lat2, lon1, lon2;
	lat1 = (double)ponto1.latitude / 36000;
	lon1 = (double)ponto1.longitude / 36000;
	lat2 = (double)ponto2.latitude / 36000;
	lon2 = (double)ponto2.longitude / 36000;

	// Converte coordenadas para radianos.
	lat1 = ConverteGrausParaRadianos(lat1);
	lon1 = ConverteGrausParaRadianos(lon1);
	lat2 = ConverteGrausParaRadianos(lat2);
	lon2 = ConverteGrausParaRadianos(lon2);

	// Obtem diferença das latitude e longitudes dos pontos
	// dlon = lon2 - lon1
	// dlat = lat2 - lat1
	double dlat, dlon;
	dlat = fabs(lat2 - lat1);
	dlon = fabs(lon2 - lon1);

	// haversin(d/R) = a = sin^2(dlat/2) + cos(lat1) * cos(lat2) * sin^2(dlon/2)
	double haverSindR, raizHaverSindR, greatCircleDist;
	haverSindR = (sin(dlat / 2))*(sin(dlat / 2)) + (cos(lat1) * cos(lat2) * (sin(dlon/2)) * (sin(dlon/2)));
	// Proteção para número negativo
	if (haverSindR < 0.0)
	{
		raizHaverSindR = 0.0;		
	}
	else 
	{
		raizHaverSindR = sqrt(haverSindR);
	}

	// great circle distance in radians = c = 2 * arcsin(min(1,sqrt(a)))
	// d = R * c
	if (raizHaverSindR < 1.0)
	{
		greatCircleDist = 2 * asin(raizHaverSindR);
	}
	else
	{
		greatCircleDist = 2 * asin(1.0);
	}
	// Calcula a distância multiplicando pela média geométrica do raio da terra.
	return (greatCircleDist * RAIO_EARTH);
}

//---------------------------------------------------------------------------
void CtrlMarcoQuilometrico::Notify(Subject *p)
{
	static bool primeiracoordenada = true;
	COORDENADAS coord;

	//guarda coordenada->notificado pela thread ctrlCoordenadas
	((CtrlCoordenadas *)p)->GetCoordenadas(coord);


	boost::lock_guard <boost::mutex> guard (mqMutex);
	//adiciona no vetor de coordenadas
	vecCoord.push(coord);
	//thread de processamento de marco
	boost::thread(Thread, this);
}

//---------------------------------------------------------------------------
bool CtrlMarcoQuilometrico::GetCoordenadas(COORDENADAS &coordAtual, bool retiraDaFila)
{
	bool retval = false;

	boost::lock_guard <boost::mutex> guard (mqMutex);
	
	if(vecCoord.empty())
		retval = false;
	else
	{
		coordAtual = vecCoord.front();
		if(retiraDaFila)
		{
			vecCoord.pop();
		}
		retval = true;
	}

	return retval;
}

//---------------------------------------------------------------------------
int CtrlMarcoQuilometrico::GetNumCoordenadas()
{
	int retval = 0;

	boost::lock_guard <boost::mutex> guard (mqMutex);
	
	retval = vecCoord.size();

	return retval;
}

//---------------------------------------------------------------------------
void CtrlMarcoQuilometrico::ProcessaMQ(PN_DATA pnData)
{
	//envia para LogMgr gravar marco
	GravaMarco("PN_MARCO", pnData);
	mmodel->GuiSendMsg("Aguarde: Gravando Marco", 3000);
}

//---------------------------------------------------------------------------
void CtrlMarcoQuilometrico::GravaMarco(string tag, PN_DATA pnData)
{
	stringstream strgpsdado;
	bool coordDisponivel = false;
	COORDENADAS coord;

	//atualiza marco atual
	mmarcoAnterior = mmarcoAtual;

	if(GetNumCoordenadas() > 0)
	{
		//verificação de segurança, sempre haverá coordenada no buffer
		GetCoordenadas(coord, false);
		coordDisponivel = true;
	}

	stringstream(pnData.Marco) >> mmarcoAtual;

	strgpsdado << "MARCO: " << pnData.Marco;

	if(coordDisponivel)
	{
		strgpsdado << ", LATITUDE: " << coord.latitude << ", LONGITUDE: " << coord.longitude << ", ALTITUDE: " << coord.altitude;
	}
	else
	{
		strgpsdado << "COORDENADAS NAO DISPONIVEIS";
	}

	std::string header;

	header = strgpsdado.str();

	LogMgr::GetInstance()->Escreve(tag, header);

	mmodel->GuiPlota(coord, pnData);
}

//---------------------------------------------------------------------------
void CtrlMarcoQuilometrico::Thread(CtrlMarcoQuilometrico *ctrlMq)
{
	ctrlMq->Run();
}

//---------------------------------------------------------------------------
// ponto1 - coordenada do primeiro ponto em décimos de segundo de grau
// ponto2 - coordenada do segundo ponto em décimos de segundo de grau
// retval - distancia em metros entre os dois pontos.
double CtrlMarcoQuilometrico::ControleDeDistanciaDeMarco(COORDENADAS coordAtual, COORDENADAS coordAnterior)
{
	//calcula distancia entre duas coordenadas
	double distancia = 0;

	if(coordAtual.velocidade > 5)
	{
		//altera distancia apenas com velocidade->evita flutuações no sinal
		//alterando distancia
		distancia = CalculaDistanciaHaversine(coordAnterior, coordAtual);

		mdistanciaMarcoAnterior += distancia;
		mdistancia10Km += distancia;
	}

	//grava marco inicial
	if(mmarcoInicialGravado == false)
	{
		PN_DATA pn;

		pn.pntipo = PN_MARCOINICIAL;

		pn.Marco = boost::lexical_cast<std::string>(mmarcoAtual);

		//envia para LogMgr gravar marco
		GravaMarco("PN_MARCOINICIAL", pn);
		mmodel->GuiSendMsg("Aguarde: Gravando Marco Inicial", 3000);

		mmodel->GuiPlota(coordAtual, pn);

	
		mmarcoInicialGravado = true;
	}

	if(mdistanciaMarcoAnterior > DISTANCIA_PARA_MARCO_AUTOMATICO)
	{
		//efetuar marco automatico
		PN_DATA data;
		data.pntipo = PN_MARCOAUTOMATICO;
		data.Marco = boost::lexical_cast<std::string>(mmarcoAtual);

		//envia para LogMgr gravar marco
		GravaMarco("PN_MARCOAUTOMATICO", data);
		mmodel->GuiSendMsg("Aguarde: Gravando Marco Automatico", 3000);

		//zerar distancia para ultimo marco
		mdistanciaMarcoAnterior = 0;
	}

	if(mdistancia10Km > DISTANCIA_PARA_MARCO_PARADO)
	{
		//avisar GUI para parar no proximo marco
		mmodel->GuiSendMsg("ATENCAO: 10 Km SEM PARADA. PARAR NO PROXIMO MARCO PARA EFETUAR MEDICAO");
		//zerar distancia 10 km para parada (marcação de marco com vel = 0 a cada 10 Km)
		mdistancia10Km = 0;
	}
	

	return distancia;
}

//---------------------------------------------------------------------------
void CtrlMarcoQuilometrico::Run()
{
	//evita rodar duas instancias de thread ao mesmo tempo
	boost::lock_guard <boost::mutex> guard(mthreadMutex);

	//thread que controla marco automatico e aviso de parada a cada 10 Km
	COORDENADAS coordAtual;
	COORDENADAS coordAnterior;
	double distMarcoAnterior;
	
	while(GetNumCoordenadas() > 1)
	{
//		if(GetNumCoordenadas() > 1)
		{
			//pego coordenada anterior (ser houver mais de duas disponiveis)
			if(GetCoordenadas(coordAnterior, true))
			{
//				int Num = GetNumCoordenadas();
				//tento pegar a coordenada atual -> não retira da fila,
				//se torna anterior no proximo processamento
				if(GetCoordenadas(coordAtual, false))
				{
					//controle de distancias entre marcos
					distMarcoAnterior = ControleDeDistanciaDeMarco(coordAtual, coordAnterior);
					//atualizar na GUI a distancia para o proximo marco (decrescente)
					mmodel->GuiSetDistanciaProximoMarco((int)(1000 - mdistanciaMarcoAnterior));
				}
			}
		}
//		boost::this_thread::sleep(boost::posix_time::milliseconds(200));
	}
}
