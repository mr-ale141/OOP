#include <iostream>
#include "engine.h"
#include "transmission.h"

bool Engine::TurnOn()
{
	m_isWorking = true;
	return true;
}

bool Engine::TurnOff()
{
	auto currentGear = m_refTransmission.GetGear();
	auto currentSpeed = m_refTransmission.GetSpeed();
	if (currentGear == N && currentSpeed == 0)
	{
		m_isWorking = false;
		return true;
	}
	else
	{
		std::cout << "ERROR! Car is moving or Gear is not N." << std::endl;
		return false;
	}
}

bool Engine::IsWorking() const
{
	return m_isWorking;
}
