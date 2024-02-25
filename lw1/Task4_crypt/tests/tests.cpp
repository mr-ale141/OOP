#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Task4_crypt/crypt.h"
#include <cmath>

TEST_CASE("Test Case 'Init Crypt data empty string'")
{
	std::string mode("");
	std::string inputFileName("");
	std::string outputFileName("");
	std::string key("");
	try
	{
		GetCryptData(mode, inputFileName, outputFileName, key);
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("Parameter 'mode'") != std::string::npos);
		return;
	}
	REQUIRE(1 == 0);
}

TEST_CASE("Test Case 'Init Crypt data 'mode' is not correct '")
{
	std::string mode = "decrypting";
	std::string inputFileName = "i";
	std::string outputFileName = "o";
	std::string key = "0";
	try
	{
		GetCryptData(mode, inputFileName, outputFileName, key);
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("Parameter 'mode'") != std::string::npos);
		return;
	}
	REQUIRE(1 == 0);
}

TEST_CASE("Test Case 'Init Crypt data 'input file' is not correct '")
{
	std::string mode = "crypt";
	std::string inputFileName = "inputFile.txt";
	std::string outputFileName = "outputFile.txt ";
	std::string key = "0";
	try
	{
		GetCryptData(mode, inputFileName, outputFileName, key);
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("Can't open " + inputFileName) != std::string::npos);
		return;
	}
	REQUIRE(1 == 0);
}

TEST_CASE("Test Case 'Init Crypt data 'output file' is not correct '")
{
	std::string mode = "crypt";
	std::string inputFileName = "in.txt";
	std::string outputFileName = "C:\\Windows\\outputFile";
	std::string key = "0";
	try
	{
		GetCryptData(mode, inputFileName, outputFileName, key);
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("Can't open " + outputFileName) != std::string::npos);
		return;
	}
	REQUIRE(1 == 0);
}

TEST_CASE("Test Case 'Init Crypt data 'key' is negative'")
{
	std::string mode = "crypt";
	std::string inputFileName = "in.txt";
	std::string outputFileName = "out.txt";
	std::string key = "-1";
	try
	{
		GetCryptData(mode, inputFileName, outputFileName, key);
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("Parameter 'key'") != std::string::npos);
		return;
	}
	REQUIRE(1 == 0);
}

TEST_CASE("Test Case 'Init Crypt data 'key' is overflow'")
{
	std::string mode = "crypt";
	std::string inputFileName = "in.txt";
	std::string outputFileName = "out.txt";
	std::string key = "256";
	try
	{
		GetCryptData(mode, inputFileName, outputFileName, key);
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("Parameter 'key'") != std::string::npos);
		return;
	}
	REQUIRE(1 == 0);
}

TEST_CASE("Test Case 'Init Crypt data smoke test'")
{
	std::string mode = "crypt";
	std::string inputFileName = "in.txt";
	std::string outputFileName = "out.txt";
	std::string key = "255";
	try
	{
		GetCryptData(mode, inputFileName, outputFileName, key);
	}
	catch (...)
	{
		REQUIRE(1 == 0);
		return;
	}
	REQUIRE(1 == 1);
}