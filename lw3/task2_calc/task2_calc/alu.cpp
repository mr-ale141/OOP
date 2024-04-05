#include "alu.h"

namespace
{
	bool IsInside(int item, std::vector<int>& arr)
	{
		return std::find(arr.begin(), arr.end(), item) != arr.end();
	}
}

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
// fn xy = x + y
// let x = 1; let y = 2;
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

bool Alu::IsChildDependence(int indexFunc, int indexVar)
{
	return IsInside(indexFunc, m_vars[indexVar].childFuncs);
}

bool Alu::IsChildDependence(int indexFunc, std::vector<int>& vars)
{
	bool res = false;
	for (auto item : vars)
	{
		if (IsInside(indexFunc, m_vars[item].childFuncs))
		{
			res = true;
			break;
		}
	}
	return res;
}

bool Alu::IsParent(int indexFunc, std::vector<int>& funcs)
{
	bool res = false;
	int indexVar = m_funcs[indexFunc].childVar;
	for (auto childFuncIndex : m_vars[indexVar].childFuncs)
	{
		if (IsInside(childFuncIndex, funcs))
		{
			res = true;
			break;
		}
	}
	return res;
}

void Alu::UpdateChildFuncs(int indexVar)
{
	std::vector<int> needUpdate;
	needUpdate.push_back(indexVar);

	while (needUpdate.size()) //empty
	{
		int parentVar = needUpdate.back();
		needUpdate.pop_back();
		auto& parentVarRefs = m_vars[parentVar].childFuncs;
		for (auto currentFunc : parentVarRefs)
		{
			if (IsInside(m_funcs[currentFunc].childVar, needUpdate))
				continue;
			if (IsChildDependence(currentFunc, needUpdate))
				continue;
			int nextVar = UpdateFuncValue(currentFunc);
			auto& childVarRefs = m_vars[nextVar].childFuncs;

			for (auto nextFunc : childVarRefs)
			{
				if (IsInside(nextFunc, parentVarRefs))
				{
					if (IsParent(nextFunc, childVarRefs))
						needUpdate.push_back(nextVar);
					continue;
				}

				if (IsChildDependence(nextFunc, needUpdate))
					continue;

				if (!IsInside(nextVar, needUpdate))
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
	// split in metod
	if (cmd.midleName.size())
	{
		value = m_vars[m_names.at(cmd.midleName)].value;
	}
	if (m_vars[indexVar].value != value)
	{
		m_vars[indexVar].value = value;
		UpdateChildFuncs(indexVar);
	}
	return true;
}

bool Alu::CreateNewVar(const Cmd& cmd)
{
	double value = cmd.value;
	// split in metod
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
	if (std::find(childFuncs.begin(), childFuncs.end(), indexFunc) != childFuncs.end())
		return;
	childFuncs.push_back(indexFunc);
}

void Alu::UpdateOperand(int& operand, int newOperand, int indexFunc)
{
	RemoveChildFunc(operand, indexFunc);
	operand = newOperand;
	AddChildFunc(operand, indexFunc);
}

void Alu::SetDependentOperand(int& operand, int newOperand, int indexFunc)
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
	SetDependentOperand(func.operandLeft, m_names.at(cmd.midleName), indexFunc);
	if (!cmd.lastName.empty())
		SetDependentOperand(func.operandRight, m_names.at(cmd.lastName), indexFunc);
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
	if (m_names.count(name))
	{
		return m_vars[m_names.at(name)];
	}
	return Var{};
}

std::vector<Var> Alu::GetVars() const
{
	return m_vars;
}
