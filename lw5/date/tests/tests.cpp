#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../date/CDate.h"
#include <sstream>

TEST_CASE("Create Date without parameters is 01.01.1970")
{
	GIVEN("Data")
	{
		CDate date;
		WHEN("Print self")
		{
			std::stringstream ss;
			ss << date;

			THEN("Compare value")
			{
				REQUIRE(ss.str() == "01.01.1970");
				REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);
			}
		}
	}
}

TEST_CASE("Create Date with any parameters")
{
	GIVEN("Data with parameter 0")
	{
		CDate date(0);
		WHEN("Print self")
		{
			std::stringstream ss;
			ss << date;

			THEN("Compare value")
			{
				REQUIRE(ss.str() == "01.01.1970");
				REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);
			}
		}
	}

	GIVEN("Data with parameter 1")
	{
		CDate date(1);
		WHEN("Print self")
		{
			std::stringstream ss;
			ss << date;

			THEN("Compare value")
			{
				REQUIRE(ss.str() == "02.01.1970");
				REQUIRE(date.GetWeekDay() == WeekDay::FRIDAY);
			}
		}
	}

	GIVEN("Data with parameter 01.03.2000 - new era of 400 years")
	{
		CDate date(1, Month::MARCH, 2000);
		WHEN("Print self")
		{
			std::stringstream ss;
			ss << date;

			THEN("Compare value")
			{
				REQUIRE(date.GetWeekDay() == WeekDay::WEDNESDAY);
				REQUIRE(date.GetDateStamp() == 11017);
				REQUIRE(ss.str() == "01.03.2000");
			}
		}
	}

	GIVEN("Data with parameter 11017 - new era of 400 years (2000 is leap)")
	{
		CDate date(11017);
		WHEN("Print self")
		{
			std::stringstream ss;
			ss << date;

			THEN("Compare value")
			{
				REQUIRE(date.GetWeekDay() == WeekDay::WEDNESDAY);
				REQUIRE(date.GetDateStamp() == 11017);
				REQUIRE(ss.str() == "01.03.2000");
			}
		}
	}

	GIVEN("Created date with negative dey")
	{
		CDate date(-10, Month::MARCH, 2000);
		WHEN("Print self")
		{
			std::stringstream ss;
			ss << date;

			THEN("Compare value")
			{
				REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);
				REQUIRE(date.GetDateStamp() == 0);
				REQUIRE(!date);
				REQUIRE(ss.str() == "INVALID");
			}
		}
	}

	GIVEN("Created date with overflow dey")
	{
		CDate date(32, Month::MARCH, 2000);
		WHEN("Print self")
		{
			std::stringstream ss;
			ss << date;

			THEN("Compare value")
			{
				REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);
				REQUIRE(date.GetDateStamp() == 0);
				REQUIRE(!date);
				REQUIRE(ss.str() == "INVALID");
			}
		}
	}

	GIVEN("Created date with incorrect year")
	{
		CDate date(2, Month::MARCH, 1969);
		WHEN("Print self")
		{
			std::stringstream ss;
			ss << date;

			THEN("Compare value")
			{
				REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);
				REQUIRE(date.GetDateStamp() == 0);
				REQUIRE(!date);
				REQUIRE(ss.str() == "INVALID");
			}
		}
	}

	GIVEN("Created date with oferflow year")
	{
		CDate date(2, Month::MARCH, 10000);
		WHEN("Print self")
		{
			std::stringstream ss;
			ss << date;

			THEN("Compare value")
			{
				REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);
				REQUIRE(date.GetDateStamp() == 0);
				REQUIRE(!date);
				REQUIRE(ss.str() == "INVALID");
			}
		}
	}

	GIVEN("Created date with start dey in year")
	{
		CDate date(1, Month::JANUARY, 2025);
		WHEN("Print self")
		{
			std::stringstream ss;
			ss << date;

			THEN("Compare value")
			{
				REQUIRE(date.GetWeekDay() == WeekDay::WEDNESDAY);
				REQUIRE(date.GetDateStamp() == 20089);
				REQUIRE(ss.str() == "01.01.2025");
			}
		}
	}

	GIVEN("Created date with last dey in year")
	{
		CDate date(31, Month::DECEMBER, 2025);
		WHEN("Print self")
		{
			std::stringstream ss;
			ss << date;

			THEN("Compare value")
			{
				REQUIRE(date.GetDateStamp() == 20453);
				REQUIRE(ss.str() == "31.12.2025");
				REQUIRE(date.GetWeekDay() == WeekDay::WEDNESDAY);
			}
		}
	}

	GIVEN("Created date with last dey in year")
	{
		CDate date(29, Month::FEBRUARY, 2024);
		WHEN("Print self")
		{
			std::stringstream ss;
			ss << date;

			THEN("Compare value")
			{
				REQUIRE(ss.str() == "29.02.2024");
			}
		}
	}
}

