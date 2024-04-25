#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../myString/CMyString.h"
#include <string>
#include <cstring>

TEST_CASE("Public methods")
{
	GIVEN("Empty")
	{
		CMyString str;
		WHEN("Get str data")
		{
			std::string data(str.GetStringData());
			THEN("Compare value")
			{
				REQUIRE(data == "");
			}
		}
	}

	GIVEN("Const char*")
	{
		CMyString str("Empty str");
		WHEN("Get str data")
		{
			std::string data(str.GetStringData());
			THEN("Compare value")
			{
				REQUIRE(data == "Empty str");
			}
		}
	}

	GIVEN("Const char* with '\\0'")
	{
		const char why[] = "Empty\0str";
		CMyString str(why, 9);
		WHEN("Get str data")
		{
			const char* p = str.GetStringData();
			THEN("Compare value")
			{
				bool f = true;
				for (size_t i = 0; i < 9; i++)
				{
					f = (why[i] == p[i]);
					if (!f) break;
				}
				REQUIRE(f);
			}
		}
	}

	GIVEN("Copy constructor")
	{
		CMyString str("Empty str");
		CMyString str1(str);
		WHEN("Get str data")
		{
			std::string data(str.GetStringData());
			std::string data1(str1.GetStringData());
			THEN("Compare value")
			{
				REQUIRE(data == data1);
			}
		}
	}

	GIVEN("Move constructor")
	{
		CMyString str("Empty str");
		CMyString str1 = std::move(str);
		WHEN("Get str data")
		{
			std::string data(str.GetStringData());
			std::string data1(str1.GetStringData());
			THEN("Compare value")
			{
				REQUIRE(data == "");
				REQUIRE(data1 == "Empty str");
			}
		}
	}

	GIVEN("std::string constructor")
	{
		std::string string("Empty str");
		CMyString str(string);
		WHEN("Get str data")
		{
			std::string data(str.GetStringData());
			THEN("Compare value")
			{
				REQUIRE(data == "Empty str");
			}
		}
	}

	GIVEN("Get length")
	{
		CMyString str("Empty str");
		WHEN("Get str data")
		{
			auto len = str.GetLength();
			THEN("Compare value")
			{
				REQUIRE(len == 9);
			}
		}
	}

	GIVEN("Sub string")
	{
		CMyString str("Empty str");
		WHEN("Get str data")
		{
			std::string data(str.SubString(5, 3).GetStringData());
			THEN("Compare value")
			{
				REQUIRE(data == "y s");
			}
		}
	}

	GIVEN("Clear")
	{
		CMyString str("Empty str");
		WHEN("Get str data")
		{
			str.Clear();
			std::string data(str.GetStringData());
			THEN("Compare value")
			{
				REQUIRE(data == "");
			}
		}
	}

	GIVEN("Get capacity")
	{
		CMyString str("Empty str");
		WHEN("Get str data")
		{
			auto len = str.GetCapacity();
			THEN("Compare value")
			{
				REQUIRE(len == defaultCap);
			}
		}
	}
}