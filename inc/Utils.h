#include <iostream>

#define FILE_LINE __FILE__ << ":" << __LINE__
#define PRINT(x) std::cout << x << std::endl;
#define THROW_EXCEPTION(x) std::stringstream errorMsg; errorMsg << "\nERROR:\n" << FILE_LINE << "\n" << x; throw MyException(errorMsg.str());


class MyException : public std::runtime_error
{
public:
    MyException(const std::string& msg) 
        : std::runtime_error(msg)
    { }
};
