#include <iostream>
#include <memory>
#include <iostream>
#include <vector>
#include "iterator.hpp"
#include "container.hpp"


struct str_t
{
    str_t() { std::cout << "Constructor" << std::endl; }
    ~str_t() { std::cout << "Destructor" << std::endl; }
};

int main()
{
    Container<int> c = {1, 2, 3};
    for(const auto& el: c) std::cout << el << ' ';
    std::cout << '\n';
    return 0;
}