#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "labyrinth.h"

bool CompareFiles(const std::string& fileName1, const std::string& fileName2)
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

TEST_CASE("Test Case 'Empty name file'")
{
	std::string inputFileName("");
	std::string outputFileName("");
	try
	{
		FindPath(inputFileName, outputFileName);
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("Can't open") != std::string::npos);
		return;
	}
	REQUIRE(1 == 0);
}

TEST_CASE("Test Case 'Smoke test'")
{
	std::string inputFileName("in\\smoke.txt");
	std::string outputFileName("out\\smoke.txt");
	try
	{
		FindPath(inputFileName, outputFileName);
	}
	catch (...)
	{
		REQUIRE(1 == 0);
		return;
	}
	REQUIRE(CompareFiles(outputFileName, std::string("compare\\smoke.txt")));
}

TEST_CASE("Test Case 'Outside path test'")
{
	std::string inputFileName("in\\outside_path.txt");
	std::string outputFileName("out\\outside_path.txt");
	try
	{
		FindPath(inputFileName, outputFileName);
	}
	catch (...)
	{
		REQUIRE(1 == 0);
		return;
	}
	REQUIRE(CompareFiles(outputFileName, std::string("compare\\outside_path.txt")));
}

TEST_CASE("Test Case 'Outside test'")
{
	std::string inputFileName("in\\outside.txt");
	std::string outputFileName("out\\outside.txt");
	try
	{
		FindPath(inputFileName, outputFileName);
	}
	catch (...)
	{
		REQUIRE(1 == 0);
		return;
	}
	REQUIRE(CompareFiles(outputFileName, std::string("compare\\outside.txt")));
}

TEST_CASE("Test Case 'Double 'A' test'")
{
	std::string inputFileName("in\\double_a.txt");
	std::string outputFileName("out\\double_a.txt");
	try
	{
		FindPath(inputFileName, outputFileName);
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("'A' many times") != std::string::npos);
		return;
	}
	REQUIRE(1 == 0);
}

TEST_CASE("Test Case 'Double 'B' test'")
{
	std::string inputFileName("in\\double_b.txt");
	std::string outputFileName("out\\double_b.txt");
	try
	{
		FindPath(inputFileName, outputFileName);
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("'B' many times") != std::string::npos);
		return;
	}
	REQUIRE(1 == 0);
}

TEST_CASE("Test Case 'Without 'A' test'")
{
	std::string inputFileName("in\\without_a.txt");
	std::string outputFileName("out\\without_a.txt");
	try
	{
		FindPath(inputFileName, outputFileName);
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("not contains 'A', 'B'") != std::string::npos);
		return;
	}
	REQUIRE(1 == 0);
}

TEST_CASE("Test Case 'Without 'B' test'")
{
	std::string inputFileName("in\\without_b.txt");
	std::string outputFileName("out\\without_b.txt");
	try
	{
		FindPath(inputFileName, outputFileName);
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("not contains 'A', 'B'") != std::string::npos);
		return;
	}
	REQUIRE(1 == 0);
}

TEST_CASE("Test Case 'Without 'A', 'B' test'")
{
	std::string inputFileName("in\\without_a_b.txt");
	std::string outputFileName("out\\without_a_b.txt");
	try
	{
		FindPath(inputFileName, outputFileName);
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("not contains 'A', 'B'") != std::string::npos);
		return;
	}
	REQUIRE(1 == 0);
}