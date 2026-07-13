#include <iostream>
#include <fstream>
#include <sstream>
#include "Date.h"  // your Date class from a previous lab
#include "Time.h"  // your Time class from this lab
#include "Vector.h" // your Template Vector class from this lab
#include "DataLog.h"
#include "Calculator.h"
#include <iomanip>
const std::string MonthArr[] =
{
    "January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December"
};

void menu();


typedef struct
{
    Date d;
    Time t;
    DataLog data;
} DataRecType;

typedef Vector<DataRecType> DatalogType;

void printWind(const DatalogType& excel_data, int month, int year);

bool loadData(DatalogType& excel_data);

void printTemperature(const DatalogType& excel_data, int year);

void printSolarRadiation(const DatalogType& excel_data, int year);

void printAll(const DatalogType& excel_data, int year);

void printsPCC(const DatalogType& excel_data, int month);

int main()
{

    DatalogType excel_data;

    if(!loadData(excel_data))
    {
        return -1;
    }

    int choice;
    do
    {
        menu();
        std::cin >> choice;

        switch(choice)
        {
        case 1:
        {
            int month;
            int year;
            std::cout << "Enter month: " << std::endl;
            std::cin >> month;
            std::cout << "Enter year: " << std::endl;
            std::cin >> year;
            printWind(excel_data, month, year);
            break;
        }
        case 2:
        {
            int year;
            std::cout << "Enter year: " << std::endl;
            std::cin >> year;
            printTemperature(excel_data,year);
            break;
        }
        case 3:
        {
            int month;
            std::cout << "Enter numeric month(1 to 12): " << std::endl;
            std::cin >> month;
            printsPCC(excel_data, month);
            break;
        }
        case 4:
        {
            int year;
            std::cout << "Enter year: " << std::endl;
            std::cin >> year;
            printAll(excel_data, year);
            break;
        }
        case 5:
        {
            std::cout << "Exiting program." << std::endl;
            break;
        }
        default:
            std::cout << "Enter input within range 1 to 5." << std::endl;
        }


    }
    while(choice != 5);
    return 0;

}

bool loadData(DatalogType& excel_data)
{
    std::ifstream infile( "data/data_source.txt" );
    if( !infile )
    {
        std::cout << "Error: Could not find or open the data/data_source.txt file!" << std::endl;
        return false;
    }
    std::string tempFileName;
    while(std::getline(infile,tempFileName))
    {


        std::ifstream tempFile("data/" + tempFileName);
        if( !tempFile )
        {
            std::cout << "Error: Could not find or open the " << tempFileName << std::endl;
            continue;
        }
        std::cout << "Opened: " << tempFileName << std::endl;


        std::string headerLine;
        int wastColumn = -1;
        int sColumn = -1;
        int tColumn = -1;
        int srColumn = -1;
        int currentColumn =0;

        std::getline(tempFile, headerLine);
        std::stringstream ss(headerLine);
        std::string columnName;
        while(std::getline(ss,columnName, ','))
        {
            if(columnName == "WAST")
            {
                wastColumn = currentColumn;
            }
            if(columnName == "S")
            {
                sColumn = currentColumn;
            }
            if(columnName == "T")
            {
                tColumn = currentColumn;
            }
            if(columnName == "SR")
            {
                srColumn = currentColumn;
            }
            currentColumn++;
        }

        std::string dataLine;

        while(std::getline(tempFile,dataLine))
        {
            std::stringstream rowStream(dataLine);
            std::string cellValue;
            int columnIndex = 0;

            DataRecType record;
            bool isWAST = false;
            bool isS = false;
            bool isT = false;
            bool isSR = false;

            while(std::getline(rowStream, cellValue, ','))
            {

                if(columnIndex == wastColumn)
                {
                    try
                    {
                        std::stringstream wastStream(cellValue);
                        std::string dateSection, timeSection;

                        if(wastStream >> dateSection >> timeSection)
                        {
                            std::stringstream dataStream(dateSection);
                            std::stringstream timeStream(timeSection);

                            dataStream >> record.d;
                            timeStream >> record.t;
                            if (record.d.GetDay() > 0 && record.t.GetHour() >= 0)
                            {
                                isWAST = true;
                            }
                        }
                    }
                    catch(...)
                    {
                        isWAST = false;
                    }

                }
                else if(columnIndex == sColumn)
                {
                    try
                    {
                        record.data.SetSpeed(std::stof(cellValue)); //stores it as km/h from m/s
                        isS = true;
                    }
                    catch(...) //catch all errors
                    {
                        isS = false;
                    }
                }
                else if(columnIndex == tColumn)
                {
                    try
                    {
                        record.data.SetTemperature(std::stof(cellValue));
                        isT = true;
                    }
                    catch(...)
                    {
                        isT = false;
                    }
                }
                else if(columnIndex == srColumn)
                {
                    try
                    {
                        record.data.SetSolarRadiation(std::stof(cellValue));
                        isSR = true;
                    }
                    catch(...)
                    {
                        isSR =false;
                    }

                }
                columnIndex ++;
            }
            if(isWAST && isS && isT && isSR)
            {
                excel_data.Insert(excel_data.GetSize(),record);
            }
        }
        tempFile.close();
    }


    infile.close();
    return true;
}


