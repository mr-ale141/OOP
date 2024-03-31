#include "calculator.h"

int main()
{
	Calculator calc(std::cout);
	std::string command;
	while (std::getline(std::cin, command))
	{
		if (!calc.Exec(command))
			std::cout << "Error!" << std::endl;
	}
}
