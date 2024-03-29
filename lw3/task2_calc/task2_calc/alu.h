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
	std::vector<Var> _vars;
	std::vector<Func> _funcs;
	std::map<std::string, int> _names;
};