#include <cassert>
#include <stdexcept>
#include "CStringList.h"

CStringList::~CStringList()
{
	if (m_size != 0)
	{
		while (m_first = m_first->m_next)
			continue;
	}
}

CStringList::CStringList(const CStringList& list)
{
	m_first = std::make_shared<CListItem>(list.m_first->m_string, nullptr, nullptr);
	auto newItem = m_first;
	auto oldItem = list.m_first;
	while (oldItem->m_next)
	{
		// проблема со стеком при исключении
		newItem->m_next = std::make_shared<CListItem>(
			oldItem->m_next->m_string,
			nullptr,
			newItem
		);
		newItem = newItem->m_next;
		oldItem = oldItem->m_next;
	}
	m_last = newItem;
	m_size = list.m_size;
}

CStringList::CStringList(CStringList&& list) noexcept
{
	m_first = std::move(list.m_first);
	m_last = std::move(list.m_last);
	m_size = list.m_size;
	list.m_size = 0;
}

void CStringList::PushFront(const std::string& str)
{
	m_first = std::make_shared<CListItem>(str, m_first, nullptr);
	if (m_size == 0)
	{
		m_last = m_first;
	}
	else if (m_size == 1)
	{
		m_last = m_first->m_next;
	}
	++m_size;
}

void CStringList::PushBack(const std::string& str)
{
	if (m_size == 0)
	{
		PushFront(str);
		return;
	}
	// надо проверять на null
	auto lastItem = m_last.lock();
	lastItem->m_next = std::make_shared<CListItem>(str, nullptr, lastItem);
	m_last = lastItem->m_next;
	++m_size;
}

std::string& CStringList::Front()
{
	if (m_first == nullptr)
	{
		throw std::out_of_range("ERROR! List is empty!");
	}
	return m_first->GetString();
}

const std::string& CStringList::Front() const
{
	if (m_first == nullptr)
	{
		throw std::out_of_range("ERROR! List is empty!");
	}
	return m_first->GetString();
}

std::string& CStringList::Back()
{
	auto lastItem = m_last.lock();
	if (lastItem == nullptr)
	{
		throw std::out_of_range("ERROR! List is empty!");
	}
	return lastItem->GetString();
}

const std::string& CStringList::Back() const
{
	auto lastItem = m_last.lock();
	if (lastItem == nullptr)
	{
		throw std::out_of_range("ERROR! List is empty!");
	}
	return lastItem->GetString();
}

// noexcept
size_t CStringList::Size() const
{
	return m_size;
}

bool CStringList::Empty() const
{
	return m_size == 0;
}

// noexcept
void CStringList::Clear()
{
	if (m_size != 0)
	{
		while (m_first = m_first->m_next)
			continue;
		m_first.reset();
		m_last.reset();
		m_size = 0;
	}
}

void CStringList::Insert(CStringListIterator<false> iter, const std::string& str)
{
	// вставить между
	// не увеличивается размер листа
	*iter = str;
}

void CStringList::Erase(CStringListIterator<false> iter)
{
	// проверить на null
	auto prev = iter.m_ptr->m_prev.lock();
	prev->m_next = iter.m_ptr->m_next;
	--m_size;
}

CStringListIterator<false> CStringList::begin()
{
	return CStringListIterator<false>(m_first);
}

CStringListIterator<false> CStringList::end()
{
	return CStringListIterator<false>();
}

CStringListIterator<true> CStringList::cbegin() const
{
	return CStringListIterator<true>(m_first);
}

CStringListIterator<true> CStringList::cend() const
{
	return CStringListIterator<true>();
}
