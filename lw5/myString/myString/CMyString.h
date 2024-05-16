#pragma once
#include <string>
#include <iostream>
#include <compare>
#include "CMyStringIterator.h"
#include "CMyStringConstIterator.h"

class CMyString
{
public:
    CMyString();
    explicit CMyString(const char* pString);
    CMyString(const char* pString, size_t length);
    CMyString(CMyString const& other);
    CMyString(CMyString&& other) noexcept;
    CMyString(std::string const& stlString);
    ~CMyString();
    size_t GetLength() const;
    const char* GetStringData() const;
    CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
    void Clear();
    size_t GetCapacity() const;
    //добавить перемещающий оператор присваивания
    CMyString& operator=(const CMyString& str);
    CMyString operator+(const CMyString& str) const;
    CMyString& operator+=(const CMyString& str);
    CMyString& operator+=(char ch);

    // <=> with weak ordering
    // эквивалентные объекты
    // через публичные методы и поля можно определить отличаются они или нет
    auto operator<=>(const CMyString& str) const
    {
        return std::strcmp(m_string, str.m_string) <=> 0;
    }

    bool operator==(const CMyString& str) const;
    bool operator==(const char* str) const;

    char operator[](size_t i) const;
    
    // and const for 'range base for'
    CMyStringIterator<false> begin();
    CMyStringIterator<false> end();
    // use const CMyStringIterator
    // const
    CMyStringIterator<true> cbegin();
    CMyStringIterator<true> cend();

private:
    size_t m_capacity = 0;
    char* m_string = nullptr;
    size_t m_length = 0;
};

static CMyString operator+(const std::string& stdStr, const CMyString& myStr)
{
    CMyString newStr(stdStr.c_str());
    return newStr + myStr;
}

static CMyString operator+(const CMyString& myStr, const std::string& stdStr)
{
    CMyString newStr(stdStr.c_str());
    return myStr + newStr;
}

static CMyString operator+(const char* cStr, const CMyString& myStr)
{
    CMyString newStr(cStr);
    return newStr + myStr;
}

static CMyString operator+(const CMyString& myStr, const char* cStr)
{
    CMyString newStr(cStr);
    return myStr + newStr;
}

static std::ostream& operator<<(std::ostream& os, const CMyString& str)
{
    for (size_t i = 0; i < str.GetLength(); ++i)
    {
        os << str.GetStringData()[i];
    }
    return os;
}

static std::istream& operator>>(std::istream& in, CMyString& str)
{
    char ch = '\0';
    in >> std::noskipws;
    while (in >> ch )
    {
        if (ch == ' ' || ch == '\t' || ch == '\n')
            break;
        str += ch;
    }
    return in;
}
