// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   map.hpp                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/07/18 12:04:27 by mroux             #+#    #+#             */
// /*   Updated: 2021/07/19 23:55:51 by mroux            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #ifndef FTMAP_HPP
// #define FTMAP_HPP
// #include <iostream>
// #include <stdexcept>
// #include <cstddef>
// #include <typeinfo>
// #include "ft_iterator.hpp"
// #include "metafunctions.hpp"
// #include "pair.hpp"

// namespace ft
// {
// 	template <class U>
// 	class bi_iterator : public ft::iterator<bidirectional_iterator_tag, U>
// 	{

// 	private:
// 		typedef ft::iterator<bidirectional_iterator_tag, U> base_iterator;

// 	public:
// 		typedef typename ft::iterator<bidirectional_iterator_tag, U>::value_type value_type;
// 		typedef typename ft::iterator<bidirectional_iterator_tag, U>::difference_type difference_type;
// 		typedef typename ft::iterator<bidirectional_iterator_tag, U>::pointer pointer;
// 		typedef typename ft::iterator<bidirectional_iterator_tag, U>::reference reference;
// 		typedef typename ft::iterator<bidirectional_iterator_tag, U>::iterator_category iterator_category;

// 		bi_iterator(pointer p = NULL) : _p(p){};
// 		~bi_iterator(){};
// 		bi_iterator(bi_iterator const &other) : _p(other._p){};
// 		bi_iterator &operator=(bi_iterator const &other)
// 		{
// 			_p = other._p;
// 			return (*this);
// 		}
// 		bi_iterator &operator++()
// 		{
// 			_p++;
// 			return *this;
// 		}
// 		bi_iterator operator++(int)
// 		{
// 			bi_iterator retval = *this;
// 			++(*this);
// 			return retval;
// 		}
// 		bi_iterator &operator--()
// 		{
// 			_p--;
// 			return *this;
// 		}
// 		bi_iterator operator--(int)
// 		{
// 			bi_iterator retval = *this;
// 			--(*this);
// 			return retval;
// 		}
// 		bool operator<(bi_iterator const &other) const { return (_p < other._p); }
// 		bool operator>=(bi_iterator const &other) const { return !(*this < other); }
// 		bool operator>(bi_iterator const &other) const { return (other < *this); }
// 		bool operator<=(bi_iterator const &other) const { return !(*this > other); }
// 		bool operator==(bi_iterator const &other) const { return (_p == other._p); }
// 		bool operator!=(bi_iterator const &other) const { return !this->operator==(other); }
// 		value_type &operator*() { return *_p; }
// 		value_type const &operator*() const { return *_p; }
// 		value_type &operator[](difference_type n) { return *(_p + n); }
// 		value_type const &operator[](difference_type n) const { return *(_p + n); }

// 		operator bi_iterator<const U>() const { return bi_iterator<const U>(_p); };

// 	protected:
// 		pointer _p;
// 	};

// 	template <
// 		class Key,
// 		class T,
// 		class Compare = std::less<Key>,
// 		class Alloc = std::allocator<ft::pair<const Key, T> > >
// 	class map
// 	{
// 	public:
// 		typedef Key key_type;
// 		typedef T mapped_type;
// 		typedef ft::pair<const key_type, mapped_type> value_type;
// 		typedef Compare key_compare;
// 		typedef Alloc allocator_type;
// 		typedef typename allocator_type::reference reference;
// 		typedef typename allocator_type::const_reference const_reference;
// 		typedef typename allocator_type::pointer pointer;
// 		typedef typename allocator_type::const_pointer const_pointer;
// 		typedef bi_iterator<T> iterator;
// 		typedef bi_iterator<const T> const_iterator;
// 		// TODO : disable function definition of reverse iterator depending on the type of iterator
// 		typedef ReverseIterator<iterator> reverse_iterator;
// 		typedef ReverseIterator<const_iterator> const_reverse_iterator;
// 		typedef typename iterator_traits<iterator>::difference_type difference_type;
// 		typedef size_t size_type;

// 		class value_compare
// 		{
// 			{ // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
// 				friend class map;

// 			protected:
// 				Compare comp;
// 				value_compare(Compare c) : comp(c) {} // constructed with map's comparison object
// 			public:
// 				typedef bool result_type;
// 				typedef value_type first_argument_type;
// 				typedef value_type second_argument_type;
// 				bool operator()(const value_type &x, const value_type &y) const
// 				{
// 					return comp(x.first, y.first);
// 				}
// 			}
// 		};

// 		explicit map(const key_compare &comp = key_compare(),
// 					 const allocator_type &alloc = allocator_type())
// 		{

// 		}

// 		template <class InputIterator>
// 		map(InputIterator first, InputIterator last,
// 			const key_compare &comp = key_compare(),
// 			const allocator_type &alloc = allocator_type());

// 		map(const map &x){
// 			*this = x;
// 		}

// 		~map() {
// 			clear();
// 		}

// 		map &operator=(const map &x)
// 		{
// 			clear();
// 			_alloc.allocate(_m, x.capacity());
// 			for (iterator it = x.begin(); it < x.end(); it++)
// 				insert(*it);
// 		}

// 		iterator begin() { return iterator(_m); }
// 		const_iterator begin() const { return const_iterator(_m); }
// 		iterator end();
// 		const_iterator end() const;
// 		reverse_iterator rbegin();
// 		const_reverse_iterator rbegin() const;
// 		reverse_iterator rend();
// 		const_reverse_iterator rend() const;
// 		bool empty() const;
// 		size_type size() const;
// 		size_type max_size() const;
// 		mapped_type &operator[](const key_type &k);
// 		ft::pair<iterator, bool> insert(const value_type &val);
// 		iterator insert(iterator position, const value_type &val);
// 		template <class InputIterator>
// 		void insert(InputIterator first, InputIterator last);
// 		void erase(iterator position);
// 		size_type erase(const key_type &k);
// 		void erase(iterator first, iterator last);
// 		void swap(map &x);
// 		void clear() {
// 			for (size_type i = 0; i < _size; i++)
// 				_alloc.destroy(&_m[i]);
// 			_alloc.deallocate(_m, _capacity);
// 		}
// 		key_compare key_comp() const;
// 		value_compare value_comp() const;
// 		iterator find(const key_type &k);
// 		const_iterator find(const key_type &k) const;
// 		size_type count(const key_type &k) const;
// 		iterator lower_bound(const key_type &k);
// 		const_iterator lower_bound(const key_type &k) const;
// 		iterator upper_bound(const key_type &k);
// 		const_iterator upper_bound(const key_type &k) const;
// 		ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const;
// 		ft::pair<iterator, iterator> equal_range(const key_type &k);
// 		allocator_type get_allocator() const;

// 	private:
// 		pointer _m;
// 		size_type _size;
// 		size_type _capacity;

// 	};
// }

// #endif
