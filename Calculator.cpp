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

void Calculator::calculateSD(int size, const Vector<double>& dataVector)
{
    double tempSum = 0;
    double mean = GetMean();
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

void Calculator::SetSum(int size,const Vector<double>& dataVector)
{
    double tempSum = 0;
    for(int i = 0; i < size; i++){
        tempSum += dataVector[i];
    }
    m_sum = tempSum;
}

double Calculator::sPCC(const Vector<double>& x, const Vector<double>& y)
{
    if(x.GetSize() != y.GetSize() || x.GetSize() == 0)
    {
        return 0;
    }

    double xSum = 0;
    double ySum = 0;


    for(int i = 0; i <x.GetSize(); i++)
    {
        xSum += x[i];
        ySum += y[i];
    }

    double xMean = xSum / x.GetSize();
    double yMean = ySum / y.GetSize();

    double numerator = 0;
    double xDenominator = 0;
    double yDenominator = 0;

    //calculation from the lab
    for(int i =0; i<x.GetSize(), i++)
    {
        numerator += (x[i] - xMean) * (y[i]- yMean);
        xDenominator += (x[i] - xMean) * ([x[i] - xMean);
        yDenominator += (y[i] - yMean) * (y[i] - yMean);

    }

    return (numerator/(std::sqrt(xDenominator)*std::sqrt(yDenominator)));

}

double Calculator::mad(const Vector<double>& dataVector)
{
    SetSum(dataVector.GetSize(), dataVector);
    calculateMean(dataVector.GetSize());

    double total = 0;

    for(int i =0; i<dataVector.GetSize();i++)
    {
        total+= std::abs(dataVector[i] - GetMean());
    }

    return (total/dataVector.GetSize());
}


std::ifstream & operator >>(std::ifstream & input, Calculator & Calc)
{
  int size = 0;

  input >> size;

  Calc.SetSize(size);

  double value = 0;

    for(int i = 0; i < size; i ++){
        input >> value;
        Calc.dataVector.Insert(i,value);
    }
    return input;
}
