#pragma once

class Transmission;

//const int rpmMax = 4000;

class Engine
{
public:
	Engine(Transmission& ref) : m_refTransmission(ref) {}
	bool TurnOn();
	bool TurnOff();
	bool IsWorking() const;
private:
	bool m_isWorking = false;
	Transmission& m_refTransmission;
};