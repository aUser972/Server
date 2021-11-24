#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include "iterator.hpp"
#include "container.hpp"


struct str_t
{
    str_t() { std::cout << "Constructor" << std::endl; }
    ~str_t() { std::cout << "Destructor" << std::endl; }
};

int main()
{
    Container<int> nums {1, 2, 4, 8, 16};
    Container<std::string> fruits {"orange", "apple", "raspberry"};
    Container<char> empty;
 
    // Print vector.
    std::for_each(nums.begin(), nums.end(), [](const int n) { std::cout << n << ' '; });
    std::cout << '\n';
 
    // Sums all integers in the vector nums (if any), printing only the result.
    std::cout << "Sum of nums: "
              << std::accumulate(nums.begin(), nums.end(), 0) << '\n';
 
    // Prints the first fruit in the vector fruits, checking if there is any.
    if (!fruits.empty())
        std::cout << "First fruit: " << *fruits.begin() << '\n';
 
    if (empty.begin() == empty.end())
        std::cout << "vector 'empty' is indeed empty.\n";
    return 0;
}