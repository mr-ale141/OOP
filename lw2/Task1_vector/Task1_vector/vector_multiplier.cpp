#include <vector>
#include <algorithm>
#include <iostream>
#include <exception>
#include "vector_multiplier.h"


void MultipliedByMin(std::vector<double>& arr)
{
	if (arr.size() == 0)
	{
		return;
	}

	auto minItem = *std::min_element(arr.begin(), arr.end());

	for (auto& i : arr)
	{
		i *= minItem;
	}
}

std::vector<double> GetVector(std::istream& input)
{
	double d{};
	std::vector<double> v;
	while (input >> d)
	{
		v.push_back(d);
	}
	if (!input.eof())
	{
		throw std::invalid_argument("ERROR! Invalid input data!");
	}
	return v;
}

void WriteVector(std::ostream& output, const std::vector<double>& arr)
{
	auto size = arr.size();

	output << std::fixed;

	const auto precisionOld = output.precision();

	output.precision(2);

	for (auto i : arr)
	{
		output << i;
		if (i != size - 1)
		{
			output << ' ';
		}
	}

	output << std::endl;

	output.precision(precisionOld);

	output << std::defaultfloat;
}