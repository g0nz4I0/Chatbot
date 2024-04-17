#pragma once
#include "Models/EthernetNode.hpp"


class ServerSocket : EthernetNode{
public: 
    ServerSocket(uint16_t port);
    ServerSocket(std::string ip,uint16_t port);
    ServerSocket(std::string ip,uint16_t port,uint8_t max_clients);
    void listen();
    //marked as nodiscard in case Server is full
    [[nodiscard]] int accept_clients();
private:
    bool is_listening{false};
    const uint8_t MAX_CLIENTS;
    int reuse_address{1};
    int use_keepalives{1};
    sockaddr_in local_address{};
    std::atomic<int> connected_clients{};
};

uint32_t string_to_ip(std::string ip);