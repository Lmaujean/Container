#pragma once

#include <memory>
#include <cstring>
#include <iterator>
#include <cstddef>

namespace ft
{
    template <class Category, class T, class Distance = ptrdiff_t,
        class Pointer = T*, class Reference = T&>
    class iterator
    {
        public:
            typedef T           value_type;
            typedef Distance    difference_type;
            typedef Pointer     pointer;
            typedef Reference   reference;
            typedef Category    iterator_category;
    };

    typedef struct std::input_iterator_tag          input_iterator_tag;
    typedef struct std::output_iterator_tag         output_iterator_tag;
    typedef struct std::forward_iterator_tag        forward_iterator_tag;
    typedef struct std::bidirectional_iterator_tag  bidirectional_iterator_tag;
    typedef struct std::random_access_iterator_tag  random_access_iterator_tag;

    template <class iterator>
    struct iterator_traits
    {
        typedef typename iterator::difference_type		difference_type;
		typedef typename iterator::value_type 			value_type;
		typedef typename iterator::pointer 				pointer;
		typedef typename iterator::reference 			reference;
		typedef typename iterator::iterator_category 	iterator_category;
    };

    template <class T>
    struct iterator_traits<T *>
    {
        typedef ptrdiff_t 									difference_type;
		typedef T 											value_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef typename ft::random_access_iterator_tag 	iterator_category;
    };

    template <class T>
    struct iterator_traits<const T *>
    {
        typedef ptrdiff_t 									difference_type;
		typedef T 											value_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef typename ft::random_access_iterator_tag 	iterator_category;
    };


}