#include "Date.h"

const std::string MonthArr[] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

Date::Date()
{
    m_day = 1;
    m_month = 3;
    m_year = 2002;
}

Date::Date(int day, int month, int year)
{
    m_day = day;
    m_month = month;
    m_year = year;
}

int Date::GetDay() const
{
    return m_day;
}

int Date::GetMonth() const
{
    return m_month;
}

int Date::GetYear() const
{
    return m_year;
}

void Date::SetDay(int day)
{
    m_day = day;
}

void Date::SetMonth(int month)
{
    m_month = month;
}

void Date::SetYear(int year)
{
    m_year = year;
}

bool Date::operator<(const Date& newValue) const
{
    if(m_year != newValue.m_year)
        return  m_year < newValue.m_year;
    if(m_month !=  newValue.m_month)
        return m_month < newValue.m_month;
    return m_day <newValue.m_day;

}

bool Date::operator>(const Date& newValue) const
{
    if(m_year != newValue.m_year)
        return  m_year > newValue.m_year;
    if(m_month !=  newValue.m_month)
        return m_month > newValue.m_month;
    return m_day > newValue.m_day;
}

bool Date::operator==(const Date& newValue) const
{
    return m_year == newValue.m_year && m_month == newValue.m_month && m_day == newValue.m_day;
}


std::ostream & operator <<( std::ostream & output, const Date & date)
{

    output << "Date: " << date.GetDay()
           << " " << MonthArr[date.GetMonth() - 1]
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
    date.SetMonth(std::stoi(tempMonth));

    input >> tempYear;
    date.SetYear(std::stoi(tempYear));
    input >> std::ws;

    return input;
}

