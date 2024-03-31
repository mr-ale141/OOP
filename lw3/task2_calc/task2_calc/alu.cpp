#include "alu.h"
/*
	std::vector<Var> m_vars;
	std::vector<Func> m_funcs;
	std::map<std::string, int> m_names;
*/

bool Alu::Declare(const Cmd& cmd)
{
	if (m_names.count(cmd.firstName))
	{
		return false;
	}
	int index = (int)m_vars.size();
	Var var;
	var.name = cmd.firstName;
	m_vars.push_back(var);
	m_names[var.name] = index;
	return true;
}

int Alu::UpdateFunc(const int indexFunc)
{
	if (indexFunc == isNotFunc)
		return notValid;
	Func& func = m_funcs[indexFunc];
	double& value = m_vars[func.childVar].value;
	value = m_vars[func.operandLeft].value;
	switch (func.operation)
	{
	case Operation::SUM:
		value += m_vars[func.operandRight].value;
		break;
	case Operation::SUB:
		value -= m_vars[func.operandRight].value;
		break;
	case Operation::MUL:
		value *= m_vars[func.operandRight].value;
		break;
	case Operation::DIV:
		value /= m_vars[func.operandRight].value;
		break;
	case Operation::UNKNOWN:
		break;
	}
	return func.childVar;
}

void Alu::UpdateChilds(const int indexVar)
{
	std::vector<int> needUpdate;
	needUpdate.push_back(indexVar);

	while (needUpdate.size())
	{
		int i = needUpdate.back();
		needUpdate.pop_back();
		for (auto indexFunc : m_vars[i].childFuncs)
		{
			int nextVar = UpdateFunc(indexFunc);
			if (nextVar != notValid)
			{
				needUpdate.push_back(nextVar);
			}
		}
	}
}

bool Alu::InitVar(const Cmd& cmd)
{
	int indexVar = (int)m_vars.size();
	if (m_names.count(cmd.firstName))
	{
		indexVar = m_names.at(cmd.firstName);
		if (m_vars[indexVar].function > isNotFunc)
		{
			return false;
		}
		m_vars[indexVar].value = cmd.value;
		UpdateChilds(indexVar);
		return true;
	}
	Var var;
	var.name = cmd.firstName;
	var.value = cmd.value;
	m_vars.push_back(var);
	m_names[var.name] = indexVar;
	return true;
}

bool Alu::InitFunc(const Cmd& cmd)
{
	if (!m_names.count(cmd.midleName) || !m_names.count(cmd.lastName))
	{
		return false;
	}
	int indexFunc = (int)m_funcs.size();
	int indexVar = (int)m_vars.size();
	if (m_names.count(cmd.firstName))
	{
		indexVar = m_names.at(cmd.firstName);
		indexFunc = m_vars[indexVar].function;
		if (indexFunc == isNotFunc)
		{
			return false;
		}
		m_funcs[indexFunc].operandLeft = m_names.at(cmd.midleName);
		m_funcs[indexFunc].operandRight = m_names.at(cmd.lastName);
		m_funcs[indexFunc].operation = cmd.operation;
		UpdateChilds(UpdateFunc(indexFunc));
		return true;
	}
	Func func;
	func.name = cmd.firstName;
	func.operandLeft = m_names.at(cmd.midleName);
	func.operandRight = m_names.at(cmd.lastName);
	func.operation = cmd.operation;
	func.childVar = indexVar;

	Var var;
	var.name = cmd.firstName;
	var.value = cmd.value;
	var.function = indexFunc;

	m_funcs.push_back(func);
	m_vars.push_back(var);
	m_names[var.name] = indexVar;
	
	UpdateFunc(indexFunc);
	return true;
}

bool Alu::CopyFunc(const Cmd& cmd)
{
	if (!m_names.count(cmd.midleName))
	{
		return false;
	}
	int indexFunc = (int)m_funcs.size();
	int indexVar = (int)m_vars.size();
	int indexCopy = m_names.at(cmd.midleName);
	if (m_names.count(cmd.firstName))
	{
		indexVar = m_names.at(cmd.firstName);
		indexFunc = m_vars[indexVar].function;
		if (indexFunc == isNotFunc)
		{
			return false;
		}
		m_funcs[indexFunc].operandLeft = indexCopy;
		m_funcs[indexFunc].operandRight = notValid;
		m_funcs[indexFunc].operation = Operation::UNKNOWN;
		UpdateChilds(UpdateFunc(indexFunc));
		return true;
	}
	Func func;
	func.name = cmd.firstName;
	func.operandLeft = indexCopy;
	func.childVar = indexVar;

	Var var;
	var.name = cmd.firstName;
	var.function = indexFunc;

	m_funcs.push_back(func);
	m_vars.push_back(var);
	m_names[var.name] = indexVar;

	UpdateFunc(indexFunc);
	return true;
}

bool Alu::CopyVar(const Cmd& cmd)
{
	if (!m_names.count(cmd.midleName))
	{
		return false;
	}
	int indexVar = (int)m_vars.size();
	int indexCopy = m_names.at(cmd.midleName);
	if (m_names.count(cmd.firstName))
	{
		indexVar = m_names.at(cmd.firstName);
		if (m_vars[indexVar].function > isNotFunc)
		{
			return false;
		}
		m_vars[indexVar].value = m_vars[indexCopy].value;
		UpdateChilds(indexVar);
		return true;
	}
	Var var;
	var.name = cmd.firstName;
	var.value = m_vars[indexCopy].value;
	m_vars.push_back(var);
	m_names[var.name] = indexVar;
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
		return InitFunc(cmd);
		break;
	case TypeCmd::COPY_FUNC:
		return CopyFunc(cmd);
		break;
	case TypeCmd::COPY_VAR:
		return CopyVar(cmd);
		break;
	}
	return false;
}

Var Alu::GetVar(const std::string& name) const
{
	return m_vars[m_names.at(name)];
}

std::vector<Var> Alu::GetVars() const
{
	return m_vars;
}
