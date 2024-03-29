#include "alu.h"
/*
	std::vector<Var> _vars;
	std::vector<Func> _funcs;
	std::map<std::string, int> _names;
*/

bool Alu::Declare(const Cmd& cmd)
{
	if (_names.count(cmd.firstName))
	{
		return false;
	}
	int index = _vars.size();
	Var var;
	var.name = cmd.firstName;
	_vars.push_back(var);
	_names[var.name] = index;
	return true;
}

void Alu::UpdateChilds(const int index)
{
	std::cout << "Not now!!!" << index << std::endl;
	if (_vars[index].function == isNotFunc)
	{

	}
}

bool Alu::InitVar(const Cmd& cmd)
{
	int index = _vars.size();
	if (_names.count(cmd.firstName))
	{
		index = _names.at(cmd.firstName);
		if (_vars[index].function > isNotFunc)
		{
			return false;
		}
		_vars[index].value = cmd.value;
		UpdateChilds(index);
		return true;
	}
	Var var;
	var.name = cmd.firstName;
	var.value = cmd.value;
	_vars.push_back(var);
	_names[var.name] = index;
	return true;
}

bool Alu::ExecCmd(const Cmd& cmd)
{
	switch (cmd.type)
	{
	case TypeCmd::DECLARATION:
		return Declare(cmd);
		break;
	case TypeCmd::INIT_VAR:
		return InitVar(cmd);
		break;
	case TypeCmd::INIT_FUNC:
		break;
	case TypeCmd::COPY:
		break;
	}
	return false;
}

Var Alu::GetVar(const std::string& name) const
{
	return _vars[_names.at(name)];
}

std::vector<Var> Alu::GetVars() const
{
	return _vars;
}
