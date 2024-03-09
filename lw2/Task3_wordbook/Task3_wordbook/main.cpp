#include <iostream>
#include <string>
#include <map>
#include "wordbook.h"

bool PrintWords(const Book& book, const std::string& keyString)
{
	auto key = GetKey(keyString);
	size_t size = book.count(key);
	if (size == 0)
	{
		return false;
	}
	auto range = book.equal_range(key);
	for (auto i = range.first; i != range.second; ++i)
	{
		std::cout << i->second;
		--size;
		if (size != 0)
		{
			std::cout << ", ";
		}
	}
	std::cout << std::endl;
	return true;
}

int main(const int argc, const char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Error! There are no required parameters!" << std::endl;
		std::cout << "Example:" << std::endl;
		std::cout << "-> bookword.exe <file_name>" << std::endl;
		return 1;
	}
	std::string fileName(argv[1]);

	auto book = GetWordBook(fileName);

	PrintWords(book.enToRu, "HeLlo");
	PrintWords(book.enToRu, "CAT");
	PrintWords(book.enToRu, "I go sleep");
	PrintWords(book.ruToEn, "прИвЕт");
	PrintWords(book.ruToEn, "Я иду спать");

	return 0;
}