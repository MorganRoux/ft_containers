/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 21:07:55 by mroux             #+#    #+#             */
/*   Updated: 2021/07/14 12:46:42 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTVECTOR_HPP
#define FTVECTOR_HPP
#include <iostream>
#include <stdexcept>
#include "ft_iterator.hpp"

namespace ft
{
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

		class ra_iterator : public ft::iterator<random_access_iterator_tag, T>
		{
		public:
			using typename ft::iterator<random_access_iterator_tag, T>::value_type;
			using typename ft::iterator<random_access_iterator_tag, T>::difference_type;
			using typename ft::iterator<random_access_iterator_tag, T>::pointer;
			using typename ft::iterator<random_access_iterator_tag, T>::reference;
			using typename ft::iterator<random_access_iterator_tag, T>::iterator_category;

			ra_iterator(pointer p = NULL): _p(p) { };
			~ra_iterator() {};
			ra_iterator(ra_iterator const& other):_p(other._p) { };
			ra_iterator &operator=(ra_iterator const& other) { _p = other._p; return (*this); }
			ra_iterator &operator++() { _p++; return *this; }
			ra_iterator operator++(int)
			{
				ft::iterator<random_access_iterator_tag, T, size_type>::testi = 0;
				ra_iterator retval = *this;
				++(*this);
				return retval;
			}
			ra_iterator &operator--() { _p--; return *this; }
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
			bool operator==(ra_iterator const& other) const { return (_p == other._p); }
			bool operator!=(ra_iterator const& other) const { return !this->operator==(other); }
			value_type& operator*() { return *_p; }
			value_type const& operator*() const { return *_p; }

		protected:
			pointer			_p;
		};

		typedef ra_iterator iterator;									  //a random access iterator to value_type	convertible to const_iterator
		typedef const ra_iterator const_iterator;								  // a random access iterator to const value_type
		typedef typename iterator_traits<ra_iterator>::difference_type difference_type; //a signed integral type, identical to: iterator_traits<iterator>::difference_type
		typedef ReverseIterator<ra_iterator> reverse_iterator;
		typedef const ReverseIterator<const_iterator> const_reverse_iterator;

		// Constructor - Destructor
		explicit vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(0)
		{
			_v = _alloc.allocate(_size, 0);
		}

		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(n)
		{
			_v = _alloc.allocate(_size, 0);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_v[i], val);
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());

		vector(const vector &x) : _alloc(x._alloc), _size(x._size)
		{
			_v = _alloc.allocate(_size, 0);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_v[i], x[i]);
		}

		~vector()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_v[i]);
			_alloc.deallocate(_v, _size);
		}

		vector &operator=(const vector &x)
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_v[i]);
			_alloc.deallocate(_v, _size);
			_alloc = x._alloc;
			_size = x._size;
			_v = _alloc.allocate(_size, 0);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_v[i], x[i]);
		}

		//Iterators
		iterator begin() { return iterator(_v); }
		const_iterator begin() const { return const_iterator(_v); }
		iterator end() { return iterator(_v + _size); };
		const_iterator end() const { return const_iterator(_v + _size); };
		reverse_iterator rbegin() {return reverse_iterator(end());};
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

		void resize(size_type n, value_type val = value_type());
		size_type capacity() const;
		bool empty() const { return (_size == 0); }
		void reserve(size_type n);

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
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		// Modifiers
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last);
		void assign(size_type n, const value_type &val);
		void push_back(const value_type &val);
		void pop_back();
		iterator insert(iterator position, const value_type &val);
		void insert(iterator position, size_type n, const value_type &val);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void swap(vector &x);
		void clear();

		allocator_type get_allocator() const;

	private:
		T *_v;
		Alloc _alloc;
		size_type _size;
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
