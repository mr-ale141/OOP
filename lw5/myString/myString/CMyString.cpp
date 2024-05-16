#include <cstring>
#include <algorithm>
#include <stdexcept>
#include "CMyString.h"

static char emptyString[] = "";

CMyString::CMyString() : m_string(emptyString)
{}

CMyString::CMyString(const char* pString)
	: CMyString(pString, SIZE_MAX)
{}

CMyString::CMyString(const char* pString, size_t lengthStr)
{
	size_t length = lengthStr == SIZE_MAX ? strlen(pString) : lengthStr;
	size_t capacity = length * 2;
	m_string = new char[capacity];
	std::memcpy(m_string, pString, length);
	m_string[length] = '\0';
	m_capacity = capacity;
	m_length = length;
}

// использовать список инициализации везде где можно
CMyString::CMyString(CMyString const& other)
	: 
	m_string(new char[m_capacity]),
	m_length(other.m_length), 
	m_capacity(other.m_capacity)
{
	std::memcpy(m_string, other.m_string, m_length + 1);
}

// noexcept
// чтобы std::move при перемещающем конструкторе не переместил адрес внутренний другого объекта
// т.к. string хранит до 15 символов внутри себя 
CMyString::CMyString(CMyString&& other) noexcept
	:
	m_length(other.m_length),
	m_capacity(other.m_capacity),
	m_string(std::move(other.m_string))
{
	other.m_string = emptyString;
	other.m_length = 0;
	other.m_capacity = 0;
}

//use with lenstr
// т.к. не корректно сработает для "some\0string"
CMyString::CMyString(const std::string& str) 
	: CMyString(str.c_str(), str.length())
{}

CMyString::~CMyString()
{
	if (m_string != emptyString)
		delete[] m_string;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_string;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	return CMyString(&m_string[start], length);
}

void CMyString::Clear()
{
	delete[] m_string;
	m_capacity = 0;
	m_length = 0;
	m_string = emptyString;
}

size_t CMyString::GetCapacity() const
{
	return m_capacity;
}

CMyString& CMyString::operator=(const CMyString& str)
{
	if (m_string == str.m_string)
		return *this;
	char* newStrPtr = new char[str.m_capacity];
	m_capacity = str.m_capacity;
	m_length = str.m_length;
	delete[] m_string;
	m_string = newStrPtr;
	std::memcpy(m_string, str.m_string, m_length + 1);
	return *this;
}

CMyString CMyString::operator+(const CMyString& str) const
{
	CMyString newStr;
	newStr.m_length = m_length + str.m_length;
	newStr.m_capacity = newStr.m_length * 2;
	if (newStr.m_capacity == 0)
	{
		newStr.m_string = emptyString;
		return newStr;
	}
	newStr.m_string = new char[newStr.m_capacity];
	std::memcpy(newStr.m_string, m_string, m_length);
	std::memcpy(newStr.m_string + m_length, str.m_string, str.m_length + 1);
	return newStr;
}

CMyString& CMyString::operator+=(const CMyString& str)
{
	size_t freeSize = m_capacity - m_length + 1;
	if (freeSize < str.m_length)
	{
		std::memcpy(m_string + m_length, str.m_string, str.m_length + 1);
	}
	else
	{
		size_t length = m_length + str.m_length;
		size_t capacity = length * 2;
		char* strPtr = new char[capacity];
		std::memcpy(strPtr, m_string, m_length);
		std::memcpy(strPtr + m_length, str.m_string, str.m_length + 1);
		delete[] m_string;
		m_string = strPtr;
		m_length = length;
		m_capacity = capacity;
	}
	return *this;
}

CMyString& CMyString::operator+=(char ch)
{
	if (m_length + 1 < m_capacity - 1)
	{
		m_string[m_length] = ch;
		m_string[m_length + 1] = '\0';
		++m_length;
		return *this;
	}

	size_t length = m_length + 1;
	size_t capacity = length * 2;
	char* strPtr = new char[capacity];
	std::memcpy(strPtr, m_string, m_length);
	strPtr[m_length] = ch;
	strPtr[length] = '\0';
	delete[] m_string;
	m_string = strPtr;
	m_length = length;
	m_capacity = capacity;

	return *this;
}

bool CMyString::operator==(const CMyString& str) const
{
	return std::strcmp(m_string, str.m_string) == 0;
}
bool CMyString::operator==(const char* str) const
{
	return std::strcmp(m_string, str) == 0;
}

char CMyString::operator[](size_t i) const
{
	if (i < 0 || i > m_length - 1)
		throw std::invalid_argument("Index outside the array!");
	return m_string[i];
}

CMyStringIterator<false> CMyString::begin()
{
	return CMyStringIterator<false>(m_string);
}

CMyStringIterator<false> CMyString::end()
{
	return CMyStringIterator<false>(m_string + m_length);
}

CMyStringIterator<true> CMyString::cbegin()
{
	// return const CMyStringIterator<char>(m_string);
	return CMyStringIterator<true>(m_string);
}

CMyStringIterator<true> CMyString::cend()
{
	// return const CMyStringIterator<char>(m_string);
	return CMyStringIterator<true>(m_string + m_length);
}
