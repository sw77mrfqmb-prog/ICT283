#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED
#include <iostream>
#include <string>
/** @brief Time.h
* @author Delvin
     */
class Time
{
public:
    /** @brief default constructor for time
     */
    Time();
    /** @brief getter for hour
     * @return hour in int type
     */
    int GetHour() const;
    /** @brief getter for minute
     * @return minute in int type
     */
    int GetMin() const;
    /** @brief setter for hour, replaces m_hour with parameter hour
     * @param hour
     */
    void SetHour(int hour);
    /** @brief setter for minutes, replaces m_minute with parameter minute
     * @param minute
     */
    void SetMin(int minute);


private:
    int m_hour;
    int m_min;

};

std::ostream & operator <<( std::ostream & output, const Time & time );

std::istream & operator >>( std::istream & input, Time & time  );

#endif // TIME_H_INCLUDED
