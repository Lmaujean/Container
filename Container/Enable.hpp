#ifndef ENABLE_IF
# define ENABLE_IF


namespace ft
{
    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { typedef T type; };
}

#endif