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

// при выводе не сущ переменной ошибка
// функция инициализируется с собой - добавить тесты
// uml добавить зависимости
// count заменить на exist
// убрать вспомогательные методы в анонимный неймспайс