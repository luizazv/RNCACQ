

#ifndef LOGMGRH
#define LOGMGRH

#include <string>
#include <queue>
#include <fstream>
#include <iostream>


#include "boost\thread.hpp"

using namespace std;


#define NOME_ARQUIVO_LOG		"RNCACQ.DAT"
#define NOME_ARQUIVO_LOG_BKP	"RNCACQ.BKP"

struct LogQueue
{
	string tag;
	string dado;
};

enum ltipoLog
{
	NovoLog,
	ContinuaLogAnterior
};

class LogMgr
{
private:
	queue <LogQueue> vecLog;
	static LogMgr *mpLogMgr;
	ltipoLog mtipoLog;
	boost::thread mThreadLog;
	boost::mutex logMutex;
	ios_base::openmode mmodo;

	LogMgr();

	bool Retira(LogQueue &log);

public:

	~LogMgr();

	static LogMgr *GetInstance();

	void IniciaLogging(ltipoLog tlog = NovoLog);
	void Escreve(string tag, string dado);
	void EscreveNoArquivo(string linha);
	static void Thread(LogMgr *logmgr);
	void Run();
};

#endif