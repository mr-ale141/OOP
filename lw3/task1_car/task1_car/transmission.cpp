#include <iostream>
#include "transmission.h"
#include "engine.h"

int Transmission::GetSpeed() const
{
	return m_speed;
}

Gear Transmission::GetGear() const 
{
	return m_gear;
}

bool Transmission::SetGear(Gear gear)
{
	if (m_refEngine.IsWorking())
	{
		if (gear == R)
		{
			if (m_speed == 0)
			{
				m_gear = gear;
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
			if (m_speed >= 0)
			{
				int newMinSpeed = speedLimits.at(gear).first;
				int newMaxSpeed = speedLimits.at(gear).second;
				if (m_speed >= newMinSpeed && m_speed <= newMaxSpeed)
				{
					m_gear = gear;
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
		m_gear = gear;
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
	int currentMinSpeed = speedLimits.at(m_gear).first;
	int currentMaxSpeed = speedLimits.at(m_gear).second;
	if (speed >= currentMinSpeed && speed <= currentMaxSpeed)
	{
		if (m_gear == N && std::abs(speed) > std::abs(m_speed))
		{
			std::cout << "ERROR! Can't boost the speed in N gear" << std::endl;
			return false;
		}
		m_speed = speed;
		return true;
	}
	else
	{
		std::cout << "ERROR! Speed is not between range for current Gear" << std::endl;
		return false;
	}
}
