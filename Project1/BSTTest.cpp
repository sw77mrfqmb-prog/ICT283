#include <iostream>
#include "intBST.h"
#include "../Assignment1/BST.h"

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
    intTree.InOrderT();
    std::cout << "PreOrder: ";
    intTree.PreOrderT();
    std::cout << "PostOrder: ";
    intTree.PostOrderT();

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

    intTree.clear();
    std::cout << "Cleared the tree" << std::endl;

    std::cout << "InOrder: ";
    intTree.InOrderT();
    std::cout << "PreOrder: ";
    intTree.PreOrderT();
    std::cout << "PostOrder: ";
    intTree.PostOrderT();



}
