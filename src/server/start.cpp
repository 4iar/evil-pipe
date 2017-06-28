#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <string>

#include "server.hpp"
#include "session.hpp"


void acceptSocket(boost::shared_ptr<boost::asio::ip::tcp::socket>, std::string x, std::string y);

void Server::start () {
    // Acts as a queue/handler for boost async operations
    boost::asio::io_service io_service;

    boost::asio::ip::tcp::acceptor acceptor(
            io_service,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), this->port)
    );

    // Start the event loop
    while (true) {
        boost::shared_ptr<boost::asio::ip::tcp::socket> socket(new boost::asio::ip::tcp::socket(io_service));

        acceptor.accept(*socket);

        boost::thread thread(boost::bind(acceptSocket, socket, this->pipe_payload, this->non_pipe_payload));
    }
}

void acceptSocket (boost::shared_ptr<boost::asio::ip::tcp::socket> socket, std::string pipe_payload, std::string non_pipe_payload) {
    Session session(socket, pipe_payload, non_pipe_payload);
    session.handleConnection();
}
