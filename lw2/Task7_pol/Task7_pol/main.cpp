#include "polNot.h"

int main()
{
    std::string str;
    while (std::getline(std::cin, str))
    {
        std::stringstream sString(str);
        std::cout << "Result = " << Calculate(sString) << std::endl;
    }
}
