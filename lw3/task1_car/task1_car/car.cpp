#include <iostream>
#include "car.h"

int Car::GetSpeed() const
{
	return _transmission.GetSpeed();
}

Gear Car::GetGear() const
{
	return _transmission.GetGear();
}

bool Car::IsTornedOn() const
{
	return _engine.IsWorking();
}

Direction Car::GetDirection() const
{
	int currentSpeed = _transmission.GetSpeed();
	if (currentSpeed < 0)
	{
		return REVERSE;
	}
	else if (currentSpeed == 0)
	{
		return STOP;
	}
	else
	{
		return FORWARD;
	}
}

bool Car::TurnOnEngine()
{
	return _engine.TurnOn();
}

bool Car::TurnOffEngine()
{
	return _engine.TurnOff();
}

bool Car::SetSpeed(int speed)
{
	if (_transmission.GetGear() == R)
	{
		speed = -speed;
	}
	return _transmission.SetSpeed(speed);
}

bool Car::SetGear(int gear)
{
	if (gear >= R && gear <= G5)
	{
		return _transmission.SetGear((Gear)gear);
	}
	else
	{
		std::cout << "ERROR! Gear is not bitween renge" << std::endl;
		return false;
	}
}
