
#ifndef QUEUEMGRH
#define QUEUEMGRH

#include <string>
 
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/scoped_ptr.hpp>

using namespace boost::interprocess;
using namespace std;

//numero de mensagens pendentes no queue_message
#define QUEUE_NUMERO_MENSAGENS	3


class QueueMgr
{
private:
	bool drop;
	boost::scoped_ptr<message_queue> mq_;
//	message_queue *mq_;
	int mtamMsg;
	string mNomeQueue;
 
public:

	QueueMgr()
	{
	}
 
	~QueueMgr()
	{
		if(drop)
		{
			message_queue::remove(mNomeQueue.c_str());
		}
//		delete mq_;
	}
 
	void InitProdutor(int tamMsg, string nomeQueue)
	{
		//produtor não remove o queue_message no destrutor
		drop = false;
		mNomeQueue = nomeQueue;
		mtamMsg = tamMsg;
		message_queue::remove(nomeQueue.c_str());
		mq_.reset( (new message_queue(create_only, (const char *)nomeQueue.c_str(), QUEUE_NUMERO_MENSAGENS, tamMsg)) );
	};

	void InitConsumidor(string nomeQueue)
	{
		//consumidor pode remover o queue_message no destrutor
		drop = true;
		mq_.reset( (new message_queue(open_only, (const char *)nomeQueue.c_str())) );
	}

	void Send(const char* msg)
	{
		unsigned int priority = 0;
		mq_->send((const void*)msg, (size_t)mtamMsg, priority);
	}
 
	bool Receive(void *buf)
	{
		unsigned int priority;
		bool retval = false;
		size_t recvdSize;

		mq_->receive(buf, mtamMsg, recvdSize, priority);
 
		if(recvdSize == mtamMsg)
		{
			retval = true;
		}

		return retval;
	}
};

#endif
