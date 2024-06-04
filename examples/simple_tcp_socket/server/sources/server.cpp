#include "server.hpp"

Server::Server() {
    std::cout << "Constructor Server" << std::endl;
}

Server::~Server() {
    std::cout << "Destructor Server" << std::endl;
}

void Server::test() {
    std::cout << "test" << std::endl;
}
