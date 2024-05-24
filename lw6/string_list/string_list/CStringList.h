#pragma once
#include <memory>
#include <string>
#include "CListItem.h"
 
/*
Использовать при пустом листе пустой Item с ссылками 
prev - next и next - prev
сам на себя.

Этот Item всегда остается последним в листе 
*/

class CStringList
{
public:
	// копировать конструктор и присваивание
	CStringList() = default;
	~CStringList();
	CStringList(const CStringList& list);
	CStringList(CStringList&& list) noexcept;

	void PushFront(const std::string& str);
	void PushBack(const std::string& str);
	std::string& Front();
	const std::string& Front() const;
	std::string& Back();
	const std::string& Back() const;

	size_t Size() const;
	bool Empty() const;
	void Clear();
	void Insert(CStringListIterator<false> iter, const std::string& str);
	void Erase(CStringListIterator<false> iter);

	CStringListIterator<false> begin();
	CStringListIterator<false> end();
	CStringListIterator<true> cbegin() const;
	CStringListIterator<true> cend() const;

private:
	// decr end
	std::shared_ptr<CListItem> m_first;
	std::weak_ptr<CListItem> m_last;
	size_t m_size = 0;
};