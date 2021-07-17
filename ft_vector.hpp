/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 21:07:55 by mroux             #+#    #+#             */
/*   Updated: 2021/07/17 09:57:58 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTVECTOR_HPP
#define FTVECTOR_HPP
#include <iostream>
#include <stdexcept>
#include <typeinfo>
#include "ft_iterator.hpp"
#include "metafunctions.hpp"

// https://stackoverflow.com/questions/24346869/wrong-constructor-called-in-custom-vector-class

namespace ft
{

	template <class U>
	class ra_iterator : public ft::iterator<random_access_iterator_tag, U>
	{

	private:
		typedef ft::iterator<random_access_iterator_tag, U> base_iterator;

	public:
		typedef typename ft::iterator<random_access_iterator_tag, U>::value_type value_type;
		typedef typename ft::iterator<random_access_iterator_tag, U>::difference_type difference_type;
		typedef typename ft::iterator<random_access_iterator_tag, U>::pointer pointer;
		typedef typename ft::iterator<random_access_iterator_tag, U>::reference reference;
		typedef typename ft::iterator<random_access_iterator_tag, U>::iterator_category iterator_category;

		ra_iterator(pointer p = NULL) : _p(p){};
		~ra_iterator(){};
		ra_iterator(ra_iterator const &other) : _p(other._p){};
		ra_iterator &operator=(ra_iterator const &other)
		{
			_p = other._p;
			return (*this);
		}
		ra_iterator &operator++()
		{
			_p++;
			return *this;
		}
		ra_iterator operator++(int)
		{
			ra_iterator retval = *this;
			++(*this);
			return retval;
		}
		ra_iterator &operator--()
		{
			_p--;
			return *this;
		}
		ra_iterator operator--(int)
		{
			ra_iterator retval = *this;
			--(*this);
			return retval;
		}
		ra_iterator operator+(int n)
		{
			ra_iterator ret = *this;
			ret._p += n;
			return ret;
		}
		difference_type operator+(ra_iterator other)
		{
			return (_p - other._p);
		}
		ra_iterator operator-(int n)
		{
			ra_iterator ret = *this;
			ret._p -= n;
			return ret;
		}
		difference_type operator-(ra_iterator other) { return _p - other._p; }
		bool operator<(ra_iterator const &other) const { return (_p < other._p); }
		bool operator>=(ra_iterator const &other) const { return !(_p < other._p); }
		bool operator>(ra_iterator const &other) const { return (_p > other._p); }
		bool operator<=(ra_iterator const &other) const { return !(_p < other._p); }
		bool operator==(ra_iterator const &other) const { return (_p == other._p); }
		bool operator!=(ra_iterator const &other) const { return !this->operator==(other); }
		value_type &operator*() { return *_p; }
		value_type const &operator*() const { return *_p; }
		value_type &operator[](difference_type n) { return *(_p + n); }
		value_type const &operator[](difference_type n) const { return *(_p + n); }

		operator ra_iterator<const U>() const { return ra_iterator<const U>(_p); };

	protected:
		pointer _p;
	};

	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;									  //defaults to: allocator<value_type>
		typedef typename allocator_type::reference reference;			  //for the default allocator: value_type&
		typedef typename allocator_type::const_reference const_reference; //for the default allocator: const value_type&
		typedef typename allocator_type::pointer pointer;				  //for the default allocator: value_type*
		typedef typename allocator_type::const_pointer const_pointer;	  //for the default allocator: const value_type*
		typedef size_t size_type;
		typedef ra_iterator<T> iterator;											 //a random access iterator to value_type	convertible to const_iterator
		typedef ra_iterator<const T> const_iterator;								 // a random access iterator to const value_type
		typedef typename iterator_traits<iterator>::difference_type difference_type; //a signed integral type, identical to: iterator_traits<iterator>::difference_type
		typedef ReverseIterator<iterator> reverse_iterator;
		typedef ReverseIterator<const_iterator> const_reverse_iterator;

		// Constructor - Destructor
		explicit vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0)
		{
			_v = _alloc.allocate(_capacity, 0);
		}

		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n)
		{
			_v = _alloc.allocate(_capacity, 0);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_v[i], val);
		}

		template <class InputIterator>
		vector(typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(last - first), _capacity(last - first)
		{
			//typedef typename Iter::iterator_category test;
			_v = _alloc.allocate(_capacity, 0);
			iterator it = begin();
			for (; first != last; it++, first++)
				*it = *first;
		}

		vector(const vector &x) : _alloc(x._alloc), _size(x._size), _capacity(x._capacity)
		{
			_v = _alloc.allocate(_capacity, 0);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_v[i], x[i]);
		}

		~vector()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_v[i]);
			_alloc.deallocate(_v, _capacity);
		}

		vector &operator=(const vector &x)
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_v[i]);
			_alloc.deallocate(_v, _capacity);
			_alloc = x._alloc;
			_size = x._size;
			_capacity = x._capacity;
			_v = _alloc.allocate(_capacity, 0);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_v[i], x[i]);
		}

		//Iterators
		iterator begin() { return iterator(_v); }
		const_iterator begin() const { return const_iterator(_v); }
		iterator end() { return iterator(_v + _size); };
		const_iterator end() const { return const_iterator(_v + _size); };
		reverse_iterator rbegin() { return reverse_iterator(end()); };
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); };
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); };

		// Capacity
		size_type size() const { return _size; }
		size_type max_size() const
		{
			size_type max_size = 0;
			try
			{
				max_size = _alloc.max_size();
			}
			catch (std::exception &e)
			{
				std::cout << "Error in vector.max_size() :" << e.what() << std::endl;
			}
			return (max_size);
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n > _capacity)
			{
				T *tmp = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&tmp[i], _v[i]);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_v[i]);
				_alloc.deallocate(_v, _capacity);

				_capacity = n;
				_size = n;
				_v = tmp;
			}
			else if (n < _size)
			{
				for (size_type i = n; i < _size; i++)
					_alloc.destroy(&_v[i]);
				_size = n;
			}
			else
			{
				for (size_type i = _size; i < n; i++)
					_alloc.construct(&_v[i], val);
				_size = n;
			}
		}
		size_type capacity() const { return _capacity; }
		bool empty() const { return (_size == 0); }
		void reserve(size_type n)
		{
			if (n > _capacity)
			{
				T *tmp = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&tmp[i], _v[i]);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_v[i]);
				_alloc.deallocate(_v, _capacity);

				_capacity = n;
				_v = tmp;
			}
		}

		// Element access
		reference operator[](size_type n) { return *(_v + n); }
		const_reference operator[](size_type n) const { return *(_v + n); }
		reference at(size_type n) throw(std::out_of_range)
		{
			if (n >= _size)
				throw std::out_of_range("Out of range error in vector.at()");
			return *(_v + n);
		}
		const_reference at(size_type n) const throw(std::out_of_range)
		{
			if (n >= _size)
				throw std::out_of_range("Out of range error in vector.at() const");
			return *(_v + n);
		}
		reference front() { return *(_v); }
		const_reference front() const { return *_v; }
		reference back() { return *(_v + _size - 1); };
		const_reference back() const { return *(_v + _size - 1); };

		// Modifiers
		template <class InputIterator>
		void assign(typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type first, InputIterator last)
		{
			if (last < first)
				return;
			size_type size = last - first;
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_v[i]);
			if (size > _capacity)
			{
				_alloc.deallocate(_v, _capacity);
				_capacity = size;
				_v = _alloc.allocate(_capacity);
			}
			_size = size;
			for (iterator it = begin(); first != last; first++, it++)
				_alloc.construct(&(*it), *first);
		}

		void assign(size_type n, const value_type &val)
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_v[i]);
			if (n > _capacity)
			{
				_alloc.deallocate(_v, _capacity);
				_capacity = n;
				_v = _alloc.allocate(_capacity);
			}
			_size = n;
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_v[i], val);
		}

		void push_back(const value_type &val)
		{
			if (_size < _capacity)
			{
				_alloc.construct(&_v[_size], val);
				_size++;
			}
			else
			{
				T *tmp = _alloc.allocate(_capacity + 1);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&tmp[i], _v[i]);
				_alloc.construct(&tmp[_size], val);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_v[i]);
				_alloc.deallocate(_v, _capacity);
				_v = tmp;
				_size++;
				_capacity++;
			}
		}

		void pop_back()
		{
			_alloc.destroy(&_v[_size - 1]);
			_size--;
		}

		iterator insert(iterator position, const value_type &val);
		void insert(iterator position, size_type n, const value_type &val);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);

		iterator erase(iterator position)
		{
			if (position == (end() - 1))
			{
				_alloc.destroy(&(*position));
				_size--;
				return end();
			}
			size_type i = 0;
			iterator it = begin();
			T *tmp = _alloc.allocate(_capacity);
			for (; it != position; i++, it++)
				_alloc.construct(&tmp[i], *it);
			*it++;
			iterator ret(&tmp[i]);
			for (; it != end(); i++, it++)
				_alloc.construct(&tmp[i], *it);
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_v[i]);
			_alloc.deallocate(_v, _capacity);
			_size--;
			_v = tmp;
			return ret;
		}

		iterator erase(iterator first, iterator last)
		{
			if (last == end())
			{
				for (iterator it = first; it != last; it++)
				{
					_alloc.destroy(&*it);
					_size--;
				}
				return first;
			}
			size_type i =0;
			iterator it = begin();
			T *tmp = _alloc.allocate(_capacity);
			for (; it != first; i++, it++)
				_alloc.construct(&tmp[i], *it);
			iterator ret = iterator(&tmp[i]);
			for (it = last; it != end(); i++, it++)
				_alloc.construct(&tmp[i], *it);
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_v[i]);
			_alloc.deallocate(_v, _capacity);
			_size -= last - first;
			_v = tmp;
			return ret;
		}

		void swap(vector &x);
		void clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_v[i]);
			_size = 0;
		}
		allocator_type get_allocator() const { return _alloc; }

	private:
		T *_v;
		Alloc _alloc;
		size_type _size;
		size_type _capacity;
	};

	// relational operators
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	// swap
	template <class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y);

	// Template specializations
	template <class Alloc>
	class vector<bool, Alloc>; // bool specialization
}

#endif
