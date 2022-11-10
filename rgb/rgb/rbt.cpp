//#include "rbt.h"
//#include <vector>
//
//template<class T, class T1>
//RBT<T, T1>::RBT()
//{
//    root = nullptr;
//}
//
//template<class T, class T1>
//void RBT<T, T1>::clear()
//{
//    std::vector< Node* > stack;
//
//    stack.push_back(root);
//
//    while (!stack.empty())
//    {
//        Node* tmp = stack.back();
//        stack.pop_back();
//
//        if (!tmp) continue;
//        stack.push_back(tmp->left);
//        stack.push_back(tmp->right);
//
//        delete tmp;
//    }
//
//    root = nullptr;
//}
//
//template<class T, class T1>
//RBT<T, T1>::~RBT()
//{
//    clear();
//}
//
//template<class T, class T1>
//T1& RBT<T, T1>::operator[](T key)
//{
//    Node* tmp = root, * p = nullptr;
//
//    while (tmp && tmp->key != key)
//    {
//        p = tmp;
//        if (tmp->key > key)
//            tmp = tmp->left;
//        else
//            tmp = tmp->right;
//    }
//
//    if (!tmp)
//    {
//        tmp = new Node();
//        tmp->key = key;
//        tmp->parent = p;
//
//        if (!p)
//            root = tmp;
//        else
//        {
//            if (p->key > key)
//                p->left = tmp;
//            else
//                p->right = tmp;
//        }
//
//        tmp->InsCase1(root);
//    }
//    return tmp->data;
//}
//
//template<class T, class T1>
//void RBT<T, T1>::add(T key, T1 value)
//{
//
//    Node* tmp = root, * p = nullptr;
//
//    while (tmp)
//    {
//        p = tmp;
//
//        if (tmp->key > key)
//            tmp = tmp->left;
//        else if (tmp->key < key)
//            tmp = tmp->right;
//        else return;
//    }
//
//    tmp = new Node(key, value);
//    tmp->parent = p;
//
//    if (p)
//    {
//        if (tmp->key > p->key)
//            p->right = tmp;
//        else
//            p->left = tmp;
//    }
//    else
//        root = tmp;
//
//    tmp->InsCase1(root);
//    return;
//}
//
//
//
//template<class T, class T1>
//void RBT<T, T1>::remove(T key)
//{
//    Node* tmp = root ? root->find(key) : nullptr;
//
//    if (!tmp)
//        return;
//
//    if (!tmp->parent && !tmp->left && !tmp->right)
//    {
//        delete tmp;
//        tmp = nullptr;
//        return;
//    }
//
//    if (tmp->left && tmp->right)
//    {
//        Node* removed = tmp->left;
//        while (removed->right)
//            removed = removed->right;
//        tmp->data = removed->data;
//        tmp->key = removed->key;
//        tmp = removed;
//    }
//
//    Node* child = tmp->left ? tmp->left : tmp->right;
//
//    if (!child)
//    {
//
//        if (tmp->color)
//            tmp->DelCase1(root);
//
//        if (tmp->parent->left == tmp)
//            tmp->parent->left = child;
//        else
//            tmp->parent->right = child;
//    }
//    else
//    {
//        child->parent = tmp->parent;
//
//        if (tmp->parent)
//        {
//            if (tmp == tmp->parent->left)
//                tmp->parent->left = child;
//            else
//                tmp->parent->right = child;
//        }
//        else
//            root = child;
//
//        if (tmp->color)
//        {
//            if (!child->color)
//                child->color = 1;
//            else
//                child->DelCase1(root);
//        }
//    }
//
//    delete tmp;
//}
//
//template<class T, class T1>
//T1 RBT<T, T1>::findValueWithKey(T key)
//{
//    Node* tmp = root, * p = nullptr;
//
//    while (tmp)
//    {
//        p = tmp;
//
//        if (tmp->key > key)
//            tmp = tmp->left;
//        else if (tmp->key < key)
//            tmp = tmp->right;
//        else {
//            return tmp->data;
//        }
//    }
//
//    throw std::exception();
//}
//
//template<class T, class T1>
//RBT<T, T1>::Node::Node(T nKey, T1 nValue)
//{
//    left = right = parent = nullptr;
//    color = 0;
//    key = nKey;
//    data = nValue;
//}
//
//template<class T, class T1>
//RBT<T, T1>::Node::Node()
//{
//    left = right = parent = nullptr;
//    color = 0;
//}
//
//template<class T, class T1>
//void RBT<T, T1>::Node::RotateLeft(Node*& root)
//{
//    Node* tmp = this->right;
//
//    tmp->parent = this->parent;
//    if (this->parent)
//    {
//        if (this->parent->left == this)
//            this->parent->left = tmp;
//        else
//            this->parent->right = tmp;
//    }
//    else
//        root = tmp;
//
//    this->right = tmp->left;
//    if (tmp->left)
//        tmp->left->parent = this;
//
//    this->parent = tmp;
//    tmp->left = this;
//}
//
//template<class T, class T1>
//void RBT<T, T1>::Node::RotateRight(Node*& root)
//{
//    Node* tmp = this->left;
//
//    tmp->parent = this->parent;
//    if (this->parent)
//    {
//        if (this->parent->left == this)
//            this->parent->left = tmp;
//        else
//            this->parent->right = tmp;
//    }
//    else
//        root = tmp;
//
//    this->left = tmp->right;
//    if (tmp->right)
//        tmp->right->parent = this;
//
//    this->parent = tmp;
//    tmp->right = this;
//}
//
//template<class T, class T1>
//typename RBT<T, T1>::Node* RBT<T, T1>::Node::grandparent()
//{
//    if (parent && parent->parent)
//        return parent->parent;
//    else
//        return nullptr;
//}
//
//template<class T, class T1>
//typename RBT<T, T1>::Node* RBT<T, T1>::Node::uncle()
//{
//    Node* tmp = grandparent();
//
//    if (tmp)
//    {
//        if (parent == tmp->left)
//            return tmp->right;
//        else
//            return tmp->left;
//    }
//    else
//        return nullptr;
//}
//
//template<class T, class T1>
//typename RBT<T, T1>::Node* RBT<T, T1>::Node::sibling()
//{
//    if (!parent) return nullptr;
//
//    if (this == parent->left)
//        return parent->right;
//    else
//        return parent->left;
//}
//
//template<class T, class T1>
//typename RBT<T, T1>::Node* RBT<T, T1>::Node::find(T key)
//{
//
//    Node* tmp = this;
//
//    while (tmp && tmp->key != key)
//        if (tmp->key > key)
//            tmp = tmp->left;
//        else
//            tmp = tmp->right;
//
//    return tmp;
//}
//
//template<class T, class T1>
//void RBT<T, T1>::Node::InsCase1(Node*& root)
//{
//    if (parent == nullptr)
//        color = 1;
//    else
//        this->InsCase2(root);
//}
//
//template<class T, class T1>
//void RBT<T, T1>::Node::InsCase2(Node*& root)
//{
//    if (parent->color)
//        return;
//    else this->InsCase3(root);
//}
//
//template<class T, class T1>
//void RBT<T, T1>::Node::InsCase3(Node*& root)
//{
//    Node* u = uncle();
//
//    if (u && !u->color)
//    {
//        parent->color = 1;
//        u->color = 1;
//        Node* g = grandparent();
//        g->color = 0;
//        g->InsCase1(root);
//    }
//    else
//        this->InsCase4(root);
//}
//
//template<class T, class T1>
//void RBT<T, T1>::Node::InsCase4(Node*& root)
//{
//    Node* g = grandparent(), * tmp = this;
//
//    if (this == parent->right && parent == g->left)
//    {
//        parent->RotateLeft(root);
//        tmp = left;
//    }
//    else if (this == parent->left && parent == g->right)
//    {
//        parent->RotateRight(root);
//        tmp = right;
//    }
//
//    tmp->InsCase5(root);
//}
//
//template<class T, class T1>
//void RBT<T, T1>::Node::InsCase5(Node*& root)
//{
//    Node* g = grandparent();
//
//    parent->color = 1;
//    g->color = 0;
//
//    if (this == parent->left)
//        g->RotateRight(root);
//    else
//        g->RotateLeft(root);
//}
//
//template<class T, class T1>
//void RBT<T, T1>::Node::DelCase1(Node*& root)
//{
//    if (parent)
//        this->DelCase2(root);
//}
//
//template<class T, class T1>
//void RBT<T, T1>::Node::DelCase2(Node*& root)
//{
//    Node* s = sibling();
//
//    if (!s->color)
//    {
//        parent->color = 0;
//        s->color = 1;
//
//        if (this == parent->left)
//            parent->RotateLeft(root);
//        else
//            parent->RotateRight(root);
//    }
//
//    this->DelCase3(root);
//}
//
//template<class T, class T1>
//void RBT<T, T1>::Node::DelCase3(Node*& root)
//{
//    Node* s = sibling();
//
//    if (parent->color && s->color && s->left->color && s->right->color)
//    {
//        s->color = 0;
//        s->DelCase1(root);
//    }
//    else
//        this->DelCase4(root);
//}
//
//template<class T, class T1>
//void RBT<T, T1>::Node::DelCase4(Node*& root)
//{
//    Node* s = sibling();
//
//    if (!parent->color && s->color && s->left->color && s->right->color)
//    {
//        s->color = 0;
//        parent->color = 1;
//    }
//    else
//        this->DelCase5(root);
//}
//
//template<class T, class T1>
//void RBT<T, T1>::Node::DelCase5(Node*& root)
//{
//    Node* s = sibling();
//
//    if (s->color)
//    {
//        if (this == parent->left &&
//            s->right->color &&
//            !s->left->color)
//        {
//            s->color = 0;
//            s->left->color = 1;
//            s->RotateRight(root);
//        }
//        else if (this == parent->right &&
//            s->left->color &&
//            !s->right->color)
//        {
//            s->color = 0;
//            s->right->color = 1;
//            s->RotateLeft(root);
//        }
//    }
//
//    this->DelCase6(root);
//}
//
//template<class T, class T1>
//void RBT<T, T1>::Node::DelCase6(Node*& root)
//{
//    Node* s = sibling();
//    s->color = parent->color;
//    parent->color = 1;
//
//    if (this == parent->left)
//    {
//        s->right->color = 1;
//        parent->RotateLeft(root);
//    }
//    else
//    {
//        s->left->color = 1;
//        parent->RotateRight(root);
//    }
//}
