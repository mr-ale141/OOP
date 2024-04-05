#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../task2_calc/calculator.h"
#include <sstream>
#include <chrono>

TEST_CASE("Not init var is NAN")
{
	GIVEN("calculator")
	{
		std::stringstream output;
		Calculator calc(output);

		WHEN("execute commands")
		{
			calc.Exec("var x");
			calc.Exec("print x");

			std::string str;
			output.clear();
			std::getline(output, str);
			THEN("answer is 'nan'")
			{
				REQUIRE(str == "nan");
			}
		}
	}
}

TEST_CASE("Smoke")
{
	GIVEN("calculator")
	{
		std::stringstream output;
		Calculator calc(output);

		WHEN("execute commands")
		{
			calc.Exec("let x = 5");
			calc.Exec("fn f = x + x");
			calc.Exec("print f");

			std::string str;
			output.clear();
			std::getline(output, str);

			THEN("answer is '10.00'")
			{
				REQUIRE(str == "10.00");
			}
		}
	}
}

#ifndef _DEBUG
TEST_CASE("fibonacci")
{
	GIVEN("calculator")
	{
		std::stringstream output;
		Calculator calc(output);

		WHEN("set the data")
		{
			std::stringstream input;
			calc.Exec("let v0 = 0");
			calc.Exec("let v1 = 1");
			calc.Exec("fn fib0 = v0");
			calc.Exec("fn fib1 = v1");

			for (size_t i = 2; i <= 50; i++)
			{
				input.str("");
				input << "fn fib" << i << " = " << "fib" << i - 1 << " + fib" << i - 2;
				calc.Exec(input.str());
			}

			std::cout << std::endl << "Start fibonacci!" << std::endl;
			THEN("execute")
			{
				auto timeBegin = std::chrono::high_resolution_clock::now();

				calc.Exec("let v0 = 1");
				std::cout << "Next var!" << std::endl;
				calc.Exec("let v1 = 1");

				auto timeEnd = std::chrono::high_resolution_clock::now();
				auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeBegin);
				std::cout << "Delta Time = " << ms.count() << " ms" << std::endl;

				calc.Exec("print fib50");
				std::string str;
				std::getline(output, str);
				REQUIRE(str == "20365011074.00");
			}
		}
	}
}

TEST_CASE("1 000 000 test")
{
	GIVEN("calculator")
	{
		std::stringstream output;
		Calculator calc(output);

		WHEN("set the data")
		{
			std::stringstream input;
			calc.Exec("let x = 1");
			calc.Exec("fn x2 = x + x");

			for (size_t i = 3; i <= 1000000; i++)
			{
				input.str("");
				input << "fn x" << i << " = " << "x" << i - 1 << " + x";
				calc.Exec(input.str());
			}
			std::cout << "Start 1 000 000!" << std::endl;
			THEN("execute")
			{
				auto timeBegin = std::chrono::high_resolution_clock::now();
				
				calc.Exec("let x = 2");
				
				auto timeEnd = std::chrono::high_resolution_clock::now();
				auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeBegin);
				std::cout << "Delta Time = " << ms.count() << " ms" << std::endl;
				
				calc.Exec("print x1000000");
				std::string str;
				std::getline(output, str);
				REQUIRE(str == "2000000.00");
			}
		}
	}
}
#endif
