#include "Models/ServerSocket.hpp"

// as a precondition it is safe to assume there will be 3 dots in the IP
uint32_t string_to_ip(std::string ip){
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
    return temporary_ip;
}

// 0.0.0.0 will translate to INADDR_ANY
ServerSocket::ServerSocket(uint16_t port):ServerSocket{"0.0.0.0",port,1}{}
ServerSocket::ServerSocket(std::string ip, uint16_t port):ServerSocket{ip,port,1}
{
    
}
ServerSocket::ServerSocket(std::string ip, uint16_t port,uint8_t max_clients):EthernetNode{ip,port},MAX_CLIENTS{max_clients}
{
    local_address.sin_addr.s_addr = htonl(string_to_ip(ip));
    local_address.sin_family = AF_INET;
    local_address.sin_port = htons(port);
    std::cout<<std::format("Trying to bind to address {}:{}...\n",ip,ntohs(local_address.sin_port));
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd == -1){throw NetworkError(std::format("Failed to create socket\n\nErrno: {}",errno));}
    //configure socket options
    if(setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR,&reuse_address,sizeof(reuse_address)) == -1){
        throw NetworkError(std::format("Failed on setting socket option SO_REUSEADDR\n Errno: {}",errno));
    }
    if(setsockopt(socket_fd,SOL_SOCKET,SO_KEEPALIVE,&use_keepalives,sizeof(use_keepalives)) == -1){
        throw NetworkError(std::format("Failed on setting socket option SO_REUSEADDR\n Errno: {}",errno));
    }
    if(bind(socket_fd,(sockaddr*)&local_address,sizeof(local_address)) == -1){
        throw NetworkError(std::format("Could not bind to address {}:{}\nErrno: {}",ip,ntohs(local_address.sin_port),errno));
    }
    std::cout<<std::format("Succesfully binded to {}:{}\n",ip,port);
}
void ServerSocket::listen(){
    if(::listen(socket_fd,MAX_CLIENTS) == -1){
        throw NetworkError("Failed to start listening");
    }
    is_listening = true;
}

int ServerSocket::accept_clients(){
    if(not is_listening){throw std::logic_error("Cannot start accepting before calling listen()");}
    //SUPER IMPORTANT TO FLUSH BEFORE BLOCKING!!!!!
    std::cout<<std::flush;
    sockaddr_storage new_client{};
    socklen_t len{sizeof(new_client)};
    int connected_sock = accept(socket_fd,(sockaddr*)&new_client,&len);
    if(connected_sock != -1){
        std::cout<<"Client connected yay\n";
    }else{
        std::cout<<"Error on accept(), errno"<<errno;
    }
    return connected_sock;
}