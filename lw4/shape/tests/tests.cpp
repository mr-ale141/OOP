#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../../../Catch2/fakeit.hpp"
#include "../shape/ShapeList.h"
#include <fstream>

static bool CompareFiles(std::string& fileName1, std::string& fileName2)
{
	std::ifstream f1(fileName1);
	std::ifstream f2(fileName2);
	if (!f1 || !f2)
		throw std::ios_base::failure("ERROR! Can't open file for compare!");

	bool answer = true;

	char c1{};
	char c2{};
	while (f1.get(c1) && f2.get(c2))
		if (c1 != c2)
			return false;

	if (f1.eof() && f1.eof())
		return answer;
	else
		return false;
}

TEST_CASE("Draw Home")
{
	GIVEN("Input data")
	{
		std::string inputFileName("in/home.txt");
		std::string outputFileName("out/home.html");
		std::string compareFileName("cmp/home.html");

		std::ifstream input(inputFileName);

		WHEN("Create ShapeList and execute commands")
		{
			{
				ShapeList shapeList(outputFileName);
				std::string str;
				while (std::getline(input, str))
				{
					std::stringstream ss(str);
					shapeList.Add(ss);
				}
			}

			THEN("Compare out file")
			{
				REQUIRE(CompareFiles(outputFileName, compareFileName));
			}
		}
	}
}

TEST_CASE("Smaller Area")
{
	GIVEN("Input data")
	{
		std::string inputFileName("in/small_area.txt");
		std::string outputFileName("out/small_area.html");

		std::ifstream input(inputFileName);

		WHEN("Create ShapeList and execute commands")
		{
			ShapeList shapeList(outputFileName);
			std::string str;
			while (std::getline(input, str))
			{
				std::stringstream ss(str);
				shapeList.Add(ss);
			}

			auto minAreaShape = shapeList.GetMinArea();

			THEN("Check small area")
			{
				REQUIRE(minAreaShape != nullptr);
				REQUIRE(minAreaShape->GetArea() == 1.0);
			}
		}
	}
}

TEST_CASE("Smaller Perimeter")
{
	GIVEN("Input data")
	{
		std::string inputFileName("in/small_perimeter.txt");
		std::string outputFileName("out/small_perimeter.html");

		std::ifstream input(inputFileName);

		WHEN("Create ShapeList and execute commands")
		{
			ShapeList shapeList(outputFileName);
			std::string str;
			while (std::getline(input, str))
			{
				std::stringstream ss(str);
				shapeList.Add(ss);
			}

			auto minPerimeterShape = shapeList.GetMinPerimeter();

			THEN("Check small Perimeter")
			{
				REQUIRE(minPerimeterShape != nullptr);
				REQUIRE(minPerimeterShape->GetPerimeter() == 1.0);
			}
		}
	}
}

using namespace fakeit;

