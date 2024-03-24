#include <iostream>
#include "engine.h"
#include "transmission.h"

bool Engine::TurnOn()
{
	_isWorking = true;
	return true;
}

bool Engine::TurnOff()
{
	auto currentGear = _refTransmission.GetGear();
	auto currentSpeed = _refTransmission.GetSpeed();
	if (currentGear == N && currentSpeed == 0)
	{
		_isWorking = false;
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
	return _isWorking;
}

/*
bool Engine::SetRpm(double rpm)
{
	_rpm = rpm;
	return true;
}

double Engine::GetRpm() const
{
	return _rpm;
}
*/
