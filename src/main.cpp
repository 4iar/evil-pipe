#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <fstream>
#include <boost/filesystem.hpp>

#include "server.hpp"

std::string readFile(std::string file_name);


int main(int argc, char* argv[]) {
    if (argc != 2) {
        throw std::invalid_argument("Invalid arguments. Correct format: ./evil-pipe <port>");
    }

    unsigned const short port = (atoi(argv[1]));
    std::cout << "Server running @ port " << port << std::endl;

    Server server(port, readFile("pipe_payload.txt"), readFile("non_pipe_payload.txt"));
    server.start();
}

std::string readFile(std::string file_name) {
    if (!boost::filesystem::exists(file_name)) {
        throw std::invalid_argument(file_name + " does not exist ");
    }

    std::ifstream t(file_name);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

