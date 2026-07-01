#include "DataLog.h"


DataLog::DataLog()
{
    m_speed = 0.0f;
    m_temperature = 0.0f;
    m_solarradiation = 0.0f;
}

float DataLog::GetSpeed() const
{
    return m_speed;
}
float DataLog::GetTemperature() const
{
    return m_temperature;
}
float DataLog::GetSolarRadiation() const
{
    return m_solarradiation;
}

void DataLog::SetSpeed(float speed)
{
    m_speed = speed*3.6;
}
void DataLog::SetTemperature(float temperature)
{
    m_temperature = temperature;
}
void DataLog::SetSolarRadiation(float solarradiation)
{
    m_solarradiation = solarradiation*(10.0f / 60.0f) / 1000.0f;
}
