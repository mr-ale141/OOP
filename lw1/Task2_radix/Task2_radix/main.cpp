/*
Task №6 – radix – [100]
*/
#include "convertor.h"

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Error! There are no required parameters!" << std::endl;
		std::cout << "Example:" << std::endl;
		std::cout << "-> radix.exe <source notation> ";
		std::cout << "<destination notation> <value>" << std::endl;
		return 1;
	}
	
	const int sourceRadix = std::stoi(argv[1]);
	const int targetRadix = std::stoi(argv[2]);
	const std::string numberString(argv[3]);	

	try
	{
		std::cout << Convert(sourceRadix, targetRadix, numberString) << std::endl;
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}
