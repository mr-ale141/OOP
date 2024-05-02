#pragma once
#include <iterator>

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
