#include <iostream>
#include "car.h"

int Car::GetSpeed() const
{
	return m_transmission.GetSpeed();
}

Gear Car::GetGear() const
{
	return m_transmission.GetGear();
}

bool Car::IsTornedOn() const
{
	return m_engine.IsWorking();
}

Direction Car::GetDirection() const
{
	int currentSpeed = m_transmission.GetSpeed();
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
	return m_engine.TurnOn();
}

bool Car::TurnOffEngine()
{
	return m_engine.TurnOff();
}

bool Car::SetSpeed(int speed)
{
	if (m_transmission.GetGear() == R)
	{
		speed = -speed;
	}
	return m_transmission.SetSpeed(speed);
}

bool Car::SetGear(int gear)
{
	if (gear >= R && gear <= G5)
	{
		return m_transmission.SetGear((Gear)gear);
	}
	else
	{
		std::cout << "ERROR! Gear is not between renge" << std::endl;
		return false;
	}
}
