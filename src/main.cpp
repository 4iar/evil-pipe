#include <iostream>
#include <stdexcept>

#include "server.hpp"


int main(int argc, char* argv[]) {
    if (argc != 2) {
        throw std::invalid_argument("Invalid arguments. Correct format: ./evil-pipe <port>");
    }

    unsigned const short port = (atoi(argv[1]));
    std::cout << "Server running @ port " << port << std::endl;

    Server server(port);
    server.start();
}
