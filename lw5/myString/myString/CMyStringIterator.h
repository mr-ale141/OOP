#pragma once
#include <iterator>

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
