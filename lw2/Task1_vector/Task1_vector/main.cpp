/*
������ ������� ������� ������ ���� ������� �� ����������� ������� ��������� �������
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
		// readVector Double � �������� �� ������������
		auto vector = GetVectorDouble(std::cin);
		// line ��������
		// peek() �� �����
		while (!std::cin.eof())
		{
			MultipliedByMin(vector);
			std::sort(vector.begin(), vector.end());
			// ���������� Read
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