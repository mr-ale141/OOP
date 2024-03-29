#pragma once
#include "define.h"

class Printer
{
public:
	Printer(std::ostream&);
	~Printer();
	void ShowValue(const Var& var);
	void ShowVars(const std::vector<Var>&);
	void ShowFuncs(const std::vector<Var>&);
	void ShowError(const std::string&);
private:
	std::ostream& _output;
	std::streamsize _precisionOld;
};
