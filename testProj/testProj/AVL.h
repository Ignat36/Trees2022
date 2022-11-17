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
        shared_ptr<Node> newNode(ll nKey, str nValue);
        shared_ptr<Node> left, right;
        int height;
        ll key;
        str data;

        int getHeight(shared_ptr<Node> node);
        int max(int a, int b);

        shared_ptr<Node> rightRotate(shared_ptr<Node> node);
        shared_ptr<Node> leftRotate(shared_ptr<Node> node);


        int getBalance(shared_ptr<Node> node);
        shared_ptr<Node> insert(shared_ptr<Node> node, int key, str value);
        shared_ptr<Node> minValueNode(shared_ptr<Node> node);
        shared_ptr<Node> deleteNode(shared_ptr<Node> root, int key);

        shared_ptr<Node> find(shared_ptr<Node> node, ll key);
    };

    shared_ptr<Node> root;
};


