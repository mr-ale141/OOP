#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Task4_crypt/crypt.h"
#include <cmath>

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

TEST_CASE("Test Case 'War and world'")
{
	std::string mode = "crypt";
	std::string inputFileName = "waw.txt";
	std::string outputFileCrypt = "waw_crypt.txt";
	std::string outputFileDecrypt = "waw_decrypt.txt";
	std::string key = "255";
	try
	{
		Сryptographer(mode, inputFileName, outputFileCrypt, key);
		REQUIRE(!CompareFiles(inputFileName, outputFileCrypt));
		mode = "decrypt";
		Сryptographer(mode, outputFileCrypt, outputFileDecrypt, key);
		REQUIRE(CompareFiles(inputFileName, outputFileDecrypt));
	}
	catch (...)
	{
		REQUIRE(1 == 0);
		return;
	}
}

TEST_CASE("Test Case 'Empty file'")
{
	std::string mode = "crypt";
	std::string inputFileName = "empty.txt";
	std::string outputFileCrypt = "empty_crypt.txt";
	std::string outputFileDecrypt = "empty_decrypt.txt";
	std::string key = "1";
	try
	{
		Сryptographer(mode, inputFileName, outputFileCrypt, key);
		REQUIRE(CompareFiles(inputFileName, outputFileCrypt));
		mode = "decrypt";
		Сryptographer(mode, outputFileCrypt, outputFileDecrypt, key);
		REQUIRE(CompareFiles(inputFileName, outputFileDecrypt));
	}
	catch (...)
	{
		REQUIRE(1 == 0);
		return;
	}
}

TEST_CASE("Test Case 'Init Crypt data empty string'")
{
	std::string mode("");
	std::string inputFileName("");
	std::string outputFileName("");
	std::string key("");
	try
	{
		Сryptographer(mode, inputFileName, outputFileName, key);
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
		Сryptographer(mode, inputFileName, outputFileName, key);
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
		Сryptographer(mode, inputFileName, outputFileName, key);
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("ERROR! Can't open " + inputFileName) != std::string::npos);
		return;
	}
	REQUIRE(1 == 0);
}

TEST_CASE("Test Case 'Init Crypt data 'output file' is not correct '")
{
	std::string mode = "crypt";
	std::string inputFileName = "hello.txt";
	std::string outputFileName = "C:\\Windows\\outputFile";
	std::string key = "0";
	try
	{
		Сryptographer(mode, inputFileName, outputFileName, key);
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("ERROR! Can't open " + outputFileName) != std::string::npos);
		return;
	}
	REQUIRE(1 == 0);
}

TEST_CASE("Test Case 'Init Crypt data 'key' is negative'")
{
	std::string mode = "crypt";
	std::string inputFileName = "hello.txt";
	std::string outputFileName = "hello_crypt.txt";
	std::string key = "-1";
	try
	{
		Сryptographer(mode, inputFileName, outputFileName, key);
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
	std::string inputFileName = "hello.txt";
	std::string outputFileName = "hello_crypt.txt";
	std::string key = "256";
	try
	{
		Сryptographer(mode, inputFileName, outputFileName, key);
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("Parameter 'key'") != std::string::npos);
		return;
	}
	REQUIRE(1 == 0);
}

TEST_CASE("Test Case 'Crypt / Decrypt smoke test'")
{
	std::string mode = "crypt";
	std::string inputFileName = "hello.txt";
	std::string outputFileCrypt = "hello_crypt.txt";
	std::string outputFileDecrypt = "hello_decrypt.txt";
	std::string key = "128";
	try
	{
		Сryptographer(mode, inputFileName, outputFileCrypt, key);
		REQUIRE(!CompareFiles(inputFileName, outputFileCrypt));
		mode = "decrypt";
		Сryptographer(mode, outputFileCrypt, outputFileDecrypt, key);
		REQUIRE(CompareFiles(inputFileName, outputFileDecrypt));
	}
	catch (...)
	{
		REQUIRE(1 == 0);
		return;
	}
}

TEST_CASE("Test Case 'EXE file'")
{
	std::string mode = "crypt";
	std::string inputFileName = "hello.txt";
	std::string outputFileCrypt = "hello_crypt.txt";
	std::string outputFileDecrypt = "hello_decrypt.txt";
	std::string key = "128";
	try
	{
		Сryptographer(mode, inputFileName, outputFileCrypt, key);
		REQUIRE(!CompareFiles(inputFileName, outputFileCrypt));
		mode = "decrypt";
		Сryptographer(mode, outputFileCrypt, outputFileDecrypt, key);
		REQUIRE(CompareFiles(inputFileName, outputFileDecrypt));
	}
	catch (...)
	{
		REQUIRE(1 == 0);
		return;
	}
}