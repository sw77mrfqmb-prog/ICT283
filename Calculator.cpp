#include "Calculator.h"
#include <cmath>
#include <iostream>

Calculator::Calculator()
{
    m_sum =0 ;
    m_mean = 0;
    m_sd = 0;
    m_size = 0;
}

void Calculator::calculateMean(int size)
{
    m_mean = m_sum/size;

}

void Calculator::calculateSD(int size, const float* array)
{
    double tempSum = 0;
    double mean = GetMean();
    for(int i = 0; i < size; i++){
        tempSum += (array[i] - mean) * (array[i] - mean);
    }
    tempSum = tempSum/(size -1);

    m_sd = std::sqrt(tempSum);
}

double Calculator::GetSum()
{
    return m_sum;
}

double Calculator::GetMean()
{
    return m_mean;
}

double Calculator::GetSD()
{
    return m_sd;
}

int Calculator::GetSize()
{
    return m_size;
}
void Calculator::SetSize(int size)
{
    m_size = size;
}

void Calculator::SetSum(int size,const float* dataArray)
{
    double tempSum = 0;
    for(int i = 0; i < size; i++){
        tempSum += dataArray[i];
    }
    m_sum = tempSum;
}
std::ifstream & operator >>(std::ifstream & input, Calculator & Calc)
{
  int size = 0;

  input >> size;

  Calc.SetSize(size);

  Calc.dataArray = new float[size];

    for(int i = 0; i < size; i ++){
        input >> Calc.dataArray[i];
    }
    return input;
}
