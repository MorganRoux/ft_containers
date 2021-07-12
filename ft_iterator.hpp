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
	template <class Iterator>
	class iterator_traits
	{
	public:
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
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
	template <class iterator>
	class ReverseIterator
	{
	public:

		typedef				iterator											iterator_type;
		typedef typename 	ft::iterator_traits<iterator>::iterator_category	iterator_category;
		typedef typename 	ft::iterator_traits<iterator>::value_type			value_type;
		typedef typename 	ft::iterator_traits<iterator>::difference_type		difference_type;
		typedef typename 	ft::iterator_traits<iterator>::pointer				pointer;
		typedef typename 	ft::iterator_traits<iterator>::reference			reference;

		ReverseIterator() {_current = iterator_type(); };
		explicit ReverseIterator(iterator_type it) { _current = it; };
		ReverseIterator(const ReverseIterator<iterator_type> &rev_it){ _current = rev_it._current; };
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
		ReverseIterator operator+(int n) { _current -= n; return *this; };
		ReverseIterator operator+(ReverseIterator other);
		ReverseIterator operator-(int n) { _current -= n; return *this; };
		ReverseIterator operator-(ReverseIterator other);
		bool operator==(ReverseIterator const &other) const { return (_current == other._current); };
		bool operator!=(ReverseIterator const &other) const { return !this->operator==(other); };
		typename iterator_type::value_type &operator*() { return *(_current - 1); };
		typename iterator_type::value_type const &operator*() const { return *(_current); };

	private:

		iterator_type	base() { return _current;};
		iterator_type 	_current;

	};
}

#endif
