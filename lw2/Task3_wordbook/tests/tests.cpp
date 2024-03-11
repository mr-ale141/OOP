#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Task3_wordbook/wordbook.h"

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
		auto GetWordBook(inputFileName);


		REQUIRE(CompareFiles(outputFileName, compareFileName));
	}
	catch (...)
	{
		REQUIRE(1 == 0);
		return;
	}
}