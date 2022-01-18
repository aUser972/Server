#pragma once
#include "shared_ptr.hpp"

template<typename T>
class weak_ptr
{
    T* ptr = nullptr;
public:
    weak_ptr() = default;
    template<typename Y>
    weak_ptr(const shared_ptr<Y>& shared) noexcept : ptr { shared.get() } {}
    shared_ptr<T> lock() const noexcept
    { 
        return shared_ptr<T>(ptr);
        
    }
};
