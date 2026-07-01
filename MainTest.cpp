
#include <iostream>
#include <fstream>
#include <sstream>
#include "Date.h"  // your Date class from a previous lab
#include "Time.h"  // your Time class from this lab
#include "Vector.h" // your Template Vector class from this lab
#include "Calculator.h"

int main()
{
    std::string fullString = "31/03/2016 9:00";


    std::stringstream mainStream(fullString);
    std::string dateSection, timeSection;

    mainStream >> dateSection >> timeSection;

    std::stringstream dateStream(dateSection);
    std::stringstream timeStream(timeSection);


    Date d;
    Time t;

    dateStream >> d;
    timeStream >> t;

    std::cout << d;
    std::cout << "Time: " << t << std::endl;
}
