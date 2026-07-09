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

    ~Bst();

    void clear();

    bool Insert(const T& value);

    bool Search(const T& value) const;

    void InOrderT() const;

    void PreOrderT() const;

    void PostOrderT() const;

private:

    Node* m_root;

    bool Insert(Node*& node,const T& value);

    bool Search(Node* node,const T& value) const;

    void DeleteTree(Node* node);

    void InOrderT(Node* node) const;

    void PreOrderT(Node* node) const;

    void PostOrderT(Node* node) const;

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
void Bst<T>::InOrderT() const
{
    InOrderT(m_root);
    std::cout << std::endl;
}
template <class T>
void Bst<T>::PreOrderT() const
{
    PreOrderT(m_root);
    std::cout << std::endl;
}
template <class T>
void Bst<T>::PostOrderT() const
{
    PostOrderT(m_root);
    std::cout << std::endl;
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
void Bst<T>::InOrderT(Node* node) const
{
    if(node == nullptr)
    {
        return;
    }
    InOrderT(node->left);
    std::cout << node->data << " ";
    InOrderT(node->right);
}
template <class T>
void Bst<T>::PreOrderT(Node* node) const
{
    if(node == nullptr)
    {
        return;
    }
    std::cout << node->data << " ";
    PreOrderT(node->left);
    PreOrderT(node->right);
}
template <class T>
void Bst<T>::PostOrderT(Node* node) const
{
    if(node == nullptr)
    {
        return;
    }
    PostOrderT(node->left);
    PostOrderT(node->right);
    std::cout << node->data << " ";
}

#endif // BST_H_INCLUDED
