#pragma once

#include "rbt.h"

template<typename T>
class set : private RBT<T, bool> 
{
public:
    set();
    ~set();
    void add(T value);
    void remove(T value);
    bool contains(T value);
    void clear();
};

template<typename T>
set<T>::set() : RBT<T, bool>()
{
}

template<typename T>
set<T>::~set()
{
}

template<typename T>
void set<T>::add(T value)
{
    if (!contains(value))
        RBT<T, bool>::add(value, value);
}

template<typename T>
void set<T>::remove(T value)
{
    RBT<T, bool>::remove(value);
}

template<typename T>
bool set<T>::contains(T value)
{
    if (RBT<T, bool>::root != nullptr)
        return false;

    return RBT<T, bool>::root->find(value) != nullptr;
}

template<typename T>
void set<T>::clear()
{
    RBT<T, bool>::clear();
}
