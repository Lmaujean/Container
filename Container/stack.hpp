#pragma once

#include "Vector.hpp"

namespace ft
{
    template< class T, class Container = ft::vector<T> > 
    class stack
    {
        public:
            typedef Container                               container_type;
            typedef typename Container::value_type          value_type;
            typedef typename Container::size_type           size_type;
            typedef typename Container::reference           reference;
            typedef typename Container::const_reference     const_reference;
            explicit stack( const container_type & cont = Container() ) : c(cont){}
            stack( const stack& other )
            {
               c = other.c;
            }
            ~stack(){}
            reference top()
            {
                return c.back();
            }
            const_reference top() const
            {
                return c.back();
            }
            size_type size()
            {
                return c.size();
            }
            void push(const     value_type &val)
            {
                c.push_back(val);
            }
            void pop()
            {
                c.pop_back();
            }
            bool empty() const
            {
                return c.empty();
            }
            template< class A, class B >
            friend bool operator==( const ft::stack<A,B>& lhs, const ft::stack<A,B>& rhs );
            template< class A, class B >
            friend bool operator!=( const ft::stack<A,B>& lhs, const ft::stack<A,B>& rhs );
            template< class A, class B >
            friend bool operator<( const ft::stack<A,B>& lhs, const ft::stack<A,B>& rhs );
            template< class A, class B >
            friend bool operator<=( const ft::stack<A,B>& lhs, const ft::stack<A,B>& rhs );
            template< class A, class B >
            friend bool operator>( const ft::stack<A,B>& lhs, const ft::stack<A,B>& rhs );
            template< class A, class B >
            friend bool operator>=( const ft::stack<A,B>& lhs, const ft::stack<A,B>& rhs );
        protected:
            container_type c;
    };
    template< class T, class Container >
    bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return lhs.c == rhs.c;
    }
    template< class T, class Container >
    bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return lhs.c != rhs.c;
    }
    template< class T, class Container >
    bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return lhs.c < rhs.c;
    }
    template< class T, class Container >
    bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return lhs.c <= rhs.c;
    }
    template< class T, class Container >
    bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return lhs.c > rhs.c;
    }
    template< class T, class Container >
    bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return lhs.c >= rhs.c;
    }
}
