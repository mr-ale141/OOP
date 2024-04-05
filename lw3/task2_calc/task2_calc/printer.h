#pragma once
#include "define.h"

class Printer
{
public:
	Printer(std::ostream& output);
	~Printer();
	void ShowValue(const Var& var);
	void ShowVars(const std::vector<Var>& vars);
	void ShowFuncs(const std::vector<Var>& vars);
	void ShowError(const std::string& msg);
private:
	std::ostream& m_output;
	std::streamsize m_precisionOld;
};
