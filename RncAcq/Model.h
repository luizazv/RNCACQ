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
	PN_MARCOAUTOMATICO,
	PN_MARCOINICIAL,
	PN_COORDENADAS,
	PN_NENHUM
};

enum PN_INICIOTIPO
{
	PN_INICIO_MARCO,
	PN_DESVIO_DIREITA,
	PN_DESVIO_ESQUERDA
};

enum PN_SENTIDO
{
	PN_CRESCENTE,
	PN_DECRESCENTE
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
	PN_CHAVE pnchave;
};

struct COORDENADAS
{
	long latitude;
	long longitude;
	double velocidade;
	double altitude;
};

struct GUI_DATA
{
	COORDENADAS coord;
	PN_DATA pn;
};


class IView;

class IModel
{
public:
	//metodos abstratos onde a GUI acessa Model (para acesso as demais classes)
	virtual void ModelIniciaGps(std::string InterfaceSerial) {}
	virtual void ModelTerminarCaptura() {}
	virtual void ModelProcessaPN(PN_DATA) {}
	virtual void ModelProcessaMQ(PN_DATA) {}
	virtual void ModelSalvaMarcoAtual(int marco) {}
};


class Model : public IModel
{
private:
	void *mlogmgr;
	void *mctrlCoord;
	void *mctrlPN;
	void *mctrlMQ;
	void *mgps;
	IView *mview;

public:
	Model(IView *view);

	//recebe da GUI
	virtual void ModelIniciaGps(std::string InterfaceSerial);
	virtual void ModelPausarCaptura();
	virtual void ModelTerminarCaptura();
	virtual void ModelProcessaPN(PN_DATA pn);
	virtual void ModelProcessaMQ(PN_DATA pn);
	virtual void ModelSalvaMarcoAtual(int marco);

	bool ModoGravacao();

	//envia para GUI
	void GuiErroGpsFalhaSentenca();
	void GuiErroGpsSentencaInvalida();
	void GuiSentencaOk();
	void GuiErroGps();
	void GuiSetHdop(float valor);
	void GuiSendMsg(const char *msg, int timer = 0);
	void GuiSetDistanciaProximoMarco(int distancia);
	void GuiPlota(COORDENADAS coord, PN_DATA pn);
};



#endif
