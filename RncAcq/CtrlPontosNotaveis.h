
#ifndef CtrlPontosNotaveisH
#define CtrlPontosNotaveisH

#include "Observer.h"

class CtrlPontosNotaveis : public Observer
{
public:
	CtrlPontosNotaveis();

	void Notify(Subject *p);
};











#endif