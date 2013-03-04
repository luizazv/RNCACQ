//---------------------------------------------------------------------------

#ifndef CtrlCoordenadasH
#define CtrlCoordenadasH

#include <string>
#include "Observer.h"
#include "QueueMgr.h"
#include "Gps.h"

using namespace std;

struct COORDENADAS
{
	double latitude;
	double longitude;
	double velocidade;
};

class CtrlCoordenadas : public Subject
{
private:
	//queue message entre CtrlCoordenadas e GPS (recebe dados GPS)
	QueueMgr mGpsQueue;
	GPSDATA mgpsData;
	boost::thread mThread;
	COORDENADAS mdadosCoordenadas;

	void ExecutaProcessamento();
	void SentencaGps(string sentenca);
	bool RecebeDadosGps();

public:
	CtrlCoordenadas();

	void Executa();
	void static Thread(CtrlCoordenadas *p);
	void Run();
	void GetCoordenadas(COORDENADAS &dados);

};










//---------------------------------------------------------------------------
#endif