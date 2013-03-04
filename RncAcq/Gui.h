
#ifndef GUIH
#define GUIH

#include "QueueMgr.h"

class Gui
{
public:
	Gui();
	~Gui();

	void operator () ()
	{
		Run();
	};

private:

	QueueMgr mgpsQueue;

	void Run();

};


#endif