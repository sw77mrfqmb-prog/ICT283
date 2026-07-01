#include "Date.h"

Date::Date()
{
    m_day = 1;
    m_month = "New";
    m_year = 2002;
}

int Date::GetDay() const
{
    return m_day;
}

void Date::GetMonth(std::string& month) const
{
    month = m_month;
}

int Date::GetYear() const
{
    return m_year;
}

void Date::SetDay(int day)
{
    m_day = day;
}

void Date::SetMonth(const std::string& month)
{
    m_month = month;
}

void Date::SetYear(int year)
{
    m_year = year;
}

std::ostream & operator <<( std::ostream & output, const Date & date)
{
    std::string tempMonth;
    date.GetMonth(tempMonth);
    output << "Date: " << date.GetDay()
           << " " << tempMonth
           << " " << date.GetYear();
    return output;
}

std::istream & operator >>( std::istream & input, Date & date )
{
    std::string tempDay;
    std::string tempMonth;
    std::string tempYear;

    std::getline(input,tempDay,'/');
    date.SetDay(std::stoi(tempDay));

    std::getline(input,tempMonth,'/');
    int monthIndex = std::stoi(tempMonth);

    std::string monthArr[]
    {
        "January", "February", "March", "April", "May", "June", "July",
        "August", "September", "October", "November", "December"

    };

    tempMonth = monthArr[monthIndex-1];
    date.SetMonth(tempMonth);

    input >> tempYear;
    date.SetYear(std::stoi(tempYear));
    input >> std::ws;

    return input;
}

