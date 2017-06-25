#include <cstdlib>
#include <chrono>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include "server.hpp"


void Server::handleConnection(boost::shared_ptr<boost::asio::ip::tcp::socket> socket) {
    boost::asio::write(*socket, boost::asio::buffer(std::string("alskdjlkfja lskdjlkaj")));

    // Gracefully close the connection
    (*socket).shutdown(boost::asio::ip::tcp::socket::shutdown_both);
}

