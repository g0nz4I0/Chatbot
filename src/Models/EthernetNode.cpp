#include "Models/EthernetNode.hpp"

EthernetNode::EthernetNode(uint16_t port):
port{port}{

} 
EthernetNode::~EthernetNode(){
    close(socket_fd);
}
EthernetNode::EthernetNode(std::string ip, uint16_t port):ip{ip},port{port}{

} 