#pragma once

#include "shared_ptr.h"
#include "weak_ptr.h"

#include <string>
#include <vector>

template<class T, class T1>
class RBT
{
public:
    RBT();
    ~RBT();
    void add(T key, T1 value);
    void remove(T key);
    T1 findValueWithKey(T key);
    bool contains(T key);
    T1& operator[](T key);
    void clear();

protected:

    class Node
    {
    public:
        Node(T nKey, T1 nValue);
        Node();
        shared_ptr<Node> left, right;
        weak_ptr<Node> parent;
        weak_ptr<Node> listNext, listPrev;
        bool color;
        T key;
        T1 data;

        weak_ptr<Node> grandparent();
        weak_ptr<Node> uncle();
        weak_ptr<Node> sibling();

        void RotateLeft(shared_ptr<Node>& root);
        void RotateRight(shared_ptr<Node>& root);

        void InsCase1(shared_ptr<Node>& root);
        void InsCase2(shared_ptr<Node>& root);
        void InsCase3(shared_ptr<Node>& root);
        void InsCase4(shared_ptr<Node>& root);
        void InsCase5(shared_ptr<Node>& root);

        void DelCase1(shared_ptr<Node>& root);
        void DelCase2(shared_ptr<Node>& root);
        void DelCase3(shared_ptr<Node>& root);
        void DelCase4(shared_ptr<Node>& root);
        void DelCase5(shared_ptr<Node>& root);
        void DelCase6(shared_ptr<Node>& root);

        weak_ptr<Node> find(T key);
        weak_ptr<Node> next();
        weak_ptr<Node> prev();

        weak_ptr<Node> min();
        weak_ptr<Node> max();

    };

    shared_ptr<Node> root, _end;

public:
    class iterator
    {
    public:
        iterator(weak_ptr<Node> node, weak_ptr<RBT<T, T1> > own);
        iterator(const iterator& it);
        bool operator!=(iterator const& other) const;
        bool operator==(iterator const& other) const;
        T1& operator*() const;
        iterator& operator++();
        iterator& operator--();

    private:
        weak_ptr<Node> iter;
        weak_ptr<RBT<T, T1> > owner;
    };

    iterator begin()
    {
        return iterator(root->min(), this);
    }

    iterator end()
    {
        return iterator(_end, this);
    }

    class iterator_l
    {
    public:
        iterator_l(weak_ptr<Node> node, weak_ptr<RBT<T, T1> > own);
        iterator_l(const iterator_l& it);
        bool operator!=(iterator_l const& other) const;
        bool operator==(iterator_l const& other) const;
        T1& operator*() const;
        iterator_l& operator++();
        iterator_l& operator--();

    private:
        weak_ptr<Node> iter;
        weak_ptr<RBT<T, T1> > owner;
    };

    iterator_l begin_l()
    {
        return iterator_l(root->min(), this);
    }

    iterator_l end_l()
    {
        return iterator_l(_end, this);
    }
};

template<class T, class T1>
RBT<T, T1>::RBT()
{;
    _end = shared_ptr<Node>(new Node());
}

template<class T, class T1>
void RBT<T, T1>::clear()
{
    root = shared_ptr<Node>();
}

template<class T, class T1>
RBT<T, T1>::~RBT()
{
}

template<class T, class T1>
T1& RBT<T, T1>::operator[](T key)
{
    if (root) root->parent = weak_ptr<Node>();
    shared_ptr<Node> tmp = root, p = shared_ptr<Node>();

    while (tmp && tmp->key != key)
    {
        p = tmp;
        if (tmp->key > key)
            tmp = tmp->left;
        else
            tmp = tmp->right;
    }

    if (!tmp)
    {
        tmp = shared_ptr<Node>(new Node());
        tmp->key = key;
        tmp->parent = p;

        if (!p)
            root = tmp;
        else
        {
            if (p->key > key)
                p->left = tmp;
            else
                p->right = tmp;
        }

        tmp->InsCase1(root);

        
        ///////////////////////////////////////
        if (root) root->parent = _end;
        shared_ptr<Node> nx = tmp->next().lock();
        shared_ptr<Node> pr = tmp->prev().lock();


        tmp->listPrev = pr; pr->listNext = tmp;
        tmp->listNext = nx; nx->listPrev = tmp;
        if (root) root->parent = weak_ptr<Node>();
        ///////////////////////////////////////
        
    }

    if (root) root->parent = _end;
    return tmp->data;
}

