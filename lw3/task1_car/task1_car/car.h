#pragma once
#include "engine.h"
#include "transmission.h"

enum Direction
{
	REVERSE = -1,
	STOP,
	FORWARD
};

class Car
{
public:
	Car() : 
		_engine      { Engine(_transmission) },
		_transmission{ Transmission(_engine) }
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
	Engine _engine;
	Transmission _transmission;
};
