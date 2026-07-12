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
    for(int i =0; i<x.GetSize(); i++)
    {
        numerator += (x[i] - xMean) * (y[i]- yMean);
        xDenominator += (x[i] - xMean) * (x[i] - xMean);
        yDenominator += (y[i] - yMean) * (y[i] - yMean);

    }

    return (numerator/(std::sqrt(xDenominator)*std::sqrt(yDenominator)));

}

//  create 3 vector first as input for sPCC
//this calls sPCC and print out the results for all speed,temp and sr
void printsPCC(const DatalogType& excel_data, int month)
{
    Vector<double> speedVector;
    Vector<double> tempVector;
    Vector<double> srVector;

    for(int i =0; i<excel_data.GetSize();i++)
    {
        if(excel_data[i].d.GetMonth() == month)
        {
            speedVector.Insert(speedVector.GetSize(),(double)excel_data[i].data.GetSpeed());
            tempVector.Insert(temoVector.GetSize(),(double)excel_data[i].data.GetTemperature());
            srVector.Insert(srVector.GetSize(),(double)excel_data[i].data.GetSolarRadiation());
        }
    }

    std::cout << "Sample Pearson Correlation Coefficient for " << MonthArr[month -1] << std::endl;

    if(speedVector.GetSize() == 0)
    {
        std::cout << "No data ";
        return;
    }

    Calculator calc;
    std::cout << "S_T: " << calc.sPCC(speedVector,tempVector) << std::endl;
    std::cout << "S_R: " << calc.sPCC(speedVector,srVector) << std::endl;
    std::cout << "T_R: " << calc.sPCC(tempVector,srVector) << std::endl;

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
