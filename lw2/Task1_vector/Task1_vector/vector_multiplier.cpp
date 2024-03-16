#include <vector>
#include <algorithm>
#include "vector_multiplier.h"

void MultipliedByMin(std::vector<double>& v)
{
	if (v.size() == 0)
	{
		return;
	}
	auto minItem = *std::min_element(v.begin(), v.end());
	// range base loop
	for (auto iter = v.begin(); iter != v.end(); iter++)
	{
		*iter *= minItem;
	}
}