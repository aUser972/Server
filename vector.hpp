#pragma once
#define VECTOR_HPP
#include <cassert>
#include <initializer_list>
#include <memory>

// Vector type - vector
template<typename T, class Allocator = std::allocator<T>> class Vector
{
  T* arr;
  size_t sz { 0 };
  size_t cap { 0 };
  Allocator allocator;

public:
  struct iterator
  {
    T* pointer;    
    iterator(T* p)
        : pointer { p } {};
    iterator(const iterator&) = default;
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
    bool operator==(const iterator& it)
    {
      if (pointer == it.pointer) return true;
      return false;
    }
    bool operator!=(const iterator& it)
    {
      if (pointer != it.pointer) return true;
      return false;
    }
    T& operator*() { return *pointer; }
    T* operator->() { return pointer; }
  };
  Vector(size_t size = 0)
      : sz { size }
      , cap { size * 2 }
  {
    // std::cout << "Constructor Vector" << std::endl;
    arr = allocator.allocate(sizeof(T) * cap);
    // void* pointer = std::aligned_alloc(alignof(T), sizeof(T) * cap);
    // arr           = reinterpret_cast<T*>(pointer);
    size_t i;
    try
    {
      for (i = 0; i < sz; ++i) { allocator.construct(arr + i, T()); }
      // for (i = 0; i < sz; ++i) { new (arr + i) T(); }
    }
    catch (const std::exception& e)
    {
      for (size_t j = 0; j < i; ++j) { allocator.destroy(arr + j); }
      // std::cout << "Catch exception" << std::endl;
      // std::destroy(arr, arr + i);
    }
  }
  Vector(const std::initializer_list<T>& list)
      : Vector(list.size())
  {
    size_t i { 0 };
    for (auto& element : list)
    {
      allocator.construct(arr + i, element);
      // new (arr + i) T(element);
      ++i;
    }
  }
  Vector(const Vector& v)
      : sz { v.sz }
      , cap { v.cap }
  {
    arr = allocator.allocate(sizeof(T) * cap);
    // void* pointer = std::aligned_alloc(alignof(T), sizeof(T) * cap);
    // arr           = reinterpret_cast<T*>(pointer);
    // Replace this for call constructor
    try
    {
      std::uninitialized_copy(v.arr, v.arr + v.sz, arr);
    }
    catch (...)
    {
      allocator.deallocate(arr, sizeof(T) * cap);
      // delete[] reinterpret_cast<uint8_t*>(arr);
      throw;
    }
  }
  Vector(Vector&& tmp)
      : arr { tmp.arr }
      , sz { tmp.sz }
      , cap { tmp.cap }
  {
    tmp.arr = nullptr;
    tmp.cap = tmp.sz = 0;
  }
  Vector& operator=(Vector&& tmp)
  {
    if (&tmp == this) return *this;
    // std::destroy(arr, arr + sz);
    for (size_t i = 0; i < sz; ++i) { allocator.destroy(arr); }
    // delete[] reinterpret_cast<uint8_t*>(arr);
    allocator.deallocate(arr, cap);
    arr     = tmp.arr;
    sz      = tmp.sz;
    cap     = tmp.cap;
    tmp.arr = nullptr;
    tmp.cap = tmp.sz = 0;
    return *this;
  }
  Vector& operator=(const Vector& cp)
  {
    if (cp.arr == arr) return *this;
    // Call Destructor for all current object and delete memory array
    // std::destroy(arr, arr + sz);
    for (size_t i = 0; i < sz; ++i) { allocator.destroy(arr); }
    // delete[] reinterpret_cast<uint8_t*>(arr);
    allocator.deallocate(arr, cap);
    // void* pointer = std::aligned_alloc(alignof(T), sizeof(T) * cp.cap);
    // arr           = reinterpret_cast<T*>(pointer);
    arr = allocator.allocate(cp.cap);
    try
    {
      std::uninitialized_copy(cp.arr, cp.arr + sz, arr);
    }
    catch (...)
    {
      // delete[] reinterpret_cast<uint8_t*>(arr);
      allocator.deallocate(arr, cap);
      throw;
    }
    cap = cp.cap;
    sz  = cp.sz;
    return *this;
  }
  ~Vector()
  {
    // std::cout << "Destructor Vector" << std::endl;
    // std::destroy(arr, arr + sz);
    for (size_t i = 0; i < sz; ++i) { allocator.destroy(arr + i); }
    // delete[] reinterpret_cast<uint8_t*>(arr);
    allocator.deallocate(arr, cap);
  }
  size_t size() const { return sz; }
  size_t capacity() const { return cap; }
  void reserve(size_t n)
  {
    // std::cout << "Reserve Vector" << std::endl;
    if (cap >= n) return;
    // T* newarr = reinterpret_cast<T*>(new uint8_t[n * sizeof(T)]);
    T* newarr = allocator.allocate(n);
    // placment new
    try
    {
      std::uninitialized_copy(arr, arr + sz, newarr);
    }
    catch (...)
    {
      allocator.deallocate(newarr, n);
      // delete[] reinterpret_cast<uint8_t*>(newarr);
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
    for (size_t i = 0; i < sz; ++i)
    {
      allocator.destroy(arr + i);
      // std::destroy_at(arr + i);
      // (arr + i)->~T();
    }
    allocator.deallocate(arr, cap);
    // delete[] reinterpret_cast<uint8_t*>(arr);
    arr = newarr;
    cap = n;
  }

  void resize(size_t n, const T& value = T())
  {
    // std::cout << "Resize Vector" << std::endl;
    if (n > cap) reserve(n);
    size_t i;
    try
    {
      for (i = sz; i < n; ++i)
      {
        allocator.construct(arr + i, value);
        // new (arr + i) T(value);
        // std::uninitialized_copy(arr, arr + sz, value);
      }
    }
    catch (...)
    {
      // std::destroy(arr, arr + i);
      for (size_t j = 0; j < i; ++j) { allocator.destroy(arr + j); }
      // for(size_t j=0; j<i; ++j)
      // {
      //     (arr + j)->~T();
      // }
      throw;
    }
  }

  void push_back(const T& value)
  {
    // std::cout << "Push back Vector" << std::endl;
    if (sz == cap)
    {
      if (sz == 0) reserve(1);
      reserve(sz * 2);
    }
    // try {
    //     std::uninitialized_copy(arr);
    // }

    // new (arr + sz) T(value);
    allocator.construct(arr + sz, value);
    ++sz;
  }
  void pop_back()
  {
    // std::cout << "Pop back Vector" << std::endl;
    --sz;
    allocator.destroy(arr + sz);
    // std::destroy_at(arr + sz);
    // (arr + sz)->~T();
  }
  bool empty()
  {
    if (sz > 0) return false;
    return true;
  }
  T& operator[](size_t index) const
  {
    // assert(index >= 0 && index < sz);
    return arr[index];
  }
  T& at(size_t index) const
  {
    if (index <= 0 && index > sz)
      throw std::out_of_range("Vector out of range");
    return arr[index];
  }
  iterator begin() const { return iterator { arr }; }
  iterator end() const { return iterator { arr + sz }; }
};
