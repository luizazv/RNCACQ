//---------------------------------------------------------------------------

#ifndef CtrlMarcoQuilometricoH
#define CtrlMarcoQuilometricoH

#include <string>
#include "Observer.h"
#include "CtrlCoordenadas.h"

using namespace std;

////// DADOS DA TERRA //////
// circunfer�ncia = 40.075 km
// circunfer�ncia nos tr�picos 23o27" = 36.784 km
// circunferencia no circulo polar = 15.992 km

const double RAIO_EARTH = 6378000;			// valor em metros
const double GRAUSTORAD = 0.0174532925199;	// rela��o para convers�o de graus para radianos
const double GPI_2 = 1.570796326;			// pi / 2
const double GPI = 3.141592653589;			// pi
const double GPDSGRAU = 3.09172;			// dist�ncia em metros na linha do equador de cada decimo de segundo de grau.			

//distancia para fazer a marca��o de marco autom�tico
#define DISTANCIA_PARA_MARCO_AUTOMATICO	1000

//distancia para avisar que o pr�ximo marco deve ser marcado parado
#define DISTANCIA_PARA_MARCO_PARADO	9500

struct MARCO
{
	long km;
	COORDENADAS coordenada;
};

class CtrlMarcoQuilometrico : public Observer
{
private:
	MARCO multimoMarco;
	MARCO mmarcoInicial;

	COORDENADAS mcoordenadaAnterior;
	double mdistanciaAcumulada;
	double mdistancia10Km;


	double ControleDeDistanciaDeMarco(COORDENADAS coordenadaAtual);
	double CalculaDistanciaHaversine(COORDENADAS ponto1, COORDENADAS ponto2);
	double ConverteGrausParaRadianos (double graus);
	void SalvarMarcoAtual(MARCO marco);
	void SalvarMarcoInicial(MARCO marco);

public:
	CtrlMarcoQuilometrico();
	
	void Notify(Subject *p);
};










//---------------------------------------------------------------------------
#endif
