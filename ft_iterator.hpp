#ifndef FTITERATOR_HPP
#define FTITERATOR_HPP
#include <iostream>
namespace ft
{
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

	template <class iterator>
	class ReverseIterator {};
}

#endif
