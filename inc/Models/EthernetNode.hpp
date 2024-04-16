#pragma once

// C++ includes

#include <iostream>
#include <string>
#include <filesystem>
#include <stdexcept>
#include <exception>
#include <source_location>
#include <format>
#include <errno.h>
#include <algorithm>
namespace fs = std::filesystem;

// Socket includes
#ifdef _WIN32
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <ifaddrs.h>
    #include <unistd.h>
#endif


// project includes

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
    sockaddr_in local_address{};
    bool reuse_address{true};
};