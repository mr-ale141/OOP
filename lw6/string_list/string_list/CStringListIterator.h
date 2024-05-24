#pragma once
#include <iterator>
#include <stdexcept>
#include <memory>
#include <compare>

class CListItem;

template<bool IsConst = false>
class CStringListIterator
{
public:
    friend class CStringList;

    //bidirectional
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using reference_type = std::conditional_t<IsConst, 
        const std::string&, 
        std::string&
    >;
    using pointer_type = std::conditional_t<IsConst, 
        const std::shared_ptr<CListItem>, 
        std::shared_ptr<CListItem>
    >;
    using value_type = std::conditional_t<IsConst, 
        const CListItem, 
        CListItem
    >;

    reference_type operator*() const;

    // возможность преобразования константного итератора к 
    // не константному (приведение типов) есть два способа
    /*
    There are two ways to write an implicit conversion.

    1. Write a converting constructor for const_iterator that takes an iterator.
    2. Write a conversion function for iterator that converts to a const_iterator.
    
    In this case, the simplest way is probably writing a conversion function:

    operator TreeIterator<T, true>() const { return ... ;
    }
    This function would exist in both TreeIterator<T, true> and TreeIterator<T, false>, 
    but will never actually be used if the object is already a TreeIterator<T, true>.
    The opposite conversion is simply impossible because nothing has been written for it.
    */


    CStringListIterator(const CStringListIterator& iter) = default;
    bool operator!=(const CStringListIterator& iter) const;
    bool operator==(const CStringListIterator& iter) const;
    //лишнее
    auto operator<=>(const CStringListIterator& iter) const = default;
    // лишнее
    CStringListIterator operator[](__int64 num);
    CStringListIterator operator+(__int64 num) const;
    CStringListIterator& operator+=(__int64 num);
    CStringListIterator& operator-=(__int64 num);
    CStringListIterator operator-(__int64 num) const;
    // до сюда лишнее

    __int64 operator-(const CStringListIterator& iter) const;
    CStringListIterator& operator++();
    CStringListIterator& operator--();
    CStringListIterator operator++(int);
    CStringListIterator operator--(int);
    ~CStringListIterator() = default;
protected:
    CStringListIterator() = default;
private:
    CStringListIterator(pointer_type ptr);
    pointer_type m_ptr = nullptr;
};

template<bool IsConst>
bool CStringListIterator<IsConst>::operator!=(const CStringListIterator<IsConst>& iter) const
{
    return m_ptr != iter.m_ptr;
}

template<bool IsConst>
bool CStringListIterator<IsConst>::operator==(const CStringListIterator<IsConst>& iter) const
{
    return m_ptr == iter.m_ptr;
}

template<bool IsConst>
typename CStringListIterator<IsConst>::reference_type CStringListIterator<IsConst>::operator*() const
{
    if (m_ptr == nullptr)
        throw std::out_of_range("ERROR! Out of range!");
    return m_ptr->m_string;
}

template<bool IsConst>
CStringListIterator<IsConst> CStringListIterator<IsConst>::operator[](__int64 num)
{
    return *this + num;
}

template<bool IsConst>
CStringListIterator<IsConst> CStringListIterator<IsConst>::operator+(__int64 num) const
{
    CStringListIterator<IsConst> it(m_ptr);
    if (num >= 0)
    {
        for (size_t i = 0; i < static_cast<size_t>(num); ++i)
            it.m_ptr = it.m_ptr->m_next;
    }
    else
    {
        return *this - std::abs(num);
    }
    return it;
}

template<bool IsConst>
CStringListIterator<IsConst>& CStringListIterator<IsConst>::operator+=(__int64 num)
{
    if (num >= 0)
    {
        while (num--)
            ++(*this);
    }
    else
    {
        while (num++)
            --(*this);
    }
    return *this;
}

template<bool IsConst>
CStringListIterator<IsConst>& CStringListIterator<IsConst>::operator-=(__int64 num)
{
    return *this += -num;
}

template<bool IsConst>
CStringListIterator<IsConst> operator+(__int64 num, const CStringListIterator<IsConst>& iter)
{
    return iter + num;
}

template<bool IsConst>
CStringListIterator<IsConst> CStringListIterator<IsConst>::operator-(__int64 num) const
{
    CStringListIterator<IsConst> it(m_ptr);
    if (num >= 0)
    {
        for (size_t i = 0; i < static_cast<size_t>(num); ++i)
            it.m_ptr = it.m_ptr->m_prev.lock();
    }
    else
    {
        return *this + std::abs(num);
    }
    return it;
}

template<bool IsConst>
__int64 CStringListIterator<IsConst>::operator-(const CStringListIterator<IsConst>& iter) const
{
    __int64 count{};
    if (m_ptr == iter.m_ptr)
        return count;

    auto next = iter.m_ptr->m_next;
    ++count;
    while (next != m_ptr)
    {
        next = next->m_next;
        if (next == nullptr)
            throw std::invalid_argument("ERROR! binary '-'");
        ++count;
    }

    return count;
}

template<bool IsConst>
CStringListIterator<IsConst>& CStringListIterator<IsConst>::operator++()
{
    m_ptr = m_ptr->m_next;
    return *this;
}

template<bool IsConst>
CStringListIterator<IsConst> CStringListIterator<IsConst>::operator++(int)
{
    CStringListIterator<IsConst> old(m_ptr);
    m_ptr = m_ptr->m_next;
    return old;
}

template<bool IsConst>
CStringListIterator<IsConst>& CStringListIterator<IsConst>::operator--()
{
    m_ptr = m_ptr->m_prev.lock();
    return *this;
}

template<bool IsConst>
CStringListIterator<IsConst> CStringListIterator<IsConst>::operator--(int)
{
    CStringListIterator<IsConst> old(m_ptr);
    m_ptr = m_ptr->m_prev.lock();
    return old;
}

template<bool IsConst>
CStringListIterator<IsConst>::CStringListIterator(typename CStringListIterator<IsConst>::pointer_type ptr)
    : m_ptr(ptr)
{}
