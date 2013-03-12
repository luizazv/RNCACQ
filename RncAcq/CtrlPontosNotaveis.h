
#ifndef CtrlPontosNotaveisH
#define CtrlPontosNotaveisH

#include "Observer.h"
#include "Model.h"

class CtrlPontosNotaveis : public Observer
{
private:
	Model *mmodel;

public:
	CtrlPontosNotaveis(Model *model);
	void ProcessaPN(PN_TIPO pn);

	void Notify(Subject *p);
};











#endif