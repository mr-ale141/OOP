#pragma once
#include <map>
#include "define.h"

class Alu
{
public:
	Alu() = default;
	bool ExecCmd(const Cmd& cmd);
	Var GetVar(const std::string& name) const;
	std::vector<Var> GetVars() const;
private:
	bool Declare(const Cmd& cmd);
	void UpdateChildFuncs(int index);
	int UpdateFuncValue(int index);
	bool HandlerVar(const Cmd& cmd);
	bool HandlerFunc(const Cmd& cmd);
	bool ReinitOldVar(const Cmd& cmd);
	bool CreateNewVar(const Cmd& cmd);
	bool ReinitOldFunc(const Cmd& cmd);
	bool CreateNewFunc(const Cmd& cmd);
	void RemoveChildFunc(int indexVar, int indexFunc);
	void AddChildFunc(int indexVar, int indexFunc);
	void UpdateOperand(int& operand, int newVar, int indexFunc);
	void SetDependentOperand(int& operand, int newOperand, int indexFunc);
	bool IsChildDependence(int indexFunc, std::vector<int>& vars);
	bool IsChildDependence(int indexFunc, int indexVar);
	bool IsParent(int indexFunc, std::vector<int>& funcs);
	std::vector<Var> m_vars;
	std::vector<Func> m_funcs;
	std::map<std::string, int> m_names;
};