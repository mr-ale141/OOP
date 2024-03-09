#pragma once

using Book = std::multimap<std::string, std::string>;

struct BookOptional
{
	Book enToRu;
	Book ruToEn;
	bool isValid = true;
	std::string msg;
};

std::string GetKey(const std::string& str);

BookOptional GetWordBook(const std::string& fileName);

void UpdateWordBook(std::ofstream& output, const BookOptional& book);