TEST_CASE("Methods 'Draw' in shapes")
{
	Mock<ICanvas> mockCanvas;

	int primitiveCount = 0;

	int* ptr = &primitiveCount;

	When(Method(mockCanvas, DrawLine)).AlwaysDo([ptr](CPoint from, CPoint to, uint32_t lineColor)
		{
			(*ptr)++;
		});
	When(Method(mockCanvas, FillPolygon)).AlwaysDo([ptr](std::vector<CPoint>& points, uint32_t fillColor)
		{
			(*ptr)++;
		});
	When(Method(mockCanvas, DrawCircle)).AlwaysDo([ptr](CPoint center, double radius, uint32_t lineColor)
		{
			(*ptr)++;
		});
	When(Method(mockCanvas, FillCircle)).AlwaysDo([ptr](CPoint center, double radius, uint32_t fillColor)
		{
			(*ptr)++;
		});

	ICanvas& mockInterface = mockCanvas.get();

	GIVEN("ShapesList witn Mock Canvas")
	{
		ShapeList shapeList("test.html");
		shapeList.ChangeCanvasI(&mockInterface);

		WHEN("Add correct triangle")
		{
			std::stringstream ss("Triangle 225 300 575 300 400 150 000000 00ff00");
			shapeList.Add(ss);

			THEN("Added 4 primitives")
			{
				REQUIRE(primitiveCount == 4);
			}
		}

		WHEN("Add correct rectangle")
		{
			std::stringstream ss("Rectangle 250 300 300 200 000000 ffff00");
			shapeList.Add(ss);

			THEN("Added 5 primitives")
			{
				REQUIRE(primitiveCount == 5);
			}
		}

		WHEN("Add correct circle")
		{
			std::stringstream ss("Circle 490 164 15 87ceeb 87ceeb");
			shapeList.Add(ss);

			THEN("Added 2 primitives")
			{
				REQUIRE(primitiveCount == 2);
			}
		}

		WHEN("Add correct line")
		{
			std::stringstream ss("LineSegment 470 380 510 380 000000");
			shapeList.Add(ss);

			THEN("Added 1 primitives")
			{
				REQUIRE(primitiveCount == 1);
			}
		}

		WHEN("Add line with negative parameter")
		{
			std::stringstream ss("LineSegment -470 380 510 -380 000000");
			shapeList.Add(ss);

			THEN("Added 0 primitives")
			{
				REQUIRE(primitiveCount == 0);
			}
		}

		WHEN("Add circle with negative parameter")
		{
			std::stringstream ss("Circle 490 -164 15 87ceeb 87ceeb");
			shapeList.Add(ss);

			THEN("Added 0 primitives")
			{
				REQUIRE(primitiveCount == 0);
			}
		}

		WHEN("Add triangle with negative parameter")
		{
			std::stringstream ss("Triangle 225 -300 575 -300 400 150 000000 00ff00");
			shapeList.Add(ss);

			THEN("Added 0 primitives")
			{
				REQUIRE(primitiveCount == 0);
			}
		}

		WHEN("Add rectangle with negative parameter")
		{
			std::stringstream ss("Rectangle 250 300 300 -200 000000 ffff00");
			shapeList.Add(ss);

			THEN("Added 0 primitives")
			{
				REQUIRE(primitiveCount == 0);
			}
		}

		WHEN("Add line with overflow color")
		{
			std::stringstream ss("LineSegment 470 380 510 380 1000000");
			shapeList.Add(ss);

			THEN("Added 0 primitives")
			{
				REQUIRE(primitiveCount == 0);
			}
		}

		WHEN("Add circle with overflow color")
		{
			std::stringstream ss("Circle 490 164 15 1000000 87ceeb");
			shapeList.Add(ss);

			THEN("Added 0 primitives")
			{
				REQUIRE(primitiveCount == 0);
			}
		}

		WHEN("Add triangle with negative color")
		{
			std::stringstream ss("Triangle 225 300 575 300 400 150 000000 -00ff00");
			shapeList.Add(ss);

			THEN("Added 0 primitives")
			{
				REQUIRE(primitiveCount == 0);
			}
		}

		WHEN("Add rectangle with overflow color")
		{
			std::stringstream ss("Rectangle 250 300 300 200 000000 1000000");
			shapeList.Add(ss);

			THEN("Added 0 primitives")
			{
				REQUIRE(primitiveCount == 0);
			}
		}

		WHEN("Add line with overflow X")
		{
			std::stringstream ss("LineSegment 801 380 510 380 000000");
			shapeList.Add(ss);

			THEN("Added 0 primitives")
			{
				REQUIRE(primitiveCount == 0);
			}
		}

		WHEN("Add circle with overflow Y")
		{
			std::stringstream ss("Circle 490 601 15 000000 87ceeb");
			shapeList.Add(ss);

			THEN("Added 0 primitives")
			{
				REQUIRE(primitiveCount == 0);
			}
		}

		WHEN("Add triangle with overflow Y and X")
		{
			std::stringstream ss("Triangle 801 601 575 300 400 150 000000 -00ff00");
			shapeList.Add(ss);

			THEN("Added 0 primitives")
			{
				REQUIRE(primitiveCount == 0);
			}
		}

		WHEN("Add rectangle with overflow Y and X")
		{
			std::stringstream ss("Rectangle 250 300 801 601 000000 000000");
			shapeList.Add(ss);

			THEN("Added 0 primitives")
			{
				REQUIRE(primitiveCount == 0);
			}
		}
	}
}
