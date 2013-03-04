//---------------------------------------------------------------------------

#ifndef CtrlMarcoQuilometricoH
#define CtrlMarcoQuilometricoH

#include <string>
#include "Observer.h"

using namespace std;

class CtrlMarcoQuilometrico : public Observer
{
public:
	CtrlMarcoQuilometrico();
	
	void Notify(Subject *p);
};










//---------------------------------------------------------------------------
#endif
