#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>
#include <bitset>
#include <memory_resource>
#include <stdio.h>

// #include "tmp_allocator.hpp"
// #include "shared_ptr.hpp"
// #include "weak_ptr.hpp"
// #include "allocator.hpp"
// #include "vector.hpp"

template<typename ... Args>
void  foo(Args& ...args)
{
    std::cout << sizeof...(args) << '\n';
}

int main()
{
    int x = 32;
    double y = 144.0;
    char c = 'c';
    std::cout << sizeof(x) << '\n';
    foo<int, double, char>(x, y, c);
    return 0;
}