#pragma once
#include <iostream>
#include <string>

template<typename U>
struct ControlBlock
{        
    size_t counter;
    U object;
    ControlBlock() = default;
};

struct shared_ptr_t {};

template<typename T>
class shared_ptr
{
private:
    // T* ptr = nullptr;
    // size_t* counter = nullptr;
    
    ControlBlock<T>* cptr;

    template<typename U, typename... Args>
    friend shared_ptr<U> make_shared(Args&& ... args);

    template<typename... Args>
    shared_ptr(shared_ptr_t s, ControlBlock<T>* storage): cptr{storage} {}
public:
    shared_ptr(T* ptr) 
    {
        cptr = new ControlBlock<T>{1, std::forward<T>(*ptr)};
    }
    shared_ptr(const shared_ptr& other): cptr{other.cptr}
    {
        ++cptr->counter;
    }
    shared_ptr(shared_ptr&& other) noexcept : cptr{other.cptr}
    {
        other.cptr = nullptr;
    }
    ~shared_ptr()
    {
        if(cptr->counter > 1)
        {
            --cptr->counter;
            return;
        }
        delete cptr;
    }
    // shared_ptr& operator=(const shared_ptr& other)
    // {
    //     ++*counter;
    //     ptr = other.ptr;
    //     counter = other.counter;
    //     return *this;
    // }
    // shared_ptr& operator=(shared_ptr&& other) noexcept
    // {
    //     ptr = other.ptr;
    //     counter = other.counter;
    //     other.counter == nullptr;
    //     other.ptr == nullptr;
    //     return *this;
    // }
    T* get() const noexcept
    {
        return &cptr->object;
    }
};

template<typename T, typename... Args>
shared_ptr<T> make_shared(Args&& ... args)
{
    auto ptr = new ControlBlock<T>{1, T{ std::forward<Args>(args)... }};
    shared_ptr_t s;
    return shared_ptr<T>(s, ptr);
}