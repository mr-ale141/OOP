#include <iostream>
#include <string>
#include <exception>
#include <map>
#include "html_decode.h"

#define USE_REPLACE_STRING 1

static const std::map<std::string, char> htmlLiterals
{
	{ std::string("&quot;"), '"'  },
	{ std::string("&apos;"), '\'' },
	{ std::string("&lt;"),   '<'  },
	{ std::string("&gt;"),   '>'  },
	{ std::string("&amp;"),  '&'  },
};

#if USE_REPLACE_STRING

std::string HtmlDecode(std::string const& html)
{
	std::string result;
	std::string searchToken;
	searchToken.push_back('&');
	size_t pos = 0;
	bool isToken;
	while (pos < html.length())
	{
		isToken = false;
		size_t foundPos = html.find(searchToken, pos);
		result.append(html, pos, foundPos - pos);
		if (foundPos == std::string::npos)
			break;
		for (auto& token : htmlLiterals)
		{
			int findOffset = html.compare(foundPos, token.first.length(), token.first);
			if (findOffset == 0)
			{
				result.push_back(token.second);
				pos = foundPos + token.first.length();
				isToken = true;
				break;
			}
		}
		if (!isToken)
		{
			result.append(searchToken);
			pos = foundPos + searchToken.length();
		}
	}
	return result;
}
#else
std::string HtmlDecode(std::string const& html)
{
	std::string str;
	std::string token;
	bool isToken = false;
	char curCh;
	for (size_t i = 0; i < html.size(); i++)
	{
		curCh = html[i];
		if (curCh != '&' && !isToken)
		{
			str.push_back(curCh);
			continue;
		}
		else if (curCh == '&')
		{
			if (isToken)
			{
				str.append(token);
				token.clear();
				token.push_back(curCh);
				continue;
			}
			token.push_back(curCh);
			isToken = true;
			continue;
		}
		if (curCh != ';')
		{
			token.push_back(curCh);
			continue;
		}
		else
		{
			token.push_back(curCh);
			if (htmlLiterals.count(token) != 0)
			{
				char ch = htmlLiterals.at(token);
				str.push_back(ch);
				
			}
			else
			{
				str.append(token);
			}
			token.clear();
			isToken = false;
		}
	}

	if (isToken)
	{
		str.append(token);
	}
	return str;
}
#endif