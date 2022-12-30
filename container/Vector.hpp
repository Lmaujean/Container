#include <iostream>

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

    };
}