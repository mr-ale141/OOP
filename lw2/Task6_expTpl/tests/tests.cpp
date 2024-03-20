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
	};
	auto result = ExpandTemplate(str, params);

	REQUIRE(result == "hello_world_!_I_can");
}
