#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>
#include <bitset>
#include <memory_resource>
#include <stdio.h>

#include "tmp_allocator.hpp"
#include "shared_ptr.hpp"
#include "allocator.hpp"
#include "vector.hpp"

template<typename T>
struct some_struct
{
    T x;
    struct another_struct
    {

    };
    some_struct(T x): x{x} { std::cout << "Call first constructor\n"; }
    some_struct(another_struct s, T x): x{x} { std::cout << "Call second constructor\n"; }
};

int main()
{
    // some_struct<int> s(some_struct<int>::another_struct(), 10);
    auto a = make_shared<std::string>("Hello");
    std::cout << *a.get() << std::endl;
    return 0;
}