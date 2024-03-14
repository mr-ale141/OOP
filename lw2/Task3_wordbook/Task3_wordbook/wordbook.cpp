#include <fstream>
#include <algorithm>
#include <cctype>
#include "wordbook.h"

static std::fstream file;

static const std::map<uint16_t, uint16_t> ruChars =
{
	{ std::make_pair((uint16_t)'А', (uint16_t)'а') },
	{ std::make_pair((uint16_t)'Б', (uint16_t)'б') },
	{ std::make_pair((uint16_t)'В', (uint16_t)'в') },
	{ std::make_pair((uint16_t)'Г', (uint16_t)'г') },
	{ std::make_pair((uint16_t)'Д', (uint16_t)'д') },
	{ std::make_pair((uint16_t)'Е', (uint16_t)'е') },
	{ std::make_pair((uint16_t)'Ё', (uint16_t)'ё') },
	{ std::make_pair((uint16_t)'Ж', (uint16_t)'ж') },
	{ std::make_pair((uint16_t)'З', (uint16_t)'з') },
	{ std::make_pair((uint16_t)'И', (uint16_t)'и') },
	{ std::make_pair((uint16_t)'Й', (uint16_t)'й') },
	{ std::make_pair((uint16_t)'К', (uint16_t)'к') },
	{ std::make_pair((uint16_t)'Л', (uint16_t)'л') },
	{ std::make_pair((uint16_t)'М', (uint16_t)'м') },
	{ std::make_pair((uint16_t)'Н', (uint16_t)'н') },
	{ std::make_pair((uint16_t)'О', (uint16_t)'о') },
	{ std::make_pair((uint16_t)'П', (uint16_t)'п') },
	{ std::make_pair((uint16_t)'Р', (uint16_t)'р') },
	{ std::make_pair((uint16_t)'С', (uint16_t)'с') },
	{ std::make_pair((uint16_t)'Т', (uint16_t)'т') },
	{ std::make_pair((uint16_t)'У', (uint16_t)'у') },
	{ std::make_pair((uint16_t)'Ф', (uint16_t)'ф') },
	{ std::make_pair((uint16_t)'Х', (uint16_t)'х') },
	{ std::make_pair((uint16_t)'Ц', (uint16_t)'ц') },
	{ std::make_pair((uint16_t)'Ч', (uint16_t)'ч') },
	{ std::make_pair((uint16_t)'Ъ', (uint16_t)'ъ') },
	{ std::make_pair((uint16_t)'Ы', (uint16_t)'ы') },
	{ std::make_pair((uint16_t)'Ь', (uint16_t)'ь') },
	{ std::make_pair((uint16_t)'Э', (uint16_t)'э') },
	{ std::make_pair((uint16_t)'Ю', (uint16_t)'ю') },
	{ std::make_pair((uint16_t)'Я', (uint16_t)'я') },
};

bool IsAsciiString(const std::string& str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		char ch = str[i];

		if ((ch >= 'A' && ch <= 'Z') || 
			(ch >= 'a' && ch <= 'z') || 
			ch == '\'' || 
			ch == '-' ||
			ch == ' ')
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

std::string ToLowerRuUtf8(const std::string& str)
{
	std::string key;
	size_t size = str.size();
	uint16_t wCh;
	char ch;
	for (size_t i = 0; i < size;)
	{
		wCh = 0;
		ch = str[i];
		wCh |= (uint16_t)ch << 8;
		if (size - i > 0)
		{
			wCh |= (uint8_t)str[i + 1];
		}
		bool isUpper = (ruChars.count(wCh) != 0);
		if (ch == ' ' || ch == '-')
		{
			key.push_back(ch);
			++i;
		}
		else if (!isUpper)
		{
			key.push_back(ch);
			++i;
			ch = str[i];
			key.push_back(ch);
			++i;
		}
		else
		{
			auto iter = ruChars.find(wCh);
			wCh = iter->second;
			uint8_t uCh = 0;
			uCh |= (uint8_t)(wCh >> 8);
			key.push_back((char)uCh);
			uCh = 0;
			uCh |= (uint8_t)wCh;
			key.push_back((char)uCh);
			++i;
			++i;
		}
	}
	return key;
}

std::string GetKey(const std::string& str)
{
	std::string key(str);
	if (IsAsciiString(key))
	{
		std::transform(key.begin(), key.end(), key.begin(),
			[](unsigned char c) { return std::tolower(c); });
	}
	else
	{
		key.clear();
		key = ToLowerRuUtf8(str);
	}
	return key;
}

std::string AddWord(BookOptional& book, const std::string& key, const std::string& value)
{
	std::string en;
	std::string ru;

	if (key.size() == 0 || value.size() == 0)
	{
		return en;
	}
	
	if (IsAsciiString(key))
	{
		en = key;
		ru = value;
	}
	else
	{
		en = value;
		ru = key;
	}
	book.enToRu.insert(std::make_pair(GetKey(en), ru));
	book.ruToEn.insert(std::make_pair(GetKey(ru), en));

	return GetKey(en);
}

void AddNewWord(BookOptional& book, const std::string& key, const std::string& value)
{
	auto newKey = AddWord(book, key, value);

	book.newEnKeys.insert(newKey);
}

BookOptional ReadWordBook(const std::string& fileName)
{
	BookOptional book;

	BookOptional invalidBook;
	invalidBook.isValid = false;
	invalidBook.msg = std::string("ERROR! Incorrect format in '" + fileName + "'");

	std::string word1;
	std::string word2;

	bool isOk = true;

	std::getline(file, word1);
	std::getline(file, word2);
	while (!file.eof())
	{
		isOk = AddWord(book, word1, word2).size() != 0;

		std::getline(file, word1);
		std::getline(file, word2);
	}

	file.clear();

	if (!isOk)
	{
		book = invalidBook;
	}
	return book;
}

BookOptional GetWordBook(const std::string& fileName)
{
	file.open(fileName, std::fstream::in | std::fstream::out | std::fstream::app);
	if (!file.is_open())
	{
		file.close();
		file.open(fileName, std::fstream::in | std::fstream::out | std::fstream::app | std::fstream::trunc);
		if (!file.is_open())
		{
			BookOptional invalidBook;
			invalidBook.isValid = false;
			invalidBook.msg = std::string("ERROR! Can't create file '" + fileName + "'");
			return invalidBook;
		}
	}
	return ReadWordBook(fileName);
}

bool PrintWords(const BookOptional& book, const std::string& keyString)
{
	auto key = GetKey(keyString);
	const Book& b = (IsAsciiString(key)) ? book.enToRu : book.ruToEn;
	size_t size = b.count(key);
	if (size == 0)
	{
		return false;
	}
	auto range = b.equal_range(key);
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

void SaveWordBook(BookOptional& book)
{
	for (auto en : book.newEnKeys)
	{
		auto range = book.enToRu.equal_range(en);
		for (auto i = range.first; i != range.second; ++i)
		{
			std::string notKeyEn = book.ruToEn.find(GetKey(i->second))->second;

			file << notKeyEn << std::endl;
			file << i->second << std::endl;
		}
	}

	if (!file.flush())
	{
		book.isValid = false;
		book.msg = "Can't write in file";
	}
}
