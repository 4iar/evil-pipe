#include <string>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>


class Server {
private:
    unsigned short port;
    std::string pipe_payload;
    std::string non_pipe_payload;


public:
    void start ();

    Server (unsigned short port, std::string pipe_payload, std::string non_pipe_payload) {
        this->port = port;
        this->pipe_payload = pipe_payload;
        this->non_pipe_payload = non_pipe_payload;
    };
};
