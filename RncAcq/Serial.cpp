
#include "Serial.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <boost/bind.hpp>

using namespace std;
using namespace boost;

Serial::Serial(): io(), port(io), timer(io), timeout(posix_time::seconds(0))
{
}

Serial::Serial(const std::string& devname,
	           unsigned int baud_rate,
               asio::serial_port_base::parity opt_parity,
               asio::serial_port_base::character_size opt_csize,
               asio::serial_port_base::flow_control opt_flow,
               asio::serial_port_base::stop_bits opt_stop)
        : io(), port(io), timer(io), timeout(posix_time::seconds(0))
{
    open(devname,baud_rate,opt_parity,opt_csize,opt_flow,opt_stop);
}


Serial::~Serial()
{
}


void Serial::open(const std::string& devname,
	              unsigned int baud_rate,
                  asio::serial_port_base::parity opt_parity,
                  asio::serial_port_base::character_size opt_csize,
                  asio::serial_port_base::flow_control opt_flow,
                  asio::serial_port_base::stop_bits opt_stop)
{
    if( isOpen() )
	{
		//permite abrir com outra configuração
		close();
	}
    port.open(devname);
    port.set_option(asio::serial_port_base::baud_rate(baud_rate));
    port.set_option(opt_parity);
    port.set_option(opt_csize);
    port.set_option(opt_flow);
    port.set_option(opt_stop);
}

bool Serial::isOpen() const
{
    return port.is_open();
}

void Serial::close()
{
    if( isOpen() )
	{
	    port.close();
	}
}

void Serial::setTimeout(const posix_time::time_duration& t)
{
    timeout = t;
}

void Serial::write(const char *data, size_t size)
{
    asio::write(port,asio::buffer(data,size));
}

void Serial::write(const std::vector<char>& data)
{
    asio::write(port,asio::buffer(&data[0],data.size()));
}

void Serial::writeString(const std::string& s)
{
    asio::write(port,asio::buffer(s.c_str(),s.size()));
}

void Serial::read(char *data, size_t size)
{
    if( readData.size() > 0 )
    {
        istream is(&readData);
        size_t toRead = min(readData.size(), size);
        is.read(data,toRead);
        data+=toRead;
        size-=toRead;
        if(size==0)
		{
			return;
		}
    }
    
    setupParameters=ReadSetupParameters(data,size);
    performReadSetup(setupParameters);

    //sem timeout->transforma em um timeout de valor grande
    if(timeout!=posix_time::seconds(0))
	{
		timer.expires_from_now(timeout);
	}
    else
	{
		timer.expires_from_now(posix_time::hours(100000));
	}
    
    timer.async_wait(boost::bind(&Serial::timeoutExpired, this, asio::placeholders::error));
    
    result = resultInProgress;
    bytesTransferred = 0;
    for(;;)
    {
        io.run_one();

        switch(result)
        {
            case resultSuccess:
                timer.cancel();
                return;

			case resultTimeoutExpired:
                port.cancel();
                throw(timeout_exception("Timeout"));
            
			case resultError:
                timer.cancel();
                port.cancel();
                throw(boost::system::system_error(boost::system::error_code(),
                        "Erro de leitura"));
        }
    }
}

std::vector<char> Serial::read(size_t size)
{
	//cria vetor com tamanho desejado
    vector<char> result(size, '\0');
    read(&result[0], size);
    return result;
}

std::string Serial::readString(size_t size)
{
	//cria string com tamanho desejado
    string result(size,'\0');
    read(&result[0],size);
    return result;
}

std::string Serial::readStringUntil(const std::string& delim)
{
	//se existirem dados antes da leitura async_read_until gerencia
	//se a quantidade de bytes for correta chama readCompleted()
	setupParameters=ReadSetupParameters(delim);
    performReadSetup(setupParameters);

    if(timeout!=posix_time::seconds(0))
	{
		timer.expires_from_now(timeout);
	}
    else
	{
		timer.expires_from_now(posix_time::hours(100000));
	}

    timer.async_wait(boost::bind(&Serial::timeoutExpired, this, asio::placeholders::error));

    result = resultInProgress;

    bytesTransferred = 0;

	for(;;)
    {
        io.run_one();

        switch(result)
        {
            case resultSuccess:
                {
                    timer.cancel();
                    bytesTransferred -= delim.size();
                    istream is(&readData);
                    string result(bytesTransferred, '\0');
                    is.read(&result[0],bytesTransferred);
                    is.ignore(delim.size());
                    return result;
                }
        
			case resultTimeoutExpired:
                port.cancel();
                throw(timeout_exception("Timeout"));
            
			case resultError:
                timer.cancel();
                port.cancel();
                throw(boost::system::system_error(boost::system::error_code(),
                        "Error de leitura"));
        }
    }
}

void Serial::performReadSetup(const ReadSetupParameters& param)
{
    if(param.fixedSize)
    {
        asio::async_read(port,asio::buffer(param.data,param.size),boost::bind(
                &Serial::readCompleted,this,asio::placeholders::error,
                asio::placeholders::bytes_transferred));
    }
	else
	{
        asio::async_read_until(port,readData,param.delim,boost::bind(
                &Serial::readCompleted,this,asio::placeholders::error,
                asio::placeholders::bytes_transferred));
    }
}

void Serial::timeoutExpired(const boost::system::error_code& error)
{
     if(!error && result == resultInProgress)
	 {
		 result=resultTimeoutExpired;
	 }
}

void Serial::readCompleted(const boost::system::error_code& error, const size_t bytesTransferred)
{
    if(!error)
    {
        result=resultSuccess;
        this->bytesTransferred=bytesTransferred;
        return;
    }

    //In case a asynchronous operation is cancelled due to a timeout,
    //each OS seems to have its way to react.
    #ifdef _WIN32
    if(error.value() == 995)
	{
		return; //Windows spits out error 995

	}
    #elif defined(__APPLE__)
    if(error.value() == 45)
    {
        performReadSetup(setupParameters);
        return;
    }
    #else //Linux
    if(error.value() == 125)
	{
		return; //Linux outputs error 125
	}
    #endif

    result = resultError;
}
