#include "tmp_allocator.hpp"
#include "allocator.hpp"
#include "vector.hpp"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>
#include <bitset>
#include <memory_resource>

template<typename T>
void print(T const & xs)
{
    std::cout << "[ ";
    for(auto const & x : xs) {
        std::cout << x << ' ';
    }
    std::cout << "]\n";
}

int main()
{
    Vector<int, Allocator<int>> numbers;
 
    print(numbers);
 
    numbers.push_back(5);
    numbers.push_back(3);
    numbers.push_back(4);
 
    print(numbers);
 
    numbers.pop_back();
 
    print(numbers);
  return 0;
}