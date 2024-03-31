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
	bool InitVar(const Cmd& cmd);
	void UpdateChilds(const int index);
	int UpdateFunc(const int index);
	bool InitFunc(const Cmd& cmd);
	bool CopyFunc(const Cmd& cmd);
	bool CopyVar(const Cmd& cmd);
	std::vector<Var> m_vars;
	std::vector<Func> m_funcs;
	std::map<std::string, int> m_names;
};