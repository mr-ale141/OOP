#include "prime.h"

static const int maxNum = 100000000;
static const int firstPrime = 2;

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::set<int> set;
	if (upperBound < 2 || upperBound > maxNum)
	{
		return set;
	}

	std::vector<bool> arr(upperBound + 1);

	int i;
	for (i = firstPrime; i * i <= upperBound; i++)
	{
		if (!arr[i])
		{
			set.insert(i);
			for (int j = i * i; j <= upperBound; j += i)
			{
				arr[j] = true;
			}
		}
	}

	for (; i <= upperBound; i++)
	{
		if (!arr[i])
		{
			set.insert(i);
		}
	}

	return set;
}