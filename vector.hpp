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
    // arr = allocator.allocate(sizeof(T) * cap);
    arr = std::allocator_traits<Allocator>::allocate(allocator, cap);
  }
  Vector(const std::initializer_list<T>& list)
      : Vector(list.size())
  {
    size_t i { 0 };
    for (auto& element : list)
    {
      std::allocator_traits<Allocator>::construct(allocator, arr + i, element);
      ++i;
    }
  }
  Vector(const Vector& v)
      : sz { v.sz }
      , cap { v.cap }
  {
    arr = std::allocator_traits<Allocator>::allocate(allocator, cap);
    try
    {
      std::uninitialized_copy(v.arr, v.arr + v.sz, arr);
    }
    catch (...)
    {
      std::allocator_traits<Allocator>::deallocate(allocator, arr, cap);
      throw;
    }
  }
  Vector(Vector&& tmp) noexcept
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
    for (size_t i = 0; i < sz; ++i)
    {
      std::allocator_traits<Allocator>::destroy(allocator, arr + i);
    }
    std::allocator_traits<Allocator>::deallocate(allocator, arr, cap);
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
    for (size_t i = 0; i < sz; ++i)
    {
      std::allocator_traits<Allocator>::destroy(allocator, arr + i);
    }
    std::allocator_traits<Allocator>::deallocate(allocator, arr, cap);
    arr = std::allocator_traits<Allocator>::allocate(allocator, cp.cap);
    try
    {
      std::uninitialized_copy(cp.arr, cp.arr + sz, arr);
    }
    catch (...)
    {
      std::allocator_traits<Allocator>::deallocate(allocator, arr, cap);
      throw;
    }
    cap = cp.cap;
    sz  = cp.sz;
    return *this;
  }
  ~Vector()
  {
    for (size_t i = 0; i < sz; ++i)
    {
      std::allocator_traits<Allocator>::destroy(allocator, arr + i);
    }
    std::allocator_traits<Allocator>::deallocate(allocator, arr, cap);
  }
  size_t size() const { return sz; }
  size_t capacity() const { return cap; }
  void reserve(size_t n)
  {
    if (cap >= n) return;
    T* newarr = std::allocator_traits<Allocator>::allocate(allocator, n);
    
    size_t i;
    try
    {
      for(i = 0; i<sz; ++i)
      {
        std::allocator_traits<Allocator>::construct(allocator, newarr, std::move_if_noexcept(arr[i]));
      }
    }
    catch (...)
    {
      for(size_t j = 0; j<i; ++j)
      {
        std::allocator_traits<Allocator>::destroy(allocator, newarr + j);
      }
      std::allocator_traits<Allocator>::deallocate(allocator, newarr, n);
      throw;
    }
    for (size_t i = 0; i < sz; ++i)
    {
      std::allocator_traits<Allocator>::destroy(allocator, arr + i);
    }
    std::allocator_traits<Allocator>::deallocate(allocator, arr, cap);
    arr = newarr;
    cap = n;
  }

  void resize(size_t n, const T& value = T())
  {
    if (n > cap) reserve(n);
    size_t i {0};
    try
    {
      for (i = sz; i < n; ++i)
      {
        std::allocator_traits<Allocator>::construct(allocator, arr + i, value);
      }
    }
    catch (...)
    {
      for (size_t j = 0; j < i; ++j)
      {
        std::allocator_traits<Allocator>::destroy(allocator, arr + j);
      }
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
    std::allocator_traits<Allocator>::construct(allocator, arr + sz, std::forward<Arg>(args)...);
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
    std::allocator_traits<Allocator>::construct(allocator, arr + sz, std::forward<const T&>(value));
    ++sz;
  }
  void push_back(T&& value)
  {
    if(sz == cap)
    {
      if (sz == 0) reserve(1);
      else reserve(sz * 2);
    }
    std::allocator_traits<Allocator>::construct(allocator, arr + sz, std::forward<T&&>(value));
  }
  void pop_back()
  {
    --sz;
    std::allocator_traits<Allocator>::destroy(allocator, arr + sz);
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
