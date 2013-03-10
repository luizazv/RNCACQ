#ifndef MODELH
#define MODELH

#include <string>

class IModel
{
public:
	IModel(){}

	virtual void ModelIniciaGps(std::string InterfaceSerial) {}
	virtual void ModelIniciarCaptura() {}
	virtual void ModelPausarCaptura() {}
	virtual void ModelTerminarCaptura() {}
};


class Model : public IModel
{
private:
	void *mctrlCoord;
	void *mctrlPN;
	void *mgps;

public:
	Model();

	virtual void ModelIniciaGps(std::string InterfaceSerial);
	virtual void ModelIniciarCaptura();
	virtual void ModelPausarCaptura();
	virtual void ModelTerminarCaptura();
};



#endif