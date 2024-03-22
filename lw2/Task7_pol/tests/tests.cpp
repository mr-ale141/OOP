#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Task7_pol/polNot.h"
#include <sstream>


TEST_CASE("Smoke")
{
	std::string stream("(+ 2 3)");

	auto res = Calculate(stream);

	REQUIRE(res == 5);
}
