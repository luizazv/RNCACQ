
#ifndef GUIH
#define GUIH

#include "QueueMgr.h"
#include "CtrlCoordenadas.h"
#include "CtrlMarcoQuilometrico.h"
#include "CtrlPontosNotaveis.h"

class Gui
{
public:
	Gui(CtrlCoordenadas *p1, CtrlMarcoQuilometrico *p2, CtrlPontosNotaveis *p3);
	~Gui();

	void operator () ()
	{
		Run();
	};

private:

	QueueMgr mgpsQueue;
	CtrlCoordenadas *mctrlCoordenadas;
	CtrlMarcoQuilometrico *mctrlMarcoQuilometrico;
	CtrlPontosNotaveis *mctrlPontosNotaveis;

	void Run();
	int EventoQt();

};


#endif