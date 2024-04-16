#include "Models/ServerSocket.hpp"

ServerSocket::ServerSocket(uint16_t port):EthernetNode{port}{}
ServerSocket::ServerSocket(std::string ip, uint16_t port):EthernetNode{ip,port}
{
}
ServerSocket::ServerSocket(std::string ip, uint16_t port,uint8_t max_clients):EthernetNode{ip,port},MAX_CLIENTS{max_clients}
{

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