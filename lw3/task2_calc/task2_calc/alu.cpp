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

int Alu::UpdateFuncValue(int indexFunc)
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

void Alu::UpdateChildFuncs(int indexVar)
{
	std::vector<int> needUpdate;
	needUpdate.push_back(indexVar);

	while (needUpdate.size())
	{
		int i = needUpdate.back();
		needUpdate.pop_back();
		for (auto indexFunc : m_vars[i].childFuncs)
		{
			int nextVar = UpdateFuncValue(indexFunc);
			if (nextVar != notValid)
			{
				needUpdate.push_back(nextVar);
			}
		}
	}
}

bool Alu::ReinitOldVar(const Cmd& cmd)
{
	int indexVar = m_names.at(cmd.firstName);
	if (m_vars[indexVar].function > isNotFunc)
	{
		return false;
	}
	double value = cmd.value;
	if (cmd.midleName.size())
	{
		value = m_vars[m_names.at(cmd.midleName)].value;
	}
	m_vars[indexVar].value = value;
	UpdateChildFuncs(indexVar);
	return true;
}

bool Alu::CreateNewVar(const Cmd& cmd)
{
	double value = cmd.value;
	if (cmd.midleName.size())
	{
		value = m_vars[m_names.at(cmd.midleName)].value;
	}
	int indexVar = (int)m_vars.size();
	Var var;
	var.name = cmd.firstName;
	var.value = value;
	m_vars.push_back(var);
	m_names[var.name] = indexVar;
	return true;
}

bool Alu::HandlerVar(const Cmd& cmd)
{
	if (m_names.count(cmd.firstName))
	{
		return ReinitOldVar(cmd);
	}
	return CreateNewVar(cmd);
}

void Alu::RemoveChildFunc(int indexVar, int indexFunc)
{
	if (indexVar == notValid)
		return;
	std::vector<int>& childFuncs = m_vars[indexVar].childFuncs;

	childFuncs.erase(std::remove(childFuncs.begin(), childFuncs.end(), indexFunc), childFuncs.end());
}

void Alu::AddChildFunc(int indexVar, int indexFunc)
{
	if (indexVar == notValid)
		return;
	std::vector<int>& childFuncs = m_vars[indexVar].childFuncs;
	childFuncs.push_back(indexFunc);
}

void Alu::UpdateOperand(int& operand, int newOperand, int indexFunc)
{
	RemoveChildFunc(operand, indexFunc);
	operand = newOperand;
	AddChildFunc(operand, indexFunc);
}

void Alu::SetOperand(int& operand, int newOperand, int indexFunc)
{
	operand = newOperand;
	AddChildFunc(operand, indexFunc);
}

bool Alu::ReinitOldFunc(const Cmd& cmd)
{
	int indexVar = m_names.at(cmd.firstName);
	int indexFunc = m_vars[indexVar].function;
	if (indexFunc == isNotFunc)
	{
		return false;
	}
	UpdateOperand(m_funcs[indexFunc].operandLeft, m_names.at(cmd.midleName), indexFunc);
	if (!cmd.lastName.empty())
		UpdateOperand(m_funcs[indexFunc].operandRight, m_names.at(cmd.lastName), indexFunc);
	m_funcs[indexFunc].operation = cmd.operation;
	UpdateChildFuncs(UpdateFuncValue(indexFunc));
	return true;
}

bool Alu::CreateNewFunc(const Cmd& cmd)
{
	int indexFunc = (int)m_funcs.size();
	int indexVar = (int)m_vars.size();

	Func func;
	func.name = cmd.firstName;
	func.operandLeft = m_names.at(cmd.midleName);
	SetOperand(func.operandLeft, m_names.at(cmd.midleName), indexFunc);
	if (!cmd.lastName.empty())
		SetOperand(func.operandRight, m_names.at(cmd.lastName), indexFunc);
	func.operation = cmd.operation;
	func.childVar = indexVar;

	Var var;
	var.name = cmd.firstName;
	var.value = cmd.value;
	var.function = indexFunc;

	m_funcs.push_back(func);
	m_vars.push_back(var);
	m_names[var.name] = indexVar;

	UpdateFuncValue(indexFunc);
	return true;
}

bool Alu::HandlerFunc(const Cmd& cmd)
{
	if (m_names.count(cmd.firstName))
	{
		return ReinitOldFunc(cmd);
	}
	return CreateNewFunc(cmd);
}

bool Alu::ExecCmd(const Cmd& cmd)
{
	switch (cmd.type)
	{
	case TypeCmd::DECLARATION:
		return Declare(cmd);
		break;
	case TypeCmd::INIT_VAR:
		return HandlerVar(cmd);
		break;
	case TypeCmd::INIT_FUNC:
		if (!m_names.count(cmd.midleName) || !m_names.count(cmd.lastName))
		{
			return false;
		}
		return HandlerFunc(cmd);
		break;
	case TypeCmd::COPY_FUNC:
		if (!m_names.count(cmd.midleName))
		{
			return false;
		}
		return HandlerFunc(cmd);
		break;
	case TypeCmd::COPY_VAR:
		if (!m_names.count(cmd.midleName))
		{
			return false;
		}
		return HandlerVar(cmd);
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
