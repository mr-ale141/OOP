#include "expTpl.h"

int main()
{
	std::string str = "hello world !!! i can";
	std::map<std::string, std::string> params =
	{
		{"!!!", "!"},
		{"i", "I"},
		{" ", "_"},
		{"or", "AND"},
	};
	auto result = ExpandTemplate(str, params);

	std::cout << result << std::endl;
	return 0;
}
