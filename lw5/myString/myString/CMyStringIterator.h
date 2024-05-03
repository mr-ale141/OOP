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

template<typename T>
class CMyStringIterator
{
public:
    friend class CMyString;

    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;

    T& operator*() const;

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
    CMyStringIterator<T> operator+(__int64 i);
    CMyStringIterator<T> operator-(__int64 i);
    CMyStringIterator<T>& operator+=(__int64 i);
    CMyStringIterator<T>& operator-=(__int64 i);
    ~CMyStringIterator() = default;
protected:
    CMyStringIterator() = default;
private:
    CMyStringIterator(T* ptr);
    T* m_ptr = nullptr;
};

template<typename T>
bool CMyStringIterator<T>::operator==(const CMyStringIterator<T>& iter) const
{
    return m_ptr == iter.m_ptr;
}

template<typename T>
static CMyStringIterator<T> operator+(__int64 i, const CMyStringIterator<T>& iter)
{
    return iter + i;
}

template<typename T>
bool CMyStringIterator<T>::operator!=(const CMyStringIterator<T>& iter) const
{
	return m_ptr != iter.m_ptr;
}

template<typename T>
bool CMyStringIterator<T>::operator<(const CMyStringIterator<T>& iter) const
{
	return m_ptr < iter.m_ptr;
}

template<typename T>
bool CMyStringIterator<T>::operator>(const CMyStringIterator<T>& iter) const
{
	return m_ptr > iter.m_ptr;
}

template<typename T>
T& CMyStringIterator<T>::operator*() const
{
	return *m_ptr;
}

template<typename T>
CMyStringIterator<T>& CMyStringIterator<T>::operator++()
{
	++m_ptr;
	return *this;
}

template<typename T>
CMyStringIterator<T> CMyStringIterator<T>::operator++(int)
{
	CMyStringIterator<char> old(m_ptr);
	++m_ptr;
	return old;
}

template<typename T>
CMyStringIterator<T>& CMyStringIterator<T>::operator--()
{
	--m_ptr;
	return *this;
}

template<typename T>
CMyStringIterator<T> CMyStringIterator<T>::operator--(int)
{
	CMyStringIterator<char> old(m_ptr);
	--m_ptr;
	return old;
}

template<typename T>
__int64 CMyStringIterator<T>::operator-(const CMyStringIterator<T>& iter) const
{
	return m_ptr - iter.m_ptr;
}

template<typename T>
CMyStringIterator<T> CMyStringIterator<T>::operator+(__int64 i)
{
	return CMyStringIterator<char>(m_ptr += i);
}

template<typename T>
CMyStringIterator<T> CMyStringIterator<T>::operator-(__int64 i)
{
	return CMyStringIterator<char>(m_ptr -= i);
}

template<typename T>
CMyStringIterator<T>& CMyStringIterator<T>::operator+=(__int64 i)
{
	m_ptr += i;
	return *this;
}

template<typename T>
CMyStringIterator<T>& CMyStringIterator<T>::operator-=(__int64 i)
{
	m_ptr -= i;
	return *this;
}

template<typename T>
CMyStringIterator<T>::CMyStringIterator(T* ptr)
	: m_ptr(ptr)
{}
