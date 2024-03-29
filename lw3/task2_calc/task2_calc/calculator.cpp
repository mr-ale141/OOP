#include "calculator.h"

Calculator::Calculator(std::ostream& output)
	: _printer(output)
{}

bool Calculator::Exec(const std::string& str)
{
	auto cmd = _scanner.GetCmd(str);

	switch (cmd.type)
	{
	case (TypeCmd::DECLARATION):
	case (TypeCmd::INIT_VAR):
	case (TypeCmd::INIT_FUNC):
	case (TypeCmd::COPY):
		return _alu.ExecCmd(cmd);
		break;
	case (TypeCmd::PRINT):
		_printer.ShowValue(_alu.GetVar(cmd.firstName));
		break;
	case (TypeCmd::PRINTVARS):
		_printer.ShowVars(_alu.GetVars());
		break;
	case (TypeCmd::PRINTFNS):
		_printer.ShowFuncs(_alu.GetVars());
		break;
	case (TypeCmd::UNKNOWN):
		_printer.ShowError("Incorrect command!");
		return false;
		break;
	}
	return true;
}
