/*
	task #3 - "invert" [80]
*/
#include "matrix_3x3.h"

int main(const int argc, const char* argv[])
{
	const size_t matrixSize = 3;

	if (argc != 2)
	{
		std::cout << "Error! There are no required parameters!" << std::endl;
		std::cout << "Example:" << std::endl;
		std::cout << "-> invert.exe <matrix file>" << std::endl;
		return 1;
	}

	std::string inputFileName(argv[1]);
	Matrix matrix;
	Matrix matrixInverse;

	try
	{
		matrix = GetMatrix(inputFileName, matrixSize);
		matrixInverse = GetInverse3x3(matrix);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	PrintMatrix(matrixInverse);

	return 0;
}