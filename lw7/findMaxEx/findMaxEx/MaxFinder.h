#pragma once
#include <vector>

template<typename T, typename Less>
bool FindMax(const std::vector<T>& arr, T& maxValue, const Less& less) noexcept
{
	bool answer = false;

	if (arr.empty())
		return answer;

	const T* value = &arr[0];
	for (const auto& item : arr)
	{
		if (less(*value, item))
		{
			value = &item;
			answer = true;
		}
		else if (less(item, *value))
		{
			answer = true;
		}
	}
	// для одного
	if (answer)
		maxValue = *value;
	
	return answer;
};
