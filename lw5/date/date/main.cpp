#include <iostream>
#include "CDate.h"

int main()
{
    CDate date;
    std::cout << '>';
    while (std::cin >> date)
    {
        std::cout << "Stamp: " << date.GetDateStamp() << std::endl;
        std::cout << "Day: " << date.GetDay() << std::endl;
        std::cout << "Month: " << (int)date.GetMonth() << std::endl;
        std::cout << "Year: " << date.GetYear() << std::endl;
        std::cout << "Week: " << (int)date.GetWeekDay() << std::endl;
        std::cout << "Date: " << date << std::endl;
        std::cout << '>';
    }
    std::cout << "Error\n";
}
