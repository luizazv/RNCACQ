

#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>

#include "LogMgr.h"

namespace io = boost::iostreams;


LogMgr *LogMgr::mpLogMgr = NULL;

//-----------------------------------------------------------------------------
LogMgr::LogMgr()
{
	mtipoLog = ContinuaLogAnterior;
}

//-----------------------------------------------------------------------------
LogMgr *LogMgr::GetInstance()
{
	if(mpLogMgr == NULL)
	{
		mpLogMgr = new LogMgr();
	}

	return mpLogMgr;
}

//-----------------------------------------------------------------------------
void *LogMgr::Register(string nomeArquivo)
{
	LogMgr::LogId *logid = new LogId(nomeArquivo, mtipoLog);

	return logid;
}

//-----------------------------------------------------------------------------
void LogMgr::Escreve(void *p, string dado)
{
	LogQueue log;

	log.dado = dado;
	log.pointer = p;

	//adicionando dado na fila
	vecLog.push(log);
}

//-----------------------------------------------------------------------------
void LogMgr::IniciaLogging(ltipoLog tlog)
{
	//inicia thread de gravação
	mThreadLog = boost::thread(Thread, this);  
}

//---------------------------------------------------------------------------------
void LogMgr::Thread(LogMgr *logmgr)
{
	logmgr->Run();
}

//---------------------------------------------------------------------------------
void LogMgr::Run()
{
	//grava os pedidos de gravação presentes no vetor de pedidos
	LogQueue queue;

	queue = vecLog.front();

	if(queue.pointer != NULL)
	{
		((LogId *)(queue.pointer))->write(queue.dado);
		//retira da fila
		vecLog.pop();
	}
}












