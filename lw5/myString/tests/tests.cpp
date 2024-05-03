#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../myString/CMyString.h"
#include <string>
#include <sstream>
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
				REQUIRE(str == "");
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
				REQUIRE(str == "Empty str");
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
				REQUIRE(str == str1);
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

TEST_CASE("Operator = with self")
{
	GIVEN("Some string")
	{
		CMyString str("Some string");
		WHEN("self-education")
		{
			str = str;
			THEN("Compare value")
			{
				std::string data(str.GetStringData());
				REQUIRE(data == "Some string");
			}
		}

		WHEN("education")
		{
			CMyString str1 = str;
			THEN("Compare value")
			{
				std::string data(str1.GetStringData());
				REQUIRE(data == "Some string");
			}
		}
	}
}

TEST_CASE("Operator +")
{
	GIVEN("Some string")
	{
		CMyString str1("Str1");

		WHEN("sum with CMyString")
		{
			CMyString str2("Str2");
			CMyString str = str1 + str2;
			THEN("Compare value")
			{
				std::string data(str.GetStringData());
				REQUIRE(data == "Str1Str2");
			}
		}

		WHEN("sum with std::string")
		{
			std::string stdStr("stdStr");
			CMyString str = stdStr + str1;
			CMyString strSwap = str1 + stdStr;
			THEN("Compare value")
			{
				std::string data(str.GetStringData());
				std::string dataSwap(strSwap.GetStringData());
				REQUIRE(data == "stdStrStr1");
				REQUIRE(dataSwap == "Str1stdStr");
			}
		}

		WHEN("sum with const char*")
		{
			CMyString str = "hello" + str1;
			CMyString strSwap = str1 + "hello";
			THEN("Compare value")
			{
				std::string data(str.GetStringData());
				std::string dataSwap(strSwap.GetStringData());
				REQUIRE(data == "helloStr1");
				REQUIRE(dataSwap == "Str1hello");
			}
		}
	}
}

TEST_CASE("Operator +=")
{
	GIVEN("Some string")
	{
		CMyString myStr("myStr");

		WHEN("sum with CMyString")
		{
			CMyString str2("Str2");
			myStr += str2;
			THEN("Compare value")
			{
				std::string data(myStr.GetStringData());
				REQUIRE(data == "myStrStr2");
			}
		}
	}
}

TEST_CASE("Operator ==")
{
	GIVEN("Some string")
	{
		CMyString myStr("myStr");

		WHEN("create compare string < length")
		{
			CMyString str2("Str2");
			THEN("Compare value")
			{
				REQUIRE(!(myStr == str2));
			}
		}

		WHEN("create compare string current length")
		{
			CMyString str2("mystr");
			THEN("Compare value")
			{
				REQUIRE(!(myStr == str2));
			}
		}

		WHEN("create compare string")
		{
			CMyString str2("myStr");
			THEN("Compare value")
			{
				REQUIRE(myStr == str2);
			}
		}
	}
}

TEST_CASE("Operator <, <=  and >, >=")
{
	GIVEN("Some string")
	{
		CMyString myStr("12345");

		WHEN("create compare string >")
		{
			CMyString str2("2");
			THEN("Compare value")
			{
				REQUIRE(myStr < str2);
				REQUIRE(!(myStr > str2));
				REQUIRE(!(myStr >= str2));
				REQUIRE(myStr <= str2);
				REQUIRE(!(CMyString("308") < CMyString("21")));
			}
		}

		WHEN("create compare string > length")
		{
			CMyString str2("123456");
			THEN("Compare value")
			{
				REQUIRE(myStr < str2);
				REQUIRE(!(myStr > str2));
				REQUIRE(!(myStr >= str2));
				REQUIRE(myStr <= str2);
			}
		}

		WHEN("create compare ==")
		{
			CMyString str2("12345");
			THEN("Compare value")
			{
				REQUIRE(!(myStr < str2));
				REQUIRE(!(myStr > str2));
				REQUIRE(myStr >= str2);
				REQUIRE(myStr <= str2);
			}
		}
	}
}

TEST_CASE("Operator []")
{
	GIVEN("Some string")
	{
		CMyString myStr("012345");

		WHEN("get char index -1")
		{
			try
			{
				char ch = myStr[-1];
			}
			catch (...)
			{
				REQUIRE(true);
				return;
			}
			REQUIRE(false);
		}

		WHEN("get char index 6")
		{
			try
			{
				char ch = myStr[6];
			}
			catch (...)
			{
				REQUIRE(true);
				return;
			}
			REQUIRE(false);
		}

		WHEN("get char index 0")
		{
			char ch = myStr[0];
			REQUIRE(ch == '0');
		}

		WHEN("get char index 5")
		{
			char ch = myStr[5];
			REQUIRE(ch == '5');
		}
	}
}

TEST_CASE("Operator <<")
{
	GIVEN("Some string")
	{
		CMyString myStr("myStr");

		WHEN("stringstream << myStr")
		{
			std::stringstream ss;
			ss << myStr;
			THEN("Compare value")
			{
				REQUIRE(ss.str() == "myStr");
			}
		}
	}
}

TEST_CASE("Operator >>")
{
	GIVEN("Some stringstream")
	{
		std::stringstream ss("string stream");

		WHEN("stringstream >> myStr")
		{
			CMyString myStr;
			ss >> myStr;
			THEN("Compare value")
			{
				std::string data(myStr.GetStringData());
				REQUIRE(data == "string");
			}
		}
	}
}

TEST_CASE("Iterator")
{
	GIVEN("Some stringstream")
	{
		CMyString str("IS UPPER STRING");

		WHEN("get value with arifmetic and increment")
		{
			auto it = str.begin();
			THEN("Compare value")
			{
				REQUIRE(*it == str.GetStringData()[0]);
			}

			THEN("Prefix inc compare value")
			{
				++it;
				REQUIRE(*it == str.GetStringData()[1]);
			}

			THEN("Postfix inc compare value")
			{
				it++;
				REQUIRE(*it == str.GetStringData()[1]);
			}

			THEN("Move iterator")
			{
				auto newIt = it + 2;
				REQUIRE(*newIt == str.GetStringData()[2]);
				newIt -= 2;
				REQUIRE(*newIt == str.GetStringData()[0]);
			}
		}

		WHEN("std::tolower")
		{
			std::transform(str.begin(), str.end(), str.begin(),
				[](unsigned char c) { return std::tolower(c); });
			THEN("Compare value")
			{
				REQUIRE(str == "is upper string");
			}
		}
	}

	GIVEN("std::sort")
	{
		CMyString str("54389061");

		WHEN("sort")
		{
			std::sort(str.begin(), str.end());
			THEN("Compare value")
			{
				REQUIRE(str == "01345689");
			}
		}
	}
}
