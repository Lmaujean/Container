#ifndef BIDIRECTIONAL_ITERATOR
#define BIDIRECTIONAL_ITERATOR

#include "class_iterator.hpp"
#include "../../node.hpp"

namespace ft
{
    template<class T>
    struct Node;
    
    template <class T>
    class bidirectional_iterator
    {
        public:
            typedef T	                            value_type;
			typedef ptrdiff_t	                    difference_type;
			typedef T	                            * pointer;
			typedef T	                            & reference;
			typedef ft::bidirectional_iterator_tag	iterator_category;
			typedef bidirectional_iterator	        iterator;
			typedef	Node<value_type> *	            node_type;

            bidirectional_iterator(void) : current(NULL), maximum(NULL), TNULL(NULL) {}
			bidirectional_iterator(node_type current, node_type maximum, node_type TNULL) : current(current), maximum(maximum), TNULL(TNULL) {}
			bidirectional_iterator(iterator const & src) { *this = src; }
			virtual ~bidirectional_iterator() {}

            iterator const & operator=(iterator const & rhs) 
            {
                if (this != &rhs) 
                {
                    current = rhs.current; 
                    maximum = rhs.maximum; 
                    TNULL = rhs.TNULL;
                } 
                return *this;
            }
			
			operator bidirectional_iterator<const T>() const
			{
				bidirectional_iterator<const T> temp(reinterpret_cast<Node<const T> *>(current), reinterpret_cast<Node<const T> *>(maximum), reinterpret_cast<Node<const T> *>(TNULL));
				return temp;
			}			

    };
}

#endif
