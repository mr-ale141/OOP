#include <sstream>
#include <algorithm>
#include "scanner.h"

// name regex
Scanner::Scanner()
	: m_nameR(std::regex(R"(^[a-zA-Z]+[0-9a-zA-Z]*)"))
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
	if (!std::regex_search(word, match, m_nameR))
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
	if (!std::regex_search(word, match, m_nameR))
	{
		return cmd;
	}
	cmd.midleName = match[0].str();

	ss >> word;
	// лишняя проверка убрать в метод get
	if (word == "+" || word == "-" || word == "*" || word == "/")
		cmd.operation = GetOperation(word);
	else
	{
		cmd.type = TypeCmd::COPY_FUNC;
		if (!ss.eof())
			return Cmd{};
		return cmd;
	}

	ss >> word;
	if (!std::regex_search(word, match, m_nameR))
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
	if (!std::regex_search(word, match, m_nameR))
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
	if (std::regex_search(word, match, m_nameR))
	{
		cmd.midleName = match[0].str();
		cmd.type = TypeCmd::COPY_VAR;
	}
	if (!ss.eof())
		return Cmd{};
	return cmd;
}

Cmd Scanner::GetDeclarationCmd(std::stringstream& ss)
{
	Cmd cmd;
	std::string word;
	ss >> word;
	if (!ss.eof())
		return Cmd{};
	std::smatch match;
	if (std::regex_search(word, match, m_nameR))
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
		if (std::regex_search(word, match, m_nameR))
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
