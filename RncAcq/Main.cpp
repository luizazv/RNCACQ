


#include <stdio.h>
#include <boost/thread.hpp>
#include <iostream>
#include "targetver.h"
#include "Serial.h"
#include "Gps.h"
#include "Gui.h"
#include "CtrlCoordenadas.h"
#include "CtrlMarcoQuilometrico.h"
#include "CtrlPontosNotaveis.h"
#include "CtrlBD.h"
#include "LogMgr.h"

using namespace std;
using namespace boost;
using namespace boost::this_thread;

int main()
{
	//inicia logger->aqui deve receber informação da Gui para iniciar novo/continuar
	LogMgr::GetInstance()->IniciaLogging();
	
	//inicia controlador de coordenadas->Subject
	CtrlCoordenadas ctrlCoordenadas;
	//executa thread do controle de coordenadas
	ctrlCoordenadas.Executa();

	//inicia controlador de marco quilometrico->Observer
	CtrlMarcoQuilometrico ctrlMarcoQuilometrico;
	//registra marco quilometrico como observer
	ctrlCoordenadas.RegisterObserver(&ctrlMarcoQuilometrico);

	//inicia controlador de pontos notaveis->Observer
	CtrlPontosNotaveis ctrlPontosNotaveis;
	//registra pontos notaveis como observer
	ctrlCoordenadas.RegisterObserver(&ctrlPontosNotaveis);

	//inicia controlador de banco de dados
	CtrlBD ctrlBD;
	//registra controlador de banco de dados como observer
	ctrlCoordenadas.RegisterObserver(&ctrlBD);

	//inicia a thread GPS
	//responsavel pelo parser e injeção de sentenças em CtrlCoordenadas
	Gps gps;
	gps.Executa();

	//inicia a GUI (simula interface grafica)
	//usa classe GUI até que a interface em QT esteja pronta
	//recebe instancias de todos os elementos
	Gui gui(&ctrlCoordenadas, &ctrlMarcoQuilometrico, &ctrlPontosNotaveis);

}

