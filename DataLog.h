#ifndef DATALOG_H_INCLUDED
#define DATALOG_H_INCLUDED

/** @brief DataLog.h
* @author Delvin
     */
class DataLog
{
public:
    /** @brief default constructor
     */

    DataLog();
    /** @brief getter for speed
     * @return m_speed
     */

    float GetSpeed() const;
    /** @brief getter for temperature
     * @return m_temperature
     */
    float GetTemperature() const;
    /** @brief getter for solar radiation
     * @return m_solarradiation
     */
    float GetSolarRadiation() const;
    /** @brief setter for speed
     * @param speed
     */

    void SetSpeed(float speed);
    /** @brief setter for temperature
     * @param temperature
     */
    void SetTemperature(float temperature);
    /** @brief setter for solar radiation
     * @param solarradiation
     */
    void SetSolarRadiation(float solarradiation);
private:
    float m_speed;
    float m_temperature;
    float m_solarradiation;

};

#endif // DATALOG_H_INCLUDED
