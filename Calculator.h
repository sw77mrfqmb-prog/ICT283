#ifndef Calculator_H_INCLUDED
#define Calculator_H_INCLUDED
#include <string>
#include <iostream>
#include <fstream>
#include "Vector.h"

/** @brief Calculator.h
* @author Delvin
     */

class Calculator
{
public:
    /** @brief default constructor
     */
    Calculator();
    /* removed cause paramater already takes in a vector
    /** @brief data vector double type
     */
    Vector<double> dataVector;
    /** @brief to calculate Mean aka average
     * @param size (number of index that holds data)
     */
    void calculateMean(int size);
    /** @brief  to calculate the standard Deviation
     * @param size (number of index that holds data)
     * @param dataVector with const double data type
     */
    void calculateSD(int size, const Vector<double>& dataVector);
    /** @brief getter for sum
     * @return sum value in double type
     *
     */
    double GetSum();
    /** @brief getter for mean
     * @return mean value in double type
     */
     double GetMean();
    /** @brief  getter for standard deviation
     * @return standard deviation value in double type
     */
    double GetSD();
    /** \brief  getter for size (number of index that holds data)
     * @return size in int type
     */
    int GetSize();
    /** @brief setter for size
     * @param size replace m_size with parameter size
     */
    void SetSize(int size);
    /** @brief  settter for sum
     * @param size (number of index that holds data)
     * @param dataVector will read each index to add it all up as new sum
     */
    void SetSum(int size, const Vector<double>& dataVector);
    /** @brief  sPCC sample Pearson Correlation Coefficient of between two numeric Vectors
     * @param x first vector
     * @param y second vector
     * @return double the calculated value of the sPCC
     */
    double sPCC(const Vector<double>& x, const Vector<double>& y);
    /** @brief MAD Mean Absolute Deviation
     * @param dataVector will read each index to add it all up as new sum
     */
    double mad(const Vector<double>& dataVector);


private:

    double m_sum;
    double m_mean;
    double m_sd;
    int m_size;
};

std::ifstream & operator >>(std::ifstream & input, Calculator & Calc);
#endif // Calculator_H_INCLUDED
