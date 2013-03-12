
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
	virtual void SendMsg(const char *msg) = 0;
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
		//executando no QT->necess�rio para compilar e rodar a GUI no QT sem
		//enxergar a implementa��o de Model
		IModel();
#endif
	}

	virtual void IniciaGps(string InterfaceSerial)
	{
		mmodel->ModelIniciaGps(InterfaceSerial);
	};

	virtual void IniciarCaptura()
	{
		mmodel->ModelIniciarCaptura();
	};

	virtual void PausarCaptura()
	{
		mmodel->ModelPausarCaptura();
	};
	virtual void TerminarCaptura()
	{
		mmodel->ModelTerminarCaptura();
	};

	virtual void ProcessaPN(PN_TIPO pn)
	{
		mmodel->ModelProcessaPN(pn);
	};

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