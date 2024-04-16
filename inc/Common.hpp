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
#include <atomic>
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
    #include <netinet/tcp.h>
#endif
