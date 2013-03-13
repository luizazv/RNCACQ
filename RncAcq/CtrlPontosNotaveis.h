
#ifndef CtrlPontosNotaveisH
#define CtrlPontosNotaveisH

#include "Observer.h"
#include "Model.h"
#include "Gps.h"
#include "CtrlCoordenadas.h"

class CtrlPontosNotaveis : public Observer
{
private:
	Model *mmodel;
	COORDENADAS mgpsData;
	PN_DATA mpnData;
	bool mterminateThread;

	void Run();
	static void Thread(CtrlPontosNotaveis *);

public:
	CtrlPontosNotaveis(Model *model);
	void ProcessaPN(PN_DATA pn);

	void Notify(Subject *p);
};











#endif