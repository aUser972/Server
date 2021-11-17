#pragma once
#define ITERATOR_HPP
#include <iostream>

template<typename T>
class InputIterator
{
private:
    std::istream& stream;
    T value;
public:
    InputIterator(std::istream& s): stream { s } { }
    T* operator->()
    {
        return &value; 
    }
    T& operator*() {
        return value;
    }
    InputIterator& operator++()
    {
        stream >> value;
        return *this;
    }
    bool operator==(InputIterator it)
    {
        if (*it==value) return true;
        return false;
    }
    bool operator!=(InputIterator it)
    {
        if (*it==value) return false;
        return true;
    }
};