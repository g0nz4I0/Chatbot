#include <stdexcept>
#include <string>

class NetworkError : std::runtime_error{
public:
    NetworkError(std::string error_msg):std::runtime_error{error_msg},error_msg{error_msg}{}
    const char* what()const _GLIBCXX_NOTHROW override{
        return error_msg.c_str();
    }
private:
std::string error_msg{};

};