/*
Каждый элемент массива должен быть умножен на минимальный элемент исходного массива
*/
#include <iostream>
#include <exception>
#include <vector>
#include <algorithm>
#include "iovector.h"
#include "vector_multiplier.h"

//vector func
int main()
{
	try
	{
		// readVector Double в названии не использовать
		auto vector = GetVectorDouble(std::cin);
		// line добавить
		// peek() не нужен
		while (!std::cin.eof())
		{
			MultipliedByMin(vector);
			std::sort(vector.begin(), vector.end());
			// аналогично Read
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