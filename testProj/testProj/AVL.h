#pragma once

#include "shared_ptr.h"
#include "weak_ptr.h"

#include <string>

class AVL
{
    typedef long long ll;
    typedef std::string str;

public:
    AVL();
    ~AVL();
    void add(ll key, str value);
    void remove(ll key);
    str findValueWithKey(ll key);
    bool contains(ll key);
    str& operator[](ll key);
    void clear();
    void directPrint();
    void reversePrint();
    void keySortedPrint();
 
private:

    class Node
    {
    public:
        Node(ll nKey, str nValue);
        Node();
        Node* newNode(ll nKey, str nValue);
        Node* left, * right;
        int height;
        ll key;
        str data;

        int getHeight(Node* node);
        int max(int a, int b);

        Node* rightRotate(Node* node);
        Node* leftRotate(Node* node);
        

        int getBalance(Node* node);
        Node* insert(Node* node, int key, str value);
        Node* minValueNode(Node* node);
        Node* deleteNode(Node* root, int key);

        Node* find(Node *node, ll key);
    } *root;
};


