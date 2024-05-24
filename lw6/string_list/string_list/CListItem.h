#pragma once
#include <memory>
#include <string>
#include <compare>
#include "CStringListIterator.h"

class CListItem
{
public:
	friend class CStringListIterator<true>;
	friend class CStringListIterator<false>;
	friend class CStringList;

	CListItem(
		const std::string& str, 
		const std::shared_ptr<CListItem> next, 
		const std::shared_ptr<CListItem> prev
	);
	CListItem(const CListItem& item) = delete;
	CListItem(CListItem&& item) noexcept;
	CListItem(const std::string& str);

	CListItem& operator=(CListItem&& item) noexcept;
	auto operator<=>(const CListItem& item) const
	{
		return m_string <=> item.m_string;
	}

	void Erase();
	std::string& GetString();

private:
	std::string m_string;
	std::shared_ptr<CListItem> m_next;
	std::weak_ptr<CListItem> m_prev;
};
