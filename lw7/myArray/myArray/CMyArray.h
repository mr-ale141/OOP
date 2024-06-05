#pragma once
#include <stdexcept>
#include <memory>
#include "CMyArrayIterator.h"
#include "CMyArrayReverseIterator.h"

template<typename T>
class CMyArray
{
public:
	CMyArray() = default;
	~CMyArray();

	explicit CMyArray(size_t size);
	
	CMyArray(const CMyArray<T>& other);
	CMyArray& operator=(const CMyArray<T>& other);

	CMyArray(CMyArray<T>&& other) noexcept;
	CMyArray& operator=(CMyArray<T>&& other) noexcept;

	size_t Size() const;
	void Clear();

	T& operator[](size_t pos);
	const T& operator[](size_t pos) const;

	void Resize(size_t size);

	void PushBack(const T& newItem);
	void PushBack(const T&& newItem);

	CMyArrayIterator<T, false> begin() { return CMyArrayIterator<T, false>(m_data); }
	CMyArrayIterator<T, true> begin() const { return CMyArrayIterator<T, true>(m_data); }
	CMyArrayIterator<T, true> cbegin() const { return CMyArrayIterator<T, true>(m_data); }

	CMyArrayIterator<T, false> end() { return CMyArrayIterator<T, false>(m_data + m_size); }
	CMyArrayIterator<T, true> end() const { return CMyArrayIterator<T, true>(m_data + m_size); }
	CMyArrayIterator<T, true> cend() const { return CMyArrayIterator<T, true>(m_data + m_size); }

	CMyArrayReverseIterator<T, false> rbegin() { return CMyArrayReverseIterator<T, false>(m_data + m_size - 1); }
	CMyArrayReverseIterator<T, true> rbegin() const { return CMyArrayReverseIterator<T, true>(m_data + m_size - 1); }
	CMyArrayReverseIterator<T, true> crbegin() const { return CMyArrayReverseIterator<T, true>(m_data + m_size - 1); }

	CMyArrayReverseIterator<T, false> rend() { return CMyArrayReverseIterator<T, false>(m_data - 1); }
	CMyArrayReverseIterator<T, true> rend() const { return CMyArrayReverseIterator<T, true>(m_data - 1); }
	CMyArrayReverseIterator<T, true> crend() const { return CMyArrayReverseIterator<T, true>(m_data - 1); }

private:
	static T* Allocate(size_t n);
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
void CMyArray<T>::Deallocate(T* buf) noexcept {
	operator delete(buf);
}

template<typename T>
void CMyArray<T>::DestroyN(T* buf, size_t n) noexcept {
	for (size_t i = 0; i != n; ++i) {
		Destroy(buf + i);
	}
}

template<typename T>
void CMyArray<T>::Destroy(T* buf) noexcept {
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

		for (; i != m_capacity; ++i)
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
CMyArray<T>& CMyArray<T>::operator=(const CMyArray<T>& other)
{
	if (m_data == other.m_data)
		return *this;

	CMyArray<T> arr(other);

	DestroyN(m_data, m_capacity);
	Deallocate(m_data);

	m_data = std::move(arr.m_data);
	m_size = arr.m_size;
	m_capacity = arr.m_capacity;

	arr.m_data = nullptr;
	arr.m_size = 0;
	arr.m_capacity = 0;

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

	m_data = nullptr;
	std::swap(m_data, other.m_data);
	
	m_capacity = 0;
	std::swap(m_capacity, other.m_capacity);

	m_size = 0;
	std::swap(m_size, other.m_size);

	return *this;
}

template<typename T>
size_t CMyArray<T>::Size() const
{
	return m_size;
}

template<typename T>
void CMyArray<T>::Clear()
{
	if (m_capacity == 0)
		return;

	DestroyN(m_data, m_capacity);
	Deallocate(m_data);
	m_data = nullptr;
	m_capacity = 0;
	m_size = 0;
}

template<typename T>
T& CMyArray<T>::operator[](size_t pos)
{
	if (pos < 0 || pos >= m_size)
		throw std::out_of_range("ERROR! Access outside the array");

	return *(m_data + pos);
}

template<typename T>
const T& CMyArray<T>::operator[](size_t pos) const
{
	if (pos < 0 || pos >= m_size)
		throw std::out_of_range("ERROR! Access outside the array");

	return *(m_data + pos);
}

template<typename T>
void CMyArray<T>::Resize(size_t size)
{
	if (size < 0)
		throw std::invalid_argument("ERROR! Size cannot be less than zero.");

	if (size == m_size)
		return;

	if (size > m_size && size <= m_capacity)
	{
		m_size = size;
		return;
	}

	if (size < m_size)
	{
		DestroyN(m_data + size, m_size - size);
		std::uninitialized_default_construct_n(m_data + size, m_size - size);
		m_size = size;
		return;
	}
	
	size_t i = m_size;
	T* newData = nullptr;
	try
	{
		newData = Allocate(size);
		for (; i != size; ++i)
			new (newData + i) T();
	}
	catch (...)
	{
		DestroyN(newData + m_size, i - m_size);
		Deallocate(newData);
		throw;
	}

	// перемещаю элементы
	std::uninitialized_move_n(m_data, m_size, newData);

	// удаляю хвосты
	DestroyN(m_data + m_size, m_capacity - m_size);

	Deallocate(m_data);
	m_data = newData;
	m_capacity = size;
	m_size = size;
}

template<typename T>
void CMyArray<T>::PushBack(const T& newItem)
{
	T item(newItem);
	PushBack(std::move(newItem));
}

template<typename T>
void CMyArray<T>::PushBack(const T&& newItem)
{
	if (m_capacity - m_size >= 1)
	{
		std::uninitialized_move_n(&newItem, 1, m_data + m_size);
		++m_size;
		return;
	}

	size_t newCapacity = m_capacity == 0 ? 1 : m_capacity * 2;
	size_t posStartDefaultItems = m_size + 1;
	size_t i = posStartDefaultItems;
	T* newData = nullptr;
	try
	{
		newData = Allocate(newCapacity);
		for (; i != newCapacity; ++i)
			new (newData + i) T();
	}
	catch (...)
	{
		DestroyN(newData + posStartDefaultItems, i - posStartDefaultItems);
		Deallocate(newData);
		throw;
	}

	// записываем новый элемент
	std::uninitialized_move_n(&newItem, 1, newData + m_size);

	// перемещаем старые элементы
	std::uninitialized_move_n(m_data, m_size, newData);

	// разрушаем хвост
	DestroyN(m_data + m_size, m_capacity - m_size);

	Deallocate(m_data);
	m_data = newData;
	m_capacity = newCapacity;
	++m_size;
}
