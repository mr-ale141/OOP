#pragma once
#include <string>
#include <limits>


int StringToInt(const std::string& str, int radix, bool& wasError)
{
	int result = 0;

	if (!str.size())
	{
		wasError = true;
		return result;
	}

	int i = 0;
	bool isSigned = false;

	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		isSigned = true;
		i++;
	}

	if (str[i] < '0' || str[i] > '9')
	{
		wasError = true;
		return result;
	}

	int MAX_VALUE;

	if (isSigned)
		MAX_VALUE = std::numeric_limits<int>::min();
	else
		MAX_VALUE = std::numeric_limits<int>::max();

	for (; i < str.size() && wasError == false; i++)
	{
		int newDigit = (int)str[i] - '0';
		if (isSigned)
		{
			if (result >= (MAX_VALUE + newDigit) / radix)
				result = result * radix - newDigit;
			else
				wasError = true;
		}
		else
		{
			if (result <= (MAX_VALUE - newDigit) / radix)
				result = result * radix + newDigit;
			else
				wasError = true;
		}
	}

	return result;
}

std::string IntToString(int n, int radix, bool & wasError)
{
	return std::string("not work");
}