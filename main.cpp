#include <vector>
#include <iostream>
#include <iomanip>
#include "container.hpp"
 
template<typename T>
void print(T const & xs)
{
    std::cout << "[ ";
    for(auto const & x : xs) {
        std::cout << x << ' ';
    }
    std::cout << "]\n";
}
 
int main()
{
    Container<int> numbers {2, 4, 6, 8};
 
    std::cout << "Second element: " << numbers[1] << '\n';
 
    numbers[0] = 5;
 
    std::cout << "All numbers:";
    for (auto i : numbers) {
        std::cout << ' ' << i;
    }
    std::cout << '\n';
}