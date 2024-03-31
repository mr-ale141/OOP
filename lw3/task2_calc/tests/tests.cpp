#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../task2_calc/calculator.h"
#include <sstream>

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
