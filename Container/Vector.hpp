#pragma once

#include <iostream>
#include <memory>
#include "utils/iterator/random_access_iterator.hpp"
#include <stdexcept>
#include <iterator>
#include "Enable.hpp"
#include "Integral.hpp"
#include "Equal.hpp"
#include "Lexico_compare.hpp"
#include "utils/iterator/reverse_iterator.hpp"


namespace ft
{
    template <class T, class Allocator = std::allocator<T> >
    class vector
    {
        public:
            typedef T value_type; // Type représentant le type de données stockées dans un vecteur.
            typedef Allocator allocator_type; // Type qui représente la classe allocator pour l'objet vector.
            typedef std::ptrdiff_t difference_type; // Type qui fournit la différence entre les adresses de deux éléments dans un vecteur.
            typedef size_t size_type; // Type qui compte le nombre d'éléments dans un vecteur.
            typedef typename allocator_type::reference reference; // Type qui fournit une référence à un élément stocké dans un vecteur.
            typedef typename allocator_type::const_reference const_reference;  // Type qui fournit une référence à un const élément stocké dans un vecteur. Elle est utilisée pour la lecture et l’utilisation des const opérations.
            typedef typename allocator_type::pointer pointer; // Type qui fournit un pointeur vers un élément d'un vecteur.
            typedef typename allocator_type::const_pointer const_pointer; // Type qui fournit un pointeur vers un élément const d'un vecteur.
            typedef random_access_iterator<value_type> iterator; // Type qui fournit un itérateur à accès aléatoire pour lire ou modifier un élément dans un vecteur.
            typedef random_access_iterator<const value_type> const_iterator; // Type qui fournit un itérateur à accès aléatoire qui peut lire un élément const dans un vecteur.
            typedef typename ft::reverse_iterator<iterator> reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
            
        private:
            size_t _capacity;
            size_t _size;
            pointer _data;
            Allocator _alloc;
            void	realloc(size_type n)
			{
				if ((n - _size) > _size)
					reserve(n);
				else
					reserve(_size + _size);
			}

        public:
            // Construit un container vide et donne allocator alloc, sans éléments.
            explicit vector(const Allocator &alloc = allocator_type()) : _capacity(0), _size(0), _data(NULL), _alloc(alloc) {}

            
            vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :  _capacity(0), _size(0), _alloc(alloc)
            {
        		assign(n, val);
            }

