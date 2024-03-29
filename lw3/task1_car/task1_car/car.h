#pragma once
#include "engine.h"
#include "transmission.h"
// class
enum Direction
{
	REVERSE = -1,
	STOP,
	FORWARD
};
// указывать имя
class Car
{
public:
	Car() : 
		m_engine      { Engine(m_transmission) },
		m_transmission{ Transmission(m_engine) }
	{}
	int GetSpeed() const;
	Gear GetGear() const;
	bool IsTornedOn() const;
	Direction GetDirection() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetSpeed(int);
	bool SetGear(int);
private:
	Engine m_engine;
	Transmission m_transmission;
};
