#pragma once
#include <regex>
#include "define.h"

class Scanner
{
public:
	Scanner();
	Cmd GetCmd(const std::string&);
private:
	const std::regex _nameR;
	Cmd GetDeclarationCmd(std::stringstream&);
	Cmd GetInitVarCmd(std::stringstream&);
	Cmd GetInitFuncCmd(std::stringstream&);
	Operation GetOperation(std::string&);
};