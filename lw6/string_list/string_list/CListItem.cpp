#include <cassert>
#include "CListItem.h"

CListItem::CListItem(
	const std::string& str,
	std::shared_ptr<CListItem> next,
	std::shared_ptr<CListItem> prev
)
	:
	m_string(str),
	m_next(next),
	m_prev(prev)
{}

CListItem::CListItem(CListItem&& item) noexcept
	:
	m_string(std::move(item.m_string)),
	m_next(std::move(item.m_next)),
	m_prev(std::move(item.m_prev))
{}

void CListItem::Erase()
{
	auto prev = m_prev.lock();
	prev->m_next = m_next;
}

std::string& CListItem::GetString()
{
	return m_string;
}

CListItem::CListItem(const std::string& str)
	: m_string(str)
{}

CListItem& CListItem::operator=(CListItem&& item) noexcept
{
	m_string = std::move(item.m_string);
	m_next = std::move(item.m_next);
	m_prev = std::move(item.m_prev.lock());
	return *this;
}
