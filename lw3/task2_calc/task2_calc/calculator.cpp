#include "calculator.h"

Calculator::Calculator(std::ostream& output)
	: m_printer(output)
{}

bool Calculator::Exec(const std::string& str)
{
	auto cmd = m_scanner.GetCmd(str);

	switch (cmd.type)
	{
	case (TypeCmd::DECLARATION):
	case (TypeCmd::INIT_VAR):
	case (TypeCmd::INIT_FUNC):
	case (TypeCmd::COPY_FUNC):
	case (TypeCmd::COPY_VAR):
		return m_alu.ExecCmd(cmd);
		break;
	case (TypeCmd::PRINT):
		m_printer.ShowValue(m_alu.GetVar(cmd.firstName));
		break;
	case (TypeCmd::PRINTVARS):
		m_printer.ShowVars(m_alu.GetVars());
		break;
	case (TypeCmd::PRINTFNS):
		m_printer.ShowFuncs(m_alu.GetVars());
		break;
	case (TypeCmd::UNKNOWN):
		m_printer.ShowError("ERROR! Incorrect command!");
		break;
	}
	return true;
}
