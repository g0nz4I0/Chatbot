#include "Common.hpp"

#include "Models/EthernetNode.hpp"

class Socket : EthernetNode{
    public:
        Socket(std::string ip,uint16_t port);
};