TEST_CASE("Increment and decrement with Date")
{
	GIVEN("Create data 31.12.2025")
	{
		CDate date(31, Month::DECEMBER, 2025);
		REQUIRE(date.GetWeekDay() == WeekDay::WEDNESDAY);
		REQUIRE(date.GetDateStamp() == 20453);

		WHEN("Prefix increment date")
		{
			auto dateNext = ++date;
			THEN("Compare value date")
			{
				std::stringstream ss;
				ss << date;
				REQUIRE(ss.str() == "01.01.2026");
				REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);
			}

			THEN("Compare value dateNext")
			{
				std::stringstream ss;
				ss << dateNext;
				REQUIRE(ss.str() == "01.01.2026");
				REQUIRE(dateNext.GetWeekDay() == WeekDay::THURSDAY);

			}
		}

		WHEN("Prefix decrement date")
		{
			auto dateNext = --date;
			THEN("Compare value date")
			{
				std::stringstream ss;
				ss << date;
				REQUIRE(ss.str() == "30.12.2025");
				REQUIRE(date.GetWeekDay() == WeekDay::TUESDAY);
			}

			THEN("Compare value dateNext")
			{
				std::stringstream ss;
				ss << dateNext;
				REQUIRE(ss.str() == "30.12.2025");
				REQUIRE(dateNext.GetWeekDay() == WeekDay::TUESDAY);

			}
		}

		WHEN("Postfix increment date")
		{
			auto dateOld = date++;
			THEN("Compare value")
			{
				std::stringstream ss;
				ss << date;
				REQUIRE(ss.str() == "01.01.2026");
				REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);
			}

			THEN("Compare value dateOld")
			{
				std::stringstream ss;
				ss << dateOld;
				REQUIRE(ss.str() == "31.12.2025");
				REQUIRE(dateOld.GetWeekDay() == WeekDay::WEDNESDAY);

			}
		}

		WHEN("Postfix decrement date")
		{
			auto dateOld = date--;
			THEN("Compare value")
			{
				std::stringstream ss;
				ss << date;
				REQUIRE(ss.str() == "30.12.2025");
				REQUIRE(date.GetWeekDay() == WeekDay::TUESDAY);
			}

			THEN("Compare value dateOld")
			{
				std::stringstream ss;
				ss << dateOld;
				REQUIRE(ss.str() == "31.12.2025");
				REQUIRE(dateOld.GetWeekDay() == WeekDay::WEDNESDAY);

			}
		}
	}
}

