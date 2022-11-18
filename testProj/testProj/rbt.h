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

    struct Node
    {
        Node(T nKey, T1 nValue);
        Node();
        shared_ptr<Node> left, right;
        weak_ptr<Node> parent;
        weak_ptr<Node> listNext, listPrev;
        bool color;
        T key;
        T1 data;
    };

    shared_ptr<Node> grandparent(shared_ptr<Node> node);
    shared_ptr<Node> uncle(shared_ptr<Node> node);
    shared_ptr<Node> sibling(shared_ptr<Node> node);

    void RotateLeft(shared_ptr<Node> node);
    void RotateRight(shared_ptr<Node> node);

    void InsCase1(shared_ptr<Node> node);
    void InsCase2(shared_ptr<Node> node);
    void InsCase3(shared_ptr<Node> node);
    void InsCase4(shared_ptr<Node> node);
    void InsCase5(shared_ptr<Node> node);

    void DelCase1(shared_ptr<Node> node);
    void DelCase2(shared_ptr<Node> node);
    void DelCase3(shared_ptr<Node> node);
    void DelCase4(shared_ptr<Node> node);
    void DelCase5(shared_ptr<Node> node);
    void DelCase6(shared_ptr<Node> node);

    shared_ptr<Node> find(shared_ptr<Node> node, T key);
    shared_ptr<Node> next(shared_ptr<Node> node);
    shared_ptr<Node> prev(shared_ptr<Node> node);

    shared_ptr<Node> min(shared_ptr<Node> node);
    shared_ptr<Node> max(shared_ptr<Node> node);
   
protected:
    shared_ptr<Node> root, _end;

public:
    class iterator
    {
    public:
        iterator(shared_ptr<Node> node, RBT<T, T1>* own);
        iterator(const iterator& it);
        bool operator!=(iterator const& other) const;
        bool operator==(iterator const& other) const;
        T1& operator*() const;
        iterator& operator++();
        iterator& operator--();

    private:
        shared_ptr<Node> iter;
        RBT<T, T1>* owner;
    };

    iterator begin()
    {
        return iterator(min(root), this);
    }

    iterator end()
    {
        return iterator(_end, this);
    }

    class iterator_l
    {
    public:
        iterator_l(shared_ptr<Node> node, RBT<T, T1>* own);
        iterator_l(const iterator_l& it);
        bool operator!=(iterator_l const& other) const;
        bool operator==(iterator_l const& other) const;
        T1& operator*() const;
        iterator_l& operator++();
        iterator_l& operator--();

    private:
        shared_ptr<Node> iter;
        RBT<T, T1>* owner;
    };

    iterator_l begin_l()
    {
        return iterator_l(min(root), this);
    }

    iterator_l end_l()
    {
        return iterator_l(_end, this);
    }
};

template<class T, class T1>
RBT<T, T1>::RBT()
{
    root = shared_ptr<Node>();
    _end = shared_ptr<Node>(new Node());
    _end->listNext = _end;
    _end->listPrev = _end;
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
    if (root) root->parent = shared_ptr<Node>();
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

        InsCase1(tmp);

        
        ///////////////////////////////////////
        if (root) root->parent = _end;
        shared_ptr<Node> nx = next(tmp);
        shared_ptr<Node> pr = prev(tmp);


        tmp->listPrev = pr; pr->listNext = tmp;
        tmp->listNext = nx; nx->listPrev = tmp;
        if (root) root->parent = shared_ptr<Node>();
        ///////////////////////////////////////
        
    }

    if (root) root->parent = _end;
    return tmp->data;
}

template<class T, class T1>
void RBT<T, T1>::add(T key, T1 value)
{
    if (root) root->parent = shared_ptr<Node>();
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

    InsCase1(tmp);

    ////////////////////////////////////////
    if (root) root->parent = _end;
    shared_ptr<Node> nx = next(tmp);
    shared_ptr<Node> pr = prev(tmp);


    tmp->listPrev = pr; pr->listNext = tmp;
    tmp->listNext = nx; nx->listPrev = tmp;
    if (root) root->parent = shared_ptr<Node>();
    ///////////////////////////////////////

    if (root) root->parent = _end;
    return;
}



