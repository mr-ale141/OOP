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

			REQUIRE(str == "nan");
		}
	}
}

