#pragma once

#include <map>
#include <utility>

class Engine;

enum Gear
{
	R = -1,
	N,
	G1,
	G2,
	G3,
	G4,
	G5
};

const std::map<Gear, std::pair<int, int>> speedLimits =
{
	{ R,  {     -20,       0  } },
	{ N,  { INT_MIN,  INT_MAX } },
	{ G1, {       0,      30  } },
	{ G2, {      20,      50  } },
	{ G3, {      30,      60  } },
	{ G4, {      40,      90  } },
	{ G5, {      50,      150 } },
};

class Transmission
{
public:
	Transmission(Engine& ref) : _refEngine(ref) {}
	int GetSpeed() const;
	Gear GetGear() const;
	bool SetGear(Gear);
	bool SetSpeed(int);
private:
	Gear _gear = N;
	int _speed = 0;
	Engine& _refEngine;
};

