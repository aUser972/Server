#pragma once
#define TMP_ALLOCATOR_HPP
#include <cstring>
#include <iostream>

// ***  Operator new and delete overloading *** //
// void* operator new (size_t size)
// {
//   std::cout << "Try to allocate " << size << " bytes" << std::endl;
//   return malloc(size);
// }

// void operator delete (void* ptr, size_t size)
// {
//   std::cout << "Try to deallocate memory" << std::endl;
//   free(ptr);
// }

namespace my_allocator
{
  struct free_chunk
  {
    size_t size;
    free_chunk* next;
  };

  template<typename T> class mem_pool
  {
    static constexpr size_t sz = 512 * 512;
    uint8_t arr[sz];
    size_t free_mem = { sz };
    size_t base_pointer { 0 };

  public:
    mem_pool() { std::memset(arr, 0, sz); }
    T* allocate(size_t size)
    {
      if (size > free_mem) throw std::bad_alloc();
      T* pointer = reinterpret_cast<T*>(arr + base_pointer);
      base_pointer += size;
      return pointer;
    }
    void deallocate(T* pointer, size_t size) { base_pointer -= size; }
    void construct(T* pointer, const T& val) {}
    void destroy(T* pointer) {}
  };
}   // namespace my_allocator

template<typename T> class my_list
{
  static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value,
                "T must be integral or floating point");
  struct node
  {
    node* next;
    T data;
  };

public:
  node* head { nullptr };
  node* tail { nullptr };
  my_list()
  {
    head       = new node;
    head->next = nullptr;
    tail       = head;
  }
  bool is_empty()
  {
    if (!head->next) return true;
    return false;
  }
  void push(const T value)
  {
    node* tmp = new node;
    if (is_empty())
    {
      head->next = tmp;
      tail       = tmp;
    }
    tail->next = tmp;
    tail       = tmp;
  }
  T& pop()
  {
    if (is_empty()) { throw std::out_of_range("Try to pop from empty list"); }
  }
  void operator delete(void*, size_t);
  void* operator new(size_t);
};

static my_allocator::mem_pool<my_list<int>> pool;

template<typename T> void my_list<T>::operator delete(void* ptr, size_t size)
{
  std::cout << "Try to deallocate memory" << std::endl;
  pool.deallocate(reinterpret_cast<my_list<T>*>(ptr), size);
}

template<typename T> void* my_list<T>::operator new(size_t size)
{
  std::cout << "Try to allocate " << size << " bytes" << std::endl;
  return pool.allocate(size);
}
