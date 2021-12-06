#include "tmp_allocator.hpp"
#include "vector.hpp"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>
#include <bitset>

int main()
{
  int start = 0;
  int end = 0;
  end=++start;
  std::cout << end << " " << start << '\n';
  return 0;
}