///////////////////////////////////////////////////////////////////////////////////
//
// Arquivo:	GPS.hpp (On-Time RTOS)
//
// Projeto: CBU 32 Bits - Computador de Bordo para Locomotivas
//
// Empresa: Daiken Indústria Eletrônica Ltda.
//
// Dez. 2004
//
// Version 1.00
//
////////////////////////////////////////////////////////////////////////////////////

#ifndef GPSH
#define GPSH

#include "boost\thread.hpp"
#include <string>
#include "Serial.h"
#include "QueueMgr.h"

const int GPS_OK      = 0;
const int GPS_VALID	  =	1;
const int GPS_INVALID =	2;
const int GPS_TIMEOUT =	3;

//queue message entre GPS e GUI->gps = consumidor
#define NOME_GPS_QUEUE "GpsQueueMessage"
//queue message entre GPS e CtrlCoordenadas->gps = produtor
#define NOME_CTRL_COORDENADAS_QUEUE "CtrlCoordQueueMessage"

#define NOME_ARQUIVO_LOG_SENTENCAS "LogSentencasGps.txt"

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
	string hora;
	string data;
	int estado;
	int nroSatelites;
	float HDOP;
	float VDOP;
	float PDOP;
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
	Gps();
	~Gps();

	void Run();

	static void Thread(Gps *p);
	void Executa();

private:
	Serial mSerial;
	string mSentenca;
	QueueMgr mgpsQueue;
	QueueMgr mctrlCoordenadasQueue;
	boost::thread mThread;
	void *mIdLog;
	
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

	bool ParserGGA();
	void CalculaBcc(char *sBcc);
	bool AguardaResposta();
	bool RequestGps();

	void FalhaSentenca();
	bool VerificaSerialAtiva();
	int  MontaSentencaConfTrimble(char *sent);
	bool LeDadosDaGUI();
	void EnviaParaCtrlCoordenadas();

    int mEstado;
	GPSDATA mgpsData;
};

//////////////////////////////////////////////////////////////////
#endif

