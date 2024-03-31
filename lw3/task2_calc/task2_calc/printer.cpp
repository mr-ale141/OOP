#include "printer.h"

const int precision = 2;

Printer::Printer(std::ostream& output)
	: m_output(output)
{
	m_output << std::fixed;
	m_precisionOld = m_output.precision();
	m_output.precision(precision);
}

Printer::~Printer()
{
	m_output.precision(m_precisionOld);
	m_output << std::defaultfloat;
}

void Printer::ShowValue(const Var& var)
{
	m_output << var.value << std::endl;
}

void Printer::ShowVars(const std::vector<Var>& vars)
{
	for (auto& var : vars)
		if (var.function == notValid)
			m_output << var.name
					<< ':'
					<< var.value
					<< std::endl;
}

void Printer::ShowFuncs(const std::vector<Var>& vars)
{
	for (auto& var : vars)
		if (var.function > notValid)
			m_output << var.name
					<< ':'
					<< var.value
					<< std::endl;
}

void Printer::ShowError(const std::string& msg)
{
	m_output << "ERROR! " << msg << std::endl;
}
