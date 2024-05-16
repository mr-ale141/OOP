#pragma once
#include <iterator>

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
template <bool IsConst>
class IteratorT
{
public:
    using value_type = std::conditional_t<IsConst, const char, char>;
    using difference_type = std::ptrdiff_t;

};
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

template<bool IsConst = false>
class CMyStringIterator
{
public:
    friend class CMyString;

    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using reference_type = std::conditional_t<IsConst, const char&, char&>;
    using pointer_type = std::conditional_t<IsConst, const char*, char*>;
    using value_type = std::conditional_t<IsConst, const char, char>;

    reference_type operator*() const;

    CMyStringIterator(const CMyStringIterator& iter) = default;
    bool operator==(const CMyStringIterator& iter) const;
    bool operator!=(const CMyStringIterator& iter) const;
    bool operator<(const CMyStringIterator& iter) const;
    bool operator>(const CMyStringIterator& iter) const;
    CMyStringIterator& operator++();
    CMyStringIterator& operator--();
    CMyStringIterator operator++(int);
    CMyStringIterator operator--(int);
    __int64 operator-(const CMyStringIterator& iter) const;
    CMyStringIterator<IsConst> operator+(__int64 i);
    CMyStringIterator<IsConst> operator-(__int64 i);
    CMyStringIterator<IsConst>& operator+=(__int64 i);
    CMyStringIterator<IsConst>& operator-=(__int64 i);
    ~CMyStringIterator() = default;
protected:
    CMyStringIterator() = default;
private:
    CMyStringIterator(pointer_type ptr);
    pointer_type m_ptr = nullptr;
};

template<bool IsConst>
bool CMyStringIterator<IsConst>::operator==(const CMyStringIterator<IsConst>& iter) const
{
    return m_ptr == iter.m_ptr;
}

template<bool IsConst>
static CMyStringIterator<IsConst> operator+(__int64 i, const CMyStringIterator<IsConst>& iter)
{
    return iter + i;
}

template<bool IsConst>
bool CMyStringIterator<IsConst>::operator!=(const CMyStringIterator<IsConst>& iter) const
{
	return m_ptr != iter.m_ptr;
}

template<bool IsConst>
bool CMyStringIterator<IsConst>::operator<(const CMyStringIterator<IsConst>& iter) const
{
	return m_ptr < iter.m_ptr;
}

template<bool IsConst>
bool CMyStringIterator<IsConst>::operator>(const CMyStringIterator<IsConst>& iter) const
{
	return m_ptr > iter.m_ptr;
}

template<bool IsConst>
CMyStringIterator<IsConst>::reference_type CMyStringIterator<IsConst>::operator*() const
{
	return *m_ptr;
}

template<bool IsConst>
CMyStringIterator<IsConst>& CMyStringIterator<IsConst>::operator++()
{
	++m_ptr;
	return *this;
}

template<bool IsConst>
CMyStringIterator<IsConst> CMyStringIterator<IsConst>::operator++(int)
{
	CMyStringIterator<IsConst> old(m_ptr);
	++m_ptr;
	return old;
}

template<bool IsConst>
CMyStringIterator<IsConst>& CMyStringIterator<IsConst>::operator--()
{
	--m_ptr;
	return *this;
}

template<bool IsConst>
CMyStringIterator<IsConst> CMyStringIterator<IsConst>::operator--(int)
{
	CMyStringIterator<IsConst> old(m_ptr);
	--m_ptr;
	return old;
}

template<bool IsConst>
__int64 CMyStringIterator<IsConst>::operator-(const CMyStringIterator<IsConst>& iter) const
{
	return m_ptr - iter.m_ptr;
}

template<bool IsConst>
CMyStringIterator<IsConst> CMyStringIterator<IsConst>::operator+(__int64 i)
{
	return CMyStringIterator<IsConst>(m_ptr += i);
}

template<bool IsConst>
CMyStringIterator<IsConst> CMyStringIterator<IsConst>::operator-(__int64 i)
{
	return CMyStringIterator<IsConst>(m_ptr -= i);
}

template<bool IsConst>
CMyStringIterator<IsConst>& CMyStringIterator<IsConst>::operator+=(__int64 i)
{
	m_ptr += i;
	return *this;
}

template<bool IsConst>
CMyStringIterator<IsConst>& CMyStringIterator<IsConst>::operator-=(__int64 i)
{
	m_ptr -= i;
	return *this;
}

template<bool IsConst>
CMyStringIterator<IsConst>::CMyStringIterator(CMyStringIterator<IsConst>::pointer_type ptr)
	: m_ptr(ptr)
{}
