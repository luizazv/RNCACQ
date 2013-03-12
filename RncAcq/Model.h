#ifndef MODELH
#define MODELH

#include <string>

enum ModoGravacao
{
	MODO_PAUSADO,
	MODO_GRAVANDO,
	MODO_PARADO
};

enum PN_TIPO
{
	PN_PONTE,
	PN_TUNEL,
	PN_PASSAGEMNIVEL,
	PN_INICIOSB,
	PN_FIMSB
};


class IView;

class IModel
{
public:
	virtual void ModelIniciaGps(std::string InterfaceSerial) {}
	virtual void ModelIniciarCaptura() {}
	virtual void ModelPausarCaptura() {}
	virtual void ModelTerminarCaptura() {}
	virtual void ModelProcessaPN(PN_TIPO) {}
};


class Model : public IModel
{
private:
	void *mlogmgr;
	void *mctrlCoord;
	void *mctrlPN;
	void *mgps;
	IView *mview;
	bool mmodoGravacao;

public:
	Model(IView *view);

	//recebe da GUI
	virtual void ModelIniciaGps(std::string InterfaceSerial);
	virtual void ModelIniciarCaptura();
	virtual void ModelPausarCaptura();
	virtual void ModelTerminarCaptura();
	virtual void ModelProcessaPN(PN_TIPO pn);

	bool ModoGravacao();

	//envia para GUI
	void ErroGpsFalhaSentenca();
	void ErroGpsSentencaInvalida();
	void SentencaOk();
	void ErroGps();
	void SetHdop(float valor);
	void SendMsg(const char *msg);


};



#endif
