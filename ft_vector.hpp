/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 21:07:55 by mroux             #+#    #+#             */
/*   Updated: 2021/07/10 21:57:15 by mroux            ###   ########.fr       */
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
		typedef T													value_type;
		typedef Alloc												allocator_type;			//defaults to: allocator<value_type>
		typedef typename allocator_type::reference					reference;				//for the default allocator: value_type&
		typedef typename allocator_type::const_reference			const_reference;		//for the default allocator: const value_type&
		typedef typename allocator_type::pointer					pointer;				//for the default allocator: value_type*
		typedef typename allocator_type::const_pointer				const_pointer;			//for the default allocator: const value_type*
		typedef Iterator<std::random_access_iterator_tag, T>		iterator;				//a random access iterator to value_type	convertible to const_iterator
		typedef Iterator<std::random_access_iterator_tag, const T>	const_iterator; 		// a random access iterator to const value_type
		typedef ReverseIterator<iterator>							reverse_iterator;
		typedef ReverseIterator<const_iterator>						const_reverse_iterator;
		typedef ptrdiff_t											difference_type;		//a signed integral type, identical to: iterator_traits<iterator>::difference_type
		typedef size_t												size_type;

		// Constructor - Destructor
		explicit vector(const allocator_type &alloc = allocator_type()):
			_alloc(alloc), _size(0)
		{
			_v = _alloc.allocate(_size, 0);
		}

		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()):
			_alloc(alloc), _size(n)
		{
			_v = _alloc.allocate(_size, 0);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_v[i], val);
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());

		vector(const vector &x):
			_alloc(x._alloc), _size(x._size)
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
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		// Capacity
		size_type size() const{ return _size; }
		size_type max_size() const
		{
			size_type max_size = 0;
			try {
				max_size = _alloc.max_size();
			} catch (std::exception& e){
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
		T*			_v;
		Alloc		_alloc;
		size_type	_size;
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
