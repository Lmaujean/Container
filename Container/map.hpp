#pragma once

#include <functional>
#include <memory>
#include "stack.hpp"
#include "pair.hpp"
#include "utils/iterator/bidirectional_iterator.hpp"
#include "utils/iterator/random_access_iterator.hpp"
#include "Enable.hpp"
#include "Integral.hpp"
#include "Equal.hpp"
#include "Lexico_compare.hpp"
#include "utils/iterator/reverse_iterator.hpp"
#include "node.hpp"

namespace ft
{
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< ft::pair <const Key, T> > >
    class map
    {
        public:
                typedef Key                                     key_type;
                typedef T                                       mapped_type;
                typedef ft::pair<const key_type, mapped_type>	value_type;
			    typedef Compare	                                key_compare;
                
                class value_compare : std::binary_function<value_type, value_type, bool>
                {
                    friend class map;
                    protected:
                        Compare comp;
                        value_compare (Compare c) : comp(c) {}
                    public:
                        bool operator() (const value_type& x, const value_type& y) const
                            { return comp(x.first, y.first); }
                };
                typedef Alloc                                           allocator_type;
                typedef typename allocator_type::reference              reference;
                typedef typename allocator_type::const_reference        const_reference;
                typedef typename allocator_type::pointer                pointer;
                typedef typename allocator_type::const_pointer          const_pointer;
                // typedef ft::bidirectional_iterator<value_type>          iterator;
                // typedef ft::bidirectional_iterator<const value_type>    const_iterator;
                typedef ft::reverse_iterator<iterator>                  reverse_ierator;
                typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;
                typedef typename allocator_type::difference_type        difference_type;
                typedef typename allocator_type::size_type              size_type;

                explicit map(const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type()) : compare(comp), alloc(alloc), _size(0)
                {
                    TNULL = allocNode.allocate(1);
                    TNULL->parent = nullptr;
                    TNULL->data = this->alloc.allocate(1);
                    TNULL->color = 0;
                    TNULL->left = nullptr;
                    TNULL->right = nullptr;
                    root = TNULL;
                    insert(first, last);
                }

                template <class InputIterator>
                map(InputIterator first, InputIterator last,
                    const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type(),
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = false)
                    : compare(comp), alloc(alloc), _size(0)
                {
                    TNULL = allocNode.allocate(1);
                    TNULL->parent = nullptr;
                    TNULL->data = this->alloc.allocate(1);
                    TNULL->color = 0;
                    TNULL->left = nullptr;
                    TNULL->right = nullptr;
                    root = TNULL;
                    insert(first, last);
                }

                map(const map & x) : compare(x.compare), alloc(x.alloc), _size(0)
                {
                    TNULL = allocNode.allocate(1);
                    TNULL->parent = nullptr;
                    TNULL->data = this->alloc.allocate(1);
                    TNULL->color = 0;
                    TNULL->left = nullptr;
                    TNULL->right = nullptr;
                    root = TNULL;
                    *this = x;
                }
                map const operator=(const map & rhs)
                {
                    clear()
                    if (this != rhs)
                        insert(rhs.begin(), rhs.end());
                    return *this;
                }

                virtual ~map()
                {
                    clear();
                    alloc.destroy(TNULL->data);
                    alloc.deallocate(TNULL->data, 1);
                    alloc.deallocate(TNULL, 1);
                }

                iterator    begin()
                {
                    return iterator(minimum(root), maximum(root), TNULL);
                }
                const iterator begin() const
                {
                    return const_iterator(reinterpret_cast<const_Node>(minimum(root)), reinterpret_cast<const_Node>(maximum(root)), reinterpret_cast<const_Node>(TNULL));
                }

                iterator	end() 
                { 
                    return iterator(TNULL, maximum(root), TNULL); 
                }
			    const_iterator	end() const
				{ 
                    return const_iterator(reinterpret_cast<const_Node>(TNULL), reinterpret_cast<const_Node>(maximum(root)), reinterpret_cast<const_Node>(TNULL)); 
                }

                reverse_iterator	rbegin() 
                { 
                    return reverse_iterator(end()); 
                }
			    const_reverse_iterator	rbegin() const  
                {
                    return const_reverse_iterator(end()); 
                }

			    reverse_iterator	rend() 
                { 
                    return reverse_iterator(begin()); 
                }
			    const_reverse_iterator	rend() const  
                { 
                    return const_reverse_iterator(begin()); 
                }

                void clear() 
                {
                    erase(begin(), end());
                }

                void erase(iterator pos)
                {
                    erase(pos->first);
                }
                void erase(iterator first, iterator end)
                {
                    while (first != end)
                    {
                        erase(first++);
                    }
                }
                
                iterator insert(iterator pos, const value_type &val)
                {
                    (void)pos;
                    return(insert(val).first);
                }

        private :
			key_compare	compare;
			allocator_type	alloc;
			size_type	_size;
            typedef Node<const value_type>	* const_Node;
			typedef Node<value_type>	Node;
			typedef	Node	* node_type;
			std::allocator<Node>	allocNode;
			node_type	root;
			node_type	TNULL;

            node_type minimum(node_type node) const
            {
                if (!_size)
                    return TNULL;
                while (node->left != TNULL)
                    node = node->left;
                return node;
            }
            node_type maximum(node_type node) const
            {
                if (!_size)
                    return TNULL;
                while (node->right != TNULL)
                    node = node->right;
                return node;
            }

    };
}