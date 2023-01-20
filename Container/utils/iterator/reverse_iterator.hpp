#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "class_iterator.hpp"

namespace ft
{
    template <class Iterator>
    class reverse_iterator
    {
        public:
            typedef Iterator                                                  iterator_type;
            typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename ft::iterator_traits<Iterator>::value_type        value_type;
            typedef typename ft::iterator_traits<Iterator>::difference_type   difference_type;
            typedef typename ft::iterator_traits<Iterator>::pointer           pointer;
            typedef typename ft::iterator_traits<Iterator>::reference         reference;

            reverse_iterator() {}
			reverse_iterator(iterator_type it) : data(it) {}
			reverse_iterator(reverse_iterator<Iterator> const & src) { *this = src; }
			reverse_iterator const & operator=(reverse_iterator<Iterator> const & rhs)
            {
                this->data = rhs.data;
                return *this;
            }
            ~reverse_iterator() {}

            iterator_type base() const
            {
                return this->data;
            }

            template < template < class > class It, class T>
            operator reverse_iterator< It<const T> >() const 
            {
                reverse_iterator< It<const T> > temp(data); 
                return (temp);
            }
            reference operator*() const
            {
                Iterator tmp = data;
                return *(--tmp);
            }
            pointer operator->() const
            {
                Iterator tmp = data;
                return &(*(--tmp));
            }
            reference operator[](difference_type n  ) const
            {
                return this->data[- n - 1];
            }
/****************************************************************************/

            reverse_iterator operator+(difference_type n) const
            {
                reverse_iterator tmp = *this;
                tmp += n;
                return tmp;
            }
            reverse_iterator operator-(difference_type n) const
            {
                reverse_iterator tmp = *this;
                tmp -= n;
                return tmp;
            }
            reverse_iterator & operator+=(difference_type n)
            {
                data = data - n;
                return *this;
            }
            reverse_iterator & operator-=(difference_type n)
            {
                data = data + n;
                return *this;
            }
            reverse_iterator operator++(int)
            {
                reverse_iterator tmp = *this;
                --this->data;
                return tmp;
            }
            reverse_iterator operator--(int)
            {
                reverse_iterator tmp = *this;
                ++this->data;
                return tmp;
            }
            reverse_iterator & operator++()
            {
                --this->data;
                return *this;
            }
            reverse_iterator & operator--()
            {
                ++this->data;
                return *this;
            }
        
        private:
            Iterator data;
    };
        
    template <class A, class B>  
    bool operator==(const reverse_iterator<A>& lhs, const reverse_iterator<B>& rhs)
    {
        return lhs.base() == rhs.base();  
    }
    template <class A, class B>  
    bool operator!=(const reverse_iterator<A>& lhs, const reverse_iterator<B>& rhs)
    {
        return lhs.base() != rhs.base();   
    }
    template <class A, class B>  
    bool operator<(const reverse_iterator<A>& lhs, const reverse_iterator<B>& rhs)
    {
        return lhs.base() > rhs.base();
    }
    template <class A, class B>  
    bool operator>  (const reverse_iterator<A>& lhs, const reverse_iterator<B>& rhs)
    {
        return lhs.base() < rhs.base();  
    }
    template <class A, class B>  
    bool operator<= (const reverse_iterator<A>& lhs, const reverse_iterator<B>& rhs)
    {
        return lhs.base() >= rhs.base();      
    }
    template <class A, class B>  
    bool operator>= (const reverse_iterator<A>& lhs, const reverse_iterator<B>& rhs)
    {
        return lhs.base() <= rhs.base();      
    }
    template <class Iterator>  
    reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n,const reverse_iterator<Iterator>& rev_it)
    {
        return (reverse_iterator<Iterator>(rev_it.base() - n));
    }
    template <class L, class R>
	typename reverse_iterator<L>::difference_type	operator-(reverse_iterator<L> const & lhs, reverse_iterator<R> const & rhs)
		{ return (rhs.base() - lhs.base()); }
}

#endif