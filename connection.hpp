#pragma once
#define CONNECTION_HPP

class Connection
{
    static int count_constructors {0};
    static int count_destructors {0};

    Connection()
    {
        std::cout << "Connection constructor number: " << count_constructors << std::endl;
        ++count_constructors;
    }
    ~Connection()
    {
        std::cout << "Connection destructor number: " << count_destructors << std::endl;
        ++count_destructors;
    }
};