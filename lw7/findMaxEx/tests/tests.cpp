#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../findMaxEx/MaxFinder.h"

static bool Cmp(int l, int r) { return l < r; }

TEST_CASE("Max element inside")
{
	GIVEN("Vector")
	{
		std::vector<int> v = {54, 25, 7, 105, 19, 23, 0};

		WHEN("Get max")
		{
			int max;
			bool result = FindMax(v, max, Cmp);
			THEN("Compare max")
			{
				REQUIRE(result == true);
				REQUIRE(max == 105);
			}
		}
	}
}

TEST_CASE("Max element is first")
{
	GIVEN("Vector")
	{
		std::vector<int> v = { 105, 54, 25, 7, 19, 23, 0 };

		WHEN("Get max")
		{
			int max;
			bool result = FindMax(v, max, Cmp);
			THEN("Compare max")
			{
				REQUIRE(result == true);
				REQUIRE(max == 105);
			}
		}
	}
}

TEST_CASE("Max element is last")
{
	GIVEN("Vector")
	{
		std::vector<int> v = { 54, 25, 7, 19, 23, 0, 105 };

		WHEN("Get max")
		{
			int max;
			bool result = FindMax(v, max, Cmp);
			THEN("Compare max")
			{
				REQUIRE(result == true);
				REQUIRE(max == 105);
			}
		}
	}
}

TEST_CASE("no maximum element")
{
	GIVEN("Vector")
	{
		std::vector<int> v = { 54, 54, 54, 54, 54, 54, 54 };

		WHEN("Get max")
		{
			int oldMax = 105;
			int max = oldMax;
			bool result = FindMax(v, max, Cmp);
			THEN("Compare max")
			{
				REQUIRE(result == false);
				REQUIRE(max == oldMax);
			}
		}
	}
}

TEST_CASE("Empty vector")
{
	GIVEN("Vector")
	{
		std::vector<int> v;

		WHEN("Get max")
		{
			int max{};
			bool result = FindMax(v, max, Cmp);
			THEN("Compare max")
			{
				REQUIRE(result == false);
				REQUIRE(max == 0);
			}
		}
	}
}

TEST_CASE("One element")
{
	GIVEN("Vector")
	{
		std::vector<int> v = { 105 };

		WHEN("Get max")
		{
			int max{};
			bool result = FindMax(v, max, Cmp);
			THEN("Compare max")
			{
				REQUIRE(result == false);
				REQUIRE(max == 0);
			}
		}
	}
}