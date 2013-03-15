
#ifndef MVPH
#define MVPH

#include <string>
#include "Model.h"

using namespace std;


enum GPS_EVENTO_ERRO
{
	GPS_ERRO_SERIAL,
	GPS_ERRO_SENTENCA
};


//implementacao de MVP

class IView
{
public:
	virtual void ErroGpsFalhaSentenca() = 0;
	virtual void ErroGpsSentencaInvalida() = 0;
	virtual void SentencaOk() = 0;
	virtual void ErroGps() = 0;
	virtual void SetHdop(int valor) = 0;
	virtual void SendMsg(const char *msg, int timer) = 0;
	virtual void SetDistanciaProximoMarco(int dist) = 0;
	virtual void Plota(COORDENADAS coord) = 0;
};


class Presenter
{
public:
	Presenter(IView *view)
	{
		mview = view;

		mmodel = new

#ifdef _EXECUTANDO_VS2010
		Model(mview);
#else
		//executando no QT->necessário para compilar e rodar a GUI no QT sem
		//enxergar a implementação de Model
		IModel();
#endif
	}

	virtual void IniciaGps(string InterfaceSerial)
	{
		mmodel->ModelIniciaGps(InterfaceSerial);
	};

	virtual void TerminarCaptura()
	{
		mmodel->ModelTerminarCaptura();
	};

	virtual void ProcessaPN(PN_DATA pn)
	{
		mmodel->ModelProcessaPN(pn);
	};

	virtual void ProcessaMQ(PN_DATA pn)
	{
		mmodel->ModelProcessaMQ(pn);
	};

	virtual void SalvaMarcoAtual(int marco)
	{
		mmodel->ModelSalvaMarcoAtual(marco);
	}


private:
	IView *mview;

	IModel *mmodel;
};

class View : public IView
{
private:

public:
	View()
	{
		mpresenter = new Presenter(this);
	}

	Presenter *mpresenter;
};




















#endif
