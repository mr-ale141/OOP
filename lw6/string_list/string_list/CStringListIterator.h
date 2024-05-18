#pragma once
#include <iterator>
#include "CListItem.h"

template<bool IsConst = false>
class CStringListIterator
{
public:
    friend class CStringList;

    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using reference_type = std::conditional_t<IsConst, const CListItem&, CListItem&>;
    using pointer_type = std::conditional_t<IsConst, const CListItem*, CListItem*>;
    using value_type = std::conditional_t<IsConst, const CListItem, CListItem>;

    reference_type operator*() const;

    CStringListIterator(const CStringListIterator& iter) = default;
    bool operator==(const CStringListIterator& iter) const;
    bool operator!=(const CStringListIterator& iter) const;
    bool operator<(const CStringListIterator& iter) const;
    bool operator>(const CStringListIterator& iter) const;
    CStringListIterator& operator++();
    CStringListIterator& operator--();
    CStringListIterator operator++(int);
    CStringListIterator operator--(int);
    __int64 operator-(const CStringListIterator& iter) const;
    CStringListIterator<IsConst> operator+(__int64 i);
    CStringListIterator<IsConst> operator-(__int64 i);
    CStringListIterator<IsConst>& operator+=(__int64 i);
    CStringListIterator<IsConst>& operator-=(__int64 i);
    ~CStringListIterator() = default;
protected:
    CStringListIterator() = default;
private:
    CStringListIterator(pointer_type ptr);
    pointer_type m_ptr = nullptr;
};

template<bool IsConst>
bool CStringListIterator<IsConst>::operator==(const CStringListIterator<IsConst>& iter) const
{
    return m_ptr == iter.m_ptr;
}

template<bool IsConst>
static CStringListIterator<IsConst> operator+(__int64 i, const CStringListIterator<IsConst>& iter)
{
    return iter + i;
}

template<bool IsConst>
bool CStringListIterator<IsConst>::operator!=(const CStringListIterator<IsConst>& iter) const
{
    return m_ptr != iter.m_ptr;
}

template<bool IsConst>
bool CStringListIterator<IsConst>::operator<(const CStringListIterator<IsConst>& iter) const
{
    return m_ptr < iter.m_ptr;
}

template<bool IsConst>
bool CStringListIterator<IsConst>::operator>(const CStringListIterator<IsConst>& iter) const
{
    return m_ptr > iter.m_ptr;
}

template<bool IsConst>
CStringListIterator<IsConst>::reference_type CStringListIterator<IsConst>::operator*() const
{
    return *m_ptr;
}

template<bool IsConst>
CStringListIterator<IsConst>& CStringListIterator<IsConst>::operator++()
{
    ++m_ptr;
    return *this;
}

template<bool IsConst>
CStringListIterator<IsConst> CStringListIterator<IsConst>::operator++(int)
{
    CStringListIterator<IsConst> old(m_ptr);
    ++m_ptr;
    return old;
}

template<bool IsConst>
CStringListIterator<IsConst>& CStringListIterator<IsConst>::operator--()
{
    --m_ptr;
    return *this;
}

template<bool IsConst>
CStringListIterator<IsConst> CStringListIterator<IsConst>::operator--(int)
{
    CStringListIterator<IsConst> old(m_ptr);
    --m_ptr;
    return old;
}

template<bool IsConst>
__int64 CStringListIterator<IsConst>::operator-(const CStringListIterator<IsConst>& iter) const
{
    return m_ptr - iter.m_ptr;
}

template<bool IsConst>
CStringListIterator<IsConst> CStringListIterator<IsConst>::operator+(__int64 i)
{
    return CStringListIterator<IsConst>(m_ptr += i);
}

template<bool IsConst>
CStringListIterator<IsConst> CStringListIterator<IsConst>::operator-(__int64 i)
{
    return CStringListIterator<IsConst>(m_ptr -= i);
}

template<bool IsConst>
CStringListIterator<IsConst>& CStringListIterator<IsConst>::operator+=(__int64 i)
{
    m_ptr += i;
    return *this;
}

template<bool IsConst>
CStringListIterator<IsConst>& CStringListIterator<IsConst>::operator-=(__int64 i)
{
    m_ptr -= i;
    return *this;
}

template<bool IsConst>
CStringListIterator<IsConst>::CStringListIterator(CStringListIterator<IsConst>::pointer_type ptr)
    : m_ptr(ptr)
{}
