//---------------------------------------------------------------------------

#include "CtrlMarcoQuilometrico.h"
#include "CtrlCoordenadas.h"


//-----------------------------------------------------------------------------
CtrlMarcoQuilometrico::CtrlMarcoQuilometrico()
{
	mmarcoInicial.coordenada.latitude = 0;
	mmarcoInicial.coordenada.longitude = 0;
	mmarcoInicial.km = 0;
	multimoMarco = mmarcoInicial;
}

//-----------------------------------------------------------------------------
void CtrlMarcoQuilometrico::SalvarMarcoInicial(MARCO marco)
{
	mmarcoInicial = marco;
}

//-----------------------------------------------------------------------------
void CtrlMarcoQuilometrico::SalvarMarcoAtual(MARCO marco)
{
	multimoMarco = marco;
}

//-----------------------------------------------------------------------------
void CtrlMarcoQuilometrico::EventoSalvarMarcoManual()
{
	//pega coordenadas atuais

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
// ponto1 - coordenada do primeiro ponto em décimos de segundo de grau
// ponto2 - coordenada do segundo ponto em décimos de segundo de grau
// retval - distancia em metros entre os dois pontos.
double CtrlMarcoQuilometrico::ControleDeDistanciaDeMarco(COORDENADAS coordenadaAtual)
{
	//calcula distancia entre duas coordenadas
	double distancia = CalculaDistanciaHaversine(mcoordenadaAnterior, coordenadaAtual);

	//atualiza coordenada
	mcoordenadaAnterior = coordenadaAtual;

	mdistanciaAcumulada += distancia;
	mdistancia10Km += distancia;

	if(mdistanciaAcumulada > DISTANCIA_PARA_MARCO_AUTOMATICO)
	{
		//efetuar marco automatico

		//zerar distancia para ultimo marco
		mdistanciaAcumulada = 0;
	}

	if(mdistanciaAcumulada > DISTANCIA_PARA_MARCO_PARADO)
	{
		//avisar GUI para parar no proximo marco

		//zerar distancia 10 km para parada (marcação de marco com vel = 0 a cada 10 Km)
		mdistancia10Km = 0;
	}

	return distancia;
}

//---------------------------------------------------------------------------
void CtrlMarcoQuilometrico::Notify(Subject *p)
{
	//processamento de marco->notificado pela thread ctrlCoordenadas
	((CtrlCoordenadas *)p)->GetCoordenadas(mcoordenadaAtual);
}
