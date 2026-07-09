#include <iostream>
#include <fstream>
#include <sstream>
#include "../Assignment1/BST.h"
#include "../Assignment1/Date.h"

const std::string MonthArr[] =
{
    "January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December"
};
bool loadData(Bst<Date>& dateTree);

int main()
{

    Bst<Date> dateTree;

    if(!loadData(dateTree))
    {
        return -1;
    }

    std::cout << "InOrder: ";
    dateTree.InOrderT();
    std::cout << "PreOrder: ";
    dateTree.PreOrderT();
    std::cout << "PostOrder: ";
    dateTree.PostOrderT();

    std::cout << std::endl << "Search 5 December 2000? ";
    if(dateTree.Search(Date(5,12,2000)))
    {
        std::cout << "Found" << std::endl;
    }
    else
    {
        std::cout << "Not found" << std::endl;
    }
    std::cout <<"Search 1 January 1999? ";
    if(dateTree.Search(Date(1,1,2009)))
    {
        std::cout << "Found" << std::endl;
    }
    else
    {
        std::cout << "Not found" << std::endl;
    }

    dateTree.clear();
    std::cout << "Cleared the tree" << std::endl;

    std::cout << "InOrder: ";
    dateTree.InOrderT();
    std::cout << "PreOrder: ";
    dateTree.PreOrderT();
    std::cout << "PostOrder: ";
    dateTree.PostOrderT();


}

bool loadData(Bst<Date>& dateTree)
{
    std::ifstream infile( "data.txt" );
    if( !infile )
    {
        std::cout << "Error: Could not find or open the data.txt file!" << std::endl;
        return -1;
    }
    int tempDay;
    int tempMonth;
    int tempYear;
    char dummy1;
    char dummy2;


        while(infile >> tempDay >> dummy1 >> tempMonth >> dummy2 >> tempYear)
    {
        dateTree.Insert(Date(tempDay, tempMonth, tempYear));

    }


    infile.close();
    return true;
}
