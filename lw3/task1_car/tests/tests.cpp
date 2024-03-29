#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../task1_car/car.h"

// R	0  – 20
// N	INF
// G1	0  – 30
// G2	20 – 50
// G3	30 – 60
// G4	40 – 90
// G5	50 – 150

TEST_CASE("Set Gear and Speed if Engine is OFF")
{
	GIVEN("car with default state where Engine is OFF")
	{
		Car car;
		REQUIRE(car.GetDirection() == STOP);
		REQUIRE(car.GetGear() == N);
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.IsTornedOn() == false);

		WHEN("Trying set GEAR R is failed")
		{
			REQUIRE(!car.SetGear((int)R));
		}

		WHEN("Trying set GEAR G1 is failed")
		{
			REQUIRE(!car.SetGear((int)G1));
		}

		WHEN("Trying set GEAR G2 is failed")
		{
			REQUIRE(!car.SetGear((int)G2));
		}

		WHEN("Trying increase SPEED == 0 with gear N is failed")
		{
			REQUIRE(!car.SetSpeed(car.GetSpeed() + 1));
		}

		WHEN("Trying decrease SPEED == 0 with gear N is failed")
		{
			REQUIRE(!car.SetSpeed(car.GetSpeed() - 1));
		}

		WHEN("Trying set SPEED = 0 with gear N is done")
		{
			REQUIRE(car.SetSpeed(0));
		}
	}
}

TEST_CASE("Turn OFF engine")
{
	GIVEN("car with default state where Engine is OFF")
	{
		Car car;
		REQUIRE(car.GetDirection() == STOP);
		REQUIRE(car.GetGear() == N);
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.IsTornedOn() == false);

		WHEN("Drive forward with speed = 30")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.SetGear((int)G1));
			REQUIRE(car.SetSpeed(30));
			// then
			WHEN("Trying turn OFF Engine is failed")
			{
				REQUIRE(!car.TurnOffEngine());
			}
		}

		WHEN("Drive back with speed = 20")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.SetGear((int)R));
			REQUIRE(car.SetSpeed(20));

			WHEN("Trying turn OFF Engine is failed")
			{
				REQUIRE(!car.TurnOffEngine());
			}
		}

		WHEN("Drive back with speed = 20")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.SetGear((int)R));
			REQUIRE(car.SetSpeed(20));

			WHEN("Trying turn OFF Engine without N is failed")
			{
				REQUIRE(car.SetSpeed(0));
				REQUIRE(!car.TurnOffEngine());
			}

			WHEN("Trying turn OFF Engine with N is done")
			{
				REQUIRE(car.SetSpeed(0));
				REQUIRE(car.SetGear((int)N));
				REQUIRE(car.TurnOffEngine());
			}
		}
	}
}

TEST_CASE("Set SPEED and GEAR with range")
{
	GIVEN("car with default state where Engine is OFF")
	{
		Car car;
		REQUIRE(car.GetDirection() == STOP);
		REQUIRE(car.GetGear() == N);
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.IsTornedOn() == false);

		WHEN("Drive forward with speed = 19")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.SetGear((int)G1));
			REQUIRE(car.SetSpeed(19));

			WHEN("Trying set GEAR 2 is failed")
			{
				REQUIRE(!car.SetGear((int)G2));
			}
		}

		WHEN("Drive forward with speed = 30")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.SetGear((int)G1));
			REQUIRE(car.SetSpeed(30));

			WHEN("Trying set GEAR 2 is done")
			{
				REQUIRE(car.SetGear((int)G2));
			}
		}

		WHEN("SET G1 and drive forward with speed = 30")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.SetGear((int)G1));
			REQUIRE(car.SetSpeed(30));

			WHEN("SET G2 and drive forward with speed = 50")
			{
				REQUIRE(car.SetGear((int)G2));
				REQUIRE(car.SetSpeed(50));

				WHEN("Trying set GEAR 1 is failed")
				{
					REQUIRE(!car.SetGear((int)G1));
				}
			}
		}

		WHEN("SET G1 and drive forward with speed = 30")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.SetGear((int)G1));
			REQUIRE(car.SetSpeed(30));

			WHEN("SET G2 and drive forward with speed = 50")
			{
				REQUIRE(car.SetGear((int)G2));
				REQUIRE(car.SetSpeed(50));

				WHEN("Slow down to 30")
				{
					REQUIRE(car.SetSpeed(30));
					
					WHEN("Trying set GEAR 1 is done")
					{
						REQUIRE(car.SetGear((int)G1));
					}
				}
			}
		}
	}
}

TEST_CASE("Chenge direction")
{
	GIVEN("car with default state where Engine is OFF")
	{
		Car car;
		REQUIRE(car.GetDirection() == STOP);
		REQUIRE(car.GetGear() == N);
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.IsTornedOn() == false);

		WHEN("Drive forward with speed = 20")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.SetGear((int)G1));
			REQUIRE(car.SetSpeed(20));

			WHEN("Trying set GEAR R is failed")
			{
				REQUIRE(!car.SetGear((int)R));
			}

			WHEN("Trying set GEAR R befor STOP is done")
			{
				REQUIRE(car.SetSpeed(0));
				REQUIRE(car.SetGear((int)R));
			}
		}

		WHEN("Drive back with speed = 20")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.SetGear((int)R));
			REQUIRE(car.SetSpeed(20));

			WHEN("Trying set GEAR 1 is failed")
			{
				REQUIRE(!car.SetGear((int)G1));
			}

			WHEN("Trying set GEAR G1 befor STOP is done")
			{
				REQUIRE(car.SetSpeed(0));
				REQUIRE(car.SetGear((int)G1));
			}
		}
	}
}

TEST_CASE("Chenge SPEED with N")
{
	GIVEN("car with default state where Engine is OFF")
	{
		Car car;
		REQUIRE(car.GetDirection() == STOP);
		REQUIRE(car.GetGear() == N);
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.IsTornedOn() == false);

		WHEN("Drive forward with speed = 20")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.SetGear((int)G1));
			REQUIRE(car.SetSpeed(20));

			WHEN("Trying set GEAR N and boost is failed")
			{
				REQUIRE(car.SetGear((int)N));
				REQUIRE(!car.SetSpeed(30));
			}

			WHEN("Trying set GEAR N and slow down is done")
			{
				REQUIRE(car.SetGear((int)N));
				REQUIRE(car.SetSpeed(10));
			}
		}
	}
}