            template <class InputIterator>
        	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), 
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = false) : _capacity(0), _size(0), _data(NULL), _alloc(alloc)
            {
   				assign(first, last);
            }
            vector (const vector& x)
            {
                this->_size = x._size;
                this->_capacity = x._capacity;
                this->_data = _alloc.allocate(x._capacity);
                for (size_type i = 0; i < x.size(); i++)
                    _data[i] = x._data[i];
            }

            vector& operator= (const vector & x)
            {
                _data = x._data;
                _alloc = x._alloc;
                _size = x._size;
                _capacity = x._capacity;
                return *this;
            }
            ~vector() {}

            bool operator== (const vector<T,allocator_type>& rhs) {return (_data == rhs._data);};
			bool operator!= (const vector<T,allocator_type>& rhs) {return (_data != rhs._data);};
			bool operator<  (const vector<T,allocator_type>& rhs) {return (_data < rhs._data);};
			bool operator<= (const vector<T,allocator_type>& rhs) {return (_data <= rhs._data);};
			bool operator>  (const vector<T,allocator_type>& rhs) {return (_data > rhs._data);};
			bool operator>= (const vector<T,allocator_type>& rhs) {return (_data >= rhs._data);};
			/* ======FIN OPERATOR====== */

			template<class InputIterator>  
			typename ft::iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last)
			{
				size_type n = 0;
				for (; first != last; first++){
					n++;
				};
				return n;
			}

            reference back(){return _data[_size - 1];}
            const_reference back() const {return _data[_size - 1];}

            reference front(){return *_data;}
            const_reference front() const {return *_data;}

            // retourne la taille de ton vecteur
            size_type size(void) const {return(_size);}
            
            // retourne la taille de l'espace de stockage du vecteur
            size_type capacity() const {return(_capacity);}

            reference operator[] (size_type n) {return(_data[n]);}
            const_reference operator[] (size_type n) const {return(_data[n]);}

            iterator begin(){return iterator(_data);}
            const_iterator begin() const {return const_iterator(_data);}

            iterator end(){return _data + _size;}
            const_iterator end() const {return _data + _size;}

            size_type max_size() const {return _alloc.max_size();}

            bool empty() const { return _size == 0? true : false;}

            iterator erase(iterator position){return erase(position, position + 1);}
            
            iterator erase(iterator first, iterator last)
            {
                size_type   n = std::distance(first, last);
                iterator    it;
                for (it = first; it != last; it++)
                    _alloc.destroy(&(*it));
                for (it = last; it != end(); it++)
                {
                    _alloc.construct(&(*(it - n)), *it);
                    _alloc.destroy(&(*it));
                }
                _size -= n;
                return (first);
            }

            template <class InputIterator>
            void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = false)
            {
                size_type n = 0;
                n = std::distance(first, last);

                clear();
                reserve(n);
                _size = n;
                for (size_type i = 0; i < _size; i++)
                    _alloc.construct((_data + i), *first++);
            }

            void assign(size_type n, const value_type & val)
            {
                clear();
				reserve(n);
				_size = n;
				for (size_type i = 0; i < _size; i++)
					_alloc.construct((_data + i), val);
            }

            void    reserve(size_type n)
            {
				if (n > _capacity)
				{
					if (n > max_size())
						throw	std::length_error("vector");
					pointer	tmp = _alloc.allocate(n); 
					for(size_type i = 0; i < _size; i++)
					{
						_alloc.construct(tmp + i, _data[i]);
						_alloc.destroy(_data + i);
					}
					_capacity = n;
					_data = tmp;
				}
            }

            reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			}
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			}
            reverse_iterator rend()
            {
                return reverse_iterator(begin());
            }
            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(begin());
            }

            void insert(iterator position, size_type n, const value_type &val)
            {
                size_type rsize = _capacity * 2;
                if (rsize < (_size + n))
                    rsize = (_size + n);
                if (rsize > max_size())
                    throw std::length_error("vector");
                pointer tmp = _alloc.allocate(rsize);
                iterator it;
                size_type i = 0;
                for (it = begin(); it != position; it++)
                    _alloc.construct(tmp + i++, *it);
                for (size_type j = 0; j < n; j++)
                    _alloc.construct(tmp + i++, val);
                while (it != end())
                    _alloc.construct(tmp + i++, *it++);
                for (i = 0; i < _size; i++)
                    _alloc.destroy(_data + i);
                _alloc.deallocate(_data, _capacity);
                _capacity = rsize;
                _size += n;
                _data = tmp; 
            }

            iterator insert(iterator position, const value_type &val)
            {
                size_type	i = 0;
				i = std::distance(begin(), position);

				insert(position, 1, val);
				return (begin() + i);
            }

            template<class InputIterator>
            void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = false)
            {
                size_type	n = std::distance(first, last);
				size_type	rsize = _capacity * 2;
				if (rsize < (_size + n))
					rsize = (_size + n);
				if (rsize > max_size())
					throw	std::length_error("vector");
				pointer	tmp = _alloc.allocate(rsize); 
				iterator	it;
				size_type i = 0;
				for (it = begin(); it != position; it++)
					_alloc.construct(tmp + i++, *it);
				while (first != last)
					_alloc.construct(tmp + i++, *first++);
				while (it != end())
					_alloc.construct(tmp + i++, *it++);
				for (i = 0; i < _size; i++)
					_alloc.destroy(_data + i);
				_alloc.deallocate(_data, _capacity);
				_capacity = rsize;
				_size += n;
				_data = tmp;
            }            

            void pop_back()
            {
                _size -= 1;
                _alloc.destroy(_data + _size - 1);
            }

            void clear()
            {
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(_data + i);
                _size = 0;
            }
            // push les éléments a l'interieur de ton vecteur
            void push_back (const value_type& val)
            {
                if (_size + 1 > _capacity)
                {
                    pointer tmp = _alloc.allocate(_size + 1);
                    size_type i = 0;
                    for (; i < _size; i++)
                        _alloc.construct(tmp + i, _data[i]);
                    _alloc.deallocate(_data, _capacity);
                    _data = _alloc.allocate(_size + 1);
                    for (size_type t = 0; t < _size ; t++)
                        _alloc.construct(_data + t, tmp[t]);
                    _alloc.deallocate(tmp, _size + 1);
                    _alloc.construct(_data + _size, val);
                    _size += 1;
                    _capacity += 1;
                }
                else 
                {
                    _alloc.construct(_data + _size, val);
                    _size += 1;
                }
			}
            // retourne une exception si ce n'est pas le cas
            reference at(size_type n)
            {
                if (n >= _size)
                    throw std::out_of_range("ft::vector Out of range exception");
                return _data[n];
            }

            const_reference at(size_type n) const
            {
                if (n >= _size)
                    throw std::out_of_range("ft::vector Out of range exception");
                return _data[n];
            }

            void swap (vector& x){

				T* tmp_data = this->_data;
				Allocator tmp_alloc = this->_alloc;
				size_type tmp_capacity = this->_capacity;
				size_type tmp_size = this->_size;

				_data = x._data;
				_alloc = x._alloc;
				_capacity = x._capacity;
				_size = x._size;

				x._data = tmp_data;
				x._alloc = tmp_alloc;
				x._capacity = tmp_capacity;
				x._size = tmp_size;
			}

            void resize(size_type n, value_type val = value_type())
            {
                if (n < _size)
                {
                    for (size_type i = n; i < _size; i++)
                        _alloc.destroy(&_data[i]);
                    _size = n;
                }
                else if (n > _size)
                {
                    if (n > _capacity)
                    {
                        pointer temp = _alloc.allocate(std::max(n, _capacity * 2));
                        for (size_type i = 0; i < _size; i++)
                        {
                            _alloc.construct(temp + i, _data[i]);
                            _alloc.destroy(&_data[i]);
                        }
                        if (_capacity != 0)
                            _alloc.deallocate(_data, _capacity);
                        _data = temp;
                        if (_size * 2 > n && n > _capacity)
                            _capacity = _size * 2;
                        else if (_size * 2 < n && n > _capacity)
                            _capacity = n;
                        for (size_type i = _size; i < n; i++)
                            _alloc.construct(_data + i, val);
                    }
                    else
                    {
                        for (size_type i = _size; i < n; i++)
                            _alloc.construct(_data + i, val);
                    }
                    _size = n;
                }
            }
    };
    template <class T, class Alloc>
	bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); 
	}
	template <class T, class Alloc>
	bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) 
	{
		return (!(lhs == rhs));
	}
	template <class T, class Alloc>
	bool operator<  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class T, class Alloc>
	bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{ 
		return (!(rhs < lhs));
	}
	template <class T, class Alloc>
	bool operator>  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) 
	{ 
		return (rhs < lhs); 
	}
	template <class T, class Alloc>
	bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) 
	{ 
		return (!(lhs < rhs)); 
	}
}
