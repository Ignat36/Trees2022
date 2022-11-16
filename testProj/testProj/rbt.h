#pragma once
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
        Node* left, * right, * parent;
        Node* listNext, * listPrev;
        bool color;
        T key;
        T1 data;

        Node* grandparent();
        Node* uncle();
        Node* sibling();

        void RotateLeft(Node*& root);
        void RotateRight(Node*& root);

        void InsCase1(Node*& root);
        void InsCase2(Node*& root);
        void InsCase3(Node*& root);
        void InsCase4(Node*& root);
        void InsCase5(Node*& root);

        void DelCase1(Node*& root);
        void DelCase2(Node*& root);
        void DelCase3(Node*& root);
        void DelCase4(Node*& root);
        void DelCase5(Node*& root);
        void DelCase6(Node*& root);

        Node* find(T key);
        Node* next();
        Node* prev();

        Node* min();
        Node* max();

    } *root, *_end;

public:
    class iterator
    {
    public:
        iterator(Node* node, RBT<T, T1>* own);
        iterator(const iterator& it);
        bool operator!=(iterator const& other) const;
        bool operator==(iterator const& other) const;
        T1& operator*() const;
        iterator& operator++();
        iterator& operator--();

    private:
        Node* iter;
        RBT<T, T1>* owner;
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
        iterator_l(Node* node, RBT<T, T1>* own);
        iterator_l(const iterator_l& it);
        bool operator!=(iterator_l const& other) const;
        bool operator==(iterator_l const& other) const;
        T1& operator*() const;
        iterator_l& operator++();
        iterator_l& operator--();

    private:
        Node* iter;
        RBT<T, T1>* owner;
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
{
    root = nullptr;
    _end = new Node();
}

template<class T, class T1>
void RBT<T, T1>::clear()
{
    std::vector< Node* > stack;

    stack.push_back(root);

    while (!stack.empty())
    {
        Node* tmp = stack.back();
        stack.pop_back();

        if (!tmp) continue;
        stack.push_back(tmp->left);
        stack.push_back(tmp->right);

        delete tmp;
    }

    root = nullptr;
}

template<class T, class T1>
RBT<T, T1>::~RBT()
{
    clear();
    delete _end;
}

template<class T, class T1>
T1& RBT<T, T1>::operator[](T key)
{
    if (root) root->parent = nullptr;
    Node* tmp = root, * p = nullptr;

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
        tmp = new Node();
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
        Node* nx = tmp->next();
        Node* pr = tmp->prev();


        tmp->listPrev = pr; pr->listNext = tmp;
        tmp->listNext = nx; nx->listPrev = tmp;
        if (root) root->parent = nullptr;
        ///////////////////////////////////////
        
    }

    if (root) root->parent = _end;
    return tmp->data;
}

template<class T, class T1>
void RBT<T, T1>::add(T key, T1 value)
{
    if (root) root->parent = nullptr;
    Node* tmp = root, * p = nullptr;

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

    tmp = new Node(key, value);
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
    Node* nx = tmp->next();
    Node* pr = tmp->prev();


    tmp->listPrev = pr; pr->listNext = tmp;
    tmp->listNext = nx; nx->listPrev = tmp;
    if (root) root->parent = nullptr;
    ///////////////////////////////////////

    if (root) root->parent = _end;
    return;
}



template<class T, class T1>
void RBT<T, T1>::remove(T key)
{
    if (root) root->parent = nullptr;
    Node* tmp = root ? root->find(key) : nullptr;

    if (!tmp)
    {
        if (root) root->parent = _end;
        return;
    }

    if (!tmp->parent && !tmp->left && !tmp->right)
    {
        delete tmp;
        tmp = nullptr;
        if (root) root->parent = _end;
        return;
    }

    if (tmp->left && tmp->right)
    {
        Node* removed = tmp->left;
        while (removed->right)
            removed = removed->right;
        tmp->data = removed->data;
        tmp->key = removed->key;
        tmp = removed;

        ////////////////////////////////////
        // swap instead of copy
        ////////////////////////////////////
    }

    Node* child = tmp->left ? tmp->left : tmp->right;

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
    Node* nx = tmp->next();
    Node* pr = tmp->prev();


    tmp->listPrev = pr; pr->listNext = tmp;
    tmp->listNext = nx; nx->listPrev = tmp;
    if (root) root->parent = nullptr;
    /////////////////////////////////////
    delete tmp;

    if (root) root->parent = nullptr;
}

template<class T, class T1>
T1 RBT<T, T1>::findValueWithKey(T key)
{
    Node* tmp = root, * p = nullptr;

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
    return root != nullptr && root->find(key) != nullptr;
}

