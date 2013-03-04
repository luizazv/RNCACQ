

#ifndef CTRLBDH
#define CTRLBDH

#include "Observer.h"

class CtrlBD : public Observer
{
private:

public:
	CtrlBD();
	void Notify(Subject *p);
};









#endif