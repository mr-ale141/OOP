#pragma once
#include <string>
#include <limits>

//если в заголовочном файле определения, то должен перед функцией писать inline
int GetDigit(char ch)
{
	if (isdigit(ch))
		return (int)ch - '0';
	else
		return 10 + (int)ch - 'A';
}

char GetChar(int digit)
{
	if (digit < 10)
		return (char) '0' + digit;
	else
		return (char) 'A' + digit - 10;
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	int result = 0;

	if (!str.size())
		throw std::exception("Error! Number string is empty!");

	//магические числа
	if (radix < 2 || radix > 36)
		throw std::exception("Error! Source radix out of range [2 .. 36]!");

	size_t i = 0;
	bool isSigned = false;
	// isNegative

	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		isSigned = true;
		i++;
	}

	int MAX_VALUE{};

	if (isSigned)
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
	bool isSigned = false;
	if (radix < 2 || radix > 36)
		throw std::exception("Error! Target radix out of range [2 .. 36]!");
	std::string str{};
	if (n < 0)
	{
		isSigned = true;
		n = std::abs(n);// для INT_MIN не определен
	}
	else if (n == 0)
		str.push_back('0');
	while (n != 0)
	{
		int nextDigit = n % radix;
		n /= radix;
		char nextChar = GetChar(nextDigit);
		if (nextChar > GetChar(radix - 1))
		{
			wasError = true;
			return str;
		}
		str.push_back(nextChar);
	}
	if (isSigned)
		str.push_back('-');
	std::reverse(str.begin(), str.end());
	return str;
}

std::string Convert(int sourceRadix, int targetRadix, std::string numberString)
{
	bool wasError = false;

	std::string answer = IntToString(StringToInt(numberString, sourceRadix, wasError), targetRadix, wasError);

	if (wasError)
		// std::exception строку не принимает!!!!!
		// подобрать подходящий тип исключений
		throw std::exception("ERROR! Check the entered data!");

	return answer;
}
