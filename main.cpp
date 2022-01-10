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

int main()
{
    auto a = make_shared<std::string>("Hello");
    std::cout << *a.get() << std::endl;
}