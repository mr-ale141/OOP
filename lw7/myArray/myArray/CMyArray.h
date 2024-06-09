#pragma once
#include <stdexcept>
#include <memory>
#include <type_traits>
#include "CMyArrayIterator.h"

template<typename T>
class CMyArray
{
public:
	CMyArray() = default;
	~CMyArray();

	explicit CMyArray(size_t size);

	void Assign(const CMyArrayIterator<T, true> begin, const CMyArrayIterator<T, true> end);
	
	CMyArray(const CMyArray<T>& other);
	CMyArray& operator=(const CMyArray<T>& other);

	CMyArray(CMyArray<T>&& other) noexcept;
	CMyArray& operator=(CMyArray<T>&& other) noexcept;

	size_t Size() const noexcept;
	void Clear() noexcept;

	T& operator[](size_t pos);
	const T& operator[](size_t pos) const;

	void Resize(size_t size);

	void PushBack(const T& newItem);
	void PushBack(T&& newItem);

	CMyArrayIterator<T, false> begin() { return CMyArrayIterator<T, false>(m_data); }
	const CMyArrayIterator<T, false> begin() const { return begin(); }
	CMyArrayIterator<T, true> cbegin() const { return CMyArrayIterator<T, true>(m_data); }

	CMyArrayIterator<T, false> end() { return CMyArrayIterator<T, false>(m_data + m_size); }
	const CMyArrayIterator<T, false> end() const { return end(); }
	CMyArrayIterator<T, true> cend() const { return CMyArrayIterator<T, true>(m_data + m_size); }
	
	auto rbegin() { return std::make_reverse_iterator(end()); }
	const auto rbegin() const { return rbegin(); }
	auto crbegin() const { return std::make_reverse_iterator(cend()); }

	auto rend() { return std::make_reverse_iterator(begin()); }
	const auto rend() const { return rend(); }
	auto crend() const { return std::make_reverse_iterator(cbegin()); }

private:
	static T* Allocate(size_t n);
	static T* Reallocate(T* oldData, size_t oldSize, size_t newCapacity);
	static void Deallocate(T* buf) noexcept;
	static void DestroyN(T* buf, size_t n) noexcept;
	static void Destroy(T* buf) noexcept;

	T* m_data = nullptr;
	size_t m_capacity = 0;
	size_t m_size = 0;
};

template<typename T>
T* CMyArray<T>::Allocate(size_t n)
{
	return n != 0
		? static_cast<T*>(operator new(n * sizeof(T)))
		: nullptr;
}

template<typename T>
T* CMyArray<T>::Reallocate(T* oldData, size_t oldSize, size_t newCapacity)
{
	T* newData = nullptr;
	size_t i = 0;
	try
	{
		newData = Allocate(newCapacity);
		for (; i != oldSize; ++i)
			new (newData + i) T(oldData[i]);
	}
	catch (...)
	{
		DestroyN(newData, i);
		Deallocate(newData);
		throw;
	}

	DestroyN(oldData, oldSize);
	Deallocate(oldData);

	oldData = nullptr;
	
	return newData;
}

template<typename T>
void CMyArray<T>::Deallocate(T* buf) noexcept
{
	operator delete(buf);
}

template<typename T>
void CMyArray<T>::DestroyN(T* buf, size_t n) noexcept
{
	for (size_t i = 0; i != n; ++i)
	{
		Destroy(buf + i);
	}
}

template<typename T>
void CMyArray<T>::Destroy(T* buf) noexcept
{
	buf->~T();
}

template<typename T>
CMyArray<T>::CMyArray(size_t size)
	: m_data(Allocate(size)),
	m_capacity(size),
	m_size(size)
{
	size_t i = 0;
	try 
	{
		for (; i != size; ++i)
		{
			new (m_data + i) T();
		}
	}
	catch (...)
	{
		DestroyN(m_data, i);
		Deallocate(m_data);
		throw;
	}
}

template<typename T>
CMyArray<T>::~CMyArray()
{
	DestroyN(m_data, m_size);
	Deallocate(m_data);
}

