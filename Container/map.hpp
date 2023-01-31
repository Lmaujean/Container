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
                typedef ft::bidirectional_iterator<value_type>          iterator;
                typedef ft::bidirectional_iterator<const value_type>    const_iterator;
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
                
                bool empty() const
                {
                    return _size == 0;
                }

                size_type size() const
                {
                    return _size;
                }

                size_type max_size() const
                {
                    return allocNode.max_size();
                }
                
                iterator insert(iterator pos, const value_type &val)
                {
                    (void)pos;
                    return(insert(val).first);
                }

                mapped_type	& operator[](const key_type & k) 
                { 
                    return ((*((this->insert(ft::make_pair(k,mapped_type()))).first)).second); 
                }

            ft::pair<iterator, bool>	insert(const value_type & val)
			{
				node_type	node;
				if ((node = search_tree(root, val.first)) != TNULL)
					return (ft::pair<iterator, bool>(iterator(node, maximum(root), TNULL), false));


				node = allocNode.allocate(1);
				node->parent = nullptr;
				node->data = this->alloc.allocate(1);
				alloc.construct(node->data, value_type(val.first, val.second));
				node->left = TNULL;
				node->right = TNULL;
				node->color = 1;

				node_type	y = nullptr;
				node_type	x = this->root;

				while (x != TNULL)
				{
					y = x;
					if (compare(node->data->first, x->data->first))
						x = x->left;
					else
						x = x->right;
				}

				node->parent = y;
				if (y == nullptr)
					root = node;
				else if (  compare(node->data->first, y->data->first))
					y->left = node;
				else
					y->right = node;

				_size++;
				if (node->parent == nullptr)
				{
					node->color = 0;
					return (ft::pair<iterator, bool>(iterator(node, maximum(root), TNULL), true));
				}

				if (node->parent->parent == nullptr)
					return (ft::pair<iterator, bool>(iterator(node, maximum(root), TNULL), true));

				insert_fix(node);
				return (ft::pair<iterator, bool>(iterator(search_tree(root, val.first), maximum(root), TNULL), true));
			}
			iterator	insert(iterator position, const value_type & val)
			{
				(void)position;
				return (insert(val).first);
			}

			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = false)
			{
				while (first != last)
					insert(*first++);
			}

			void	erase(iterator position)
			{
				erase(position->first);
			}

			size_type	erase(const key_type & key)
			{
				node_type	node = this->root;
				node_type	z = TNULL;
				node_type	x;
				node_type	y;
				while (node != TNULL)
				{
					if (node->data->first == key)
						z = node;
					if (compare(key, node->data->first))
						node = node->left;
					else
						node = node->right;
				}

				if (z == TNULL)
					return(0);

				y = z;
				int	y_original_color = y->color;
				if (z->left == TNULL)
				{
					x = z->right;
					rb_transplamt(z, z->right);
				}
				else if (z->right == TNULL)
				{
					x = z->left;
					rb_transplamt(z, z->left);
				}
				else
				{
					y = minimum(z->right);
					y_original_color = y->color;
					x = y->right;
					if (y->parent == z)
						x->parent = y;
					else
					{
						rb_transplamt(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}

					rb_transplamt(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				alloc.destroy(z->data);
				alloc.deallocate(z->data, 1);
				allocNode.deallocate(z, 1);
				if (y_original_color == 0)
					delete_fix(x);
				_size--;
				return (1);
			}

			void	erase(iterator first, iterator last)
			{
				while (first != last)
					erase(first++);
			}

			void	swap(map & x)
			{
				size_type	tmp_size = x._size;
				node_type	tmp_root = x.root;
				node_type	tmp_TNULL = x.TNULL;

				x._size = _size;
				x.root = root;
				x.TNULL = TNULL;

				_size = tmp_size;
				root = tmp_root;
				TNULL = tmp_TNULL;
			} 

			void	clear() 
			{ 
				erase(begin(), end());
			}


			key_compare	key_comp() const 
			{ 
				return (key_compare()); 
			}

			value_compare	value_comp() const 
			{ 
				return (value_compare(key_compare())); 
			}			


			iterator	find(const key_type & k) 
			{ 
				return (iterator(search_tree(root, k), maximum(root), TNULL));
			}

			const_iterator	find(const key_type & k) const
			{ 
				return (const_iterator(reinterpret_cast<const_Node>(search_tree(root, k)), reinterpret_cast<const_Node>(maximum(root)), reinterpret_cast<const_Node>(TNULL))); 
			}

			size_type	count(const key_type & k) const { return ((search_tree(root, k) == TNULL) ? 0 : 1); }

			iterator	lower_bound(const key_type & k)
			{
				iterator	it;

				for (it = begin(); it != end(); it++)
					if (!compare(it->first, k))
						return (it);
				return (it);
			}
			const_iterator	lower_bound(const key_type & k) const
			{
				const_iterator	it;

				for (it = begin(); it != end(); it++)
					if (!compare(it->first, k))
						return (it);
				return (it);
			}
			
			iterator	upper_bound(const key_type & k)
			{
				iterator	it;

				for (it = begin(); it != end(); it++)
					if (compare(k, it->first))
						return (it);
				return (it);
			}
			const_iterator	upper_bound(const key_type & k) const
			{
				const_iterator	it;

				for (it = begin(); it != end(); it++)
					if (compare(k, it->first))
						return (it);
				return (it);
			}
			ft::pair<iterator, iterator>	equal_range(const key_type & k)
			{ 
				return (ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
			}
			ft::pair<const_iterator, const_iterator>	equal_range(const key_type & k) const	
			{ 
				return (ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
			}
			allocator_type	get_allocator() const 
			{ 
				return (allocator_type()); 
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

            node_type	search_tree(node_type node, const key_type & key) const
			{
				if (node == TNULL || key == node->data->first)
					return (node);
				if (compare(key, node->data->first))
					return (search_tree(node->left, key));
				return (search_tree(node->right, key));
			}

            void	right_rotate(node_type x)
			{
				node_type	y = x->left;
				x->left = y->right;
				if (y->right != TNULL)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == nullptr)
					this->root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}

			void	left_rotate(node_type x)
			{
				node_type	y = x->right;
				x->right = y->left;
				if (y->left != TNULL)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == nullptr)
					this->root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

            void	rb_transplamt (node_type u, node_type v)
			{
				if (u->parent == nullptr)
					root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

			void	insert_fix(node_type k)
			{
				node_type	u;
				while (k->parent->color == 1)
				{
					if (k->parent == k->parent->parent->right)
					{
						u = k->parent->parent->left;
						if (u->color == 1)
						{
							u->color = 0;
							k->parent->color = 0;
							k->parent->parent->color = 1;
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->left)
							{
								k = k->parent;
								right_rotate(k);
							}
							k->parent->color = 0;
							k->parent->parent->color = 1;
							left_rotate(k->parent->parent);
						}
					}
					else
					{
						u = k->parent->parent->right;
						if (u->color == 1)
						{
							u->color = 0;
							k->parent->color = 0;
							k->parent->parent->color = 1;
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->right)
							{
								k = k->parent;
								left_rotate(k);
							}
							k->parent->color = 0;
							k->parent->parent->color = 1;
							right_rotate(k->parent->parent);
						}
					}
					if (k == root)
						break;
				}
				root->color = 0;
			}

			void delete_fix(node_type x)
			{
				node_type	s;
				while (x != root && x->color == 0)
				{
					if (x == x->parent->left)
					{
						s = x->parent->right;
						if (s->color == 1)
						{
							s->color = 0;
							x->parent->color = 1;
							left_rotate(x->parent);
							s = x->parent->right;
						}
						if (s->left->color == 0 && s->right->color == 0)
						{
							s->color = 1;
							x = x->parent;
						}
						else
						{
							if (s->right->color == 0)
							{
								s->left->color = 0;
								s->color = 1;
								right_rotate(s);
								s = x->parent->right;
							}
							s->color = x->parent->color;
							x->parent->color = 0;
							s->right->color = 0;
							left_rotate(x->parent);
							x = root;
						}
					}
					else
					{
					
						s = x->parent->left;
						if (s->color == 1)
						{
							s->color = 0;
							x->parent->color = 1;
							right_rotate(x->parent);
							s = x->parent->left;
						}
						if (s->right->color == 0 && s->left->color == 0)
						{
							s->color = 1;
							x = x->parent;
						}
						else
						{
							if (s->left->color == 0)
							{
								s->right->color = 0;
								s->color = 1;
								left_rotate(s);
								s = x->parent->left;
							}
							s->color = x->parent->color;
							x->parent->color = 0;
							s->left->color = 0;
							right_rotate(x->parent);
							x = root;

						}
					}
				}
				x->color = 0;
			}
    };

    template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) 	
		{ return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) 	
		{ return (!(lhs == rhs)); }

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) 	
		{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) 	
		{ return (!(rhs < lhs)); }

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) 	
		{ return (rhs < lhs); }

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) 	
		{ return (!(lhs < rhs)); }
};