/*
каждый элемент массива должен быть умножен на минимальный элемент исходного массива
*/
#include <iostream>
#include <exception>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include "vector_multiplier.h"

std::stringstream GetStreamLine(std::istream& input)
{
	std::stringstream ss;
	std::string str;
	std::getline(input, str);
	ss << str;
	return ss;
}

int main()
{
	try
	{
		while (!std::cin.eof())
		{
			auto streamLine = GetStreamLine(std::cin);
			auto vector = GetVector(streamLine);
			MultipliedByMin(vector);
			std::sort(vector.begin(), vector.end());
			WriteVector(std::cout, vector);
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}