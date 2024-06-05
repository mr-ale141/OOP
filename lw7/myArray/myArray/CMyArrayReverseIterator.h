#pragma once
#include <iterator>

template<typename T>
class CMyArray;

template<typename T, bool IsConst = false>
class CMyArrayReverseIterator
{
    friend class CMyArray<T>;

public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using reference_type = std::conditional_t<IsConst, const T&, T&>;
    using pointer_type = std::conditional_t<IsConst, const T*, T*>;
    using value_type = std::conditional_t<IsConst, const T, T>;

    reference_type operator*() const;

    CMyArrayReverseIterator(const CMyArrayReverseIterator& iter) = default;
    bool operator==(const CMyArrayReverseIterator& iter) const;
    bool operator!=(const CMyArrayReverseIterator& iter) const;
    bool operator<(const CMyArrayReverseIterator& iter) const;
    bool operator>(const CMyArrayReverseIterator& iter) const;
    CMyArrayReverseIterator& operator++();
    CMyArrayReverseIterator& operator--();
    CMyArrayReverseIterator operator++(int);
    CMyArrayReverseIterator operator--(int);
    __int64 operator-(const CMyArrayReverseIterator& iter) const;
    CMyArrayReverseIterator<T, IsConst> operator+(__int64 i);
    CMyArrayReverseIterator<T, IsConst> operator-(__int64 i);
    CMyArrayReverseIterator<T, IsConst>& operator+=(__int64 i);
    CMyArrayReverseIterator<T, IsConst>& operator-=(__int64 i);
    ~CMyArrayReverseIterator() = default;
protected:
    CMyArrayReverseIterator() = default;
private:
    CMyArrayReverseIterator(pointer_type ptr);
    pointer_type m_ptr = nullptr;
};


template<typename T, bool IsConst>
bool CMyArrayReverseIterator<T, IsConst>::operator==(const CMyArrayReverseIterator<T, IsConst>& iter) const
{
    return m_ptr == iter.m_ptr;
}

template<typename T, bool IsConst>
static CMyArrayReverseIterator<T, IsConst> operator+(__int64 i, const CMyArrayReverseIterator<T, IsConst>& iter)
{
    return iter - i;
}

template<typename T, bool IsConst>
bool CMyArrayReverseIterator<T, IsConst>::operator!=(const CMyArrayReverseIterator<T, IsConst>& iter) const
{
    return m_ptr != iter.m_ptr;
}

template<typename T, bool IsConst>
bool CMyArrayReverseIterator<T, IsConst>::operator<(const CMyArrayReverseIterator<T, IsConst>& iter) const
{
    return m_ptr > iter.m_ptr;
}

template<typename T, bool IsConst>
bool CMyArrayReverseIterator<T, IsConst>::operator>(const CMyArrayReverseIterator<T, IsConst>& iter) const
{
    return m_ptr < iter.m_ptr;
}

template<typename T, bool IsConst>
CMyArrayReverseIterator<T, IsConst>::reference_type CMyArrayReverseIterator<T, IsConst>::operator*() const
{
    return *m_ptr;
}

template<typename T, bool IsConst>
CMyArrayReverseIterator<T, IsConst>& CMyArrayReverseIterator<T, IsConst>::operator++()
{
    --m_ptr;
    return *this;
}

template<typename T, bool IsConst>
CMyArrayReverseIterator<T, IsConst> CMyArrayReverseIterator<T, IsConst>::operator++(int)
{
    CMyArrayReverseIterator<T, IsConst> old(m_ptr);
    ++(*this);
    return old;
}

template<typename T, bool IsConst>
CMyArrayReverseIterator<T, IsConst>& CMyArrayReverseIterator<T, IsConst>::operator--()
{
    ++m_ptr;
    return *this;
}

template<typename T, bool IsConst>
CMyArrayReverseIterator<T, IsConst> CMyArrayReverseIterator<T, IsConst>::operator--(int)
{
    CMyArrayReverseIterator<T, IsConst> old(m_ptr);
    --(*this);
    return old;
}

template<typename T, bool IsConst>
__int64 CMyArrayReverseIterator<T, IsConst>::operator-(const CMyArrayReverseIterator<T, IsConst>& iter) const
{
    return iter.m_ptr - m_ptr;
}

template<typename T, bool IsConst>
CMyArrayReverseIterator<T, IsConst> CMyArrayReverseIterator<T, IsConst>::operator+(__int64 i)
{
    CMyArrayReverseIterator<T, IsConst> iter(m_ptr);
    iter += i;
    return iter;
}

template<typename T, bool IsConst>
CMyArrayReverseIterator<T, IsConst> CMyArrayReverseIterator<T, IsConst>::operator-(__int64 i)
{
    CMyArrayReverseIterator<T, IsConst> iter(m_ptr);
    iter -= i;
    return iter;
}

template<typename T, bool IsConst>
CMyArrayReverseIterator<T, IsConst>& CMyArrayReverseIterator<T, IsConst>::operator+=(__int64 i)
{
    m_ptr -= i;
    return *this;
}

template<typename T, bool IsConst>
CMyArrayReverseIterator<T, IsConst>& CMyArrayReverseIterator<T, IsConst>::operator-=(__int64 i)
{
    m_ptr += i;
    return *this;
}

template<typename T, bool IsConst>
CMyArrayReverseIterator<T, IsConst>::CMyArrayReverseIterator(CMyArrayReverseIterator<T, IsConst>::pointer_type ptr)
    : m_ptr(ptr)
{}
