#include "matrix_3x3.h"

Matrix GetMatrix(const std::string& inputFileName, const size_t matrixSize)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile)
		throw std::ios_base::failure("Can't open " + inputFileName);

	Matrix matrix(matrixSize, std::vector<double>(matrixSize));

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

void PrintMatrix(const Matrix& m)
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
double GetDet2x2(const Matrix& m)
{
	return m[0][0] * m[1][1] - m[1][0] * m[0][1];
}

double GetDet3x3(const Matrix& m)
{
	return
		+ m[0][0] * (GetDet2x2({ { m[1][1], m[1][2] }, { m[2][1], m[2][2] } }))
		- m[0][1] * (GetDet2x2({ { m[1][0], m[1][2] }, { m[2][0], m[2][2] } }))
		+ m[0][2] * (GetDet2x2({ { m[1][0], m[1][1] }, { m[2][0], m[2][1] } }));
}

Matrix GetTransparent(const Matrix& m)
{
	size_t mSize = m.size();
	Matrix mT(m);
	for (size_t i = 0; i < mSize; i++)
		for (size_t j = 0; j < mSize; j++)
			mT[i][j] = m[j][i];
	return mT;
}

Matrix GetInverse3x3(const Matrix& m)
{
	size_t mSize = m.size();

	if (mSize != 3 || mSize != m[0].size())
		throw std::invalid_argument("ERROR! Matrix is not 3x3!");

	double det = GetDet3x3(m);

	//optional
	if (det <= std::numeric_limits<double>::epsilon())
		throw std::invalid_argument("The entered matrix has no inverse! (Determinant = 0)");

	Matrix newMatrix(m);
	const double detInverse = 1 / det;

	//найти название этой операции и вынести в функцию
	for (size_t i = 0; i < mSize; i++)
		for (size_t j = 0; j < mSize; j++)
		{
			size_t m2x2_i0 = (i % 2) ? (i + 2) % mSize : (i + 1) % mSize;
			size_t m2x2_i1 = (i % 2) ? (i + 1) % mSize : (i + 2) % mSize;
			size_t m2x2_j0 = (j % 2) ? (j + 2) % mSize : (j + 1) % mSize;
			size_t m2x2_j1 = (j % 2) ? (j + 1) % mSize : (j + 2) % mSize;

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

	//transpose
	return GetTransparent(newMatrix);
}
