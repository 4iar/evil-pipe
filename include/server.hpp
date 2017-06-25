#include <string>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>


class Server {
private:
    double port;
    std::string pipe_payload;
    std::string non_pipe_payload;

    void static handleConnection (boost::shared_ptr<boost::asio::ip::tcp::socket> socket);

public:
    void start ();

    Server (double port) {
        this->port = port;
    };

};
