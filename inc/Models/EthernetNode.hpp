#pragma once

#include "Common.hpp"

#include "Error.hpp"
class EthernetNode{
public:
    EthernetNode() = default;
    explicit EthernetNode(uint16_t port);
    explicit EthernetNode(std::string ip,uint16_t port);
    ~EthernetNode();
    std::string get_ip_as_string()const;
protected:
    //precondition for the ip address is that it should contain 3 dots separating each field
    std::string ip{};
    int socket_fd;
    uint16_t port;
};