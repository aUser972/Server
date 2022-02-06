#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>
#include <bitset>
#include <memory_resource>
#include <stdio.h>
#include <tuple>
#include <stdexcept>
#include <tuple>

#include "tmp_allocator.hpp"
#include "shared_ptr.hpp"
#include "weak_ptr.hpp"
#include "allocator.hpp"
#include "vector.hpp"
#include "tuple.hpp"

template<int I, typename... Args>
std::tuple<Args...> func(Args... args)
{
    std::cout << "I value is :" << I << std::endl;
    return std::tuple<Args...>(args...);
}
 
int main()
{
    // tuple<int, double, int> a(1, 3.3, 4);
    // tuple<int, double, int> b(1, 14.1,  5);
    // a = b;
    // int x = 2;
    // auto var = get<2>(a);
    // std::cout << "2 Value is: " << var << std::endl;
    auto a = func<45>(1, 2, 3);
    std::cout << "Result: " << std::get<0>(a) << ' ' << std::get<1>(a) << ' ' << std::get<2>(a);
    return 0;
}
