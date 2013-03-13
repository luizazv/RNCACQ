//---------------------------------------------------------------------------

#ifndef CtrlCoordenadasH
#define CtrlCoordenadasH

#include <string>
#include "Observer.h"
#include "Gps.h"
#include "Model.h"

using namespace std;

struct COORDENADAS
{
	long latitude;
	long longitude;
	double velocidade;
	double altitude;
};


class CtrlCoordenadas : public Subject
{
private:
	//queue message entre CtrlCoordenadas e GPS (recebe dados GPS)
	QueueMgr mgpsQueue;
	GPSDATA mgpsData;
	boost::thread mThread;
	COORDENADAS mdadosCoordenadas;
	Model *mmodel;

	void ExecutaProcessamento();
	bool RecebeDadosGps();
	void Run();

public:
	CtrlCoordenadas(Model *model);

	void static Thread(CtrlCoordenadas *p);

	void GetCoordenadas(COORDENADAS &dados);

};










//---------------------------------------------------------------------------
#endif