TEST_CASE("Arifmetic with date")
{
	GIVEN("Data 31.12.2024")
	{
		CDate date(31, Month::DECEMBER, 2024);

		std::stringstream ss;
		ss << date;
		REQUIRE(ss.str() == "31.12.2024");
		REQUIRE(date.GetWeekDay() == WeekDay::TUESDAY);

		WHEN("Add 2 days")
		{
			auto newDate = date + 2;

			THEN("Compare date")
			{
				ss.str("");
				ss << date;
				REQUIRE(ss.str() == "31.12.2024");
				REQUIRE(date.GetWeekDay() == WeekDay::TUESDAY);
			}

			THEN("Compare newDate")
			{
				ss.str("");
				ss << newDate;
				REQUIRE(ss.str() == "02.01.2025");
				REQUIRE(newDate.GetWeekDay() == WeekDay::THURSDAY);
			}
		}

		WHEN("Sub 2 days")
		{
			auto newDate = date - 2;

			THEN("Compare date")
			{
				ss.str("");
				ss << date;
				REQUIRE(ss.str() == "31.12.2024");
				REQUIRE(date.GetWeekDay() == WeekDay::TUESDAY);
			}

			THEN("Compare newDate")
			{
				ss.str("");
				ss << newDate;
				REQUIRE(ss.str() == "29.12.2024");
				REQUIRE(newDate.GetWeekDay() == WeekDay::SUNDAY);
			}
		}

		WHEN("Add 32 days")
		{
			date += 32;

			THEN("Compare date")
			{
				ss.str("");
				ss << date;
				REQUIRE(ss.str() == "01.02.2025");
				REQUIRE(date.GetWeekDay() == WeekDay::SATURDAY);
			}
		}

		WHEN("Sub 31 days")
		{
			date -= 31;

			THEN("Compare date")
			{
				ss.str("");
				ss << date;
				REQUIRE(ss.str() == "30.11.2024");
				REQUIRE(date.GetWeekDay() == WeekDay::SATURDAY);
			}
		}

		WHEN("Add 400 years")
		{
			date += 400 * 365 + 97;

			THEN("Compare date")
			{
				ss.str("");
				ss << date;
				REQUIRE(ss.str() == "31.12.2424");
			}
		}
	}

	GIVEN("Data 01.01.2000")
	{
		CDate date(01, Month::JANUARY, 2000);

		std::stringstream ss;
		ss << date;
		REQUIRE(ss.str() == "01.01.2000");
		REQUIRE(date.GetWeekDay() == WeekDay::SATURDAY);

		WHEN("Add 400 years")
		{
			date += 400 * 365 + 97;

			THEN("Compare date")
			{
				ss.str("");
				ss << date;
				REQUIRE(ss.str() == "01.01.2400");
			}
		}

		WHEN("Add 400 years + 365")
		{
			date += 400 * 365 + 97 + 365;
			
			THEN("Compare date")
			{
				ss.str("");
				ss << date;
				REQUIRE(ss.str() == "31.12.2400");
			}
		}

		WHEN("Add 200 years + 365")
		{
			date += 200 * 365 + 48 + 365;

			THEN("Compare date")
			{
				ss.str("");
				ss << date;
				REQUIRE(ss.str() == "31.12.2200");
			}
		}
	}

	GIVEN("Data 01.01.2010 and 30.12.2009")
	{
		CDate date1(01, Month::JANUARY, 2010);
		CDate date2(30, Month::DECEMBER, 2009);

		WHEN("Add 400 years")
		{
			int num = date1 - date2;

			THEN("Compare date")
			{
				REQUIRE(num == 2);
			}
		}
	}

	GIVEN("Data 01.01.2010 and 03.01.2010")
	{
		CDate date1(01, Month::JANUARY, 2010);
		CDate date2(03, Month::JANUARY, 2010);

		WHEN("Add 400 years")
		{
			int num = date1 - date2;

			THEN("Compare date")
			{
				REQUIRE(num == -2);
			}
		}
	}

	GIVEN("Data 01.01.1970 and 01.01.2000")
	{
		CDate date1(01, Month::JANUARY, 2000);
		CDate date2(01, Month::JANUARY, 1970);

		WHEN("Add 400 years")
		{
			int num = date1 - date2;

			THEN("Compare date")
			{
				REQUIRE(num == 10957);
			}
		}
	}
}
