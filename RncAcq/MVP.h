
#ifndef MVPH
#define MVPH

#include <string>
#include "Model.h"

using namespace std;


//implementacao de MVP

class IView
{
public:

};


class Presenter
{
public:
	Presenter(IView *view)
	{
		mview = view;

		mmodel = new
#ifdef _EXCUTANDO_VS2010
		Model();
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


private:
	IView *mview;

	IModel *mmodel;
};

class View : public IView
{
public:
	View()
	{
		mpresenter = new Presenter(this);
	}

	Presenter *GetPresenter()
	{
		return mpresenter;
	}


	Presenter *mpresenter;
};




















#endif
