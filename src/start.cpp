#include "server.hpp"

#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread/thread.hpp>


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

        boost::thread thread(boost::bind(this->handleConnection, socket));
    }
}
