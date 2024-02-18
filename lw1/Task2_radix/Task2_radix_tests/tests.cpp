#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Task2_radix/convertor.h"

TEST_CASE("Test StrToInt ''")
{
	bool wasError = false;
	int zero = StringToInt(std::string(""), 10, wasError);
	REQUIRE(wasError == true);
}

TEST_CASE("Test StrToInt 'a'")
{
	bool wasError = false;
	int zero = StringToInt(std::string("a"), 10, wasError);
	REQUIRE(wasError == true);
	zero = StringToInt(std::string("-a"), 10, wasError);
	REQUIRE(wasError == true);
}

TEST_CASE("Test StrToInt '1'")
{
	bool wasError = false;
	int zero = StringToInt(std::string("1"), 10, wasError);
	REQUIRE(zero == 1);
	REQUIRE(wasError == false);
	zero = StringToInt(std::string("-1"), 10, wasError);
	REQUIRE(zero == -1);
	REQUIRE(wasError == false);
}

TEST_CASE("Test StrToInt '0'")
{
	bool wasError = false;
	int zero = StringToInt(std::string("0"), 10, wasError);
	REQUIRE(zero == 0);
	REQUIRE(wasError == false);
	zero = StringToInt(std::string("-0"), 10, wasError);
	REQUIRE(zero == 0);
	REQUIRE(wasError == false);
}

TEST_CASE("Test StrToInt '-2147483648'")
{
	bool wasError = false;
	int zero = StringToInt(std::string("-2147483648"), 10, wasError);
	REQUIRE(zero == -2147483648);
	REQUIRE(wasError == false);
	zero = StringToInt(std::string("-2147483649"), 10, wasError);
	REQUIRE(wasError == true);
}

TEST_CASE("Test StrToInt '2147483647'")
{
	bool wasError = false;
	int zero = StringToInt(std::string("2147483647"), 10, wasError);
	REQUIRE(zero == 2147483647);
	REQUIRE(wasError == false);
	zero = StringToInt(std::string("2147483648"), 10, wasError);
	REQUIRE(wasError == true);
}