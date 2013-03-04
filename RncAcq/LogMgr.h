

#ifndef LOGMGRH
#define LOGMGRH

#include <string>
#include <queue>
#include <fstream>

#include "boost\thread.hpp"

using namespace std;

struct LogQueue
{
	string dado;
	void *pointer;
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

	class LogId
	{
	private:
		std::ofstream hfile;

	public:
		LogId(string nomeArquivo, ltipoLog tipo)
		{
			//abre arquivo para
			//criação->novo log
			//append->continua log anterior
			ios_base::openmode modo;

			if(tipo == ContinuaLogAnterior)
			{
				modo = ios_base::out | ios_base::app | ios_base::binary;
			}
			else
			{
				modo = ios_base::out | ios_base::trunc | ios_base::binary;
			}

			//abre arquivo
			hfile.open(nomeArquivo.c_str(), modo);
		};

		bool write(string log)
		{
			bool retval = false;

			try
			{
				if(hfile.is_open())
				{
					//escreve a string
					hfile.write(log.c_str(), log.size());
					retval = true;
				}
			}
			catch(...)
			{
				retval = false;
			}

			return retval;
		};
	};


	LogMgr();

public:

	~LogMgr();

	static LogMgr *GetInstance();
	void *Register(string nomeArquivo);

	void IniciaLogging(ltipoLog tlog = NovoLog);
	void Escreve(void *p, string dado);
	static void Thread(LogMgr *logmgr);
	void Run();
};

#endif