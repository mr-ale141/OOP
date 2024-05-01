#pragma once
#include <string>
#include <iostream>
#include <iterator>

static const size_t defaultCap = 15;

class CMyString;

template<typename T>
class CMyStringIterator
{
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    friend class CMyString;
public:
    CMyStringIterator(const CMyStringIterator& iter) = default;
    bool operator==(const CMyStringIterator& iter) const;
    bool operator!=(const CMyStringIterator& iter) const;
    bool operator<(const CMyStringIterator& iter) const;
    bool operator>(const CMyStringIterator& iter) const;
    T& operator*();
    CMyStringIterator& operator++();
    CMyStringIterator& operator--();
    CMyStringIterator operator++(int);
    CMyStringIterator operator--(int);
    size_t operator-(const CMyStringIterator& iter) const;
    CMyStringIterator<T> operator+(int i);
    CMyStringIterator<T>& operator+=(int i);
    CMyStringIterator<T>& operator-=(int i);
    CMyStringIterator(T* ptr);
private:
    T* m_ptr = nullptr;
};

template<typename T>
static CMyStringIterator<T> operator+(int i, const CMyStringIterator<T>& iter)
{
    return iter + i;
}

template<typename T>
class CMyStringConstIterator
{
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = const T;
    using pointer = T*;
    using reference = const T&;

    friend class CMyString;
public:
    CMyStringConstIterator(const CMyStringConstIterator& iter) = default;
    bool operator==(const CMyStringConstIterator& iter) const;
    bool operator!=(const CMyStringConstIterator& iter) const;
    bool operator<(const CMyStringConstIterator& iter) const;
    bool operator>(const CMyStringConstIterator& iter) const;
    const T& operator*() const;
    CMyStringConstIterator& operator++();
    CMyStringConstIterator& operator--();
    CMyStringConstIterator operator--(int);
    CMyStringConstIterator operator++(int);
    size_t operator-(const CMyStringConstIterator& iter);
    CMyStringConstIterator<T> operator+(int i);
    CMyStringConstIterator<T>& operator+=(int i);
    CMyStringConstIterator<T>& operator-=(int i);
    CMyStringConstIterator(const T* ptr);
private:
    const T* m_ptr = nullptr;
};

template<typename T>
static CMyStringConstIterator<T> operator+(int i, const CMyStringConstIterator<T>& iter)
{
    return iter + i;
}

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
    CMyStringConstIterator<char> cbegin() const;
    CMyStringConstIterator<char> cend() const;

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
