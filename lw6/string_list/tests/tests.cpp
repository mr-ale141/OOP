#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../string_list/CStringList.h"
#include <iostream>

TEST_CASE("Public methods")
{
	GIVEN("Empty")
	{
		CStringList list;
		WHEN("Get size")
		{
			size_t size = list.GetSize();
			THEN("Compare value")
			{
				REQUIRE(size == 0);
			}
		}
	}
}
