#include "printer.h"

const int precision = 2;

Printer::Printer(std::ostream& output)
	: _output(output)
{
	_output << std::fixed;
	_precisionOld = _output.precision();
	_output.precision(precision);
}

Printer::~Printer()
{
	_output.precision(_precisionOld);
	_output << std::defaultfloat;
}

void Printer::ShowValue(const Var& var)
{
	_output << var.value << std::endl;
}

void Printer::ShowVars(const std::vector<Var>& vars)
{
	for (auto& var : vars)
		if (var.function == notValid)
			_output << var.name
					<< ':'
					<< var.value
					<< std::endl;
}

void Printer::ShowFuncs(const std::vector<Var>& vars)
{
	for (auto& var : vars)
		if (var.function > notValid)
			_output << var.name
					<< ':'
					<< var.value
					<< std::endl;
}

void Printer::ShowError(const std::string& msg)
{
	_output << "ERROR! " << msg << std::endl;
}
