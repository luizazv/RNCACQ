///////////////////////////////////////////////////////////////////////////////////
//
// Arquivo:	GPS.hpp (On-Time RTOS)
//
// Projeto: CBU 32 Bits - Computador de Bordo para Locomotivas
//
// Empresa: Daiken Ind�stria Eletr�nica Ltda.
//
// Dez. 2004
//
// Version 1.00
//
////////////////////////////////////////////////////////////////////////////////////

#ifndef GPSH
#define GPSH


#include <string>
#include "Serial.h"
#include "QueueMgr.h"
#include "boost\thread.hpp"
#include "Model.h"


const int GPS_OK      = 0;
const int GPS_VALID	  =	1;
const int GPS_INVALID =	2;
const int GPS_TIMEOUT =	3;

//queue message entre GPS e CtrlCoordenadas->gps = produtor
#define NOME_CTRL_COORDENADAS_QUEUE "GpsCtrlCoordQueue"

#define HDOP_FIMESCALA 100

struct COORDENADA
{
	long valor;
	char hemisferio;
};

struct GPSDATA
{
	float velocidade;
	COORDENADA latitude;
	COORDENADA longitude;
	char receiverWarning;
	bool ParserRMC;
	bool ParserGGA;
	unsigned int direcao;
	std::string hora;
	std::string data;
	int estado;
	int nroSatelites;
	float HDOP;
	float VDOP;
	float PDOP;
	float altitude;
};

struct SERIALDATA
{
	std::string devName;
	int baudrate;

	enum ACAO
	{
		serOpen = 0,
		serClose
	}acao;
};


class Gps
{ 
public:
	Gps(Model *model);
	~Gps();

	void Run();

	static void Thread(Gps *p);
	//inicia leitura do GPS
	void Inicia(std::string com);
	//termina leitura do GPS
	void Termina();

private:
	Serial mSerial;
	std::string mSentenca;
	Model *mmodel;
	QueueMgr mgpsQueue;
	boost::thread mThread;
	void *mIdLog;
	bool mterminaThread;
	int mtolerancia;
	boost::scoped_ptr<message_queue> mq;

	void EnviaSentenca(char *sentenca);
	void GravaLog();

	bool LeDadosGUI();

	bool Passo1(char *Token);
	bool Passo2(char *Token);
	bool Passo3(char *Token);
	bool Passo4(char *Token);
	bool Passo5(char *Token);
	bool Passo6(char *Token);
	bool Passo7(char *Token);
	bool Passo8(char *Token);
	bool Passo9(char *Token);
	bool Passo10(char *Token);
	bool VerificaBcc();
	bool LeSentenca();
	bool VerificaSentenca();
	void EnviaSentenca(char *Sentenca, int Tam);
	void ProgramaGpsSerial();
	bool ParserRMC();

	bool PassoGGA( char *Token);
	bool PassoVazio( char *Token);
	bool PassoNroSat( char *Token );
	bool PassoHDOP( char *Token );
	bool PassoAltitude( char *Token );

	bool ParserGGA();
	void CalculaBcc(char *sBcc);
	bool AguardaResposta();
	bool RequestGps();

	void FalhaSentenca();
	bool VerificaSerialAtiva();
	int  MontaSentencaConfTrimble(char *sent);
	void EnviaParaCtrlCoordenadas();
	void ProcessaSentenca();

    int mEstado;
	GPSDATA mgpsData;
};

//////////////////////////////////////////////////////////////////
#endif

