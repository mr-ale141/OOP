#pragma once
#include <vector>

template<typename T, typename Less>
bool FindMax(const std::vector<T>& arr, T& maxValue, const Less& less)
{
	bool answer = false; 
	if (arr.empty())
		return answer;

	T oldValue = std::move(maxValue);

	maxValue = arr[0];
	for (auto& item : arr)
	{
		if (less(maxValue, item))
		{
			maxValue = item;
			answer = true;
		}
		else if (less(item, maxValue))
		{
			answer = true;
		}
	}

	if (!answer)
		maxValue = std::move(oldValue);
	
	return answer;
};