void menu()
{
    std::cout << "-------------- MENU --------------" << std::endl;
    std::cout << "1.The average wind speed and sample standard deviation for this wind speed given a specified month and year." << std::endl;
    std::cout << "2.Average ambient air temperature and sample deviation for each month of a specified year." << std::endl;
    std::cout << "3.sPPC 3 combinations." << std::endl;
    std::cout << "4.Average wind speed (km/h, average ambient air temperature and total solar radiation in kWh/m^2 for each month of a specified year." << std::endl;
}

void printWind(const DatalogType& excel_data, int month, int year)
{

    Vector<double> speedVector;
    int size =0;

    for(int i = 0; i < excel_data.GetSize(); i++)
    {
        //check if year and month is the same based on input, then add into the speedVector
        if( excel_data[i].d.GetMonth() == month && excel_data[i].d.GetYear() == year)
        {
            speedVector.Insert(speedVector.GetSize(),(double)excel_data[i].data.GetSpeed());
            size++;
        }
    }
    if(size == 0)
    {
        std::cout << MonthArr[month-1] << " " << year << ": No Data" << std::endl;
        return;
    }
    Calculator windCalc;
    windCalc.SetSum(speedVector.GetSize(), speedVector);
    windCalc.calculateMean(speedVector.GetSize());
    windCalc.calculateSD(speedVector.GetSize(), speedVector);

    std::cout << MonthArr[month-1] << " " << year << ":" <<std::endl;
    std::cout << "Average speed: " << windCalc.GetMean() << " km/h" << std::endl;
    std::cout << "Sample stdev: "  << windCalc.GetSD() << std::endl;
}

void printTemperature(const DatalogType& excel_data, int year)
{

    for(int m = 1; m <= 12; m++)
    {
        Vector<double> tempVector;

        int size = 0;

        for(int i =0; i< excel_data.GetSize(); i++)
        {

            if(excel_data[i].d.GetMonth() == m && excel_data[i].d.GetYear() == year)
            {
                tempVector.Insert(tempVector.GetSize(), (double)excel_data[i].data.GetTemperature());
                size++;
            }
        }
        if(size ==0)
        {
            std::cout << MonthArr[m-1] << ": No Data" << std::endl;
        }
        else
        {
            Calculator calc;
            calc.SetSum(tempVector.GetSize(), tempVector);
            calc.calculateMean(tempVector.GetSize());
            calc.calculateSD(tempVector.GetSize(), tempVector);

            std::cout << MonthArr[m-1] << ": ";
            std::cout << "average: " << calc.GetMean() << " degrees C, ";
            std::cout << "stdev: " << calc.GetSD() << std::endl;
        }
    }
}
//changed but not used.
void printSolarRadiation(const DatalogType& excel_data, int year)
{
    Vector<double> srVector;
    for(int m = 1; m <= 12; m++)
    {
        int size = 0;
        float totalSR = 0.0f;

        for(int i =0; i< excel_data.GetSize(); i++)
        {
            if(excel_data[i].d.GetMonth() == m && excel_data[i].d.GetYear() == year)
            {
                totalSR +=(double)excel_data[i].data.GetSolarRadiation();
                size++;
            }
        }
        if(size ==0)
        {
            std::cout << MonthArr[m-1] << ": No Data" << std::endl;
        }
        else
        {
            std::cout << MonthArr[m-1] << ": " << totalSR << " kWh/m2" << std::endl;
        }
    }
}

