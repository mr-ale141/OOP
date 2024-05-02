#include "CMyStringIterator.h"
#include <iterator>

bool CMyStringIterator<char>::operator==(const CMyStringIterator<char>& iter) const
{
	return m_ptr == iter.m_ptr;
}

bool CMyStringIterator<char>::operator!=(const CMyStringIterator<char>& iter) const
{
	return m_ptr != iter.m_ptr;
}

bool CMyStringIterator<char>::operator<(const CMyStringIterator<char>& iter) const
{
	return m_ptr < iter.m_ptr;
}

bool CMyStringIterator<char>::operator>(const CMyStringIterator<char>& iter) const
{
	return m_ptr > iter.m_ptr;
}
/*
template<typename T>
CMyStringIterator<T>::CMyStringIterator(const CMyStringIterator<T>& iter)
{
	m_ptr = iter.m_ptr;
}
*/

char& CMyStringIterator<char>::operator*()
{
	return *m_ptr;
}

CMyStringIterator<char>& CMyStringIterator<char>::operator++()
{
	++m_ptr;
	return *this;
}

CMyStringIterator<char> CMyStringIterator<char>::operator++(int)
{
	CMyStringIterator<char> old(m_ptr);
	++m_ptr;
	return old;
}

CMyStringIterator<char>& CMyStringIterator<char>::operator--()
{
	--m_ptr;
	return *this;
}

CMyStringIterator<char> CMyStringIterator<char>::operator--(int)
{
	CMyStringIterator<char> old(m_ptr);
	--m_ptr;
	return old;
}

size_t CMyStringIterator<char>::operator-(const CMyStringIterator<char>& iter) const
{
	return m_ptr - iter.m_ptr;
}

CMyStringIterator<char> CMyStringIterator<char>::operator+(int i)
{
	CMyStringIterator<char> newIter(m_ptr += i);
	return newIter;
}

template<typename T>
CMyStringIterator<T>& CMyStringIterator<T>::operator+=(int i)
{
	m_ptr += i;
	return *this;
}

CMyStringIterator<char>& CMyStringIterator<char>::operator-=(int i)
{
	m_ptr -= i;
	return *this;
}

template<typename T>
CMyStringIterator<T>::CMyStringIterator(T* ptr)
	: m_ptr(ptr)
{}
