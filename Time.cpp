#include "Time.h"

Time::Time()
{
    m_hour = 5;
    m_min = 5;
}

int Time::GetHour() const
{
    return m_hour;
}
int Time::GetMin() const
{
    return m_min;
}

void Time::SetHour(int hour)
{
    m_hour = hour;
}
void Time::SetMin(int minute)
{
    m_min = minute;
}

std::ostream & operator <<( std::ostream & output, const Time & time)
{
    output << time.GetHour() << ":" << time.GetMin();

    return output;
}

std::istream & operator >>( std::istream & input, Time & time )
{
    std::string temphour;
    std::string tempminute;

    std::getline(input,temphour,':');
    time.SetHour(stoi(temphour));

    std::getline(input,tempminute);
    time.SetMin(stoi(tempminute));

    return input;

}
