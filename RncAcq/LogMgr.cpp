

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
void LogMgr::Escreve(string tag, string dado)
{
	LogQueue log;

	log.tag = tag;
	log.dado = dado;

	//adicionando dado na fila
	boost::lock_guard<boost::mutex> guard (logMutex);
	vecLog.push(log);
}

//-----------------------------------------------------------------------------
bool LogMgr::Retira(LogQueue &log)
{
	bool retval = false;

	boost::lock_guard<boost::mutex> guard (logMutex);
	if(!vecLog.empty())
	{
		//retira elemento da fila
		log = vecLog.front();
		vecLog.pop();
		retval = true;
	}

	return retval;
}

//-----------------------------------------------------------------------------
void LogMgr::IniciaLogging(ltipoLog tlog)
{
	//abre arquivo para
	//criação->novo log
	//append->continua log anterior
	if(tlog == ContinuaLogAnterior)
	{
		mmodo = ios_base::out | ios_base::app | ios_base::binary;
	}
	else
	{
		mmodo = ios_base::out | ios_base::trunc | ios_base::binary;
	}

	//inicia thread de gravação
	mThreadLog = boost::thread(Thread, this);  
}

//---------------------------------------------------------------------------------
void LogMgr::EscreveNoArquivo(string linha)
{
	std::ofstream hfile;
	std::ofstream hfilebkp;

	//abre arquivo
	hfile.open(NOME_ARQUIVO_LOG, mmodo);
	hfilebkp.open(NOME_ARQUIVO_LOG_BKP, mmodo);

	if(hfile.is_open())
	{
		hfile << linha << endl;
		hfile.close();
	}

	if(hfilebkp.is_open())
	{
		hfilebkp << linha << endl;
		hfilebkp.close();
	}
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
	LogQueue log;

	if(	Retira(log) )
	{
		//adiciona tag do elemento 
		string linha("tag[");
		linha += log.tag;
		linha += "]:dado[";
		linha += log.dado;
		linha += "]";

		EscreveNoArquivo(linha);
	}
}


