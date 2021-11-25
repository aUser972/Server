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
    Container<std::string> letters;
 
    letters.push_back("abc");
    std::string s = "def";
    letters.push_back("def");
    

    std::cout << "vector holds: ";
    std::cout << letters[0] << std::endl;
    std::cout << letters[1] << std::endl;
    // for(size_t i=0; i<letters.size(); ++i){
    //     std::cout << letters[i] << std::endl;
    // }
    // for (auto&& i : letters) std::cout << std::quoted(i) << ' ';
    // std::cout << "\nMoved-from string holds " << std::quoted(s) << '\n';
}