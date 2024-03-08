#include <iostream>
#include <exception>
#include <vector>
#include <algorithm>
#include "iovector.h"
#include "vector_multiplier.h"

int main(const int argc, const char* argv[])
{
	try
	{
		auto vector = GetVectorDouble(std::cin);
		while (!std::cin.eof())
		{
			MultipliedByMin(vector);
			std::sort(vector.begin(), vector.end());
			WriteVectorDouble(std::cout, vector);
			vector = GetVectorDouble(std::cin);
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}