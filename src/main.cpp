// C++ includes

#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <exception>
#include <source_location>
#include <format>
namespace fs = std::filesystem;
#include <errno.h>

// Socket includes
#ifdef _WIN32
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

int main()
{
    int socket_id = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_id == -1)
    {
        throw std::logic_error(std::format("Error when trying to open socket, Errno {}", errno));
    }
    char ip[20];
    sockaddr_in local_address{.sin_family = AF_INET,.sin_port = 6969, .sin_addr = inet_addr("127.0.0.1")};
        inet_ntop(AF_INET,&local_address.sin_addr,&ip[0],20);

    if (bind(socket_id, (const sockaddr* )&local_address, 100) == -1)
    {
        throw std::logic_error(std::format("Error when trying to bind to address \"{}\"\n\t in file: \"{}\" line {}\n Errno: {}",
                                           ip, std::source_location::current().file_name(),
                                           std::source_location::current().line(), errno));
    }
    std::cout<<"\nIP:"<<ip<<"\n";
}