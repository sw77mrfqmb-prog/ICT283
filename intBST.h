#ifndef INTBST_H_INCLUDED
#define INTBST_H_INCLUDED
#include <iostream>

class intBst
{
public:

    intBst();

    ~intBst();

    void Insert(int value);

    bool Search(int value) const;

    void InOrderT() const;

    void PreOrderT() const;

    void PostOrderT() const;

private:

    struct Node
    {
        int data;
        Node* left;
        Node* right;
    };

    Node* m_root;

    Node* Insert(Node* node, int value);

    bool Search(Node* node,int value) const;

    void DeleteTree(Node* node);

    void InOrderT(Node* node) const;

    void PreOrderT(Node* node) const;

    void PostOrderT(Node* node) const;

};

intBst::intBst()
{
    m_root = nullptr;
}

intBst::~intBst()
{
    DeleteTree(m_root);
}

void intBst::Insert(int value)
{
    m_root = Insert(m_root, value);
}

bool intBst::Search(int value) const
{
    return Search(m_root, value);
}
void intBst::InOrderT() const
{
    InOrderT(m_root);
    std::cout << std::endl;
}

void intBst::PreOrderT() const
{
    PreOrderT(m_root);
    std::cout << std::endl;
}

void intBst::PostOrderT() const
{
    PostOrderT(m_root);
    std::cout << std::endl;
}

intBst::Node* intBst::Insert(Node* node, int value)
{
    if(node == nullptr)
    {
    // this initialize the tree
    Node* newNode = new Node;
    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
    }

    if(value < node->data)
    {
        node->left = Insert(node->left,value);
    }

    else if(value > node->data)
    {
        node->right = Insert(node->right,value);
    }
    return node;
}

bool intBst::Search(Node* node, int value)const
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
        return Search(node->left, value);
    return Search(node->right, value);

}

void intBst::DeleteTree(Node* node)
{
    if(node == nullptr)
    {
        return;
    }
    DeleteTree(node->left);
    DeleteTree(node->right);
    delete node;
}

void intBst::InOrderT(Node* node) const
{
    if(node == nullptr)
    {
        return;
    }
    InOrderT(node->left);
    std::cout << node->data << " ";
    InOrderT(node->right);
}

void intBst::PreOrderT(Node* node) const
{
    if(node == nullptr)
    {
        return;
    }
    std::cout << node->data << " ";
    PreOrderT(node->left);
    PreOrderT(node->right);
}

void intBst::PostOrderT(Node* node) const
{
    if(node == nullptr)
    {
        return;
    }
    PostOrderT(node->left);
    PostOrderT(node->right);
    std::cout << node->data << " ";
}
#endif // INTBST_H_INCLUDED
