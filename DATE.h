#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED
#include <iostream>
#include <string>

/** @brief DATE.h
* @author Delvin
     */
class Date
{
public:
    /** @brief default Unit class
     */
    Date();
    /** @brief getter to return Date's day
     * @return day int
     */
    int GetDay() const;
    /** @brief getter to retrieve stored month into parameter
     * @param month
     */
    void GetMonth(std::string& month) const;
    /** @brief getter to return Date's year
     * @return year int
     */
    int GetYear() const;
    /** @brief to update the day by taking it from the parameter
     *  @param  day
     */
    void SetDay(int day);
    /** @brief to update the month by taking it from the parameter
     *  @param  month
     */
    void SetMonth(const std::string& month) ;
    /** @brief to update the year by taking it from the parameter
     *  @param  year
     */
    void SetYear(int year) ;

private:

    int m_day;
    std::string m_month;
    int m_year;
};
/** \brief to read from the output file
* \param  output is output file
* \param Date object just to for display
*/
std::ostream & operator <<( std::ostream & output, const Date & date);

/** \brief to read from the input file
* \param  input is input file
* \param Date object just to for display
*/
std::istream & operator >>( std::istream & input, Date & date );

#endif // DATE_H_INCLUDED