template<class T, class T1>
void RBT<T, T1>::add(T key, T1 value)
{
    if (root) root->parent = weak_ptr<Node>();
    shared_ptr<Node> tmp = root, p = shared_ptr<Node>();

    while (tmp)
    {
        p = tmp;

        if (tmp->key > key)
            tmp = tmp->left;
        else if (tmp->key < key)
            tmp = tmp->right;
        else
        {
            if (root) root->parent = _end;
            return;
        }
    }

    tmp = shared_ptr<Node>(new Node(key, value));
    tmp->parent = p;

    if (p)
    {
        if (tmp->key > p->key)
            p->right = tmp;
        else
            p->left = tmp;
    }
    else
        root = tmp;

    tmp->InsCase1(root);

    ////////////////////////////////////////
    if (root) root->parent = _end;
    shared_ptr<Node> nx = tmp->next().lock();
    shared_ptr<Node> pr = tmp->prev().lock();


    tmp->listPrev = pr; pr->listNext = tmp;
    tmp->listNext = nx; nx->listPrev = tmp;
    if (root) root->parent = weak_ptr<Node>();
    ///////////////////////////////////////

    if (root) root->parent = _end;
    return;
}



template<class T, class T1>
void RBT<T, T1>::remove(T key)
{
    if (root) root->parent = weak_ptr<Node>();
    shared_ptr<Node> tmp;
    if (root)
        tmp = root->find(key);
    else 
        tmp = shared_ptr<Node>();

    if (!tmp)
    {
        if (root) root->parent = _end;
        return;
    }

    if (!tmp->parent && !tmp->left && !tmp->right)
    {
        root = shared_ptr<Node>();
        return;
    }

    if (tmp->left && tmp->right)
    {
        shared_ptr<Node> removed = tmp->left;
        while (removed->right)
            removed = removed->right;
        tmp->data = removed->data;
        tmp->key = removed->key;
        tmp = removed;

        ////////////////////////////////////
        // swap instead of copy
        ////////////////////////////////////
    }

    shared_ptr<Node> child = tmp->left ? tmp->left : tmp->right;

    if (!child)
    {

        if (tmp->color)
            tmp->DelCase1(root);

        if (tmp->parent->left == tmp)
            tmp->parent->left = child;
        else
            tmp->parent->right = child;
    }
    else
    {
        child->parent = tmp->parent;

        if (tmp->parent)
        {
            if (tmp == tmp->parent->left)
                tmp->parent->left = child;
            else
                tmp->parent->right = child;
        }
        else
            root = child;

        if (tmp->color)
        {
            if (!child->color)
                child->color = 1;
            else
                child->DelCase1(root);
        }
    }
    ////////////////////////////////////
    if (root) root->parent = _end;
    shared_ptr<Node> nx = tmp->next().lock();
    shared_ptr<Node> pr = tmp->prev().lock();


    tmp->listPrev = pr; pr->listNext = tmp;
    tmp->listNext = nx; nx->listPrev = tmp;
    if (root) root->parent = weak_ptr<Node>();
    /////////////////////////////////////

    if (root) root->parent = _end;
}

template<class T, class T1>
T1 RBT<T, T1>::findValueWithKey(T key)
{
    shared_ptr<Node> tmp = root,  p = shared_ptr<Node>();

    while (tmp)
    {
        p = tmp;

        if (tmp->key > key)
            tmp = tmp->left;
        else if (tmp->key < key)
            tmp = tmp->right;
        else {
            return tmp->data;
        }
    }

    throw std::exception();
}

template<class T, class T1>
bool RBT<T, T1>::contains(T key)
{
    return root && root->find(key);
}

template<class T, class T1>
RBT<T, T1>::Node::Node(T nKey, T1 nValue)
{
    left = right = parent = weak_ptr<Node>();
    listNext = listPrev = weak_ptr<Node>();
    color = 0;
    key = nKey;
    data = nValue;
}

template<class T, class T1>
RBT<T, T1>::Node::Node()
{
    left = right = parent = weak_ptr<Node>();
    listNext = listPrev = weak_ptr<Node>();
    color = 0;
}

template<class T, class T1>
void RBT<T, T1>::Node::RotateLeft(shared_ptr<Node>& root)
{
    shared_ptr<Node> tmp = this->right;

    tmp->parent = this->parent;
    if (this->parent)
    {
        if (this->parent->left == this)
            this->parent->left = tmp;
        else
            this->parent->right = tmp;
    }
    else
        root = tmp.lock();

    this->right = tmp->left;
    if (tmp->left)
        tmp->left->parent = this;

    this->parent = tmp;
    tmp->left = this;
}

