#include "matrix_3x3.h"

const size_t matrixSize = 3;

Matrix3x3 GetMatrix3x3(const std::string& inputFileName)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile)
		throw std::ios_base::failure("Can't open " + inputFileName);

	Matrix3x3 matrix;

	for (size_t i = 0; (i < matrixSize) && inputFile; i++)
	{
		for (size_t j = 0; (j < matrixSize) && (inputFile >> matrix[i][j]); j++)
			continue;
		if (inputFile.get() != '\n')
		{
			inputFile.setstate(std::ios_base::failbit);
			break;
		}
	}

	if (inputFile.eof() || inputFile.fail())
		throw std::invalid_argument("ERROR! Matrix 3x3 in '" + inputFileName + "' is incorrect!");

	inputFile.close();

	return matrix;
}

void PrintMatrix3x3(const Matrix3x3& m)
{
	const size_t matrixSize = m.size();

	std::cout << std::fixed;

	const auto precisionOld = std::cout.precision();

	std::cout.precision(3);

	for (size_t i = 0; i < matrixSize; i++)
	{
		std::cout << "| ";
		for (size_t j = 0; j < matrixSize; j++)
		{
			std::cout.width(10);
			std::cout << m[i][j] << ((j < matrixSize - 1) ? " | " : "");
		}
		std::cout << " |";
		std::cout << std::endl;
	}

	std::cout.precision(precisionOld);

	std::cout << std::defaultfloat;
}

//array2x2 array3x3
double GetDet2x2(const Matrix2x2& m)
{
	return m[0][0] * m[1][1] - m[1][0] * m[0][1];
}

double GetDet3x3(const Matrix3x3& m)
{
	return
		+ m[0][0] * (GetDet2x2({ { m[1][1], m[1][2] }, { m[2][1], m[2][2] } }))
		- m[0][1] * (GetDet2x2({ { m[1][0], m[1][2] }, { m[2][0], m[2][2] } }))
		+ m[0][2] * (GetDet2x2({ { m[1][0], m[1][1] }, { m[2][0], m[2][1] } }));
}

Matrix3x3 GetTranspose3x3(const Matrix3x3& m)
{
	size_t mSize = m.size();
	Matrix3x3 mT(m);
	for (size_t i = 0; i < mSize; i++)
		for (size_t j = 0; j < mSize; j++)
			mT[i][j] = m[j][i];
	return mT;
}

Matrix3x3 GetÑomplement(const Matrix3x3& m)
{
	double det = GetDet3x3(m);

	if (det <= std::numeric_limits<double>::epsilon())
		throw std::invalid_argument("The entered matrix has no inverse! (Determinant = 0)");

	const double detInverse = 1 / det;

	Matrix3x3 newMatrix(m);
	for (size_t i = 0; i < matrixSize; i++)
		for (size_t j = 0; j < matrixSize; j++)
		{
			size_t m2x2_i0 = (i % 2) ? (i + 2) % matrixSize : (i + 1) % matrixSize;
			size_t m2x2_i1 = (i % 2) ? (i + 1) % matrixSize : (i + 2) % matrixSize;
			size_t m2x2_j0 = (j % 2) ? (j + 2) % matrixSize : (j + 1) % matrixSize;
			size_t m2x2_j1 = (j % 2) ? (j + 1) % matrixSize : (j + 2) % matrixSize;

			newMatrix[i][j] =
				std::pow(-1, i + j) *
				GetDet2x2(
			{
				{ m[m2x2_i0][m2x2_j0], m[m2x2_i0][m2x2_j1] },
				{ m[m2x2_i1][m2x2_j0], m[m2x2_i1][m2x2_j1] },
			}
			) *
				detInverse;
		}
	return newMatrix;
}

Matrix3x3 GetInverse3x3(const Matrix3x3& m)
{
	if (matrixSize != 3 || matrixSize != m[0].size())
		throw std::invalid_argument("ERROR! Matrix is not 3x3!");

	Matrix3x3 complement = GetÑomplement(m);

	return GetTranspose3x3(complement);
}
