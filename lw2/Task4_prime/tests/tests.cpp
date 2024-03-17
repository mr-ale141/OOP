#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Task4_prime/prime.h"


TEST_CASE("Zero max")
{
	const int maxNum = 0;
	const int countPrimes = 0;

	auto set = GeneratePrimeNumbersSet(maxNum);

	REQUIRE(set.size() == countPrimes);
}

TEST_CASE("One max")
{
	const int maxNum = 1;
	const int countPrimes = 0;

	auto set = GeneratePrimeNumbersSet(maxNum);

	REQUIRE(set.size() == countPrimes);
}

TEST_CASE("Ten thousand")
{
	const int maxNum = 10000;
	const int countPrimes = 1229;

	auto set = GeneratePrimeNumbersSet(maxNum);

	REQUIRE(set.size() == countPrimes);
}


TEST_CASE("One hundred million")
{
	const int maxNum = 100000000;
	const int countPrimes = 5761455;

	auto set = GeneratePrimeNumbersSet(maxNum);

	REQUIRE(set.size() == countPrimes);
}
