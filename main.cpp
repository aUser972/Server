#include "allocator.hpp"
#include "container.hpp"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

int main()
{
  my_list<int>* ptr = new my_list<int>;
  delete ptr;
  return 0;
}