#include <iostream>
#include <chrono>
#include <string>
#include "prime.h"

#define WITH_PRINT 0

const int usInSecond = 1000000;
const int msInSecond = 1000;

int main(const int argc, const char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Error! There are no required parameters!" << std::endl;
		std::cout << "Example:" << std::endl;
		std::cout << "-> prime.exe <max_number>" << std::endl;
		return 1;
	}

	const int maxNumber = std::stoi(argv[1]);

	auto timeBegin = std::chrono::high_resolution_clock::now();

	auto primeNumbers = GeneratePrimeNumbersSet(maxNumber);

	auto timeEnd = std::chrono::high_resolution_clock::now();
	auto us = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeBegin).count();

#if WITH_PRINT
	for (auto& i : primeNumbers)
	{
		std::cout << i << std::endl;
	}
#endif

	auto s = us / usInSecond;
	us -= s * usInSecond;
	auto ms = us/ msInSecond;
	us -= ms * msInSecond;
	std::cout << "Delta Time = " << s << " s " << ms << " ms " << us << " us " << std::endl;
	return 0;
}