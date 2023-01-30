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

            reference operator*() const
            {
                return *current->data;
            }
            pointer operator->() const
            {
                return current->data;
            }

            iterator & operator++()
            {
                current = next(current);
                return *this;
            }
            iterator operator++(int)
            {
                iterator tmp(*this);
                ++*this;
                return tmp;
            }

            iterator & operator--()
            {
                current = previous(current);
                return *this;
            }
            iterator operator--(int);
            {
                iterator tmp(*this);
                --*this;
                return tmp;
            }

            template <class It>
			bool	operator==(It const & rhs) const {return (current->data == &(*rhs));}
			template <class It>
			bool	operator!=(It const & rhs) const {return (current->data != &(*rhs));}

        private:
            node_type current;
            node_type max;
            node_type TNULL;

            node_type min(node_type node)
            {
                while(node->left != TNULL)
                    node = node->left;
                return node;
            }
            node_type max(node_type node)
            {
                while (node->right != TNULL)
                    node = node->right;
                return node;
            }

            node_type next(node_type x)
            {
                if (x == maximum)
                    return TNULL;
                if (x->right != TNULL)
                    return min(x->right);
                node_type y = x->parent;
                while (y != NULL && x = y->right)
                {
                    x = y;
                    y = y->parent;
                }
                return y;
            }
            node_type previous(node_type x)
            {
                if (x == TNULL)
                    return maximum;
                if (x->left != TNULL)
                    return max(x->left);
                node_type y = x->parent;
                while (y != TNULL && x = y->left)
                {
                    x = y;
                    y = y->parent;
                }
                return y;
            }

    };
}

#endif
