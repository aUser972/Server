#include <vector>
#include <iostream>
#include <iomanip>
#include <thread>
#include "container.hpp"
#include "allocator.hpp"

int main()
{
    char* ptr = new char();
    delete ptr;
    return 0;
}