#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Task7_pol/polNot.h"
#include <sstream>

TEST_CASE("One operand with SUM")
{
	std::stringstream stream("(+ 7)");

	auto res = Calculate(stream);

	REQUIRE(res == 7);
}

TEST_CASE("One operand with MULT")
{
	std::stringstream stream("(* 8)");

	auto res = Calculate(stream);

	REQUIRE(res == 8);
}

TEST_CASE("Two operand")
{
	std::stringstream stream("(+ 2 3)");

	auto res = Calculate(stream);

	REQUIRE(res == 5);
}

TEST_CASE("Three operand")
{
	std::stringstream stream("(+ 2 3 4)");

	auto res = Calculate(stream);

	REQUIRE(res == 9);
}

TEST_CASE("Three operand with negative")
{
	std::stringstream stream("(+ 2 -3 4)");

	auto res = Calculate(stream);

	REQUIRE(res == 3);
}

TEST_CASE("Nested operations with SUM")
{
	std::stringstream stream("(+ (* 2 3) (* 3 4))");

	auto res = Calculate(stream);

	REQUIRE(res == 18);
}

TEST_CASE("Nested operations with MULT")
{
	std::stringstream stream("(* (+ 1 2) (+ 3 1))");

	auto res = Calculate(stream);

	REQUIRE(res == 12);
}

TEST_CASE("Multiple nested operations")
{
	std::stringstream stream("(+ 5 (* 2 3 2) (+ 5 (+ 2 5) (* 2 2) ))");

	auto res = Calculate(stream);

	REQUIRE(res == 33);
}
