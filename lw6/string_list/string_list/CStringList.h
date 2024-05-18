#pragma once
#include <memory>
#include <string>
#include "CListItem.h"
#include "CStringListIterator.h"

class CStringList
{
public:
	CStringList();
	CStringList(const CStringList& list);
	CStringList(const CStringList&& list);
	CStringListIterator<false> begin();
	CStringListIterator<false> end();
	CStringListIterator<true> cbegin();
	CStringListIterator<true> cend();

private:
	std::unique_ptr<CListItem> m_first = nullptr;
	std::unique_ptr<CListItem> m_last = nullptr;
	size_t m_size = 0;
};