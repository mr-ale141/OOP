#include "prime.h"

const int maxNum = 100000000;
const int firstPrime = 2;

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::set<int> set;
	if (upperBound < firstPrime || upperBound > maxNum)
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
			int step = (i == 2) ? i : i * 2;
			for (int j = i * i; j <= upperBound; j += step)
			{
				arr[j] = true;
			}
		}
	}

	// время втсавки и удаления разными способами в set от количества элементов во множестве
	for (; i <= upperBound; i++)
	{
		if (!arr[i])
		{
			set.insert(set.end(), i);
		}
	}

	return set;
}