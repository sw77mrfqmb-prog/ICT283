#include "Calculator.h"
#include <cmath>
#include <iostream>
#include "Vector.h"

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

void Calculator::calculateSD(int size, const Vector<float>& dataVector)
{
    float tempSum = 0;
    float mean = GetMean();
    for(int i = 0; i < size; i++){
        tempSum += (dataVector[i] - mean) * (dataVector[i] - mean);
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

void Calculator::SetSum(int size,const Vector<float>& dataVector)
{
    float tempSum = 0;
    for(int i = 0; i < size; i++){
        tempSum += dataVector[i];
    }
    m_sum = tempSum;
}
std::ifstream & operator >>(std::ifstream & input, Calculator & Calc)
{
  int size = 0;

  input >> size;

  Calc.SetSize(size);

  float value = 0;

    for(int i = 0; i < size; i ++){
        input >> value;
        Calc.dataVector.Insert(i,value);
    }
    return input;
}
