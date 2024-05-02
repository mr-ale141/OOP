#pragma once
#include <iterator>
#include "CMyStringIterator.h"

template<typename T>
class CMyStringConstIterator : public CMyStringIterator<T>
{
public:
    friend class CMyString;

    using iterator_category = std::input_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    CMyStringConstIterator(const CMyStringConstIterator& iter) = default;
    const T& operator*() const;
    ~CMyStringConstIterator() = default;
protected:
private:
    CMyStringConstIterator(T* ptr);
    T* m_ptr = nullptr;
};

template<typename T>
static CMyStringConstIterator<T> operator+(int i, const CMyStringConstIterator<T>& iter)
{
    return iter + i;
}

template<typename T>
CMyStringConstIterator<T>::CMyStringConstIterator(T* ptr)
    : m_ptr(ptr)
{}

template<typename T>
const T& CMyStringConstIterator<T>::operator*() const
{
    return *m_ptr;
}
