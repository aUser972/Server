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
        try {
            for(size_t i; i < size; ++i)
            {
                new (newarr + i)T(arr[i]);
            }
        }
        catch(...)
        {
            for(size_t j=i-1; j >=0; --j)
            {
                (newarr + i)->~T();
            }
            delete[] reinteret_cast<uint8_t>(newarr);
            throw;
        }
        for(size_t i=0; i < size; ++i)
        {
            (arr + i)->~T();
        }
        delete[] reinterpret_cast<uint8_t*>(arr);
        arr = newarr;
        capacity = n;
    }

    void resize(size_t n, T value = T())
    {        
        if(n > capacity) reserve(n);
        size = n;

        // insert default data
    }

    void push_back(const T& value)
    {
        if (size >= capacity) resize(size*2);
        try {
            new (arr + size) value;
        }
        catch(...)
        {
            // Shoud I do something?
            throw;
        }
        ++size;        
    }
    void pop_back() {};
};