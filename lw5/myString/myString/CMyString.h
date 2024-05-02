#pragma once
#include <string>
#include <iostream>
#include "CMyStringIterator.h"
#include "CMyStringConstIterator.h"

static const size_t defaultCap = 15;

class CMyString
{
public:
    CMyString();
    CMyString(const char* pString);
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
    CMyString& operator=(const CMyString& str);
    CMyString operator+(const CMyString& str) const;
    CMyString& operator+=(const CMyString& str);
    CMyString& operator+=(char ch);
    bool operator==(const CMyString& str) const;
    bool operator!=(const CMyString& str) const;
    bool operator<(const CMyString& str) const;
    bool operator>(const CMyString& str) const;
    bool operator<=(const CMyString& str) const;
    bool operator>=(const CMyString& str) const;
    char operator[](size_t i) const;
    
    CMyStringIterator<char> begin();
    CMyStringIterator<char> end();
    CMyStringConstIterator<char> cbegin();
    CMyStringConstIterator<char> cend();

private:
    size_t m_capacity = defaultCap;
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
