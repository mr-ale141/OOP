#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Task6_expTpl/expTpl.h"

TEST_CASE("Smoke test")
{
	std::string str = "hello world !!! i can";
	std::map<std::string, std::string> params =
	{
		{"!!!", "!"},
		{"i", "I"},
		{" ", "_"},
		{"or", "AND"},
	};
	auto result = ExpandTemplate(str, params);

	REQUIRE(result == "hello_wANDld_!_I_can");
}

TEST_CASE("Double words")
{
	std::string str = "hello world !!! i can";
	std::map<std::string, std::string> params =
	{
		{"hel", "HEL"},
		{"hello", "HELLO"},
		{" ", "_"},
		{"i", "I"},
	};
	auto result = ExpandTemplate(str, params);

	REQUIRE(result == "HELLO_world_!!!_I_can");
}

TEST_CASE("Split")
{
	std::string str = "&amp;lt;";
	std::map<std::string, std::string> params =
	{
		{"&amp;", "&"},
		{"&lt;", "<"},
		{" ", "_"},
		{"or", "AND"},
	};
	auto result = ExpandTemplate(str, params);

	REQUIRE(result == "&lt;");
}
