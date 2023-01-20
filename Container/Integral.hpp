#ifndef IS_INTEGRAL
# define IS_INTEGRAL

#include <type_traits>
#include <cstdint>

namespace ft
{
    template <class T> struct is_integral : public std::false_type {};
    template <class T> struct is_integral<const T> : public is_integral<T> {};
    template <class T> struct is_integral<volatile const T> : public is_integral<T>{};
    template <class T> struct is_integral<volatile T> : public is_integral<T>{};
    template<> struct is_integral<unsigned char> : public std::true_type {};
    template<> struct is_integral<unsigned short> : public std::true_type{};
    template<> struct is_integral<unsigned int> : public std::true_type{};
    template<> struct is_integral<unsigned long> : public std::true_type{};
    template<> struct is_integral<signed char> : public std::true_type{};
    template<> struct is_integral<short> : public std::true_type{};
    template<> struct is_integral<int> : public std::true_type{};
    template<> struct is_integral<long> : public std::true_type{};
    template<> struct is_integral<char> : public std::true_type{};
    template<> struct is_integral<bool> : public std::true_type{};
    template<> struct is_integral<char16_t> : public std::true_type{};
    template<> struct is_integral<char32_t> : public std::true_type{};
}


#endif