#include <iostream>
#include <exception>
#include <vector>
#include "iovector.h"
#include "vector_multiplier.h"

int main(const int argc, const char* argv[])
{
	try
	{
		auto vector = GetVectorDouble(std::cin);
		MultipliedByMin(vector);
		WriteVectorDouble(std::cout, vector);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}