void printAll(const DatalogType& excel_data, int year)
{

    std::ofstream outfile("WindTempSolar.csv");

    outfile << year << std::endl;

    bool checkData = false; //check if there is data inside\

    for(int m = 1; m <= 12; m++)
    {
        Vector<double>  speedVector;
        Vector<double>  tempVector;
        float totalSR =0.0f;
        int srSize = 0;

        for(int i =0 ; i< excel_data.GetSize(); i++)
        {
            if(excel_data[i].d.GetMonth() == m && excel_data[i].d.GetYear() == year )
            {
                speedVector.Insert(speedVector.GetSize(),(double)excel_data[i].data.GetSpeed());

                tempVector.Insert(tempVector.GetSize(), (double)excel_data[i].data.GetTemperature());

                totalSR += excel_data[i].data.GetSolarRadiation();
                srSize ++;
            }
        }

        if(speedVector.GetSize() >0 || tempVector.GetSize() >0 || srSize >0)
        {
            checkData = true;
            outfile << MonthArr[m-1] << ",";

            if(speedVector.GetSize() >0)
            {
                Calculator calc;
                calc.SetSum(speedVector.GetSize(), speedVector);
                calc.calculateMean(speedVector.GetSize());
                calc.calculateSD(speedVector.GetSize(), speedVector);
                outfile << calc.GetMean() << "(" << calc.GetSD() << ")";
            }
            outfile << ",";

            if(tempVector.GetSize() >0)
            {
                Calculator calc;
                calc.SetSum( tempVector.GetSize(), tempVector);
                calc.calculateMean( tempVector.GetSize());
                calc.calculateSD( tempVector.GetSize(), tempVector);
                outfile << calc.GetMean() << "(" << calc.GetSD() << ")";
            }
            outfile << ",";

            if(srSize >0)
            {
                outfile << totalSR;
            }

            outfile << std::endl;
        }
    }
    if(!checkData)
    {
        outfile << "No Data" << std::endl;
    }
    outfile.close();
    std::cout << "Success" << std::endl;
}
//  create 3 vector first as input for sPCC
//this calls sPCC and print out the results for all speed,temp and sr
void printsPCC(const DatalogType& excel_data, int month)
{
    if(month < 1 || month >12)
    {
        std::cout << "Invalid month only 1 to 12.";
        return;
    }
    Vector<double> speedVector;
    Vector<double> tempVector;
    Vector<double> srVector;

    for(int i =0; i<excel_data.GetSize();i++)
    {
        if(excel_data[i].d.GetMonth() == month)
        {
            speedVector.Insert(speedVector.GetSize(),(double)excel_data[i].data.GetSpeed());
            tempVector.Insert(tempVector.GetSize(),(double)excel_data[i].data.GetTemperature());
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
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "S_T: " << calc.sPCC(speedVector,tempVector) << std::endl;
    std::cout << "S_R: " << calc.sPCC(speedVector,srVector) << std::endl;
    std::cout << "T_R: " << calc.sPCC(tempVector,srVector) << std::endl;

}
