#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include "MaxFinder.h"

struct Sportsman
{
	std::string firstName;
	std::string lastName;
	float height;
	float weight;
};

static bool CmpWithWeight(const Sportsman& left, const Sportsman& right)
{
	if (left.weight < .0 || right.weight < .0)
		throw std::invalid_argument("ERROR! weight < 0");
	double diff = right.weight - left.weight;
	return diff > std::numeric_limits<double>::epsilon();
}

static bool CmpWithHeight(const Sportsman& left, const Sportsman& right)
{
	if (left.height < .0 || right.height < .0)
		throw std::invalid_argument("ERROR! height < 0");
	double diff = right.height - left.height;
	return diff > std::numeric_limits<double>::epsilon();
}

int main()
{
	std::vector<Sportsman> sportsmanList = { 
		{"Feder",  "Adamson", 151.1f, 250.5f},
		{"Jacob",  "Backer",  156.3f, 98.6f},
		{"Max",    "Birch",   220.3f, 78.9f},
		{"Victor", "Faber",   196.5f, 59.6f},
		{"Bob",    "Green",   194.2f, 96.3f},
		{"Jack",   "Gill",    170.5f, 85.4f},
		{"Logan",  "Fox",     169.9f, 46.1f},
	};

	try
	{
		Sportsman sportsman{"", "", 0.0, 0.0};
		if (FindMax(sportsmanList, sportsman, CmpWithHeight))
		{
			std::cout << "I found max Height! Is:" << std::endl;
			std::cout << "First name: " << sportsman.firstName << std::endl;
			std::cout << "Last name : " << sportsman.lastName << std::endl;
			std::cout << "Height    : " << sportsman.height << std::endl;
			std::cout << "Weight    : " << sportsman.weight << std::endl;
		}
		else
		{
			std::cout << "I didn't find it!" << std::endl;
		}

		if (FindMax(sportsmanList, sportsman, CmpWithWeight))
		{
			std::cout << "I found max Weight! Is:" << std::endl;
			std::cout << "First name: " << sportsman.firstName << std::endl;
			std::cout << "Last name : " << sportsman.lastName << std::endl;
			std::cout << "Height    : " << sportsman.height << std::endl;
			std::cout << "Weight    : " << sportsman.weight << std::endl;
		}
		else
		{
			std::cout << "I didn't find it!" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}