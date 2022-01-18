#pragma once
#include <iostream>
#include <string>

template<typename T>
class shared_ptr
{
private:
    template<typename U>
    struct ControlBlock
    {
        size_t counter;
        U object;
        ControlBlock() = default;
    };
    ControlBlock<T>* cptr;
    struct shared_ptr_t {};
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
    explicit operator bool() const noexcept
    {
        return true;
    }
    T& operator*() const noexcept
    {
        return cptr->object;
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
    auto ptr = new typename shared_ptr<T>::template ControlBlock<T>{1, T{ std::forward<Args>(args)... }};
    return shared_ptr<T>(typename shared_ptr<T>::shared_ptr_t(), ptr);
}