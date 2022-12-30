#ifndef VECTOR_HPP
# define VECTOR_HPP
#include <iostream>
#include <memory>

namespace ft
{
    template <class T, class Allocator = std::allocator<T>>
    class vector
    {
        public:
            typedef T value_type; // Type représentant le type de données stockées dans un vecteur.
            typedef T allocator_type; // Type qui représente la classe allocator pour l'objet vector.
            typedef std::ptrdiff_t difference_type; // Type qui fournit la différence entre les adresses de deux éléments dans un vecteur.
            typedef size_t size_type; // Type qui compte le nombre d'éléments dans un vecteur.
            typedef typename allocator_type::reference reference; // Type qui fournit une référence à un élément stocké dans un vecteur.
            typedef typename allocator_type::const_reference const_reference;  // Type qui fournit une référence à un const élément stocké dans un vecteur. Elle est utilisée pour la lecture et l’utilisation des const opérations.
            typedef typename allocator_type::pointer pointer; // Type qui fournit un pointeur vers un élément d'un vecteur.
            typedef typename allocator_type::const_pointer const_pointer; // Type qui fournit un pointeur vers un élément const d'un vecteur.
        // typedef random_access_iterator<pointer> iterator; // Type qui fournit un itérateur à accès aléatoire pour lire ou modifier un élément dans un vecteur.
        // typedef random_access_iterator<const_pointer> const_iterator; // Type qui fournit un itérateur à accès aléatoire qui peut lire un élément const dans un vecteur.
        // typedef ft::reverse_iterator<iterator> reverse_iterator; // Type qui fournit un itérateur à accès aléatoire pouvant lire ou modifier un élément d'un vecteur inversé.
        // typedef ft::reverse_iterator<const_iterator> const_reverse_iterator; // Type qui fournit un itérateur à accès aléatoire pouvant lire ou modifier un élément const d'un vecteur inversé.
            
        private:
            size_t _capacity;
            size_t _size;
            pointer _data;
            Allocator _alloc;

        public:
            // Construit un container vide et donne allocator alloc, sans éléments.
            explicit vector(const Allocator &alloc = allocator_type()) : _capacity(0), _size(0), _data(NULL), _alloc(alloc) {}
            // Construit un container avec n element chaque element est une copy de la value.
            explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _capacity(n), _size(n), _data(NULL), _alloc(alloc)
            {
                _data = _alloc.allocate(n);
                for (size_type i = 0; i < n; i++)
                    _alloc.construct(_data + i, val);
            }

            // retourne la taille de ton vecteur
            size_type size(void) const {return(_size);}
            
            // push les éléments a l'interieur de ton vecteur
            void push_back(const value_type &val)
            {
                if (_size + 1 > _capacity)
                {
                    pointer temp = _alloc.allocate(_capacity == 0 ? 1 : _capacity * 2);
                    for (size_type i = 0; i < _size; i++)
                    {
                        _alloc.construct(temp + i, _data[i]);
                        _alloc.destroy(&_data[i]);
                    }
                    _alloc.deallocate(_data, _capacity);
                    _data = temp;
                    if (_capacity == 0)
                        _capacity = 1;
                    else
                        _capacity = _capacity * 2;
                }
                _alloc.construct(_data + _size, val);
                _size++;
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

            void resize(size_type n, value_type val = value_type())
            {
                if (n < _size)
                {
                    for (size_type i = n; i < size; i++)
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
                            _capacity = size * 2;
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
}

#endif