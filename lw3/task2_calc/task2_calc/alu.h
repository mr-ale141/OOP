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
	void UpdateChildVars(const int index);
	int UpdateFuncValue(const int index);
	bool HandlerVar(const Cmd& cmd);
	bool HandlerFunc(const Cmd& cmd);
	bool ReinitOldVar(const std::string& name, double newValue);
	bool CreateNewVar(const std::string& name, double newValue);
	bool ReinitOldFunc(const Cmd& cmd);
	bool CreateNewFunc(const Cmd& cmd);
	std::vector<Var> m_vars;
	std::vector<Func> m_funcs;
	std::map<std::string, int> m_names;
};