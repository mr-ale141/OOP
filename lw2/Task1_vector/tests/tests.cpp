#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "iovector.h"
#include "vector_multiplier.h"


bool CompareFiles(std::string& fileName1, std::string& fileName2)
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

TEST_CASE("Test Case 'Smoke test'")
{
	auto inputFileName = std::string("in\\smoke.txt");
	auto outputFileName = std::string("out\\smoke.txt");
	auto compareFileName = std::string("compare\\smoke.txt");
	try
	{
		std::ifstream input(inputFileName);
		std::ofstream output(outputFileName);
		if (!input.is_open() || !output.is_open())
			throw std::ios_base::failure("ERROR! Can't open file for compare!");

		auto v = GetVectorDouble(input);
		MultipliedByMin(v);
		WriteVectorDouble(output, v);

		if (!output.flush())
		{
			throw std::ios_base::failure("ERROR! Can't write in output file");
		}

		input.close();
		output.close();

		REQUIRE(CompareFiles(outputFileName, compareFileName));
	}
	catch (...)
	{
		REQUIRE(1 == 0);
		return;
	}
}

TEST_CASE("Test Case 'Invalid input'")
{
	auto inputFileName = std::string("in\\invalid.txt");
	try
	{
		std::ifstream input(inputFileName);
		GetVectorDouble(input);
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("Invalid input data") != std::string::npos);
		return;
	}
	std::cout << "ERROR! '0.f' - read into the double variable!" << std::endl;
	REQUIRE(1 == 0);
}

TEST_CASE("Test Case 'Single number'")
{
	auto inputFileName = std::string("in\\single.txt");
	auto outputFileName = std::string("out\\single.txt");
	auto compareFileName = std::string("compare\\single.txt");
	try
	{
		std::ifstream input(inputFileName);
		std::ofstream output(outputFileName);
		if (!input.is_open() || !output.is_open())
			throw std::ios_base::failure("ERROR! Can't open file for compare!");

		auto v = GetVectorDouble(input);
		MultipliedByMin(v);
		WriteVectorDouble(output, v);

		if (!output.flush())
		{
			throw std::ios_base::failure("ERROR! Can't write in output file");
		}

		input.close();
		output.close();

		REQUIRE(CompareFiles(outputFileName, compareFileName));
	}
	catch (...)
	{
		REQUIRE(1 == 0);
		return;
	}
}

TEST_CASE("Test Case 'Empty array'")
{
	auto inputFileName = std::string("in\\empty.txt");
	auto outputFileName = std::string("out\\empty.txt");
	auto compareFileName = std::string("compare\\empty.txt");
	try
	{
		std::ifstream input(inputFileName);
		std::ofstream output(outputFileName);
		if (!input.is_open() || !output.is_open())
			throw std::ios_base::failure("ERROR! Can't open file for compare!");

		auto v = GetVectorDouble(input);
		MultipliedByMin(v);
		WriteVectorDouble(output, v);

		if (!output.flush())
		{
			throw std::ios_base::failure("ERROR! Can't write in output file");
		}

		input.close();
		output.close();

		REQUIRE(CompareFiles(outputFileName, compareFileName));
	}
	catch (...)
	{
		REQUIRE(1 == 0);
		return;
	}
}

TEST_CASE("Test Case 'Min in negative'")
{
	auto inputFileName = std::string("in\\negative.txt");
	auto outputFileName = std::string("out\\negative.txt");
	auto compareFileName = std::string("compare\\negative.txt");
	try
	{
		std::ifstream input(inputFileName);
		std::ofstream output(outputFileName);
		if (!input.is_open() || !output.is_open())
			throw std::ios_base::failure("ERROR! Can't open file for compare!");

		auto v = GetVectorDouble(input);
		MultipliedByMin(v);
		WriteVectorDouble(output, v);

		if (!output.flush())
		{
			throw std::ios_base::failure("ERROR! Can't write in output file");
		}

		input.close();
		output.close();

		REQUIRE(CompareFiles(outputFileName, compareFileName));
	}
	catch (...)
	{
		REQUIRE(1 == 0);
		return;
	}
}

TEST_CASE("Test Case 'Zero array'")
{
	auto inputFileName = std::string("in\\zero.txt");
	auto outputFileName = std::string("out\\zero.txt");
	auto compareFileName = std::string("compare\\zero.txt");
	try
	{
		std::ifstream input(inputFileName);
		std::ofstream output(outputFileName);
		if (!input.is_open() || !output.is_open())
			throw std::ios_base::failure("ERROR! Can't open file for compare!");

		auto v = GetVectorDouble(input);
		MultipliedByMin(v);
		WriteVectorDouble(output, v);

		if (!output.flush())
		{
			throw std::ios_base::failure("ERROR! Can't write in output file");
		}

		input.close();
		output.close();

		REQUIRE(CompareFiles(outputFileName, compareFileName));
	}
	catch (...)
	{
		REQUIRE(1 == 0);
		return;
	}
}