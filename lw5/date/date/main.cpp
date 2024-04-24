#include <iostream>
#include "CDate.h"

int main()
{
    CDate date;
    std::cout << date << std::endl;

    std::cout << date << std::endl;

    std::cin >> date;

    std::cout << date << " : " << date.GetDateStamp() << " days\n";
}
