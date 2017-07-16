#include <iostream>

#define PRINT(x) std::cout << __FILE__ << "+" << __LINE__ << ": " << x << std::endl;

class MyException : public std::runtime_error
{
public:
    MyException(const std::string& msg) 
        : std::runtime_error(msg)
    { }
};
