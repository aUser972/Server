#pragma once
#define ALLOCATOR_HPP
#include <bitset>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>

// allocator to improve std unordered_map performance
template<typename T> class Allocator
{
  static constexpr size_t mem_pool_sz { 4096 };
  static constexpr size_t ch_count { mem_pool_sz / sizeof(T) };
  std::bitset<ch_count> filled_chunk;
  T* arr;
public:
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T value_type;
  Allocator()
  {
    arr = reinterpret_cast<T*>(calloc(ch_count, sizeof(T)));
    // memset(ptr, 0, mem_pool_sz);
    // arr = reinterpret_cast<T*>(ptr);
    // arr = reinterpret_cast<T*>(std::aligned_alloc(alignof(T), ch_count));
  }
  ~Allocator() { delete[] reinterpret_cast<uint8_t*>(arr); }
  T* allocate(size_t sz)
  {
    size_t start { 0 };
    size_t end { 0 };
    size_t i { 0 };
    if(sz > ch_count) throw std::bad_alloc();
    try
    {
      while (end < sz)
      {
        if (filled_chunk.test(i)) { end = ++start; }
        else
          ++end;
        ++i;
      }
    }
    catch (const std::out_of_range& e)
    {
      throw std::bad_alloc();
    }
    for (i = start; i < end; ++i) { filled_chunk.set(i); }
    return arr + start;
  }
  void deallocate(T* ptr, size_t sz)
  {
    // std::cout << "Deallocate " << sz << " chunks\n";
    size_t i = ptr - arr;
    try
    {
      while (i < sz) { filled_chunk.reset(i); ++i; }
    }
    catch (const std::exception& e)
    {
      for (size_t j = (ptr - arr); j < i; ++j) { filled_chunk.set(j); }
      throw;
    }
  }
  template<typename... Arg>
  void construct(T* ptr, Arg&&... args)
  {
    new (reinterpret_cast<void*>(ptr)) T(args...);
  }
  void destroy(T* ptr)
  {
    std::destroy_at(ptr);
  }
};