template<class T, class T1>
void RBT<T, T1>::Node::RotateRight(shared_ptr<Node>& root)
{
    Node* tmp = this->left;

    tmp->parent = this->parent;
    if (this->parent)
    {
        if (this->parent->left == this)
            this->parent->left = tmp;
        else
            this->parent->right = tmp;
    }
    else
        root = tmp;

    this->left = tmp->right;
    if (tmp->right)
        tmp->right->parent = this;

    this->parent = tmp;
    tmp->right = this;
}

template<class T, class T1>
weak_ptr<typename RBT<T, T1>::Node > RBT<T, T1>::Node::grandparent()
{
    if (parent && parent->parent)
        return parent->parent;
    else
        return nullptr;
}

template<class T, class T1>
weak_ptr<typename RBT<T, T1>::Node > RBT<T, T1>::Node::uncle()
{
    Node* tmp = grandparent();

    if (tmp)
    {
        if (parent == tmp->left)
            return tmp->right;
        else
            return tmp->left;
    }
    else
        return nullptr;
}

template<class T, class T1>
weak_ptr<typename RBT<T, T1>::Node > RBT<T, T1>::Node::sibling()
{
    if (!parent) return nullptr;

    if (this == parent->left)
        return parent->right;
    else
        return parent->left;
}

template<class T, class T1>
weak_ptr<typename RBT<T, T1>::Node > RBT<T, T1>::Node::find(T key)
{

    Node* tmp = this;

    while (tmp && tmp->key != key)
        if (tmp->key > key)
            tmp = tmp->left;
        else
            tmp = tmp->right;

    return tmp;
}

template<class T, class T1>
weak_ptr<typename RBT<T, T1>::Node > RBT<T, T1>::Node::next()
{
    Node* tmp = right;
    if (tmp)
    {
        while (tmp->left) tmp = tmp->left;
        return tmp;
    }

    tmp = this;
    while (tmp->parent && tmp == tmp->parent->right) tmp = tmp->parent;

    return tmp->parent ? tmp->parent : this;
}

template<class T, class T1>
weak_ptr<typename RBT<T, T1>::Node > RBT<T, T1>::Node::prev()
{
    Node* tmp = left;
    if (tmp)
    {
        while (tmp->right) tmp = tmp->right;
        return tmp;
    }

    tmp = this;
    while (tmp->parent && tmp == tmp->parent->left) tmp = tmp->parent;

    return tmp->parent ? tmp->parent : this;
}

template<class T, class T1>
weak_ptr<typename RBT<T, T1>::Node > RBT<T, T1>::Node::min()
{
    Node* tmp = this;
    while (tmp->left) tmp = tmp->left;
    return tmp;
}

template<class T, class T1>
weak_ptr<typename RBT<T, T1>::Node > RBT<T, T1>::Node::max()
{
    Node* tmp = this;
    while (tmp->right) tmp = tmp->right;
    return tmp;
}

template<class T, class T1>
void RBT<T, T1>::Node::InsCase1(shared_ptr<Node>& root)
{
    if (parent == nullptr)
        color = 1;
    else
        this->InsCase2(root);
}

template<class T, class T1>
void RBT<T, T1>::Node::InsCase2(shared_ptr<Node>& root)
{
    if (parent->color)
        return;
    else this->InsCase3(root);
}

template<class T, class T1>
void RBT<T, T1>::Node::InsCase3(shared_ptr<Node>& root)
{
    Node* u = uncle();

    if (u && !u->color)
    {
        parent->color = 1;
        u->color = 1;
        Node* g = grandparent();
        g->color = 0;
        g->InsCase1(root);
    }
    else
        this->InsCase4(root);
}

template<class T, class T1>
void RBT<T, T1>::Node::InsCase4(shared_ptr<Node>& root)
{
    Node* g = grandparent(), * tmp = this;

    if (this == parent->right && parent == g->left)
    {
        parent->RotateLeft(root);
        tmp = left;
    }
    else if (this == parent->left && parent == g->right)
    {
        parent->RotateRight(root);
        tmp = right;
    }

    tmp->InsCase5(root);
}

template<class T, class T1>
void RBT<T, T1>::Node::InsCase5(shared_ptr<Node>& root)
{
    Node* g = grandparent();

    parent->color = 1;
    g->color = 0;

    if (this == parent->left)
        g->RotateRight(root);
    else
        g->RotateLeft(root);
}

template<class T, class T1>
void RBT<T, T1>::Node::DelCase1(shared_ptr<Node>& root)
{
    if (parent)
        this->DelCase2(root);
}

