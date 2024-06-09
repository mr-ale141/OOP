#include <iostream>
#include <string>
#include <iomanip>
#include "CMyArray.h"

#include <vector>

template<typename T>
static void PrintArr(CMyArray<T>& arr)
{
	if (arr.Size() == 0)
	{
		std::cout << "Arr is empty!" << std::endl;
		return;
	}

	size_t i{};
	for (auto& item : arr)
	{
		std::cout << std::setw(3) << i << ": " << item << std::endl;
		++i;
	}
}

int main()
{
	CMyArray<std::string> arrString;
	CMyArray<double> arrDouble;

	arrString.PushBack(std::string("first"));
	arrString.PushBack(std::string("second"));
	arrString.PushBack(std::string("last"));
	
	std::cout << "---------- Print Arr String ------------" << std::endl;
	PrintArr(arrString);
	std::cout << "----------------------------------------" << std::endl;

	CMyArray<std::string> arrString2;

	arrString2 = arrString;

	arrDouble.PushBack(1.1);
	arrDouble.PushBack(0.1);
	arrDouble.PushBack(1.0000000001);

	std::cout << "---------- Print Arr Double ------------" << std::endl;
	PrintArr(arrDouble);
	std::cout << "----------------------------------------" << std::endl;

	std::cout << "arrString[2] = " << arrString[2] << std::endl;
	std::cout << "arrDouble[2] = " << arrDouble[2] << std::endl;


}