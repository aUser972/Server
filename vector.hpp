#pragma once
#define VECTOR_HPP
#include <cassert>
#include <initializer_list>
#include <memory>

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
    arr = allocator.allocate(sizeof(T) * cap);
    size_t i;
  }
  Vector(const std::initializer_list<T>& list)
      : Vector(list.size())
  {
    size_t i { 0 };
    for (auto& element : list)
    {
      allocator.construct(arr + i, element);
      ++i;
    }
  }
  Vector(const Vector& v)
      : sz { v.sz }
      , cap { v.cap }
  {
    arr = allocator.allocate(sizeof(T) * cap);
    try
    {
      std::uninitialized_copy(v.arr, v.arr + v.sz, arr);
    }
    catch (...)
    {
      allocator.deallocate(arr, sizeof(T) * cap);
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
    for (size_t i = 0; i < sz; ++i) { allocator.destroy(arr); }
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
    for (size_t i = 0; i < sz; ++i) { allocator.destroy(arr); }
    allocator.deallocate(arr, cap);
    arr = allocator.allocate(cp.cap);
    try
    {
      std::uninitialized_copy(cp.arr, cp.arr + sz, arr);
    }
    catch (...)
    {
      allocator.deallocate(arr, cap);
      throw;
    }
    cap = cp.cap;
    sz  = cp.sz;
    return *this;
  }
  ~Vector()
  {
    for (size_t i = 0; i < sz; ++i) { allocator.destroy(arr + i); }
    allocator.deallocate(arr, cap);
  }
  size_t size() const { return sz; }
  size_t capacity() const { return cap; }
  void reserve(size_t n)
  {
    if (cap >= n) return;
    T* newarr = allocator.allocate(n);
    try
    {
      std::uninitialized_copy(arr, arr + sz, newarr);
    }
    catch (...)
    {
      allocator.deallocate(newarr, n);
      throw;
    }
    for (size_t i = 0; i < sz; ++i)
    {
      allocator.destroy(arr + i);
    }
    allocator.deallocate(arr, cap);
    arr = newarr;
    cap = n;
  }

  void resize(size_t n, const T& value = T())
  {
    if (n > cap) reserve(n);
    size_t i;
    try
    {
      for (i = sz; i < n; ++i)
      {
        allocator.construct(arr + i, value);
      }
    }
    catch (...)
    {
      for (size_t j = 0; j < i; ++j) { allocator.destroy(arr + j); }
      throw;
    }
  }

  template<typename... Arg>
  T& emplace_back(Arg&&... args)
  {
    if (sz == cap)
    {
      if (sz == 0) reserve(1);
      else reserve(sz * 2);
    }
    allocator.construct(arr + sz, std::forward<Arg>(args)...);
    ++sz;
    return *reinterpret_cast<T*>(arr + sz);
  }

  void push_back(const T& value)
  {
    if (sz == cap)
    {
      if (sz == 0) reserve(1);
      else reserve(sz * 2);
    }
    allocator.construct(arr + sz, value);
    ++sz;
  }
  void pop_back()
  {
    --sz;
    allocator.destroy(arr + sz);
  }
  bool empty()
  {
    if (sz > 0) return false;
    return true;
  }
  T& operator[](size_t index) const
  {
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