template<class T, class T1>
void RBT<T, T1>::Node::DelCase2(shared_ptr<Node>& root)
{
    Node* s = sibling();

    bool scol = s ? s->color : 1;

    if (!scol)
    {
        parent->color = 0;
        s->color = 1;

        if (this == parent->left)
            parent->RotateLeft(root);
        else
            parent->RotateRight(root);
    }

    this->DelCase3(root);
}

template<class T, class T1>
void RBT<T, T1>::Node::DelCase3(shared_ptr<Node>& root)
{
    Node* s = sibling();

    bool scol = s ? s->color : 1;
    bool lcol = s && s->left ? s->left->color : 1;
    bool rcol = s && s->left ? s->left->color : 1;

    if (parent->color && scol && lcol && rcol)
    {
        if (s) s->color = 0;
        parent->DelCase1(root);
    }
    else
        this->DelCase4(root);
}

template<class T, class T1>
void RBT<T, T1>::Node::DelCase4(shared_ptr<Node>& root)
{
    Node* s = sibling();

    bool scol = s ? s->color : 1;
    bool lcol = s && s->left ? s->left->color : 1;
    bool rcol = s && s->left ? s->left->color : 1;

    if (!parent->color && scol && lcol && rcol)
    {
        if (s) s->color = 0;
        parent->color = 1;
    }
    else
        this->DelCase5(root);
}

template<class T, class T1>
void RBT<T, T1>::Node::DelCase5(shared_ptr<Node>& root)
{
    Node* s = sibling();

    bool lcol = s->left ? s->left->color : 1;
    bool rcol = s->left ? s->left->color : 1;

    if (s->color)
    {
        if (this == parent->left &&
            rcol &&
            !lcol)
        {
            s->color = 0;
            s->left->color = 1;
            s->RotateRight(root);
        }
        else if (this == parent->right &&
           lcol &&
            !rcol)
        {
            s->color = 0;
            s->right->color = 1;
            s->RotateLeft(root);
        }
    }

    this->DelCase6(root);
}

template<class T, class T1>
void RBT<T, T1>::Node::DelCase6(shared_ptr<Node>& root)
{
    Node* s = sibling();
    s->color = parent->color;
    parent->color = 1;

    if (this == parent->left)
    {
        if (s->right) s->right->color = 1;
        parent->RotateLeft(root);
    }
    else
    {
        if (s->left) s->left->color = 1;
        parent->RotateRight(root);
    }
}

template<class T, class T1>
RBT<T, T1>::iterator::iterator(weak_ptr<Node> node, weak_ptr<RBT<T, T1> > own)
{
    this->iter = node;
    owner = own;
}

template<class T, class T1>
RBT<T, T1>::iterator::iterator(const iterator& it)
{
    this->iter = it.iter;
    this->owner = it.owner;
}

template<class T, class T1>
bool RBT<T, T1>::iterator::operator!=(iterator const& other) const
{
    return owner != other.owner || iter != other.iter;
}

template<class T, class T1>
bool RBT<T, T1>::iterator::operator==(iterator const& other) const
{
    return owner != other.owner && iter == other.iter;
}

template<class T, class T1>
T1& RBT<T, T1>::iterator::operator*() const
{
    return iter->data;
}

template<class T, class T1>
typename RBT<T, T1>::iterator& RBT<T, T1>::iterator::operator++()
{
    iter = iter->next();
    return *this;
}

template<class T, class T1>
typename RBT<T, T1>::iterator& RBT<T, T1>::iterator::operator--()
{
    iter = iter->prev();
    return *this;
}

template<class T, class T1>
RBT<T, T1>::iterator_l::iterator_l(weak_ptr<Node> node, weak_ptr<RBT<T, T1> > own)
{
    this->iter = node;
    owner = own;
}

template<class T, class T1>
RBT<T, T1>::iterator_l::iterator_l(const iterator_l& it)
{
    this->iter = it.iter;
    this->owner = it.owner;
}

template<class T, class T1>
bool RBT<T, T1>::iterator_l::operator!=(iterator_l const& other) const
{
    return owner != other.owner || iter != other.iter;
}

template<class T, class T1>
bool RBT<T, T1>::iterator_l::operator==(iterator_l const& other) const
{
    return owner != other.owner && iter == other.iter;
}

template<class T, class T1>
T1& RBT<T, T1>::iterator_l::operator*() const
{
    return iter->data;
}

template<class T, class T1>
typename RBT<T, T1>::iterator_l& RBT<T, T1>::iterator_l::operator++()
{
    iter = iter->listNext;
    return *this;
}

template<class T, class T1>
typename RBT<T, T1>::iterator_l& RBT<T, T1>::iterator_l::operator--()
{
    iter = iter->listPrev;
    return *this;
}
