#include <iostream>

#define FILE_LINE "[ " << __FILE__ << ":" << __LINE__ << " ]\t"
#define PRINT(x) std::cout << FILE_LINE << x << std::endl;
#define THROW_EXCEPTION(x) std::stringstream errorMsg; errorMsg << FILE_LINE << x; throw MyException(errorMsg.str());


class MyException : public std::runtime_error
{
public:
    MyException(const std::string& msg) 
        : std::runtime_error(msg)
    { }
};
