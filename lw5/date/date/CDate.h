#pragma once
#include <iostream>
#include <cstdint>
#include <iomanip>

enum class Month
{
    JANUARY = 1, FEBRUARY, MARCH, APRIL,
    MAY, JUNE, JULY, AUGUST, SEPTEMBER,
    OCTOBER, NOVEMBER, DECEMBER
};

enum class WeekDay
{
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
    THURSDAY, FRIDAY, SATURDAY
};

// не возможно создать не валидное состояние

class CDate
{
public:
    CDate(unsigned day, Month month, unsigned year);
    explicit CDate(unsigned datestamp);
    // 01-01-1970
    CDate() = default;
    operator bool() const;
    unsigned GetDay() const;
    Month GetMonth() const;
    unsigned GetYear() const;
    WeekDay GetWeekDay() const;
    uint32_t GetDateStamp() const;
    bool SetDateStamp(unsigned day, Month month, unsigned year);
    bool IsValid() const;
    // prefix inc
    CDate& operator++();
    CDate& operator--();
    // postfix inc
    CDate operator++(int);
    CDate operator--(int);
    // arithmetic
    CDate operator+(int days) const;
    // add int + CDate
    CDate operator-(int days) const;
    int operator-(const CDate& d) const;
    CDate& operator+=(int days);
    CDate& operator-=(int days);
    // compare
    bool operator==(const CDate& d) const;
    bool operator!=(const CDate& d) const;
    bool operator>(const CDate& d) const;
    bool operator<(const CDate& d) const;
    bool operator>=(const CDate& d) const;
    bool operator<=(const CDate& d) const;

private:
    void Update();
    bool IsLeap(unsigned year) const;
    unsigned UpdateYearAndGetRem();
    uint32_t m_datestamp = 0;
    WeekDay m_week = WeekDay::THURSDAY;
    unsigned m_day = 1;
    Month m_month = Month::JANUARY;
    unsigned m_year = 1970;
};

static std::ostream& operator<<(std::ostream& os, const CDate& date)
{
    if (!date.IsValid())
    {
        os << "INVALID";
        return os;
    }

    os
        << std::setfill('0') << std::setw(2) << date.GetDay()
        << '.'
        << std::setfill('0') << std::setw(2) << (int)date.GetMonth()
        << '.'
        << std::setfill('0') << std::setw(4) << date.GetYear();

    return os;
}

static std::istream& operator>>(std::istream& in, CDate& date)
{
    unsigned day{};
    unsigned month{};
    unsigned year{};
    char ch{};

    if (
        in >> day &&
        in >> ch && ch == '.' &&
        in >> month && (month >= 1 && month <= 12) &&
        in >> ch && ch == '.' &&
        in >> year &&
        date.SetDateStamp(day, (Month)month, year)
        )
    {
        return in;
    }

    in.setstate(std::ios_base::failbit);
    return in;
}
