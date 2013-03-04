//---------------------------------------------------------------------------

#include "CtrlMarcoQuilometrico.h"
#include "CtrlCoordenadas.h"

//---------------------------------------------------------------------------
CtrlMarcoQuilometrico::CtrlMarcoQuilometrico()
{
}

//---------------------------------------------------------------------------
void CtrlMarcoQuilometrico::Notify(Subject *p)
{
	//processamento de marco->notificado pela thread ctrlCoordenadas
	COORDENADAS coordenadas;

	((CtrlCoordenadas *)p)->GetCoordenadas(coordenadas);
}
