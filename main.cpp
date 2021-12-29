#include "tmp_allocator.hpp"
#include "allocator.hpp"
#include "vector.hpp"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>
#include <bitset>
#include <memory_resource>
#include <stdio.h>

 
struct President
{
    std::string name;
    std::string country;
    int year;
 
    President(std::string p_name, std::string p_country, int p_year)
        : name(std::move(p_name)), country(std::move(p_country)), year(p_year)
    {
        std::cout << "I am being constructed.\n";
    }
    President(President&& other) noexcept
        : name(std::move(other.name)), country(std::move(other.country)), year(other.year)
    {
        std::cout << "I am being moved.\n";
    }
    President(const President& other) = default;
    President& operator=(const President& other) = default;
};

int main()
{
    Vector<President> elections;
    std::cout << "emplace_back:\n";
    elections.emplace_back("Nelson Mandela", "South Africa", 1994);
    // assert(ref.year == 1994 && "uses a reference to the created object (C++17)");
 
    Vector<President> reElections;
    std::cout << "\npush_back:\n";
    reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));
 
    std::cout << "\nContents:\n";
    for (President const& president: elections) {
        std::cout << president.name << " was elected president of "
                  << president.country << " in " << president.year << ".\n";
    }
    for (President const& president: reElections) {
        std::cout << president.year << " was re-elected president of "
                  << president.country << " in " << president.year << ".\n";
    }
}