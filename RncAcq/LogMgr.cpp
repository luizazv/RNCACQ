

#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>

#include "LogMgr.h"

namespace io = boost::iostreams;


LogMgr *LogMgr::mpLogMgr = NULL;

//-----------------------------------------------------------------------------
LogMgr::LogMgr()
{
	mtipoLog = ContinuaLogAnterior;

	mterminaThread = false;
	IniciaLogging();
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
	std::ofstream hfile;
	std::ofstream hfilebkp;

	bool first = true;

void LogMgr::EscreveNoArquivo(string linha)
{

	//abre arquivo
	if(!hfile.is_open())
	{
		hfile.open(NOME_ARQUIVO_LOG, ios::app | ios::binary);
		hfilebkp.open(NOME_ARQUIVO_LOG_BKP, ios::app | ios::binary);
	}

	if(hfile.is_open())
	{
		if(first)
		{
			hfile << "[INICIO]" << endl;
			first = false;
		}

		hfile << linha << endl;
		hfile.flush();
//		hfile.close();
	}

//	if(hfilebkp.is_open())
//	{
//		hfilebkp << linha << endl;
//		hfilebkp.close();
//	}
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

	while(!mterminaThread)
	{
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

		boost::this_thread::sleep(boost::posix_time::milliseconds(200));
	}
}


