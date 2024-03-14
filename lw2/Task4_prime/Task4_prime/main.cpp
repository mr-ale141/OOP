#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <set>

const int usInSecond = 1000000;
const int msInSecond = 1000;

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::set<int> set;
	for (int i = 1; i <= upperBound; i++)
	{
		set.insert(i);
	}
	return set;
}

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
	
	for (auto iter = primeNumbers.begin(); iter != primeNumbers.end(); iter++)
	{
		std::cout << *iter << std::endl;
	}

	auto s = us / usInSecond;
	us -= s * usInSecond;
	auto ms = us/ msInSecond;
	us -= ms * msInSecond;
	std::cout << "Delta Time = " << s << " s " << ms << " ms " << us << " us " << std::endl;
}