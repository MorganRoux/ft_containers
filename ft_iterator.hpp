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
		ReverseIterator() {_base = iterator(); };
		explicit ReverseIterator(iterator it){ _base = --it; };
		ReverseIterator(const ReverseIterator<iterator> &rev_it){ _base = rev_it._base; }
		ReverseIterator &operator=(ReverseIterator const& other) { _base = other._base; return (*this); }
		ReverseIterator& operator++() { _base--; return *this; }
		ReverseIterator operator++(int)
		{
			ReverseIterator retval = *this;
			++(*this);
			return retval;
		}
		ReverseIterator &operator--() { _base++; return *this; }
		ReverseIterator operator--(int)
		{
			ReverseIterator retval = *this;
			--(*this);
			return retval;
		}
		bool operator==(ReverseIterator const &other) const { return (_base == other._base); }
		bool operator!=(ReverseIterator const &other) const { return !this->operator==(other); }
		typename iterator::value_type &operator*() { return *_base; }
		typename iterator::value_type const &operator*() const { return *_base; }

	private:

		iterator	base() { return _base + 1;}
		iterator 	_base;

	};
}

#endif
