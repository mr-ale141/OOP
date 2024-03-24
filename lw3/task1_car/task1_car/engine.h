#pragma once

class Transmission;

const int rpmMax = 4000;

class Engine
{
public:
	Engine(Transmission& ref) : _refTransmission(ref) {}
	bool TurnOn();
	bool TurnOff();
	bool IsWorking() const;
	// bool SetRpm(double);
	// double GetRpm() const;
private:
	bool _isWorking = false;
	Transmission& _refTransmission;
	// double _rpm = 0.0;
};