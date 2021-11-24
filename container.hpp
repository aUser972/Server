#pragma once
#define CONTAINER_HPP
#include <memory>
#include <initializer_list>
#include <cassert>

// container type - vector
template<typename T>
class Container
{
    T* arr;
    size_t sz;
    size_t capacity;
public:
    struct iterator {
        T* pointer;
        iterator(T* p): pointer{p} {};
        iterator(iterator&) = default;
        iterator& operator++()
        {
            ++pointer;
            return *this;
        }
        iterator operator++(int)
        {
            iterator tmp(pointer);
            ++pointer;
            return tmp;
        }
        bool operator==(iterator& it)
        {
            if(pointer == it.pointer) return true;
            return false;
        }
        bool operator!=(iterator& it)
        {
            if(pointer != it.pointer) return true;
            return false;
        }
        T& operator*()
        {
            return *pointer;
        }
        T* operator->()
        {
            return pointer;
        }
    };
    Container(size_t size = 0): sz {size}, capacity {size * 2}
    {
        std::cout << "Constructor container" << std::endl;
        void* pointer = std::aligned_alloc(alignof(T), sizeof(T)*capacity);
        arr = reinterpret_cast<T*>(pointer);
        size_t i;
        try
        {
            for (i=0; i<sz; ++i)
            {
                new (arr + i) T();
            }
        }
        catch(const std::exception& e)
        {
            std::cout << "Catch exception" << std::endl;
            std::destroy(arr, arr + i);
        }
    }
    Container(const std::initializer_list<T> &list): Container(list.size())
    {
        size_t i {0};
        for (auto &element : list)
        {
            new(arr+i)T(element);
            ++i;
        }
    }
    ~Container()
    {
        std::cout << "Destructor container" << std::endl;
        std::destroy(arr, arr+sz);
        delete[] reinterpret_cast<char*>(arr);
    }
    size_t size()
    {
        return sz;
    }
    void reserve(size_t n)
    {
        std::cout << "Reserve container" << std::endl;
        if(capacity >= n) return;
        T* newarr = reinterpret_cast<T*>(new uint8_t[ n*sizeof(T) ]);
        //placment new
        try {
            std::uninitialized_copy(arr, arr + sz, newarr);
        }
        catch(...)
        {
            delete[] reinterpret_cast<uint8_t*>(newarr);
            throw;    
        }
        // try {
        //     for(size_t i=0; i < sz; ++i)
        //     {
        //         new (newarr + i)T(arr[i]);
        //     }
        // }
        // catch(...)
        // {
        //     for(size_t j=0; j<i; ++j)
        //     {
        //         (newarr + i)->~T();
        //     }
        //     delete[] reinteret_cast<uint8_t>(newarr);
        //     throw;
        // }
        for(size_t i=0; i < sz; ++i)
        {
            std::destroy_at(arr + i);
            // (arr + i)->~T();
        }
        delete[] reinterpret_cast<uint8_t*>(arr);
        arr = newarr;
        capacity = n;
    }

    void resize(size_t n, const T& value = T())
    {
        std::cout << "Resize container" << std::endl;
        if(n > capacity) reserve(n);
        size_t i;
        try {
            for(i=sz; i<n; ++i)
            {
                new (arr + i)T(value);
                // std::uninitialized_copy(arr, arr + sz, value);
            }
        }
        catch(...)
        {
            std::destroy(arr, arr + i);
            // for(size_t j=0; j<i; ++j)
            // {
            //     (arr + j)->~T();
            // }
            throw;    
        }
        sz = n;
    }

    void push_back(const T& value)
    {
        std::cout << "Push back container" << std::endl;
        if (sz == capacity) resize(sz*2);
        // try {
        //     std::uninitialized_copy(arr);
        // }
        new (arr + sz) T(value);
        ++sz;
    }
    void pop_back() 
    {
        std::cout << "Pop back container" << std::endl;
        --sz;
        std::destroy_at(arr + sz);
        // (arr + sz)->~T();
    }
    bool empty()
    {
        if(sz>0) return false;
        return true;
    }
    T& operator[](size_t index)
    {
        assert(index >= 0 && index < sz);
        return arr[index];
    }
    iterator begin()
    {
        return iterator {arr};
    }
    iterator end()
    {
        return iterator {arr + sz};
    }
};