#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Task2_html_decode/html_decode.h"

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

		std::string str;
		std::getline(input, str);
		output << HtmlDecode(str) << std::endl;

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

TEST_CASE("Test Case 'Invalid token'")
{
	auto inputFileName = std::string("in\\invalid_token.txt");
	try
	{
		std::ifstream input(inputFileName);
		std::string str;
		std::getline(input, str);
		std::cout << HtmlDecode(str) << std::endl;
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("token-string is incorrect") != std::string::npos);
		return;
	}
	REQUIRE(1 == 0);
}

TEST_CASE("Test Case 'Token without end'")
{
	auto inputFileName = std::string("in\\token_without_end.txt");
	try
	{
		std::ifstream input(inputFileName);
		std::string str;
		std::getline(input, str);
		std::cout << HtmlDecode(str) << std::endl;
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("token-string without end") != std::string::npos);
		return;
	}
	REQUIRE(1 == 0);
}

TEST_CASE("Test Case 'Empty test'")
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

		std::string str;
		std::getline(input, str);
		output << HtmlDecode(str) << std::endl;

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

TEST_CASE("Test Case 'Without token'")
{
	auto inputFileName = std::string("in\\without_token.txt");
	auto outputFileName = std::string("out\\without_token.txt");
	auto compareFileName = std::string("compare\\without_token.txt");
	try
	{
		std::ifstream input(inputFileName);
		std::ofstream output(outputFileName);
		if (!input.is_open() || !output.is_open())
			throw std::ios_base::failure("ERROR! Can't open file for compare!");

		std::string str;
		std::getline(input, str);
		output << HtmlDecode(str) << std::endl;

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