#include "crypt.h"

int main(const int argc, const char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Error! There are no required parameters!" << std::endl;
		std::cout << "Example:" << std::endl;
		std::cout << "-> crypt.exe <crypt | decrypt> <input file>";
		std::cout << "<output file> <key between 0 .. 255>" << std::endl;
		return 1;
	}

	std::string mode(argv[1]);
	std::string inputFileName(argv[2]);
	std::string outputFileName(argv[3]);
	std::string key(argv[4]);

	try
	{
		Сryptographer(mode, inputFileName, outputFileName, key);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}