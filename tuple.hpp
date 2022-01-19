#pragma once

template<>
class tuple<> {};

template<typename... Args>
class tuple {};

template<typename Head, typename ... Tail>
class tuple : tuple<Tail...>
{
    typedef tuple<Tail...> basic_type;
    typedef Head value_type;

    Head head;
public:
    tuple(Head head, Tail ... tail): head{head}, tuple<Tail...>{tail...}
    {
        
    }
private:

};