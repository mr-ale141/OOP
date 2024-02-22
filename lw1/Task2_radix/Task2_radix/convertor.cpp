#include "convertor.h"

const int minRadix = 2;
const int maxRadix = 36;
const int digitSymbolCount = 10;

int GetDigit(char ch)
{
	if (isdigit(ch))
		return (int)ch - '0';
	else
		return digitSymbolCount + (int)ch - 'A';
}

char GetChar(int digit)
{
	if (digit < digitSymbolCount)
		return (char)('0' + digit);
	else
		return (char)('A' + digit - digitSymbolCount);
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	int result = 0;

	if (!str.size())
		throw std::invalid_argument("Error! Number string is empty!");

	if (radix < minRadix || radix > maxRadix)
		throw std::invalid_argument("Error! Source radix out of range [2 .. 36]!");

	size_t i = 0;
	bool isNegative = false;

	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		isNegative = true;
		i++;
	}

	int MAX_VALUE{};

	if (isNegative)
		MAX_VALUE = INT_MIN;
	else
		MAX_VALUE = INT_MAX;

	for (; i < str.size() && wasError == false; i++)
	{
		if (!isalpha(str[i]) && !isdigit(str[i]))
		{
			wasError = true;
			return result;
		}

		int newDigit = GetDigit(str[i]);

		if (newDigit >= radix)
		{
			wasError = true;
			return result;
		}

		if (isNegative)
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
	bool isNegative = false;
	if (radix < minRadix || radix > maxRadix)
		throw std::invalid_argument("Error! Target radix out of range [2 .. 36]!");

	std::string str;
	unsigned absoluteN = n < 0 ? -unsigned(n) : unsigned(n);

	if (n < 0)
		isNegative = true;
	else if (n == 0)
		str.push_back('0');

	while (absoluteN != 0)
	{
		int nextDigit = absoluteN % radix;
		absoluteN /= radix;
		char nextChar = GetChar(nextDigit);
		if (nextChar > GetChar(radix - 1))
		{
			wasError = true;
			return str;
		}
		str.push_back(nextChar);
	}

	if (isNegative)
		str.push_back('-');

	std::reverse(str.begin(), str.end());

	return str;
}

std::string Convert(int sourceRadix, int targetRadix, std::string numberString)
{
	bool wasError = false;

	std::string answer = IntToString(StringToInt(numberString, sourceRadix, wasError), targetRadix, wasError);

	if (wasError)
		throw std::invalid_argument("ERROR! Check the entered data!");

	return answer;
}