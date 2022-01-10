//#pragma once
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
    T* ptr = nullptr;
    size_t* counter = nullptr;
    

    
    template<typename U, typename... Args>
    friend shared_ptr<U> make_shared(Args&& ... args);
    
    ControlBlock<T>* cptr;
    template<typename... Args>
    shared_ptr(int s, ControlBlock<T>* storage): cptr{storage} {}
public:
    shared_ptr(T* ptr): ptr{ptr}, counter{new size_t(1)} {}
    shared_ptr(const shared_ptr& other): ptr{other.ptr}, counter{other.counter}
    {
        ++*counter;
    }
    shared_ptr(shared_ptr&& other) noexcept : ptr{other.ptr}, counter{other.counter}
    {
        other.counter == nullptr;
        other.ptr == nullptr;
    }
    ~shared_ptr()
    {
        if(*counter > 1)
        {
            --*counter;
            return;
        }
        delete ptr;
        delete counter;
    }
    shared_ptr& operator=(const shared_ptr& other)
    {
        ++*counter;
        ptr = other.ptr;
        counter = other.counter;
        return *this;
    }
    shared_ptr& operator=(shared_ptr&& other) noexcept
    {
        ptr = other.ptr;
        counter = other.counter;
        other.counter == nullptr;
        other.ptr == nullptr;
        return *this;
    }
    T* get() const noexcept
    {
        return &cptr->object;
    }
};

template<typename T, typename... Args>
shared_ptr<T>& make_shared(Args&& ... args)
{
    auto ptr = new ControlBlock<T>{1, T{ std::forward<Args>(args)... }};
    return shared_ptr<T>(shared_ptr_t(), ptr);
}

int main()
{
    auto a = make_shared<std::string>("Hello");
    std::cout << *a.get() << std::endl;
}