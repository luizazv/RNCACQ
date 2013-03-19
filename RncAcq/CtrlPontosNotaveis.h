
#ifndef CtrlPontosNotaveisH
#define CtrlPontosNotaveisH

#include "Observer.h"
#include "Model.h"
#include "Gps.h"
#include "CtrlCoordenadas.h"

//tempo que deve aguardar parado para marcar o pontos (em segundos)
#define TEMPO_LEITURA_DE_PONTO_NOTAVEL	3

class CtrlPontosNotaveis : public Observer
{
private:
	Model *mmodel;
	COORDENADAS mgpsData;
	PN_DATA mpnData;
	bool mterminateThread;
	boost::mutex gpsMutex;
	bool mdadoGpsNovo;

	void Run();
	static void Thread(CtrlPontosNotaveis *);
	void SetMarco();
	void SetPassagemNivel();
	bool GetCoordenadas(COORDENADAS &coord);
	void SetDadosGps(COORDENADAS data);

public:
	CtrlPontosNotaveis(Model *model);
	void ProcessaPN(PN_DATA pn);

	void Notify(Subject *p);
};


#endif