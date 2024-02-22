#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Task2_radix/convertor.h"

TEST_CASE("Test Case empty number string")
{
	try
	{
		std::string answer = Convert(0, 16, std::string(""));
		REQUIRE(1 == 0);
	}
	catch (...)
	{
		REQUIRE(1 == 1);
	}
}

TEST_CASE("Test Case out range source")
{
	try
	{
		std::string answer = Convert(0, 16, std::string("1F"));
		REQUIRE(1 == 0);
	}
	catch (...)
	{
		REQUIRE(1 == 1);
	}
}

TEST_CASE("Test Case bad numberString")
{
	try
	{
		std::string answer = Convert(10, 16, std::string("1F"));
		REQUIRE(1 == 0);
	}
	catch (...)
	{
		REQUIRE(1 == 1);
	}
}

TEST_CASE("Test Case 36 36 ZZZ")
{
	std::string answer = Convert(36, 36, std::string("ZZZ"));
	REQUIRE(answer == "ZZZ");
}

TEST_CASE("Test Case 16 10 1F")
{
	std::string answer = Convert(16, 10, std::string("1F"));
	REQUIRE(answer == "31");
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

TEST_CASE("Test IntToStr 'INT_MIN and INT_MAX'")
{
	bool wasError = false;
	std::string str = IntToString(-2147483648, 10, wasError);
	REQUIRE(str == "-2147483648");
	REQUIRE(wasError == false);
	str = IntToString(2147483647, 10, wasError);
	REQUIRE(str == "2147483647");
	REQUIRE(wasError == false);
}

TEST_CASE("Test StrToInt '-2147483648'")
{
	bool wasError = false;
	int zero = StringToInt(std::string("-2147483648"), 10, wasError);
	REQUIRE(zero == INT_MIN);
	REQUIRE(wasError == false);
	zero = StringToInt(std::string("-2147483649"), 10, wasError);
	REQUIRE(wasError == true);
}

TEST_CASE("Test StrToInt '2147483647'")
{
	bool wasError = false;
	int zero = StringToInt(std::string("2147483647"), 10, wasError);
	REQUIRE(zero == INT_MAX);
	REQUIRE(wasError == false);
	zero = StringToInt(std::string("2147483648"), 10, wasError);
	REQUIRE(wasError == true);
}

TEST_CASE("Test StrToInt 'FFFF'")
{
	bool wasError = false;
	int zero = StringToInt(std::string("FFFF"), 16, wasError);
	REQUIRE(zero == 65535);
	REQUIRE(wasError == false);
	zero = StringToInt(std::string("-FFFF"), 16, wasError);
	REQUIRE(zero == -65535);
	REQUIRE(wasError == false);
}

TEST_CASE("Test StrToInt '7FFFFFFF'")
{
	bool wasError = false;
	int zero = StringToInt(std::string("7FFFFFFF"), 16, wasError);
	REQUIRE(zero == INT_MAX);
	REQUIRE(wasError == false);
	zero = StringToInt(std::string("-7FFFFFFF"), 16, wasError);
	REQUIRE(zero == -INT_MAX);
	REQUIRE(wasError == false);
}

TEST_CASE("Test StrToInt 'ZZZ' 36")
{
	bool wasError = false;
	int num = StringToInt(std::string("ZZZ"), 36, wasError);
	REQUIRE(num == 46655);
	REQUIRE(wasError == false);
	num = StringToInt(std::string("-ZZZ"), 36, wasError);
	REQUIRE(num == -46655);
	REQUIRE(wasError == false);
}