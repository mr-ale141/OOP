#include "labyrinth.h"

int main(const int argc, const char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Error! There are no required parameters!" << std::endl;
		std::cout << "Example:" << std::endl;
		std::cout << "-> labyrinth.exe <input file> ";
		std::cout << "<output file>" << std::endl;
		return 1;
	}

	std::string inputFileName(argv[1]);
	std::string outputFileName(argv[2]);

	try
	{
		FindPath(inputFileName, outputFileName);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}