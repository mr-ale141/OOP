#pragma once
#include <memory>

class CListItem
{
public:
	CListItem(const std::string& str);
	void Erase();
private:
	std::unique_ptr<CListItem> m_next;
	std::unique_ptr<CListItem> m_prev;
	std::string m_string;
};