template<class T, class T1>
RBT<T, T1>::Node::Node(T nKey, T1 nValue)
{
    left = right = parent = nullptr;
    listNext = listPrev = nullptr;
    color = 0;
    key = nKey;
    data = nValue;
}

template<class T, class T1>
RBT<T, T1>::Node::Node()
{
    left = right = parent = nullptr;
    listNext = listPrev = nullptr;
    color = 0;
}

template<class T, class T1>
void RBT<T, T1>::Node::RotateLeft(Node*& root)
{
    Node* tmp = this->right;

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

    this->right = tmp->left;
    if (tmp->left)
        tmp->left->parent = this;

    this->parent = tmp;
    tmp->left = this;
}

template<class T, class T1>
void RBT<T, T1>::Node::RotateRight(Node*& root)
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
typename RBT<T, T1>::Node* RBT<T, T1>::Node::grandparent()
{
    if (parent && parent->parent)
        return parent->parent;
    else
        return nullptr;
}

template<class T, class T1>
typename RBT<T, T1>::Node* RBT<T, T1>::Node::uncle()
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
typename RBT<T, T1>::Node* RBT<T, T1>::Node::sibling()
{
    if (!parent) return nullptr;

    if (this == parent->left)
        return parent->right;
    else
        return parent->left;
}

template<class T, class T1>
typename RBT<T, T1>::Node* RBT<T, T1>::Node::find(T key)
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
typename RBT<T, T1>::Node* RBT<T, T1>::Node::next()
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
typename RBT<T, T1>::Node* RBT<T, T1>::Node::prev()
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
typename RBT<T, T1>::Node* RBT<T, T1>::Node::min()
{
    Node* tmp = this;
    while (tmp->left) tmp = tmp->left;
    return tmp;
}

template<class T, class T1>
typename RBT<T, T1>::Node* RBT<T, T1>::Node::max()
{
    Node* tmp = this;
    while (tmp->right) tmp = tmp->right;
    return tmp;
}

template<class T, class T1>
void RBT<T, T1>::Node::InsCase1(Node*& root)
{
    if (parent == nullptr)
        color = 1;
    else
        this->InsCase2(root);
}

template<class T, class T1>
void RBT<T, T1>::Node::InsCase2(Node*& root)
{
    if (parent->color)
        return;
    else this->InsCase3(root);
}

template<class T, class T1>
void RBT<T, T1>::Node::InsCase3(Node*& root)
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
void RBT<T, T1>::Node::InsCase4(Node*& root)
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
void RBT<T, T1>::Node::InsCase5(Node*& root)
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
void RBT<T, T1>::Node::DelCase1(Node*& root)
{
    if (parent)
        this->DelCase2(root);
}

template<class T, class T1>
void RBT<T, T1>::Node::DelCase2(Node*& root)
{
    Node* s = sibling();

    if (!s->color)
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
void RBT<T, T1>::Node::DelCase3(Node*& root)
{
    Node* s = sibling();

   /* bool lcol = s->left ? s->left->color : 1;
    bool rcol = s->left ? s->left->color : 1;*/

    if (parent->color && s->color && s->left->color && s->right->color)
    {
        s->color = 0;
        s->DelCase1(root);
    }
    else
        this->DelCase4(root);
}

template<class T, class T1>
void RBT<T, T1>::Node::DelCase4(Node*& root)
{
    Node* s = sibling();

    if (!parent->color && s->color && s->left->color && s->right->color)
    {
        s->color = 0;
        parent->color = 1;
    }
    else
        this->DelCase5(root);
}

template<class T, class T1>
void RBT<T, T1>::Node::DelCase5(Node*& root)
{
    Node* s = sibling();

    if (s->color)
    {
        if (this == parent->left &&
            s->right->color &&
            !s->left->color)
        {
            s->color = 0;
            s->left->color = 1;
            s->RotateRight(root);
        }
        else if (this == parent->right &&
            s->left->color &&
            !s->right->color)
        {
            s->color = 0;
            s->right->color = 1;
            s->RotateLeft(root);
        }
    }

    this->DelCase6(root);
}

template<class T, class T1>
void RBT<T, T1>::Node::DelCase6(Node*& root)
{
    Node* s = sibling();
    s->color = parent->color;
    parent->color = 1;

    if (this == parent->left)
    {
        s->right->color = 1;
        parent->RotateLeft(root);
    }
    else
    {
        s->left->color = 1;
        parent->RotateRight(root);
    }
}

template<class T, class T1>
RBT<T, T1>::iterator::iterator(Node* node, RBT<T, T1>* own)
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
RBT<T, T1>::iterator_l::iterator_l(Node* node, RBT<T, T1>* own)
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
