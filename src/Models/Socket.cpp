#include "Models/Socket.hpp"

Socket::Socket(std::string ip, uint16_t port):EthernetNode{ip,port}{}