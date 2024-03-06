/*
	task #3 - "invert" [80]
*/
#include "matrix_3x3.h"

int main(const int argc, const char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Error! There are no required parameters!" << std::endl;
		std::cout << "Example:" << std::endl;
		std::cout << "-> invert.exe <matrix file>" << std::endl;
		return 1;
	}

	std::string inputFileName(argv[1]);

	try
	{
		Matrix3x3 matrix;
		Matrix3x3 matrixInverse;
		matrix = GetMatrix3x3(inputFileName);
		matrixInverse = GetInverse3x3(matrix);
		PrintMatrix3x3(matrixInverse);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}