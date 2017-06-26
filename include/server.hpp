#include <string>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>


class Server {
private:
    unsigned short port;
    std::string pipe_payload;
    std::string non_pipe_payload;

    void static handleConnection (boost::shared_ptr<boost::asio::ip::tcp::socket> socket);

public:
    void start ();

    Server (unsigned short port) {
        this->port = port;
    };

};
