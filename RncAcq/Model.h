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
	PN_INICIOPONTE,
	PN_FIMPONTE,
	PN_INICIOTUNEL,
	PN_FIMTUNEL,
	PN_PASSAGEMNIVEL,
	PN_INICIOSB,
	PN_FIMSB,
	PN_MARCO,
	PN_MARCOAUTOMATICO
};

enum PN_INICIOTIPO
{
	PN_INICIO_MARCO,
	PN_INICIO_CHAVE
};

enum PN_SENTIDO
{
	PN_CRESCENTE,
	PN_DECRESCENTE
};

enum PN_DESVIO
{
	PN_DESVIO_DIREITA,
	PN_DESVIO_ESQUERDA
};

enum PN_CHAVE
{
	PN_CHAVE_A_FRENTE,
	PN_SEM_CHAVE
};

struct PN_DATA
{
	std::string Sb;
	std::string Marco;

	PN_TIPO pntipo;
	PN_INICIOTIPO pntipoinicio;
	PN_SENTIDO pnsentido;
	PN_DESVIO pndesvio;
	PN_CHAVE pnchave;
};



class IView;

class IModel
{
public:
	virtual void ModelIniciaGps(std::string InterfaceSerial) {}
	virtual void ModelIniciarCaptura() {}
	virtual void ModelPausarCaptura() {}
	virtual void ModelTerminarCaptura() {}
	virtual void ModelProcessaPN(PN_DATA) {}
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
	virtual void ModelProcessaPN(PN_DATA pn);

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
