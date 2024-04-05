#pragma once
#include <regex>
#include "define.h"

class Scanner
{
public:
	Scanner();
	Cmd GetCmd(const std::string& str);
private:
	const std::regex m_nameR;
	Cmd GetDeclarationCmd(std::stringstream& ss);
	Cmd GetInitVarCmd(std::stringstream& ss);
	Cmd GetInitFuncCmd(std::stringstream& ss);
	Operation GetOperation(std::string& str);
};