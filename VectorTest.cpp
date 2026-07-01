#include "Vector.h"
#include <iostream>

using namespace std;

int main()
{
    Vector<int> numbers;
    cout << "size of vector: " << numbers.GetSize() << endl;
    numbers.Insert(0, 555);
    numbers.Insert(1, 666);
    numbers.Insert(2, 777);
    cout << "size of vector now : " << numbers.GetSize() << endl;

    for(int i =0; i< numbers.GetSize(); i++)
    {
        cout << numbers[i] << endl; // const T& operator
    }
    numbers.Insert(1,567);
    cout << "added first index with 567 and moving the rest behind" << endl;
    for(int i =0; i< numbers.GetSize(); i++)
    {
        cout << numbers[i] << endl; // const T& operator
    }
    numbers.Delete(1);

    cout << "deleting the added number" << endl;
        for(int i =0; i< numbers.GetSize(); i++)
    {
        cout << numbers[i] << endl; // const T& operator
    }

    Vector<int> numbers2(3);
    cout <<"testing parameterized constructor" << endl;
    numbers2.Insert(0, 500);
    numbers2.Insert(1, 550);
    numbers2.Insert(2, 555);

    for(int i =0; i< numbers2.GetSize(); i++)
    {
        cout << numbers[i] << endl; // const T& operator
    }





}
