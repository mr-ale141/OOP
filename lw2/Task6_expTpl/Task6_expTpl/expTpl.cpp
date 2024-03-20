#include <vector>
#include "expTpl.h"

// v - текущая вершина
// u - наидлиннейший суффикс строки v + ch || root

const int countChar = 256;

struct bohrVrtx
{
	int nextVrtx[countChar];
	int patNum;
	int suffLink;
	int autoMove[countChar]; //запоминание перехода автомата
	int par; //вершина-отец в дереве
	char symb; //символ на ребре от par к этой вершине 
	int suffFlink; //"хорошая" суф. ссылка
	bool flag;
};

std::vector<bohrVrtx> bohr;
std::vector<std::string> pattern;

bohrVrtx MakeBohrVrtx(int p, char c) //передаем номер отца и символ на ребре в боре
{
	bohrVrtx v;
	//(255)=(2^8-1)=(все единицы в каждом байте памяти)=(-1 в дополнительном коде целого 4-байтного числа int)
	memset(v.nextVrtx, 255, sizeof(v.nextVrtx));
	v.flag = false;
	v.suffLink = -1;
	memset(v.autoMove, 255, sizeof(v.autoMove));
	v.par = p;
	v.symb = c;
	v.suffFlink = -1;
	return v;
}

int GetAutoMove(int v, char ch);

int GetSuffLink(int v)
{
	if (bohr[v].suffLink == -1) //если еще не считали
		if (v == 0 || bohr[v].par == 0) //если v - корень или предок v - корень
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
		if (u == 0) //либо v - корень, либо суф. ссылка v указывает на корень 
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
	//добавляем единственную вершину - корень
	bohr.push_back(MakeBohrVrtx(0, 0));
}

void AddStringToBohr(const std::string& s) 
{
	int num = 0; //начинаем с корня   
	for (int i = 0; i < s.length(); i++)
	{
		char ch = s[i]; //получаем номер в алфавите
		if (bohr[num].nextVrtx[ch] == -1) //-1 - признак отсутствия ребра
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
