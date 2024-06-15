#include <iostream>
#include "server.hpp"

int main(int argc, char* argv[]) {
    std::cout<<"server"<<std::endl;

    Server server;
    server.test();

    std::cout<<"bye bye"<<std::endl;
    return 0;
}
