#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Task3_invert/matrix_3x3.h"
#include <cmath>

std::vector<std::vector<double>> MultiplyMatrices(
	const std::vector<std::vector<double>>& m1, 
	const std::vector<std::vector<double>>& m2
)
{
	std::vector<std::vector<double>> newM(m1);
	for (size_t i = 0; i < m1.size(); i++)
		for (size_t j = 0; j < m1[0].size(); j++)
			newM[i][j] = m1[i][0] * m2[0][j] + m1[i][1] * m2[1][j] + m1[i][2] * m2[2][j];
	return newM;
}

bool IsEquMatrix(
	const std::vector<std::vector<double>>& m1,
	const std::vector<std::vector<double>>& m2
)
{
	bool answer = true;
	if ((m1.size() != m2.size()) || (m1[0].size() != m2[0].size()))
		return false;
	for (size_t i = 0; i < m1.size(); i++)
		for (size_t j = 0; j < m1[0].size(); j++)
		{
			double diff = std::abs(m1[i][j] - m2[i][j]);
			if (diff > std::numeric_limits<double>::epsilon())
				answer = false;
		}
	return answer;
}

const std::vector<std::vector<double>> E =
{
	{ 1.0,  .0,  .0 },
	{  .0, 1.0,  .0 },
	{  .0,  .0, 1.0 },
};

TEST_CASE("Test Case 'Smoke test'")
{
	std::vector<std::vector<double>> mInverse;
	std::vector<std::vector<double>> m =
	{
		{ 1.0, 2.0, 3.0 },
		{  .0, 1.0, 4.0 },
		{ 5.0, 6.0,  .0 },
	};
	try
	{
		mInverse = GetInverse3x3(m);
	}
	catch (...)
	{
		REQUIRE(1 == 0);
		return;
	}
	REQUIRE(IsEquMatrix(E, MultiplyMatrices(m, mInverse)));
}

TEST_CASE("Test Case 'Smoke test with negative'")
{
	std::vector<std::vector<double>> mInverse;
	std::vector<std::vector<double>> m =
	{
		{ 3.0,  4.0,  8.0 },
		{ 2.4, -1.0, 11.0 },
		{ 7.0, -3.2,   .0 },
	};
	try
	{
		mInverse = GetInverse3x3(m);
	}
	catch (...)
	{
		REQUIRE(1 == 0);
		return;
	}
	REQUIRE(IsEquMatrix(E, MultiplyMatrices(m, mInverse)));
}

TEST_CASE("Test Case 'Det == 0'")
{
	std::vector<std::vector<double>> mInverse;
	std::vector<std::vector<double>> m =
	{
		{ 1.0,  .0, 1.0 },
		{  .0, 1.0,  .0 },
		{ 1.0,  .0, 1.0 },
	};
	try
	{
		mInverse = GetInverse3x3(m);
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("Determinant = 0") != std::string::npos);
		return;
	}
	PrintMatrix(mInverse);
	REQUIRE(1 == 0);
}

TEST_CASE("Test Case 'Det == 0 without 0 in matrix'")
{
	std::vector<std::vector<double>> mInverse;
	std::vector<std::vector<double>> m =
	{
		{ 3.0,  4.0, -5.0 },
		{ 8.0,  7.0, -2.0 },
		{ 2.0, -1.0,  8.0 },
	};
	try
	{
		mInverse = GetInverse3x3(m);
	}
	catch (const std::exception& e)
	{
		REQUIRE(std::string(e.what()).find("Determinant = 0") != std::string::npos);
		return;
	}
	PrintMatrix(mInverse);
	REQUIRE(1 == 0);
}
