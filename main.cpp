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
#include "weak_ptr.hpp"
#include "allocator.hpp"
#include "vector.hpp"

void observe(std::weak_ptr<int> weak) 
{
    if (auto observe = weak.lock()) {
        std::cout << "\tobserve() able to lock weak_ptr<>, value=" << "\n";
    } else {
        std::cout << "\tobserve() unable to lock weak_ptr<>\n";
    }
}
 
int main()
{
    std::weak_ptr<int> weak;
    std::cout << "weak_ptr<> not yet initialized\n";
    observe(weak);
 
    {
        auto shared = std::make_shared<int>(42);
        weak = shared;
        std::cout << "weak_ptr<> initialized with shared_ptr.\n";
        observe(weak);
    }
 
    std::cout << "shared_ptr<> has been destructed due to scope exit.\n";
    observe(weak);
}