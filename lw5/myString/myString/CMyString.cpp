﻿#include <cstring>
#include <algorithm>
#include <stdexcept>
#include "CMyString.h"

static char emptyString[] = "";

// noexcept
// чтобы std::move при перемещающем конструкторе не переместил адрес внутренний другого объекта
// т.к. string хранит до 15 символов внутри себя 
CMyString::CMyString() : m_string(emptyString)
{}

//использовать делегирующий конструктор
CMyString::CMyString(const char* pString)
{
	m_length = strlen(pString);
	if (m_length >= m_capacity - 1)
		m_capacity = m_length * 2;
	m_string = new char[m_capacity];
	strncpy_s(m_string, m_capacity, pString, m_length + 1);
}

CMyString::CMyString(const char* pString, size_t length)
{
	m_length = length == SIZE_MAX ? strlen(pString) : length;
	if (m_length >= m_capacity - 1)
		m_capacity = m_length * 2;
	m_string = new char[m_capacity];
	std::memcpy(m_string, pString, m_length);
	m_string[m_length] = '\0';
}

// использовать список инициализации везде где можно
CMyString::CMyString(CMyString const& other)
{
	m_length = other.m_length;
	m_capacity = other.m_capacity;
	m_string = new char[m_capacity];
	std::memcpy(m_string, other.m_string, m_length + 1);
}

CMyString::CMyString(CMyString&& other) noexcept
{
	m_length = other.m_length;
	m_capacity = other.m_capacity;
	m_string = std::move(other.m_string);
	other.m_string = emptyString;
	other.m_length = 0;
	other.m_capacity = defaultCap; // = 0
}

//use with lenstr
// т.к. не корректно сработает для "some\0string"
CMyString::CMyString(std::string const& str) : CMyString(str.c_str())
{}

CMyString::~CMyString()
{
	if (m_string != emptyString)
		delete[] m_string;
}

size_t CMyString::GetLength()const
{
	return m_length;
}

const char* CMyString::GetStringData()const
{
	return m_string;
}

CMyString CMyString::SubString(size_t start, size_t length)const
{
	// index 0 and after '\0'
	return CMyString(&m_string[start - 1], length);
}

void CMyString::Clear()
{
	m_capacity = defaultCap;
	m_length = 0;
	this->~CMyString();// нельзя
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
	Clear();
	m_capacity = str.m_capacity;
	m_length = str.m_length;
	// m_strin not valid if except
	m_string = new char[m_capacity];
	std::memcpy(m_string, str.m_string, m_length + 1);
	return *this;
}

CMyString CMyString::operator+(const CMyString& str) const
{
	CMyString newStr;
	newStr.m_length = m_length + str.m_length;
	if (newStr.m_length >= newStr.m_capacity)
		newStr.m_capacity = newStr.m_length * 2;
	newStr.m_string = new char[newStr.m_capacity];// with except not valid, use private constructor(ptr, len, cap)
	std::memcpy(newStr.m_string, m_string, m_length);
	std::memcpy(newStr.m_string + m_length, str.m_string, str.m_length + 1);
	return newStr;
}

CMyString& CMyString::operator+=(const CMyString& str)
{
	// optimizate
	for (size_t i = 0; i < str.m_length; i++)
	{
		*this += str.m_string[i];
	}
	return *this;
}

CMyString& CMyString::operator+=(char ch)
{
	if (m_length + 1 < m_capacity)
	{
		m_string[m_length] = ch;
		m_string[m_length + 1] = '\0';
		++m_length;
		return *this;
	}

	size_t holdLength = m_length;
	char* holdPtr = m_string;
	m_string = nullptr;

	++m_length;
	m_capacity = m_length * 2;
	//if except not valid
	m_string = new char[m_capacity];

	std::memcpy(m_string, holdPtr, holdLength);
	m_string[holdLength] = ch;
	m_string[m_length] = '\0';

	delete[] holdPtr;

	return *this;
}

bool CMyString::operator==(const CMyString& str) const
{
	//дублирование
	if (m_length != str.m_length)
		return false;
	bool b = true;
	for (size_t i = 0; i < m_length; ++i)
	{
		b = m_string[i] == str.m_string[i];
		if (!b) break;
	}
	return b;
}

bool CMyString::operator!=(const CMyString& str) const
{
	if (m_length != str.m_length)
		return true;
	bool b = false;
	for (size_t i = 0; i < m_length; ++i)
	{
		b = m_string[i] != str.m_string[i];
		if (b) break;
	}
	return b;
}

bool CMyString::operator<(const CMyString& str) const
{
	if (m_length == 0 || str.m_length == 0)
		return m_length < str.m_length;

	bool b = false;
	// not work "308" < "21"
	for (size_t i = 0; i < std::min(m_length, str.m_length); ++i)
	{
		b = m_string[i] < str.m_string[i];
		if (b) return b;
	}
	return m_length < str.m_length;
}

bool CMyString::operator>(const CMyString& str) const
{
	if (m_length == 0 || str.m_length == 0)
		return m_length > str.m_length;

	bool b = true;
	for (size_t i = 0; i < std::min(m_length, str.m_length); ++i)
	{
		b = m_string[i] > str.m_string[i];
		if (!b) return b;
	}
	return b;
}

bool CMyString::operator<=(const CMyString& str) const
{
	return *this < str || *this == str;
}

bool CMyString::operator>=(const CMyString& str) const
{
	return *this > str || *this == str;
}

char CMyString::operator[](size_t i) const
{
	if (i < 0 || i > m_length - 1)
		throw std::invalid_argument("Index outside the array!");
	return m_string[i];
}

CMyStringIterator<char> CMyString::begin()
{
	return CMyStringIterator<char>(m_string);
}

CMyStringIterator<char> CMyString::end()
{
	return CMyStringIterator<char>(m_string + m_length);
}

CMyStringConstIterator<char> CMyString::cbegin()
{
	// return const CMyStringIterator<char>(m_string);
	return CMyStringConstIterator<char>(m_string);
}

CMyStringConstIterator<char> CMyString::cend()
{
	// return const CMyStringIterator<char>(m_string);
	return CMyStringConstIterator<char>(m_string + m_length);
}
