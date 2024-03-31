#include "calculator.h"

int main()
{
	Calculator calc(std::cout);
	std::string command;
	while (std::getline(std::cin, command))
	{
		calc.Exec(command);
	}
}
