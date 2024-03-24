#include <iostream>
#include <string>
#include <sstream>
#include "car.h"

// Info.¬ыводит состо€ние двигател€ автомобил€, направление движени€, скорость и передачу :
// EngineOn.¬ключает двигатель
// EngineOff.¬ыключает двигатель
// SetGear передача.¬ключает заданную передачу, заданную числом от - 1 до 5. 
//   ¬ случае ошибки сообщает почему невозможно переключить передачу.
// SetSpeed скорость.”станавливает указанную скорость движени€, заданную неотрицательным числом. 
//   ¬ случае невозможности изменени€ скорости сообщает, почему нельз€ изменить скорость на указанную.

static void PrintMenu()
{
    std::cout << "[INFO] Use: ";
    std::cout << "'Info' ";
    std::cout << "'EngineOn' ";
    std::cout << "'EngineOff' ";
    std::cout << "'SetGear' ";
    std::cout << "'SetSpeed'" << std::endl;
}

static void PrintInfo(const Car& car)
{
    std::cout << "Car INFO:" << std::endl;
    std::cout << "GEAR     : " << (int)car.GetGear() << std::endl;
    std::cout << "SPEED    : " << std::abs(car.GetSpeed()) << std::endl;
    std::cout << "STATE    : " << ((car.IsTornedOn())? "on" : "off") << std::endl;

    auto dir = car.GetDirection();
    std::string directionName;
    switch (dir)
    {
    case REVERSE:
        directionName = "backward";
        break;
    case STOP:
        directionName = "standing still";
        break;
    case FORWARD:
        directionName = "forward";
        break;
    }
    std::cout << "DIRECTION: " << directionName << std::endl;
}

static void PrintError(std::string str)
{
    std::cout << "ERROR! " << str << std::endl;
}

static bool GetArg(int& arg)
{
    std::cout << "Insert value:" << std::endl << ">";
    if (std::cin >> arg)
    {
        return true;
    }
    else
    {
        PrintError("Is not number!");
    }
    return false;
}

int main()
{
    Car car;
    std::string cmd;
    int arg{};
    std::string res;
    PrintMenu();
    while (std::getline(std::cin, cmd))
    {
        if (!cmd.length())
        {
            continue;
        }

        res.clear();
        if (cmd == "Info")
        {
            PrintInfo(car);
        }
        else if (cmd == "EngineOn")
        {
            if (car.TurnOnEngine())
            {
                res = "Ok";
            }
        }
        else if (cmd == "EngineOff")
        {
            if (car.TurnOffEngine())
            {
                res = "Ok";
            }
        }
        else if (cmd == "SetGear")
        {
            if (GetArg(arg) && car.SetGear(arg))
            {
                res = "Ok";
            }
        }
        else if (cmd == "SetSpeed")
        {
            if (GetArg(arg) && car.SetSpeed(arg))
            {
                res = "Ok";
            }
        }
        else
        {
            PrintError("Unknown command");
        }

        if (res.length())
        {
            std::cout << res << std::endl;
        }
        PrintMenu();
    }
}
