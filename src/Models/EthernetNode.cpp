#include "Models/EthernetNode.hpp"

EthernetNode::EthernetNode(uint16_t port):
port{port}{

} 
EthernetNode::~EthernetNode(){
    close(socket_fd);
}
EthernetNode::EthernetNode(std::string ip, uint16_t port):ip{ip},port{port}{
    std::size_t idx = 0;
    std::size_t pos = 0;
    uint32_t temporary_ip = 0;
    for(std::size_t i = 0; i < 3;i++)
    {
        pos = ip.find('.',idx);
        temporary_ip += std::stoi(ip.substr(idx,pos-idx))<< (24-(8*i));
        idx = pos;
        idx++;
    }
    temporary_ip += std::stoi(ip.substr(idx,ip.length()));
    local_address.sin_addr.s_addr = htonl(temporary_ip);
    local_address.sin_family = AF_INET;
    local_address.sin_port = htons(port);
    std::cout<<std::format("Trying to bind to address {}:{}...\n",ip,ntohs(local_address.sin_port));
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd == -1){throw NetworkError(std::format("Failed to create socket\n\nErrno: {}",errno));}
    setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR,&reuse_address,sizeof(reuse_address));
    if(bind(socket_fd,(sockaddr*)&local_address,sizeof(local_address)) == -1){
        throw NetworkError(std::format("Could not bind to address {}:{}\nErrno: {}",ip,ntohs(local_address.sin_port),errno));
    }

} 