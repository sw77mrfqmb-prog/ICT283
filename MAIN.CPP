#include <iostream>
#include <fstream>
#include <sstream>
#include "Date.h"  // your Date class from a previous lab
#include "Time.h"  // your Time class from this lab
#include "Vector.h" // your Template Vector class from this lab
#include "DataLog.h"
#include "Calculator.h"
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
        return -1;
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
    std::cout << "3.Total solar radiation in kWh/m^2 for each month of a specified year." << std::endl;
    std::cout << "4.Average wind speed (km/h, average ambient air temperature and total solar radiation in kWh/m^2 for each month of a specified year." << std::endl;
}

void printWind(const DatalogType& excel_data, int month, int year)
{

    std::string strMonth = MonthArr[month -1];

    float* speedArray = new float[excel_data.GetSize()];
    int size = 0;

    for(int i = 0; i < excel_data.GetSize(); i++)
    {
        std::string recordMonth;
        excel_data[i].d.GetMonth(recordMonth);

        if(recordMonth == strMonth && excel_data[i].d.GetYear() == year)
        {
            speedArray[size] = excel_data[i].data.GetSpeed();
            size++;
        }
    }
    if(size == 0)
    {
        std::cout << strMonth << " " << year << ": No Data" << std::endl;
        delete[] speedArray;
        return;
    }
    Calculator windCalc;
    windCalc.SetSum(size, speedArray);
    windCalc.calculateMean(size);
    windCalc.calculateSD(size, speedArray);

    std::cout << strMonth << " " << year << ":" <<std::endl;
    std::cout << "Average speed: " << windCalc.GetMean() << " km/h" << std::endl;
    std::cout << "Sample stdev: "  << windCalc.GetSD() << std::endl;

    delete[] speedArray;
}

void printTemperature(const DatalogType& excel_data, int year)
{

    for(int m = 1; m <= 12; m++)
    {

        std::string stringMonth = MonthArr[m-1];

        float* tempArray = new float[excel_data.GetSize()];
        int size = 0;

        for(int i =0; i< excel_data.GetSize(); i++)
        {
            std::string recordMonth;
            excel_data[i].d.GetMonth(recordMonth);

            if(recordMonth == stringMonth && excel_data[i].d.GetYear() == year)
            {
                tempArray[size] = excel_data[i].data.GetTemperature();
                size++;
            }
        }
        if(size ==0)
        {
            std::cout << stringMonth << ": No Data" << std::endl;
        }
        else
        {
            Calculator calc;
            calc.SetSum(size, tempArray);
            calc.calculateMean(size);
            calc.calculateSD(size, tempArray);

            std::cout << stringMonth << ": ";
            std::cout << "average: " << calc.GetMean() << " degrees C, ";
            std::cout << "stdev: " << calc.GetSD() << std::endl;
        }
    }
}

void printSolarRadiation(const DatalogType& excel_data, int year)
{
    for(int m = 1; m <= 12; m++)
    {
        std::string stringMonth = MonthArr[m-1];
        float totalSR = 0.0f;
        int size = 0;

        for(int i =0; i< excel_data.GetSize(); i++)
        {
            std::string recordMonth;
            excel_data[i].d.GetMonth(recordMonth);

            if(recordMonth == stringMonth && excel_data[i].d.GetYear() == year)
            {
                totalSR += excel_data[i].data.GetSolarRadiation();
                size++;
            }
        }
        if(size ==0)
        {
            std::cout << stringMonth << ": No Data" << std::endl;
        }
        else
        {
            std::cout << stringMonth << ": " << totalSR << " kWh/m2" << std::endl;
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
        std::string stringMonth = MonthArr[m-1];

        float* speedArray = new float[excel_data.GetSize()];
        float* tempArray = new float[excel_data.GetSize()];
        float totalSR =0.0f;
        int speedSize = 0;
        int tempSize = 0;
        int srSize = 0;

        for(int i =0 ; i< excel_data.GetSize(); i++)
        {
            std::string recordMonth;
            excel_data[i].d.GetMonth(recordMonth);

            if(recordMonth == stringMonth && excel_data[i].d.GetYear() == year )
            {
                speedArray[speedSize] = excel_data[i].data.GetSpeed();
                speedSize ++;

                tempArray[tempSize] = excel_data[i].data.GetTemperature();
                tempSize ++;

                totalSR += excel_data[i].data.GetSolarRadiation()*(10.0f / 60.0f) / 1000.0f;
                srSize ++;
            }
        }

        if(speedSize >0 || tempSize >0 || srSize >0)
        {
            checkData = true;
            outfile << stringMonth << ",";

            if(speedSize >0)
            {
                Calculator calc;
                calc.SetSum(speedSize, speedArray);
                calc.calculateMean(speedSize);
                calc.calculateSD(speedSize, speedArray);
                outfile << calc.GetMean() << "(" << calc.GetSD() << ")";
            }
            outfile << ",";

            if(tempSize >0)
            {
                Calculator calc;
                calc.SetSum(tempSize, tempArray);
                calc.calculateMean(tempSize);
                calc.calculateSD(tempSize, tempArray);
                outfile << calc.GetMean() << "(" << calc.GetSD() << ")";
            }
            outfile << ",";

            if(srSize >0)
            {
                outfile << totalSR;
            }

            outfile << std::endl;

            delete[] speedArray;
            delete[] tempArray;
        }
    }
    if(!checkData)
    {
        outfile << "No Data" << std::endl;
    }
    outfile.close();
    std::cout << "Success" << std::endl;
}
