#include <chrono>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>

#include "session.hpp"


/**
 * \brief Determine if a request was piped to bash
 *
 */
bool Session::isPipedToBash () {
    std::chrono::duration<double> sleep_duration;
    std::chrono::duration<double> control_duration;
    try {
        auto control_start = std::chrono::high_resolution_clock::now();
        sendNullChunk();
        sendNullChunk();
        auto control_finish = std::chrono::high_resolution_clock::now();
        control_duration = control_start - control_finish;

        auto sleep_start = std::chrono::high_resolution_clock::now();
        boost::asio::write(*(this->socket), boost::asio::buffer(std::string("\nsleep 5\n")));
        sendNullChunk();
        sendNullChunk();
        auto sleep_finish = std::chrono::high_resolution_clock::now();
        sleep_duration = sleep_start - sleep_finish;
    } catch (std::exception& e) {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }

    double variance = control_duration.count() - sleep_duration.count();

    return variance > 4;
};