template<class T, class T1>
void RBT<T, T1>::remove(T key)
{
    if (root) root->parent = shared_ptr<Node>();
    shared_ptr<Node> tmp = root ? find(root, key) : shared_ptr<Node>();

    if (!tmp)
    {
        if (root) root->parent = _end;
        return;
    }

    if (!tmp->parent && !tmp->left && !tmp->right)
    {
        root = shared_ptr<Node>();
        if (root) root->parent = _end;
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

    ////////////////////////////////////
    if (root) root->parent = _end;
    shared_ptr<Node> nx = next(tmp);
    shared_ptr<Node> pr = prev(tmp);


    pr->listNext = nx;
    nx->listPrev = pr;
    if (root) root->parent = shared_ptr<Node>();
    /////////////////////////////////////

    shared_ptr<Node> child = tmp->left ? tmp->left : tmp->right;

    if (!child)
    {
        if (tmp->color)
            DelCase1(tmp);

        shared_ptr<Node> p = tmp->parent;

        if (p->left.equals(tmp))
            p->left = child;
        else
            p->right = child;
    }
    else
    {
        child->parent = tmp->parent;
        shared_ptr<Node> p = tmp->parent;

        if (tmp->parent)
        {
            if (tmp.equals(p->left))
                p->left = child;
            else
                p->right = child;
        }
        else
            root = child;

        if (tmp->color)
        {
            if (!child->color)
                child->color = 1;
            else
                DelCase1(child);
        }
    }

    if (root) root->parent = _end;
}

template<class T, class T1>
T1 RBT<T, T1>::findValueWithKey(T key)
{
    shared_ptr<Node> tmp = root, p = shared_ptr<Node>();

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
    return root && find(root, key) ;
}

template<class T, class T1>
RBT<T, T1>::Node::Node(T nKey, T1 nValue)
{
    left = right = parent = shared_ptr<Node>();
    listNext = listPrev = shared_ptr<Node>();
    color = 0;
    key = nKey;
    data = nValue;
}

template<class T, class T1>
RBT<T, T1>::Node::Node()
{
    left = right = parent = shared_ptr<Node>();
    listNext = listPrev = shared_ptr<Node>();
    color = 0;
}

template<class T, class T1>
void RBT<T, T1>::RotateLeft(shared_ptr<Node> node)
{
    shared_ptr<Node> tmp = node->right;

    tmp->parent = node->parent;
    if (node->parent)
    {
        shared_ptr<Node> p = node->parent;

        if (p->left.equals(node))
            p->left = tmp;
        else
            p->right = tmp;
    }
    else
        root = tmp;

    node->right = tmp->left;
    if (tmp->left)
        tmp->left->parent = node;

    node->parent = tmp;
    tmp->left = node;
}

template<class T, class T1>
void RBT<T, T1>::RotateRight(shared_ptr<Node> node)
{
    shared_ptr<Node> tmp = node->left;

    tmp->parent = node->parent;
    if (node->parent)
    {
        shared_ptr<Node> p = node->parent;

        if (p->left.equals(node))
            p->left = tmp;
        else
            p->right = tmp;
    }
    else
        root = tmp;

    node->left = tmp->right;
    if (tmp->right)
        tmp->right->parent = node;

    node->parent = tmp;
    tmp->right = node;
}

template<class T, class T1>
shared_ptr<typename RBT<T, T1>::Node> RBT<T, T1>::grandparent(shared_ptr<Node> node)
{
    shared_ptr<Node> p = node->parent;
    if (p && p->parent)
        return p->parent;
    else
        return shared_ptr<Node>();
}

template<class T, class T1>
shared_ptr<typename RBT<T, T1>::Node> RBT<T, T1>::uncle(shared_ptr<Node> node)
{
    shared_ptr<Node> tmp = grandparent(node);

    if (tmp)
    {
        if (tmp->left.equals(node->parent))
            return tmp->right;
        else
            return tmp->left;
    }
    else
        return shared_ptr<Node>();
}

template<class T, class T1>
shared_ptr<typename RBT<T, T1>::Node> RBT<T, T1>::sibling(shared_ptr<Node> node)
{
    if (!node->parent) return shared_ptr<Node>();

    shared_ptr<Node> p = node->parent;

    if (node.equals(p->left))
        return p->right;
    else
        return p->left;
}

template<class T, class T1>
shared_ptr<typename RBT<T, T1>::Node> RBT<T, T1>::find(shared_ptr<Node> node, T key)
{

    shared_ptr<Node> tmp = node;

    while (tmp && tmp->key != key)
        if (tmp->key > key)
            tmp = tmp->left;
        else
            tmp = tmp->right;

    return tmp;
}

template<class T, class T1>
shared_ptr<typename RBT<T, T1>::Node> RBT<T, T1>::next(shared_ptr<Node> node)
{
    shared_ptr<Node> tmp = node->right;

    if (tmp)
    {
        while (tmp->left) tmp = tmp->left;
        return tmp;
    }

    tmp = node;
    while (tmp->parent && tmp.equals(tmp->parent.lock()->right)) tmp = tmp->parent;

    return tmp->parent ? tmp->parent.lock() : node;
}

template<class T, class T1>
shared_ptr<typename RBT<T, T1>::Node> RBT<T, T1>::prev(shared_ptr<Node> node)
{
    shared_ptr<Node> tmp = node->left;
    if (tmp)
    {
        while (tmp->right) tmp = tmp->right;
        return tmp;
    }

    tmp = node;
    while (tmp->parent && tmp.equals(tmp->parent.lock()->left)) tmp = tmp->parent;

    return tmp->parent ? tmp->parent.lock() : node;
}

template<class T, class T1>
shared_ptr<typename RBT<T, T1>::Node> RBT<T, T1>::min(shared_ptr<Node> node)
{
    if (!node)
        return _end;

    shared_ptr<Node> tmp = node;
    while (tmp->left) tmp = tmp->left;
    return tmp;
}

template<class T, class T1>
shared_ptr<typename RBT<T, T1>::Node> RBT<T, T1>::max(shared_ptr<Node> node)
{
    Node* tmp = node;
    while (tmp->right) tmp = tmp->right;
    return tmp;
}

template<class T, class T1>
void RBT<T, T1>::InsCase1(shared_ptr<Node> node)
{
    if (!node->parent)
        node->color = 1;
    else
        InsCase2(node);
}

template<class T, class T1>
void RBT<T, T1>::InsCase2(shared_ptr<Node> node)
{
    if (node->parent.lock()->color)
        return;
    else InsCase3(node);
}

template<class T, class T1>
void RBT<T, T1>::InsCase3(shared_ptr<Node> node)
{
    shared_ptr<Node> u = uncle(node);

    if (u && !u->color)
    {
        node->parent.lock()->color = 1;
        u->color = 1;
        shared_ptr<Node> g = grandparent(node);
        g->color = 0;
        InsCase1(g);
    }
    else
        InsCase4(node);
}

template<class T, class T1>
void RBT<T, T1>::InsCase4(shared_ptr<Node> node)
{
    shared_ptr<Node> g = grandparent(node), tmp = node;
    shared_ptr<Node> p = node->parent;
    if (node.equals(p->right) && p.equals(g->left))
    {
        RotateLeft(p);
        tmp = node->left;
    }
    else if (node.equals(p->left) && p.equals(g->right))
    {
        RotateRight(p);
        tmp = node->right;
    }

    InsCase5(tmp);
}

template<class T, class T1>
void RBT<T, T1>::InsCase5(shared_ptr<Node> node)
{
    shared_ptr<Node> g = grandparent(node);
    shared_ptr<Node> p = node->parent;
    p->color = 1;
    g->color = 0;

    if (node.equals(p->left))
        RotateRight(g);
    else
        RotateLeft(g);
}

template<class T, class T1>
void RBT<T, T1>::DelCase1(shared_ptr<Node> node)
{
    if (node->parent)
        DelCase2(node);
}

template<class T, class T1>
void RBT<T, T1>::DelCase2(shared_ptr<Node> node)
{
    shared_ptr<Node> s = sibling(node);
    shared_ptr<Node> p = node->parent;
    bool scol = s ? s->color : 1;

    if (!scol)
    {
        p->color = 0;
        s->color = 1;

        if (node.equals(p->left))
            RotateLeft(p);
        else
            RotateRight(p);
    }

    DelCase3(node);
}

template<class T, class T1>
void RBT<T, T1>::DelCase3(shared_ptr<Node> node)
{
    shared_ptr<Node> s = sibling(node);
    shared_ptr<Node> p = node->parent;

    bool scol = s ? s->color : 1;
    bool lcol = s && s->left ? s->left->color : 1;
    bool rcol = s && s->right ? s->right->color : 1;

    if (p->color && scol && lcol && rcol)
    {
        if (s) s->color = 0;
        DelCase1(p);
    }
    else
        DelCase4(node);
}

template<class T, class T1>
void RBT<T, T1>::DelCase4(shared_ptr<Node> node)
{
    shared_ptr<Node> s = sibling(node);
    shared_ptr<Node> p = node->parent;

    bool scol = s ? s->color : 1;
    bool lcol = s && s->left ? s->left->color : 1;
    bool rcol = s && s->right ? s->right->color : 1;

    if (!p->color && scol && lcol && rcol)
    {
        if (s) s->color = 0;
        p->color = 1;
    }
    else
        DelCase5(node);
}

template<class T, class T1>
void RBT<T, T1>::DelCase5(shared_ptr<Node> node)
{
    shared_ptr<Node> s = sibling(node);
    shared_ptr<Node> p = node->parent;

    bool lcol = s->left ? s->left->color : 1;
    bool rcol = s->right ? s->right->color : 1;

    if (s->color)
    {
        if (node.equals(p->left) &&
            rcol &&
            !lcol)
        {
            s->color = 0;
            s->left->color = 1;
            RotateRight(s);
        }
        else if (node.equals(p->right) &&
           lcol &&
            !rcol)
        {
            s->color = 0;
            s->right->color = 1;
            RotateLeft(s);
        }
    }

    DelCase6(node);
}

template<class T, class T1>
void RBT<T, T1>::DelCase6(shared_ptr<Node> node)
{
    shared_ptr<Node>  s = sibling(node);
    shared_ptr<Node> p = node->parent;
    s->color = p->color;
    p->color = 1;

    if (node.equals(p->left))
    {
        if (s->right) s->right->color = 1;
        RotateLeft(p);
    }
    else
    {
        if (s->left) s->left->color = 1;
        RotateRight(p);
    }
}

template<class T, class T1>
RBT<T, T1>::iterator::iterator(shared_ptr<Node> node, RBT<T, T1>* own)
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
    return owner != other.owner || !iter.equals(other.iter);
}

template<class T, class T1>
bool RBT<T, T1>::iterator::operator==(iterator const& other) const
{
    return owner != other.owner && iter.equals(other.iter);
}

template<class T, class T1>
T1& RBT<T, T1>::iterator::operator*() const
{
    return iter->data;
}

template<class T, class T1>
typename RBT<T, T1>::iterator& RBT<T, T1>::iterator::operator++()
{
    iter = owner->next(iter);
    return *this;
}

template<class T, class T1>
typename RBT<T, T1>::iterator& RBT<T, T1>::iterator::operator--()
{
    iter = owner->prev(iter);
    return *this;
}

template<class T, class T1>
RBT<T, T1>::iterator_l::iterator_l(shared_ptr<Node> node, RBT<T, T1>* own)
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
    return owner != other.owner || !iter.equals(other.iter);
}

template<class T, class T1>
bool RBT<T, T1>::iterator_l::operator==(iterator_l const& other) const
{
    return owner != other.owner && iter.equals(other.iter);
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
