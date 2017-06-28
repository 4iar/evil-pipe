#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>

#include "session.hpp"


const double BUFFER_SIZE = 4194304;


/**
 * \brief Send a chunk of data that fills up the buffer
 *
 */
void Session::sendNullChunk () {
    // Note: Need to refactor this chunk generation code
    // as it only has to be created once
    const size_t null_buffer_size = BUFFER_SIZE / sizeof(char);
    char null_buffer[null_buffer_size];

    // We use a null char because it will not be rendered in the terminal
    const char NULL_CHAR = 0;
    for (size_t i = 0; i < null_buffer_size; i++) {
        null_buffer[i] = NULL_CHAR;
    }

    boost::asio::write(*(this->socket), boost::asio::buffer(null_buffer, null_buffer_size));
}