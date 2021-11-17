#pragma once
#define CONTAINER_HPP

// container type - vector
template<typename T>
class Container
{
    T* arr;
    size_t size;
    size_t capacity;
    Container(size_t size): size {size}, capacity {size * 2}
    {        
        arr = new T[capacity];
    }
    void reserve(size_t n)
    {
        if(capacity >= n) return;
        T* newarr = reinterpret_cast<T*>(new uint8_t[ n*sizeof(T) ]);
        //placment new
        for(size_t i; i < size; ++i)
        {
            new (newarr +i)T(arr[i]);
        }
        for(size_t i=0; i < size; ++i)
        {
            arr[i].~T();
        }
        delete[] reinterpret_cast<uint8_t*>(arr);
        arr = newarr;
        capacity = n;
    }

    void resize(size_t n)
    {        
        if(n > capacity) reserve(n);
        size = n;
    }

    void push_back(const T& value) {};
    void pop_back() {};
};