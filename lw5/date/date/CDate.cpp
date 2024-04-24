#include "CDate.h"

CDate::CDate(unsigned day, Month month, unsigned year)
{
	SetDateStamp(day, month, year);
}

CDate::CDate(unsigned datestamp) : m_datestamp(datestamp) 
{ 
	Update(); 
}

CDate::operator bool() const
{
	return IsValid();
}

unsigned CDate::GetDay() const
{
	return m_day;
}

Month CDate::GetMonth() const
{
	return m_month;
}

unsigned CDate::GetYear() const
{
	return m_year;
}

WeekDay CDate::GetWeekDay() const
{
	return m_week;
}

uint32_t CDate::GetDateStamp() const
{
	return m_datestamp;
}

bool CDate::IsValid() const
{
	if (m_day < 0 || m_year < 1970 || m_year > 9999)
		return false;

	if (IsLeap(m_year))
	{
		if (m_day > daysLeap[(int)m_month - 1])
		{
			return false;
		}
	}
	else
	{
		if (m_day > days[(int)m_month - 1])
		{
			return false;
		}
	}

	return true;
}

// ++date
CDate& CDate::operator++()
{
	++m_datestamp;
	Update();
	return *this;
}

// --date
CDate& CDate::operator--()
{
	if (m_datestamp == 0)
		return *this;
	--m_datestamp;
	Update();
	return *this;
}

// date++
CDate CDate::operator++(int)
{
	CDate date(m_datestamp);
	m_datestamp++;
	Update();
	return date;
}

// date--
CDate CDate::operator--(int)
{
	if (m_datestamp == 0)
		return *this;
	CDate date(m_datestamp);
	m_datestamp--;
	Update();
	return date;
}

CDate CDate::operator+(int days)
{
	if (days < 0 && m_datestamp < (uint32_t)-days)
		return CDate();

	CDate date(m_datestamp + days);
	return date;
}

CDate CDate::operator-(int days)
{
	if (days > 0 && m_datestamp < (uint32_t)days)
		return CDate();

	CDate date(m_datestamp - days);
	return date;
}

int CDate::operator-(CDate& d)
{
	// + current day
	return (int)m_datestamp - (int)d.GetDateStamp();
}

CDate& CDate::operator+=(int days)
{
	if (days < 0 && m_datestamp < (uint32_t)-days)
	{
		m_datestamp = 0;
		Update();
	}
	else
	{
		m_datestamp += days;
		Update();
	}
	
	return *this;
}

CDate& CDate::operator-=(int days)
{
	if (days > 0 && m_datestamp < (uint32_t)days)
	{
		m_datestamp = 0;
		Update();
	}
	else
	{
		m_datestamp -= days;
		Update();
	}

	return *this;
}

bool CDate::operator==(CDate& d)
{
	if (!IsValid() || !d.IsValid())
		return false;

	return m_datestamp == d.GetDateStamp();
}

bool CDate::operator!=(CDate& d)
{
	if (!IsValid() || !d.IsValid())
		return false;

	return m_datestamp != d.GetDateStamp();
}

bool CDate::operator>(CDate& d)
{
	if (!IsValid() || !d.IsValid())
		return false;

	return m_datestamp > d.GetDateStamp();
}

bool CDate::operator<(CDate& d)
{
	if (!IsValid() || !d.IsValid())
		return false;

	return m_datestamp < d.GetDateStamp();
}

bool CDate::operator>=(CDate& d)
{
	if (!IsValid() || !d.IsValid())
		return false;

	return m_datestamp >= d.GetDateStamp();
}

bool CDate::operator<=(CDate& d)
{
	if (!IsValid() || !d.IsValid())
		return false;

	return m_datestamp <= d.GetDateStamp();
}

bool CDate::SetDateStamp(unsigned day, Month month, unsigned year)
{
	m_day = day;
	m_month = month;
	m_year = year;

	if (!IsValid())
		return false;

	constexpr unsigned leapsCountBeforeUnix = 1970 / 4 - 1970 / 100 + 1970 / 400;

	unsigned leapsCount = year / 4 - year / 100 + year / 400 - leapsCountBeforeUnix;

	m_datestamp = (year - 1970) * 365 + leapsCount;
	
	// if current year is leap, it has already been added in leapsCount: sub him
	m_datestamp -= IsLeap(year) ? 1 : 0;

	for (unsigned i = 0; i < (unsigned)month - 1; i++)
	{
		if (IsLeap(year))
			m_datestamp += daysLeap[i];
		else
			m_datestamp += days[i];
	}

	// without current day
	m_datestamp += day - 1;

	// 01.01.1970 - THURSDAY + 1 (current day) 
	m_week = (WeekDay)((m_datestamp + 4) % 7);

	return true;
}

unsigned CDate::UpdateYearAndGetRem()
{
	m_year = 1970;

	static constexpr unsigned daysIn400Year = 365 * 400 + 97;              // 146 097
	static constexpr unsigned daysIn100Year = 365 * 100 + 24;              // 36 524
	static constexpr unsigned daysIn4Year = 365 * 4 + 1;                   // 1461
	static constexpr unsigned daysInLast400YearBeforeEnd = 365 * 31 + 8;   // 11 323 (01/01/2001)

	unsigned rem = 0;
	unsigned years = 0;

	if (m_datestamp < daysInLast400YearBeforeEnd)
	{
		m_year += 4 * (m_datestamp / daysIn4Year);
		rem = m_datestamp % daysIn4Year;
	}
	else
	{
		m_year += 31;
		rem = m_datestamp - daysInLast400YearBeforeEnd;

		m_year += 400 * (rem / daysIn400Year);
		rem = rem % daysIn400Year;

		years = 100 * (rem / daysIn100Year);
		m_year += years;
		if (years == 400) // 31.12 2400, 2800 ...
		{
			--m_year;
			return 365;
		}
		else
			rem = rem % daysIn100Year;

		m_year += 4 * (rem / daysIn4Year);
		rem = rem % daysIn4Year;
	}

	years = rem / 365;
	m_year += years;
	if (years == 4) // 31.12, year % 4 == 0
	{
		--m_year;
		return 365;
	}
	else
		rem = rem % 365;

	return rem;
}

void CDate::Update()
{
	unsigned rem = UpdateYearAndGetRem();

	unsigned month = 0;
	
	if (IsLeap(m_year))
	{
		while (rem >= daysLeap[month])
		{
			rem -= daysLeap[month];
			month++;
		}
	}
	else
	{
		while (rem >= days[month])
		{
			rem -= days[month];
			month++;
		}
	}

	m_month = (Month)(month + 1);

	// add current day
	m_day = rem + 1;

	// 01.01.1970 - THURSDAY + 1 (current day)
	m_week = (WeekDay)((m_datestamp + 4) % 7);
}

bool CDate::IsLeap(unsigned year) const
{
	return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}
