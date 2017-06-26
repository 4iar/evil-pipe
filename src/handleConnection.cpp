#include <cstdlib>
#include <chrono>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include "server.hpp"


void sendNullChunk (boost::shared_ptr<boost::asio::ip::tcp::socket> socket);
bool isPipedToBash (boost::shared_ptr<boost::asio::ip::tcp::socket> socket);

const double BUFFER_SIZE = 4194304;


void Server::handleConnection(boost::shared_ptr<boost::asio::ip::tcp::socket> socket) {
    if (isPipedToBash(socket)) {
        std::cout << "Request -> piped to bash" << std::endl;
        boost::asio::write(*socket, boost::asio::buffer(std::string("echo piped to bash")));
    } else {
        std::cout << "Request -> not piped to bash" << std::endl;
        boost::asio::write(*socket, boost::asio::buffer(std::string("echo not piped to bash")));
    }

    // Temporary magic
    // - Need to set proper headers to prevent (56) Recv failure on client
    sleep(1);

    // Gracefully close the connection
    (*socket).shutdown(boost::asio::ip::tcp::socket::shutdown_both);
}

/**
 * \brief Determine if a request was piped to bash
 *
 */
bool isPipedToBash (boost::shared_ptr<boost::asio::ip::tcp::socket> socket) {
    std::chrono::duration<double> sleep_duration;
    std::chrono::duration<double> control_duration;
    try {
        auto control_start = std::chrono::high_resolution_clock::now();
        sendNullChunk(socket);
        sendNullChunk(socket);
        auto control_finish = std::chrono::high_resolution_clock::now();
        control_duration = control_start - control_finish;

        auto sleep_start = std::chrono::high_resolution_clock::now();
        boost::asio::write(*socket, boost::asio::buffer(std::string("\nsleep 5\n")));
        sendNullChunk(socket);
        sendNullChunk(socket);
        auto sleep_finish = std::chrono::high_resolution_clock::now();
        sleep_duration = sleep_start - sleep_finish;
    } catch (std::exception& e) {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }

    double variance = control_duration.count() - sleep_duration.count();

    return variance > 4;
};


/**
 * \brief Send a chunk of data that fills up the buffer
 *
 */
void sendNullChunk (boost::shared_ptr<boost::asio::ip::tcp::socket> socket) {
    // Note: Need to refactor this chunk generation code
    // as it only has to be created once
    const size_t null_buffer_size = BUFFER_SIZE / sizeof(char);
    char null_buffer[null_buffer_size];

    // We use a null char because it will not be rendered in the terminal
    const char NULL_CHAR = 0;
    for (size_t i = 0; i < null_buffer_size; i++) {
        null_buffer[i] = NULL_CHAR;
    }

    boost::asio::write(*socket, boost::asio::buffer(null_buffer, null_buffer_size));
}
