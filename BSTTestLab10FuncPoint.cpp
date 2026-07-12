#include <iostream>
#include "BST.h"


void PrintInt(int& value)
{
    std::cout << value << " ";
}
void TestByValue(Bst<int> tree);
void TestByReference(Bst<int>& tree);
void TestByConstReference(const Bst<int>& tree);



int main()
{

    Bst<int> intTree;

    intTree.Insert(50);
    intTree.Insert(60);
    intTree.Insert(80);
    intTree.Insert(30);
    intTree.Insert(55);
    intTree.Insert(35);
    intTree.Insert(35);

    std::cout << "InOrder: ";
    intTree.InOrderT(PrintInt);
    std::cout << "PreOrder: ";
    intTree.PreOrderT(PrintInt);
    std::cout << "PostOrder: ";
    intTree.PostOrderT(PrintInt);

    std::cout <<"Search 50? ";
    if(intTree.Search(50))
    {
        std::cout << "Found" << std::endl;
    }
    else
    {
        std::cout << "Not found" << std::endl;
    }
    std::cout <<"Search 50? ";
    if(intTree.Search(11))
    {
        std::cout << "Found" << std::endl;
    }
    else
    {
        std::cout << "Not found" << std::endl;
    }
    TestByValue(intTree);
    TestByReference(intTree);
    TestByConstReference(intTree);

    intTree.clear();
    std::cout << "Cleared the tree" << std::endl;

    std::cout << "InOrder: ";
    intTree.InOrderT(PrintInt);
    std::cout << "PreOrder: ";
    intTree.PreOrderT(PrintInt);
    std::cout << "PostOrder: ";
    intTree.PostOrderT(PrintInt);



}

void TestByValue(Bst<int> tree)
{
    std::cout<< "Test pass by value" << std::endl;
    tree.InOrderT(PrintInt);
}
void TestByReference(Bst<int>& tree)
{
    std::cout<< "Test pass by Reference" << std::endl;
    tree.InOrderT(PrintInt);
}
void TestByConstReference(const Bst<int>& tree)
{
    std::cout<< "Test pass by Const Reference" << std::endl;
    tree.InOrderT(PrintInt);
}
