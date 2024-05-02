#include "CMyStringConstIterator.h"
#include <iterator>

/*
template<typename T>
CMyStringConstIterator<T>::CMyStringConstIterator(const CMyStringConstIterator<T>& iter)
{
	m_ptr = iter.m_ptr;
}
*/

bool CMyStringConstIterator<char>::operator==(const CMyStringConstIterator<char>& iter) const
{
	return m_ptr == iter.m_ptr;
}

bool CMyStringConstIterator<char>::operator!=(const CMyStringConstIterator<char>& iter) const
{
	return m_ptr != iter.m_ptr;
}

bool CMyStringConstIterator<char>::operator<(const CMyStringConstIterator<char>& iter) const
{
	return m_ptr < iter.m_ptr;
}

bool CMyStringConstIterator<char>::operator>(const CMyStringConstIterator<char>& iter) const
{
	return m_ptr > iter.m_ptr;
}

const char& CMyStringConstIterator<char>::operator*() const
{
	return *m_ptr;
}

CMyStringConstIterator<char>& CMyStringConstIterator<char>::operator++()
{
	++m_ptr;
	return *this;
}

CMyStringConstIterator<char>& CMyStringConstIterator<char>::operator--()
{
	--m_ptr;
	return *this;
}

CMyStringConstIterator<char> CMyStringConstIterator<char>::operator--(int)
{
	CMyStringConstIterator<char> old(m_ptr);
	--m_ptr;
	return old;
}

CMyStringConstIterator<char> CMyStringConstIterator<char>::operator++(int)
{
	CMyStringConstIterator<char> old(m_ptr);
	++m_ptr;
	return old;
}

size_t CMyStringConstIterator<char>::operator-(const CMyStringConstIterator& iter)
{
	return m_ptr - iter.m_ptr;
}

CMyStringConstIterator<char> CMyStringConstIterator<char>::operator+(int i)
{
	CMyStringConstIterator<char> newIter(m_ptr += i);
	return newIter;
}

template<typename T>
CMyStringConstIterator<T>& CMyStringConstIterator<T>::operator+=(int i)
{
	m_ptr += i;
	return *this;
}

CMyStringConstIterator<char>& CMyStringConstIterator<char>::operator-=(int i)
{
	m_ptr -= i;
	return *this;
}

template<typename T>
CMyStringConstIterator<T>::CMyStringConstIterator(const T* ptr)
	: m_ptr(ptr)
{}