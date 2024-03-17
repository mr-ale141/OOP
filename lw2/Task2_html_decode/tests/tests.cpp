#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Task2_html_decode/html_decode.h"
#include <sstream>

TEST_CASE("Empty string")
{
	std::string input;
	std::string output;
	
	REQUIRE(HtmlDecode(input) == output);
}

TEST_CASE("Invalid token")
{
	std::string input("hello&ampl;world");
	std::string output("hello&ampl;world");

	REQUIRE(HtmlDecode(input) == output);
}

TEST_CASE("Token without end")
{
	std::string input("hello i &amp; am proger &amplworld");
	std::string output("hello i & am proger &amplworld");

	REQUIRE(HtmlDecode(input) == output);
}

TEST_CASE("Without token")
{
	std::string input("hello world!!!!!");
	std::string output("hello world!!!!!");

	REQUIRE(HtmlDecode(input) == output);
}

TEST_CASE("Mixed token")
{
	std::string input("hello&amp;lt;world!!!!!");
	std::string output("hello&lt;world!!!!!");

	REQUIRE(HtmlDecode(input) == output);
}

TEST_CASE("Double ampersand")
{
	std::string input("&&&&&&amp;lt;world!!!!!");
	std::string output("&&&&&&lt;world!!!!!");

	REQUIRE(HtmlDecode(input) == output);
}
