#include <vector>
#include "expTpl.h"

// v - current point
// u - longer suffics v + ch || root

// размер алфавита
const int countChar = 256;

//структуры с заглавной буквы
struct bohrVrtx
{
	//это в память не влезет
	int nextVrtx[countChar];
	int patNum;//название не удачное
	int suffLink;
	int autoMove[countChar]; //remember step
	int par; //parent
	char symb; //symbol for this
	int suffFlink; //"best" suf. link
	bool flag;// описать сущность
};

std::vector<bohrVrtx> bohr;
std::vector<std::string> pattern;

bohrVrtx MakeBohrVrtx(int p, char c) //p - parrent, c - char in 
{
	bohrVrtx v;
	memset(v.nextVrtx, 255U, sizeof(v.nextVrtx));
	v.flag = false;
	v.suffLink = -1;
	memset(v.autoMove, 255U, sizeof(v.autoMove));
	v.par = p;
	v.symb = c;
	v.suffFlink = -1;
	return v;
}

int GetAutoMove(int v, char ch);

int GetSuffLink(int v)
{
	if (bohr[v].suffLink == -1) //if suffics not found
		if (v == 0 || bohr[v].par == 0) //if v - root or parent v - root
			bohr[v].suffLink = 0;
		else
			bohr[v].suffLink = GetAutoMove(GetSuffLink(bohr[v].par), bohr[v].symb);
	return bohr[v].suffLink;
}

int GetAutoMove(int v, char ch)
{
	if (bohr[v].autoMove[ch] == -1)
		if (bohr[v].nextVrtx[ch] != -1)
			bohr[v].autoMove[ch] = bohr[v].nextVrtx[ch];
		else
			if (v == 0)
				bohr[v].autoMove[ch] = 0;
			else
				bohr[v].autoMove[ch] = GetAutoMove(GetSuffLink(v), ch);
	return bohr[v].autoMove[ch];
}

int GetSuffFlink(int v)
{
	if (bohr[v].suffFlink == -1)
	{
		int u = GetSuffLink(v);
		if (u == 0) //or v - root, or sufics link v pointer to root 
			bohr[v].suffFlink = 0;
		else
			bohr[v].suffFlink = (bohr[u].flag) ? u : GetSuffFlink(u);
	}
	return bohr[v].suffFlink;
}

std::string Check(int v, int i)
{
	for (int u = v; u != 0; u = GetSuffFlink(u))
	{
		if (bohr[u].flag)
			return pattern[bohr[u].patNum];
	}
	return std::string();
}

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

std::string Replace(const std::string& s, std::map<std::string, std::string> const& params)
{
	int u = 0;
	int uOld = 0;
	std::string result;
	std::string find;
	std::string findNew;
	std::string buf;
	for (int i = 0; i < s.length(); i++)
	{
		uOld = u;
		u = GetAutoMove(u, s[i]);
		findNew = Check(u, i + 1);

		if (u == 0 && uOld == 0)
		{
			result.push_back(s[i]);
		}
		else
		{
			buf.push_back(s[i]);
		}

		if (findNew.length() < find.length() && u < uOld)
		{
			if (findNew.length()) buf.pop_back();
			result.append(ReplaceString(buf, find, params.at(find)));
			buf.clear();
			if (findNew.length()) buf.push_back(s[i]);
		}

		if (findNew.length() != 0 && (u == 0 && uOld != 0) || (findNew.length() == 1 && u != 0))
		{
			result.append(ReplaceString(buf, findNew, params.at(findNew)));
			findNew.clear();
			buf.clear();
			u = 0;
		}

		find = findNew;
	}
	return result;
}

void BohrInit() 
{
	bohr.clear();
	pattern.clear();
	//add ones Node - root
	bohr.push_back(MakeBohrVrtx(0, 0));
}

void AddStringToBohr(const std::string& s) 
{
	int num = 0; //start from root  
	for (int i = 0; i < s.length(); i++)
	{
		char ch = s[i];
		if (bohr[num].nextVrtx[ch] == -1) // -1 - not found
		{ 
			bohr.push_back(MakeBohrVrtx(num, ch));
			bohr[num].nextVrtx[ch] = bohr.size() - 1;
		}
		num = bohr[num].nextVrtx[ch];
	}
	bohr[num].flag = true;
	pattern.push_back(s);
	bohr[num].patNum = pattern.size() - 1;
}

bool IsStringInBohr(const std::string& s) 
{
	int num = 0;
	for (int i = 0; i < s.length(); i++) 
	{
		char ch = s[i];
		if (bohr[num].nextVrtx[ch] == -1)
		{
			return false;
		}
		num = bohr[num].nextVrtx[ch];
	}
	return true;
}

std::string ExpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params)
{
	std::string str;

	BohrInit();

	for (auto iter : params)
	{
		AddStringToBohr(iter.first);
	}

	return Replace(tpl, params);
}
