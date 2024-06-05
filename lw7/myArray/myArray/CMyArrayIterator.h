#pragma once
#include <iterator>

template<typename T>
class CMyArray;

template<typename T, bool IsConst = false>
class CMyArrayIterator
{
    friend class CMyArray<T>;

public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using reference_type = std::conditional_t<IsConst, const T&, T&>;
    using pointer_type = std::conditional_t<IsConst, const T*, T*>;
    using value_type = std::conditional_t<IsConst, const T, T>;

    reference_type operator*() const;

    CMyArrayIterator(const CMyArrayIterator& iter) = default;
    bool operator==(const CMyArrayIterator& iter) const;
    bool operator!=(const CMyArrayIterator& iter) const;
    bool operator<(const CMyArrayIterator& iter) const;
    bool operator>(const CMyArrayIterator& iter) const;
    CMyArrayIterator& operator++();
    CMyArrayIterator& operator--();
    CMyArrayIterator operator++(int);
    CMyArrayIterator operator--(int);
    __int64 operator-(const CMyArrayIterator& iter) const;
    CMyArrayIterator<T, IsConst> operator+(__int64 i);
    CMyArrayIterator<T, IsConst> operator-(__int64 i);
    CMyArrayIterator<T, IsConst>& operator+=(__int64 i);
    CMyArrayIterator<T, IsConst>& operator-=(__int64 i);
    ~CMyArrayIterator() = default;
protected:
    CMyArrayIterator() = default;
private:
    CMyArrayIterator(pointer_type ptr);
    pointer_type m_ptr = nullptr;
};


template<typename T, bool IsConst>
bool CMyArrayIterator<T, IsConst>::operator==(const CMyArrayIterator<T, IsConst>& iter) const
{
    return m_ptr == iter.m_ptr;
}

template<typename T, bool IsConst>
static CMyArrayIterator<T, IsConst> operator+(__int64 i, const CMyArrayIterator<T, IsConst>& iter)
{
    return iter + i;
}

template<typename T, bool IsConst>
bool CMyArrayIterator<T, IsConst>::operator!=(const CMyArrayIterator<T, IsConst>& iter) const
{
    return m_ptr != iter.m_ptr;
}

template<typename T, bool IsConst>
bool CMyArrayIterator<T, IsConst>::operator<(const CMyArrayIterator<T, IsConst>& iter) const
{
    return m_ptr < iter.m_ptr;
}

template<typename T, bool IsConst>
bool CMyArrayIterator<T, IsConst>::operator>(const CMyArrayIterator<T, IsConst>& iter) const
{
    return m_ptr > iter.m_ptr;
}

template<typename T, bool IsConst>
CMyArrayIterator<T, IsConst>::reference_type CMyArrayIterator<T, IsConst>::operator*() const
{
    return *m_ptr;
}

template<typename T, bool IsConst>
CMyArrayIterator<T, IsConst>& CMyArrayIterator<T, IsConst>::operator++()
{
    ++m_ptr;
    return *this;
}

template<typename T, bool IsConst>
CMyArrayIterator<T, IsConst> CMyArrayIterator<T, IsConst>::operator++(int)
{
    CMyArrayIterator<T, IsConst> old(m_ptr);
    ++m_ptr;
    return old;
}

template<typename T, bool IsConst>
CMyArrayIterator<T, IsConst>& CMyArrayIterator<T, IsConst>::operator--()
{
    --m_ptr;
    return *this;
}

template<typename T, bool IsConst>
CMyArrayIterator<T, IsConst> CMyArrayIterator<T, IsConst>::operator--(int)
{
    CMyArrayIterator<T, IsConst> old(m_ptr);
    --m_ptr;
    return old;
}

template<typename T, bool IsConst>
__int64 CMyArrayIterator<T, IsConst>::operator-(const CMyArrayIterator<T, IsConst>& iter) const
{
    return m_ptr - iter.m_ptr;
}

template<typename T, bool IsConst>
CMyArrayIterator<T, IsConst> CMyArrayIterator<T, IsConst>::operator+(__int64 i)
{
    return CMyArrayIterator<T, IsConst>(m_ptr += i);
}

template<typename T, bool IsConst>
CMyArrayIterator<T, IsConst> CMyArrayIterator<T, IsConst>::operator-(__int64 i)
{
    return CMyArrayIterator<T, IsConst>(m_ptr -= i);
}

template<typename T, bool IsConst>
CMyArrayIterator<T, IsConst>& CMyArrayIterator<T, IsConst>::operator+=(__int64 i)
{
    m_ptr += i;
    return *this;
}

template<typename T, bool IsConst>
CMyArrayIterator<T, IsConst>& CMyArrayIterator<T, IsConst>::operator-=(__int64 i)
{
    m_ptr -= i;
    return *this;
}

template<typename T, bool IsConst>
CMyArrayIterator<T, IsConst>::CMyArrayIterator(CMyArrayIterator<T, IsConst>::pointer_type ptr)
    : m_ptr(ptr)
{}

