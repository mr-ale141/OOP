#include <iostream>
#include <vector>
#include <exception>
#include "iovector.h"

std::vector<double> GetVectorDouble(std::istream& input)
{
	double d{};
	std::vector<double> v;
	while (input.peek() != '\n')
	{
		input >> d;
		if (input.fail() && !input.eof())
		{
			throw std::invalid_argument("ERROR! Invalid input data!");
		}
		else if (input.eof())
		{
			return v;
		}
		else
		{
			v.push_back(d);
		}
	}
	input.get();
	return v;
}

void WriteVectorDouble(std::ostream& output, const std::vector<double>& v)
{
	auto size = v.size();

	output << std::fixed;

	const auto precisionOld = output.precision();

	output.precision(2);

	for (size_t i = 0; i < size; i++)
	{
		output << v[i];
		if (i != size - 1)
		{
			output << ' ';
		}
	}
	output << std::endl;

	output.precision(precisionOld);

	output << std::defaultfloat;
}