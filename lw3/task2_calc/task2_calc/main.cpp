#include "calculator.h"

int main()
{
	Calculator calc(std::cout);
	calc.Exec("var x");
	calc.Exec("print x");
}
