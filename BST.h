#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
#include <iostream>

template <class T>
class Bst
{
public:

    struct Node
    {
        T data;
        Node* left;
        Node* right;
    };

    Bst();

    Bst(const Bst& other);

    Bst& operator=(const Bst& other);

    ~Bst();

    void clear();

    bool Insert(const T& value);

    bool Search(const T& value) const;

    void InOrderT(void (*visit)(T&)) const;

    void PreOrderT(void (*visit)(T&)) const;

    void PostOrderT(void (*visit)(T&)) const;

private:

    Node* CopyTree(Node* node);

    Node* m_root;

    bool Insert(Node*& node,const T& value);

    bool Search(Node* node,const T& value) const;

    void DeleteTree(Node* node);

    void InOrderT(Node* node, void (*visit)(T&)) const;

    void PreOrderT(Node* node, void (*visit)(T&)) const;

    void PostOrderT(Node* node, void (*visit)(T&)) const;

};
template <class T>
Bst<T>::Bst()
{
    m_root = nullptr;
}


template <class T>
Bst<T>::~Bst()
{
    DeleteTree(m_root);
}
template <class T>
void Bst<T>::clear()
{
    DeleteTree(m_root);
    m_root = nullptr;
}
template <class T>
bool Bst<T>::Insert(const T& value)
{
    return Insert(m_root, value);
}
template <class T>
bool Bst<T>::Search(const T& value) const
{
    return Search(m_root, value);
}
template <class T>
void Bst<T>::InOrderT(void (*visit)(T&)) const
{
    InOrderT(m_root,visit);
    std::cout << std::endl;
}
template <class T>
void Bst<T>::PreOrderT(void (*visit)(T&)) const
{
    PreOrderT(m_root,visit);
    std::cout << std::endl;
}
template <class T>
void Bst<T>::PostOrderT(void (*visit)(T&)) const
{
    PostOrderT(m_root,visit);
    std::cout << std::endl;
}

template <class T>
Bst<T>::Bst(const Bst& other)
{
    m_root = CopyTree(other.m_root);
}

template <class T>
Bst<T>& Bst<T>::operator=(const Bst& other)
{

        DeleteTree(m_root);
        m_root = CopyTree(other.m_root);


    return *this;
}

template <class T>
typename Bst<T>::Node* Bst<T>::CopyTree(Node* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    Node* newNode = new Node;

    newNode->data = node->data;

    newNode->left = CopyTree(node->left);

    newNode->right = CopyTree(node->right);

    return newNode;
}
template <class T>
bool Bst<T>::Insert(Node*& node, const T& value)
{
    if(node == nullptr)
    {
        // this initialize the tree
        node = new Node;
        node->data = value;
        node->left = nullptr;
        node->right = nullptr;
        return true;
    }

    if(value < node->data)
    {
        return Insert(node->left, value);
    }

    else if(value > node->data)
    {
        return Insert(node->right, value);
    }
    return false;
}
template <class T>
bool Bst<T>::Search(Node* node,const T& value)const
{
    if(node == nullptr)
    {
        return false;
    }

    if(value == node->data)
    {
        return true;
    }
    if(value < node->data)
    {
        return Search(node->left, value);
    }
    return Search(node->right, value);

}
template <class T>
void Bst<T>::DeleteTree(Node* node)
{
    if(node == nullptr)
    {
        return;
    }
    DeleteTree(node->left);
    DeleteTree(node->right);
    delete node;
}
template <class T>
void Bst<T>::InOrderT(Node* node, void (*visit)(T&)) const
{
    if(node == nullptr)
    {
        return;
    }
    InOrderT(node->left,visit);
    visit(node->data);
    InOrderT(node->right,visit);
}
template <class T>
void Bst<T>::PreOrderT(Node* node, void (*visit)(T&)) const
{
    if(node == nullptr)
    {
        return;
    }
    visit(node->data);
    PreOrderT(node->left,visit);
    PreOrderT(node->right,visit);
}
template <class T>
void Bst<T>::PostOrderT(Node* node, void (*visit)(T&)) const
{
    if(node == nullptr)
    {
        return;
    }
    PostOrderT(node->left,visit);
    PostOrderT(node->right,visit);
    visit(node->data);
}

#endif // BST_H_INCLUDED
