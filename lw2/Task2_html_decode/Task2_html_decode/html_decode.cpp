#include <iostream>
#include <string>
#include <exception>
#include <map>
#include "html_decode.h"

#define USE_REPLACE_STRING 1

enum State
{
	WAIT  = '\0',
	QUOTE = '"',
	APOS  = '\'',
	LT    = '<',
	GT    = '>',
	AMP   = '&',
};

//добавить тесты
static const std::map<std::string, char> htmlLiterals
{
	{ std::string("&quot;"), char(QUOTE) },
	{ std::string("&apos;"), char(APOS)  },
	{ std::string("&lt;"),   char(LT)    },
	{ std::string("&gt;"),   char(GT)    },
	{ std::string("&amp;"),  char(AMP)   },
};

//&&lt;
#if USE_REPLACE_STRING
std::string ReplaceString(
	const std::string& subject,
	const std::string& searchString,
	const std::string& replacementString)
{
	if (searchString.empty())
		return subject;
	size_t pos = 0;
	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);
		if (foundPos == std::string::npos)
			break;
		result.append(replacementString);
		pos = foundPos + searchString.length();
	}
	return result;
}

std::string HtmlDecode(std::string const& html)
{
	std::string str(html);
	for (auto i = htmlLiterals.begin(); i != htmlLiterals.end(); i++)
	{
		auto key = i->first;
		auto val = i->second;
		str = ReplaceString(str, key, std::string({ val, '\0' }));
	}
	return str;
}
#else
std::string HtmlDecode(std::string const& html)
{
	std::string str;
	std::string token;
	bool isToken = false;
	//range base for
	for (size_t i = 0; i < html.size(); i++)
	{
		if (html[i] != '&' && !isToken)
		{
			str.push_back(html[i]);
			continue;
		}
		else if (html[i] == '&')
		{
			token.push_back(html[i]);
			isToken = true;
			continue;
		}
		if (html[i] != ';')
		{
			token.push_back(html[i]);
			continue;
		}
		else
		{
			token.push_back(html[i]);
			if (htmlLiterals.count(token) != 0)
			{
				char ch = htmlLiterals.at(token);
				str.push_back(ch);
				token.clear();
				isToken = false;
				continue;
			}
			else
			{
				throw std::invalid_argument("ERROR! HTML token-string is incorrect!");
			}
		}
	}

	if (isToken)
	{
		throw std::invalid_argument("ERROR! HTML token-string without end!");
	}
	
	return str;
}
#endif