#pragma once

#include "class_iterator.hpp"
#include "../../node.hpp"

namespace ft
{
    template< class T>
    class BSTIterator 
    {
        public :


            typedef T	value_type;
            typedef ptrdiff_t	difference_type;
            typedef T	* pointer;
            typedef T	& reference;
            typedef typename ft::node<T>* 		node_type;
            typedef ft::bidirectional_iterator_tag	iterator_category;

        private :

            typedef BSTIterator	iterator;

            node_type	current;
            node_type	max;
            node_type	TNULL;	

        public :


            BSTIterator() : current(NULL), max(NULL), TNULL(NULL) {}
            BSTIterator(node_type current, node_type max, node_type TNULL) : current(current), max(max), TNULL(TNULL) {}
            BSTIterator(iterator const & src) { *this = src; }
            virtual ~BSTIterator() {}

            iterator const & operator=(iterator const & rhs) {if (this != &rhs) {current = rhs.current; max = rhs.max; TNULL = rhs.TNULL;} return (*this);}

            reference	operator*() const {return (*current->key);}
            pointer		operator->() const {return (current->key);}

            iterator	& operator++() {current = successor(current); return (*this);}
            iterator	operator++(int) { iterator tmp(*this); ++*this; return (tmp);}
            iterator	& operator--() {current = predecessor(current); return (*this);}
            iterator	operator--(int) {iterator tmp(*this); --*this; return (tmp);}

            
            template <class It>
            bool	operator==(It const & rhs) const {return (current->data == &(*rhs));}
            template <class It>
            bool	operator!=(It const & rhs) const {return (current->data != &(*rhs));}

        private :

            node_type	minimum(node_type node)
            {
                while (node->left != TNULL)
                    node = node->left;
                return (node);
            }

            node_type	maximum(node_type node)
            {
                while (node->right != TNULL)
                    node = node->right;
                return (node);
            }

            node_type	successor(node_type x)
            {
                if (x == max)
                    return (TNULL);
                if (x->right != TNULL)
                    return (minimum(x->right));

                node_type	y = x->parent;
                while (y != TNULL && x == y->right)
                {
                    x = y;
                    y = y->parent;
                }
                return (y);
            }

            node_type	predecessor(node_type x)
            {
                if (x == TNULL)
                    return (max);
                if (x->left != TNULL)
                    return (maximum(x->left));

                node_type	y = x->parent;
                while (y != TNULL && x == y->left)
                {
                    x = y;
                    y = y->parent;
                }
                return (y);
            }
        };
} 
