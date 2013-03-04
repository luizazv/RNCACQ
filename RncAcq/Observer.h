//---------------------------------------------------------------------------

#ifndef ObserverH
#define ObserverH

#include <vector>

class Subject;


class Observer
{
public:
	virtual void Notify(Subject *s) = 0;
};


class Subject
{
	std::vector < Observer * > mObservers;

public:
	void NotifyObservers()
    {
    	for(unsigned int i = 0; i < mObservers.size(); i++)
        {
        	mObservers[i]->Notify(this);
        }
    };

	void RegisterObserver(Observer *observer)
    {
    	mObservers.push_back(observer);
    };
};


//---------------------------------------------------------------------------


#endif
