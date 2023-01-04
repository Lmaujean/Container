#pragma once

#include "class_iterator.hpp"

namespace ft
{
    template <class T>
    class random_access_iterator
    {
        public:
            typedef T                                   value_type;
            typedef ptrdiff_t                           difference_type;
            typedef T                                   *pointer;
            typedef T                                   &reference;
            typedef std::random_access_iterator_tag     iterator_category;

            random_access_iterator(): data(NULL) {}
			random_access_iterator(T* x) : data(x) {}
			random_access_iterator(random_access_iterator const & rhs) { *this = rhs; }
            virtual ~random_access_iterator() {}

            pointer base() const
            {
                return data;
            };
            random_access_iterator const & operator=(random_access_iterator const & rhs) 
            {
                if (this != &rhs)
                    {data = rhs.data;} 
                return (*this);
            }
            operator random_access_iterator<const T>() const
            {
                random_access_iterator<const T> tmp(this->data);
                return tmp;
            };
//SOURCE ----> https://stackoverflow.com/questions/12092448/code-for-a-basic-random-access-iterator-based-on-pointers
/*************************************************************************/
            random_access_iterator & operator++()
            {
                data++;
                return *this;
            };
            random_access_iterator & operator++(int)
            {
                random_access_iterator tmp = *this;
                ++this->data;
                return tmp;
            };
            random_access_iterator & operator--()
            {
                data--;
                return *this;
            };
            random_access_iterator & operator--(int)
            {
                random_access_iterator tmp = *this;
                --this->data;
                return tmp;
            };

/*************************************************************************/
            pointer operator->() const
            {
                return data;
            };
            reference operator*() const
            {
                return *data;
            };
            reference operator[](difference_type rhs) const
            {
                return data[rhs];
            };
/*************************************************************************/

            random_access_iterator operator+(const difference_type & rhs) const 
            {
                return random_access_iterator(this->data + rhs);
            };
            difference_type operator+(const random_access_iterator & rhs) const
            {
                return random_access_iterator(this->data + rhs.data);
            };
            random_access_iterator operator-(const difference_type & rhs) const
            {
                return random_access_iterator(this->data - rhs);
            };
            difference_type operator-(const random_access_iterator & right) const 
            {
                return this->data - right.data;
            }
/*************************************************************************/
        protected:
            pointer data;
    };
    template<class A, class B>
    bool operator==(random_access_iterator<A> const & lhs, random_access_iterator<B> const & rhs)
    {
        return lhs.base() == rhs.base();
    };
    template<class A, class B>
    bool operator!=(random_access_iterator<A> const & lhs, random_access_iterator<B> const & rhs)
    {
        return lhs.base() != rhs.base();
    };
    template<class A, class B>
    bool operator>(random_access_iterator<A> const & lhs, random_access_iterator<B> const & rhs)
    {
        return lhs.base() > rhs.base();
    };
    template<class A, class B>
    bool operator<(random_access_iterator<A> const & lhs, random_access_iterator<B> const & rhs)
    {
        return lhs.base() < rhs.base();
    };
    template<class A, class B>
    bool operator>=(random_access_iterator<A> const & lhs, random_access_iterator<B> const & rhs)
    {
        return lhs.base() >= rhs.base();
    };
    template<class A, class B>
    bool operator<=(random_access_iterator<A> const & lhs, random_access_iterator<B> const & rhs)
    {
        return lhs.base() <= rhs.base();
    };
    template <typename L, typename R>
    typename random_access_iterator<L>::difference_type operator-(const random_access_iterator<L> lhs, const random_access_iterator<R> rhs)
    {
        return &(*lhs) - &(*rhs);
    };
    template <class T>
    random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type lhs, random_access_iterator<T> const & rhs)
    {
        return random_access_iterator<T>(lhs + &(*rhs));
    };
}