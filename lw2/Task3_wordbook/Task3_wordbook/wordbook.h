#pragma once
#include <string>
#include <map>
#include <set>
#include <vector>
#include <iostream>

using Book = std::multimap<std::string, std::string>;

struct BookOptional
{
	Book enToRu;
	Book ruToEn;
	std::set<std::string> newEnKeys;
	bool isValid = true;
	std::string msg;
};

bool IsAsciiString(const std::string& str);

std::string GetKey(const std::string& str);

BookOptional GetWordBook(const std::string& fileName);

bool PrintWords(const BookOptional& book, const std::string& keyString);

void SaveWordBook(BookOptional& book);

void AddNewWord(BookOptional& book, const std::string& key, const std::string& value);
