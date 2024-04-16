/**
 * 
 *  small Chatbot using Modern C++ and UNIX socket API
*/
#include "Models/ServerSocket.hpp"
int main()
{
    ServerSocket ss{"127.0.0.1",6969};
    ss.listen();
    while(true){
        ss.accept_clients();
    }
}