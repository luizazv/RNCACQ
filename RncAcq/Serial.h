
#ifndef SERIALH
#define	SERIALH

//#include <vector>
//#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/utility.hpp>
#include <boost/function.hpp>
#include <boost/shared_array.hpp>

//#include <stdexcept>
//#include <boost/utility.hpp>
#include <boost/asio.hpp>

class timeout_exception: public std::runtime_error
{
public:
    timeout_exception(const std::string& arg): runtime_error(arg) {}
};


class Serial // : private boost::noncopyable
{
public:
    Serial();

    Serial(const std::string& devname,
		          unsigned int baud_rate,
				  boost::asio::serial_port_base::parity opt_parity = boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none),
                  boost::asio::serial_port_base::character_size opt_csize = boost::asio::serial_port_base::character_size(8),
				  boost::asio::serial_port_base::flow_control opt_flow = boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none),
                  boost::asio::serial_port_base::stop_bits opt_stop = boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));

    void open(const std::string& devname,
		      unsigned int baud_rate,
              boost::asio::serial_port_base::parity opt_parity = boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none),
              boost::asio::serial_port_base::character_size opt_csize = boost::asio::serial_port_base::character_size(8),
              boost::asio::serial_port_base::flow_control opt_flow = boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none),
              boost::asio::serial_port_base::stop_bits opt_stop = boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));

    bool isOpen() const;
    void close();

	//timeout para read/write->desabilita com setTimeout(boost::posix_time::secondos(0))
	void setTimeout(const boost::posix_time::time_duration& t);

    void write(const char *data, size_t size);

    void write(const std::vector<char>& data);

    void writeString(const std::string& s);

	//se timeout->throws timeout_exception
    void read(char *data, size_t size);

	//se timeout->throws timeout_exception
    std::vector<char> read(size_t size);

	//se timeout->throws timeout_exception
    std::string readString(size_t size);

	//se timeout->throws timeout_exception
    std::string readStringUntil(const std::string& delim="\n");
    
    ~Serial();

    class ReadSetupParameters
    {
    public:
        ReadSetupParameters(): fixedSize(false), delim(""), data(0), size(0) {}

        explicit ReadSetupParameters(const std::string& delim):
                fixedSize(false), delim(delim), data(0), size(0) { }

        ReadSetupParameters(char *data, size_t size): fixedSize(true),
                delim(""), data(data), size(size) { }

        bool fixedSize;
        std::string delim;
        char *data;
        size_t size;
    };

	//le até a string delimitadora
	void performReadSetup(const ReadSetupParameters& param);

	//callback chamada quando ocorre timeou ou leitura cancelada
	//se timeout->result = resultTimeoutExpired
	void timeoutExpired(const boost::system::error_code& error);

	//callback chamada quando leitura completa ou erro de leitura
	//se erro->result = resultError
	void readCompleted(const boost::system::error_code& error,
            const size_t bytesTransferred);

    enum ReadResult
    {
        resultInProgress,
        resultSuccess,
        resultError,
        resultTimeoutExpired
    };

    boost::asio::io_service io;
    boost::asio::serial_port port;
    boost::asio::deadline_timer timer;
    boost::posix_time::time_duration timeout;
    boost::asio::streambuf readData;
    enum ReadResult result;
    size_t bytesTransferred;
    ReadSetupParameters setupParameters;
};

#endif


