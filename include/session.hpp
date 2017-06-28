#include <string>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

class Session {
private:
    boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
    std::string pipe_payload;
    std::string non_pipe_payload;

    void sendNullChunk ();
    bool isPipedToBash ();

public:
    Session (boost::shared_ptr<boost::asio::ip::tcp::socket> socket, std::string pipe_payload, std::string non_pipe_payload) {
        this->socket = socket;
        this->non_pipe_payload = non_pipe_payload;
        this->pipe_payload = pipe_payload;
    }

    void handleConnection ();
};
