#include <sstream>
#include <algorithm>
#include "scanner.h"

Scanner::Scanner()
	: _nameR(std::regex(R"([a-zA-Z]+[0-9a-zA-Z]*)"))
{}

Operation Scanner::GetOperation(std::string& str)
{
	if (str == "+")
		return Operation::SUM;
	else if (str == "-")
		return Operation::SUB;
	else if (str == "*")
		return Operation::MUL;
	else if (str == "/")
		return Operation::DIV;
	else
		return Operation::UNKNOWN;
}

Cmd Scanner::GetInitFuncCmd(std::stringstream& ss)
{
	Cmd cmd;
	std::string word;
	std::smatch match;

	ss >> word;
	if (!std::regex_search(word, match, _nameR))
	{
		return cmd;
	}
	cmd.firstName = match[0].str();

	ss >> word;
	if (word != "=")
	{
		return cmd;
	}

	ss >> word;
	if (!std::regex_search(word, match, _nameR))
	{
		return cmd;
	}
	cmd.midleName = match[0].str();

	ss >> word;
	if (word == "+" || word == "-" || word == "*" || word == "/")
		cmd.operation = GetOperation(word);
	else
	{
		cmd.type = TypeCmd::COPY;
		return cmd;
	}

	ss >> word;
	if (!std::regex_search(word, match, _nameR))
	{
		return cmd;
	}
	cmd.lastName = match[0].str();
	cmd.type = TypeCmd::INIT_FUNC;
	return cmd;
}

Cmd Scanner::GetInitVarCmd(std::stringstream& ss)
{
	Cmd cmd;
	std::string word;
	std::smatch match;

	ss >> word;
	if (!std::regex_search(word, match, _nameR))
	{
		return cmd;
	}
	cmd.firstName = match[0].str();

	ss >> word;
	if (word != "=")
	{
		return cmd;
	}

	double value;
	if (ss >> value)
	{
		cmd.value = value;
		cmd.type = TypeCmd::INIT_VAR;
		return cmd;
	}

	ss.clear();
	ss >> word;
	if (std::regex_search(word, match, _nameR))
	{
		cmd.midleName = match[0].str();
		cmd.type = TypeCmd::COPY;
	}
	return cmd;
}

Cmd Scanner::GetDeclarationCmd(std::stringstream& ss)
{
	Cmd cmd;
	std::string word;
	ss >> word;
	std::smatch match;
	if (std::regex_search(word, match, _nameR))
	{
		cmd.type = TypeCmd::DECLARATION;
		cmd.firstName = match[0].str();
	}
	return cmd;
}

Cmd Scanner::GetCmd(const std::string& str)
{
	std::stringstream ss(str);
	Cmd cmd;

	std::string word;
	ss >> word;
	if (word == "var")
	{
		return GetDeclarationCmd(ss);
	}
	else if (word == "let")
	{
		return GetInitVarCmd(ss);
	}
	else if (word == "fn")
	{
		return GetInitFuncCmd(ss);
	}
	else if (word == "print")
	{
		std::smatch match;
		ss >> word;
		if (std::regex_search(word, match, _nameR))
		{
			cmd.firstName = match[0].str();
			cmd.type = TypeCmd::PRINT;
		}
		return cmd;
	}
	else if (word == "printvars")
	{
		cmd.type = TypeCmd::PRINTVARS;
		return cmd;
	}
	else if (word == "printfns")
	{
		cmd.type = TypeCmd::PRINTFNS;
		return cmd;
	}
	else
		return cmd;
}
