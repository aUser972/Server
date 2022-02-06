#pragma once
#include <iostream>

template<typename... Args>
struct tuple;

template<typename Head, typename... Tail>
struct tuple<Head, Tail...> : tuple<Tail...>
{
    typedef tuple<Tail...> basic_type;
    typedef Head value_type;

    

    Head head;
    tuple(Head head, Tail ... tail): head{head}, tuple<Tail...>{tail...}
    {
        std::cout << "Create tuple instance with type: " << typeid(*this).name() << '\n';
        std::cout << "And head type: " << typeid(head).name() << '\n';
    }
    tuple& operator=(const tuple other)
    {
        std::cout << "Call assignment operator\n";
        this->head = other.head;
        return *this;
    }
    // friend static value_type get(tuple<Head, Tail...> t);
};

template<>
struct tuple<>
{};

template<int I, typename Head, typename... Args>
struct getter
{
    typedef typename getter<I-1, Args...>::return_type return_type;
    static return_type get(tuple<Head, Args...> t)
    {
        std::cout << "Second I is:" << I << std::endl;
        return getter<I-1, Args...>::get(t);
    }
};

template<typename Head, typename... Args>
struct getter<0, Head, Args...>
{
    typedef typename tuple<Head, Args...>::value_type return_type;
    static return_type get(tuple<Head, Args...> t)
    {
        std::cout << "Bottom" << std::endl;
        return t.head;
    }
};

template<int I, typename Head, typename... Args>
typename getter<I, Head, Args...>::return_type
get(tuple<Head, Args...> t)
{
    std::cout << "First I is:" << I << std::endl;
    return getter<I, Head, Args...>::get(t);
}