#include <iostream>
#include "transmission.h"
#include "engine.h"

int Transmission::GetSpeed() const
{
	return _speed;
}

Gear Transmission::GetGear() const 
{
	return _gear;
}

bool Transmission::SetGear(Gear gear)
{
	if (_refEngine.IsWorking())
	{
		if (gear == R)
		{
			if (_speed == 0)
			{
				_gear = gear;
				return true;
			}
			else
			{
				std::cout << "ERROR! Speed is not Null" << std::endl;
				return false;
			}
		}
		else
		{
			if (_speed >= 0)
			{
				int newMinSpeed = speedLimits.at(gear).first;
				int newMaxSpeed = speedLimits.at(gear).second;
				if (_speed >= newMinSpeed && _speed <= newMaxSpeed)
				{
					_gear = gear;
					return true;
				}
				else
				{
					std::cout << "ERROR! Current speed is not supported" << std::endl;
					return false;
				}
			}
			else
			{
				std::cout << "ERROR! Direction is REVERSE" << std::endl;
				return false;
			}
		}
	}
	else if (gear == N)
	{
		_gear = gear;
		return true;
	}
	else
	{
		std::cout << "ERROR! Can't set not N gear with the engine turned off" << std::endl;
		return false;
	}
}

bool Transmission::SetSpeed(int speed)
{
	int currentMinSpeed = speedLimits.at(_gear).first;
	int currentMaxSpeed = speedLimits.at(_gear).second;
	if (speed >= currentMinSpeed && speed <= currentMaxSpeed)
	{
		if (_gear == N && std::abs(speed) > std::abs(_speed))
		{
			std::cout << "ERROR! Can't boost the speed in N gear" << std::endl;
			return false;
		}
		_speed = speed;
		return true;
	}
	else
	{
		std::cout << "ERROR! Speed is not bitween range for current Gear" << std::endl;
		return false;
	}
}