template<typename T>
void CMyArray<T>::Assign(const CMyArrayIterator<T, true> otherBegin, const CMyArrayIterator<T, true> otherEnd)
{
	auto iterThis = begin();
	auto iterOther = otherBegin;
	while (iterThis != end() && iterOther != otherEnd)
	{
		*iterThis = *iterOther;
		++iterThis;
		++iterOther;
	}

	// в текущем объекте не хватило места
	if (iterThis == end() && iterOther != otherEnd)
	{
		size_t newCapacity = otherEnd - otherBegin;
		T* newData = Reallocate(m_data, m_size, newCapacity);
		m_capacity = newCapacity;
		
		std::uninitialized_copy_n(iterOther, otherEnd - iterOther, newData);
		m_data = newData;
		m_size = newCapacity;
	}

	// в текущем объекте остались лишние элементы
	if (iterThis != end() && iterOther == otherEnd)
	{
		size_t newSize = otherEnd - otherBegin;
		DestroyN(m_data + m_size, newSize - m_size);
		m_size = newSize;
	}
}

template<typename T>
CMyArray<T>::CMyArray(const CMyArray<T>& other)
	: m_data(Allocate(other.m_capacity)),
	m_capacity(other.m_capacity),
	m_size(other.m_size)
{
	size_t i = 0;
	try
	{
		for (; i != m_size; ++i)
		{
			new (m_data + i) T(other[i]);
		}
	}
	catch (...)
	{
		DestroyN(m_data, i);
		Deallocate(m_data);
		throw;
	}
}

template<typename T>
CMyArray<T>& CMyArray<T>::operator=(const CMyArray<T>& other)
{
	if (m_data == other.m_data)
		return *this;

	Assign(other.cbegin(), other.cend());

	return *this;
}

template<typename T>
CMyArray<T>::CMyArray(CMyArray<T>&& other) noexcept
	: m_data(std::move(other.m_data)),
	m_capacity(other.m_capacity),
	m_size(other.m_size)
{
	other.m_data = nullptr;
	other.m_size = 0;
	other.m_capacity = 0;
}

template<typename T>
CMyArray<T>& CMyArray<T>::operator=(CMyArray<T>&& other) noexcept
{
	if (m_data == other.m_data)
		return *this;

	DestroyN(m_data, m_size);
	Deallocate(m_data);
	
	m_data = std::exchange(other.m_data, nullptr);
	m_size = std::exchange(other.m_size, 0);
	m_capacity = std::exchange(other.m_capacity, 0);

	return *this;
}

template<typename T>
size_t CMyArray<T>::Size() const noexcept
{
	return m_size;
}

template<typename T>
void CMyArray<T>::Clear() noexcept
{
	if (m_size == 0)
		return;

	DestroyN(m_data, m_size);
	m_size = 0;
}

template<typename T>
T& CMyArray<T>::operator[](size_t pos)
{
	if (pos >= m_size)
		throw std::out_of_range("ERROR! Access outside the array");

	return *(m_data + pos);
}

template<typename T>
const T& CMyArray<T>::operator[](size_t pos) const
{
	if (pos >= m_size)
		throw std::out_of_range("ERROR! Access outside the array");

	return *(m_data + pos);
}

template<typename T>
void CMyArray<T>::Resize(size_t newSize)
{
	if (newSize == m_size)
		return;

	if (newSize < m_size)
	{
		DestroyN(m_data + newSize, m_size - newSize);
		m_size = newSize;
		return;
	}

	// если не хватает места увеличиваем размер контейнера
	if (newSize > m_capacity)
	{
		m_data = Reallocate(m_data, m_size, newSize);
		m_capacity = newSize;
	}

	// заполняем элементами по умолчанию
	size_t i = m_size;
	try
	{
		for (; i != newSize; ++i)
			new (m_data + i) T();
	}
	catch (...)
	{
		DestroyN(m_data + m_size, i - m_size);
		throw;
	}

	m_size = newSize;
}

template<typename T>
void CMyArray<T>::PushBack(const T& newItem)
{
	PushBack(std::move(T(newItem)));
}

template<typename T>
void CMyArray<T>::PushBack(T&& newItem)
{
	if (m_capacity == m_size)
	{
		size_t newCapacity = m_capacity == 0 ? 1 : m_capacity * 2;
		m_data = Reallocate(m_data, m_size, newCapacity);
		m_capacity = newCapacity;
	}

	if constexpr (std::is_nothrow_move_assignable_v<T>)
	{
		std::uninitialized_move_n(&newItem, 1, m_data + m_size);
	}
	else
	{
		std::uninitialized_copy_n(&newItem, 1, m_data + m_size);
		Destroy(&newItem);
	}
	
	++m_size;
}
