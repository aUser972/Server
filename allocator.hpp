#pragma once
#define ALLOCATOR_HPP
#include <iostream>
#include <cstring>

namespace my_allocator
{
  struct free_chunk
  {
    size_t size;
    free_chunk* next;
  };

  class mem_pool
  {
    static constexpr size_t sz = 1024*1024;
    uint8_t arr[sz];
    size_t free_mem = {sz};
    size_t base_pointer {0};
  public:
    
    mem_pool()
    {
      std::memset(arr, 0, sz);
    }
    void* allocate(size_t size)
    {
      if(size > free_mem) throw std::bad_alloc();
      void* pointer = reinterpret_cast<void*>(arr[base_pointer]); 
      base_pointer += size;
      return pointer;
    }
    void deallocate(void* pointer, size_t size)
    {
      base_pointer -= size; 
    }
  };
}

static my_allocator::mem_pool pool;

template<typename T>
class my_list
{
  static_assert(std::is_integral(T)::value || std::is_floating_point(T)::value, "T must be integral or floating point");  
  struct node 
  {    
    node* next;
    T data;
  };
  node* head;
  node* tail;
public:
  my_list()
  {
    head = new node;
    head->next = nullptr;
    tail = head;
  }
  bool is_empty()
  {
    if(!head->next) return true;
    return false;
  }
  void push(const T value)
  {
    node* tmp = new node;
    if(is_empty())
    {
      head->next = tmp;
      tail = tmp;
    }
    tail->next = tmp;
    tail = tmp;    
  }
  T& pop()
  {
    if(is_empty())
    {
      throw std::out_of_range("Try to pop from empty list");
    }
  }
  void operator delete  ( void* ptr ) noexcept
  {
    std::cout << "Try to deallocate memory" << std::endl;
    // pool.deallocate(pointer, size);
  }

  void* operator new(size_t size)
  {
    std::cout << "Try to allocate " << size << " bytes" << std::endl; 
    // return pool.allocate(size);
    return nullptr;
  }
};

