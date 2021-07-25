/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 11:57:54 by mroux             #+#    #+#             */
/*   Updated: 2021/07/25 10:03:39 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTITERATOR_HPP
#define FTITERATOR_HPP
#include <iostream>
namespace ft
{
	//------------- TAGS -------------//
	struct input_iterator_tag
	{
	}; // Input Iterator
	struct output_iterator_tag
	{
	}; // Output Iterator
	struct forward_iterator_tag
	{
	}; // Forward Iterator
	struct bidirectional_iterator_tag
	{
	}; // Bidirectional Iterator
	struct random_access_iterator_tag
	{
	}; // Random-access Iterator

	//------------- TRAITS -------------//
	template <class Iter>
	class iterator_traits
	{
	public:
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
		typedef typename Iter::iterator_category iterator_category;
	};

	template <class T>
	class iterator_traits<T *>
	{
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template <class T>
	class iterator_traits<const T *>
	{
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template<> class iterator_traits<int>{}; //to resolve error: type 'int' cannot be used prior to '::' because it has no members => silencing all
    template<> class iterator_traits<char>{};
    template<> class iterator_traits<double>{};
    template<> class iterator_traits<std::string>{};
    template<> class iterator_traits<unsigned int>{};
    template<> class iterator_traits<long>{};
    template<> class iterator_traits<long long>{};
    template<> class iterator_traits<short int>{};
    template<> class iterator_traits<bool>{};
    template<> class iterator_traits<unsigned long>{};
    template<> class iterator_traits<unsigned long long>{};



	//------------- ITERATOR -------------//
	template <class Category, class T, class Distance = ptrdiff_t,
			  class Pointer = T *, class Reference = T &>
	struct iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	//------------- REVERSE ITERATOR -------------//
	template <class Iter>
	class ReverseIterator
	{
	public:

		typedef				Iter												iterator_type;
		typedef typename 	ft::iterator_traits<Iter>::iterator_category		iterator_category;
		typedef typename 	ft::iterator_traits<Iter>::value_type				value_type;
		typedef typename 	ft::iterator_traits<Iter>::difference_type			difference_type;
		typedef typename 	ft::iterator_traits<Iter>::pointer					pointer;
		typedef typename 	ft::iterator_traits<Iter>::reference				reference;

		ReverseIterator() {_current = iterator_type(); };
		ReverseIterator(iterator_type it) { _current = it; };
		ReverseIterator(ReverseIterator<iterator_type> const& rev_it){ _current = rev_it._current; };
		ReverseIterator& operator=(ReverseIterator const& other) { _current = other._current; return (*this); };
		ReverseIterator& operator++() { _current--; return *this; };
		ReverseIterator operator++(int)
		{
			ReverseIterator retval = *this;
			++(*this);
			return retval;
		}
		ReverseIterator& operator--() { _current++; return *this; };
		ReverseIterator operator--(int)
		{
			ReverseIterator retval = *this;
			--(*this);
			return retval;
		}
		ReverseIterator operator+(int n) const
		{
			ReverseIterator rit = *this;
			rit._current -= n;
			return rit;
		};
		ReverseIterator operator-(int n) const
		{
			ReverseIterator rit = *this;
			rit._current += n;
			return rit;
		};
		difference_type operator-(ReverseIterator other) { return -(_current - other._current); }
		bool operator==(ReverseIterator const &other) const { return (_current == other._current); };
		bool operator!=(ReverseIterator const &other) const { return !this->operator==(other); };
		bool operator<(ReverseIterator const &other) const { return (_current > other._current); }
		bool operator>=(ReverseIterator const &other) const { return !(*this < other); }
		bool operator>(ReverseIterator const &other) const { return (other < *this); }
		bool operator<=(ReverseIterator const &other) const { return !(*this > other); }
		typename iterator_type::value_type &operator[](difference_type n) { return *(_current - 1 - n); }
		typename iterator_type::value_type const &operator[](difference_type n) const { return *(_current - 1 - n); }
		typename iterator_type::value_type &operator*()
		{
			iterator_type tmp = _current;
			tmp--;
			return *tmp;
		};
		typename iterator_type::value_type const &operator*() const
		{
			iterator_type tmp = _current;
			tmp--;
			return *tmp;
		};
		typename iterator_type::value_type *operator->()
		{
			iterator_type tmp = _current;
			tmp--;
			return &(*tmp);
		};
		typename iterator_type::value_type const *operator->() const
		{
			iterator_type tmp = _current;
			tmp--;
			return &(*tmp);
		};

	private:

		iterator_type	base() { return _current;};
		iterator_type 	_current;

	};
}

#endif
