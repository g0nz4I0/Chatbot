#include <stdexcept>
#include <string>

class NetworkError : std::exception{
public:
    NetworkError(std::string error_msg):error_msg{error_msg}{}
    const char* what()const _GLIBCXX_NOTHROW override{
        return error_msg.c_str();
    }
private:
std::string error_msg{};

};