#include "expTpl.h"

int main()
{
    std::string str = "hello ghjk kl njworldjn fjg n";
	std::map<std::string, std::string> params =
	{
		{"hel", "!"},
		{"hello", "I"},
		{"world", "_"},
	};
	auto result = ExpandTemplate(str, params);

	std::cout << result << std::endl;
	return 0;
}
