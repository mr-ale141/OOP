#pragma once
#include <map>
#include "define.h"

class Alu
{
public:
	Alu(){};
	bool ExecCmd(const Cmd&);
	Var GetVar(const std::string&) const;
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
	void SetOperand(int& operand, int newOperand, int indexFunc);
	std::vector<Var> m_vars;
	std::vector<Func> m_funcs;
	std::map<std::string, int> m_names;
};