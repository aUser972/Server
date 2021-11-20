#pragma once
#define CONTAINER_HPP

// container type - vector
template<typename T>
class Container
{
    T* arr;
    size_t size;
    size_t capacity;
    Container(size_t size, T value = T()): size {size}, capacity {size * 2}
    {        
        arr = new T[capacity];
    }
    void reserve(size_t n)
    {
        if(capacity >= n) return;
        T* newarr = reinterpret_cast<T*>(new uint8_t[ n*sizeof(T) ]);
        //placment new
        try {
            std::uninitialized_copy(arr, arr + size, newarr);
        }
        catch(...)
        {
            delete[] reinteret_cast<uint8_t>(newarr);
            throw;    
        }
        // try {
        //     for(size_t i; i < size; ++i)
        //     {
        //         new (newarr + i)T(arr[i]);
        //     }
        // }
        // catch(...)
        // {
        //     for(size_t j=0; j<i; ++qj)
        //     {
        //         (newarr + i)->~T();
        //     }
        //     delete[] reinteret_cast<uint8_t>(newarr);
        //     throw;
        // }
        for(size_t i=0; i < size; ++i)
        {
            (arr + i)->~T();
        }
        delete[] reinterpret_cast<uint8_t*>(arr);
        arr = newarr;
        capacity = n;
    }

    void resize(size_t n, const T& value = T())
    {        
        if(n > capacity) reserve(n);
        size = n;

        try {
            std::uninitialized_copy(arr, arr + size, newarr);
        }
        catch(...)
        {
            delete[] reinteret_cast<uint8_t>(newarr);
            throw;    
        }

        // insert default data
    }

    void push_back(const T& value)
    {
        if (size == capacity) resize(size*2);
        new (arr + size) T(value);
        ++size;        
    }
    void pop_back() 
    {
        --size;
        (arr + size)->~T();
    }
};