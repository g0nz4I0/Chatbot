#pragma once
#include "Models/EthernetNode.hpp"


class ServerSocket : EthernetNode{
public: 
    ServerSocket(uint16_t port);
    ServerSocket(std::string ip,uint16_t port);
    ServerSocket(std::string ip,uint16_t port,uint8_t max_clients);
    void listen();
    int accept_clients();
private:
    bool is_listening{false};
    uint8_t MAX_CLIENTS{1};
};