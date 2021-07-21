/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 12:04:27 by mroux             #+#    #+#             */
/*   Updated: 2021/07/22 00:25:01 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMAP_HPP
#define FTMAP_HPP
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <typeinfo>
#include "ft_iterator.hpp"
#include "metafunctions.hpp"
#include "pair.hpp"
#include "Node.hpp"

namespace ft
{


	template <class U, class Compare>
	class bi_iterator : public ft::iterator<bidirectional_iterator_tag, U>
	{

	private:
		typedef ft::iterator<bidirectional_iterator_tag, U> base_iterator;
		typedef Compare key_compare;
	public:
		typedef typename ft::iterator<bidirectional_iterator_tag, U>::value_type value_type;
		typedef typename ft::iterator<bidirectional_iterator_tag, U>::reference reference;


		bi_iterator(Node<value_type> *p = NULL, const key_compare &comp = key_compare()) : _p(p), _value_comp(comp) {};
		~bi_iterator(){};
		bi_iterator(bi_iterator const &other) : _p(other._p), _value_comp(other._value_comp){};
		bi_iterator &operator=(bi_iterator const &other)
		{
			_p = other._p;
			return *this;
		}
		bi_iterator &operator++()
		{
			_p = _p->next();
			return *this;
		}
		bi_iterator operator++(int)
		{
			bi_iterator retval = *this;
			++(*this);
			return retval;
		}
		bi_iterator &operator--()
		{
			_p = _p->prev();
			return *this;
		}
		bi_iterator operator--(int)
		{
			bi_iterator retval = *this;
			--(*this);
			return retval;
		}
		bool operator<(bi_iterator const &other) const { return (_value_comp(_p->_value,other._p->_value)); }
		bool operator>=(bi_iterator const &other) const { return !(*this < other); }
		bool operator>(bi_iterator const &other) const { return (other < *this); }
		bool operator<=(bi_iterator const &other) const { return !(*this > other); }
		bool operator==(bi_iterator const &other) const { return ( !_value_comp(_p->_value, other._p->_value) && !_value_comp(other._p->_value, _p->_value)); }
		bool operator!=(bi_iterator const &other) const { return !this->operator==(other); }
		value_type &operator*() { return _p->_value; }
		value_type const &operator*() const { return _p->_value; }

		operator bi_iterator<const U, key_compare>() const { return bi_iterator<const U, key_compare>(_p); };

		class value_compare
		{
			// in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			friend class bi_iterator;

		protected:
			key_compare comp;
			value_compare(key_compare c) : comp(c) {} // constructed with map's comparison object
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};

		protected:
		Node<value_type>* _p;
		value_compare _value_comp;
	};

	template <
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef bi_iterator<value_type, key_compare> iterator;
		typedef bi_iterator<const value_type, key_compare> const_iterator;
		// TODO : disable function definition of reverse iterator depending on the type of iterator
		typedef ReverseIterator<iterator> reverse_iterator;
		typedef ReverseIterator<const_iterator> const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef size_t size_type;
		typedef Node<value_type> node_type;

		class value_compare
		{
			// in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			friend class map;

		protected:
			key_compare comp;
			value_compare(key_compare c) : comp(c) {} // constructed with map's comparison object
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};

	private:

		//pointer _m;
		node_type	*_root;
		node_type	_lastNode;
		size_type 		_size;
		allocator_type _alloc;
		key_compare _key_comp;
		value_compare _value_comp;

	public:
		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type()) :_root(NULL), _size(0), _alloc(alloc), _key_comp(comp), _value_comp(comp){};

		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) :  _root(NULL), _size(last - first), _alloc(alloc), _key_comp(comp), _value_comp(comp)
		{
			for (iterator it = first; it != last; it++)
				insert(*it);
		}

		map(const map &x)
		{
			*this = x;
		}

		~map()
		{
			//clear();
		}

		map &operator=(const map &x)
		{
			clear();
			for (iterator it = x.begin(); it != x.end(); it++)
				insert(*it);
		}

		// Iterators
		iterator begin()					{ return iterator(node_type::leftmost(_root)); }
		const_iterator begin() const		{ return const_iterator(node_type::leftmost(_root)); }
		iterator end()						{ return iterator(&_lastNode); }
		const_iterator end() const			{ return iterator(&_lastNode); }
		// reverse_iterator rbegin();				{ return reverse_iterator(node_type::rightmost(_root)); }
		// const_reverse_iterator rbegin() const;	{ return const_reverse_iterator(node_type::rightmost(_root)); }
		// reverse_iterator rend();				{ return reverse_iterator(&_rendNode); }
		// const_reverse_iterator rend() const;	{ return const_reverse_iterator(&_rendNode); }

		// Capacity
		bool empty() const { return (_size == 0); }
		size_type size() const { return _size; }
		size_type max_size() const
		{
			std::allocator<node_type> al;
			size_type max_size = 0;
			try
			{
				max_size = al.max_size();
			}
			catch (std::exception &e)
			{
				std::cout << "Error in map.max_size() :" << e.what() << std::endl;
			}
			return (max_size);
		}

		// Element access
		mapped_type &operator[](const key_type &k);

		// Modifiers
		ft::pair<iterator, bool> insert(const value_type &val)
		{
			if (_root == NULL)
			{
				_root = new node_type(val, NULL, &_lastNode, NULL);
				return ft::pair<iterator, bool>(iterator(_root), true);
			}
			node_type *node = _root;
			while(1) //node->_left != NULL || node->_right != NULL)
			{
				if (_value_comp(val, node->_value))		//val < node->_value
				{
					if (node->_left == NULL || node->_left == &_lastNode)
					{
						node_type *newNode = new node_type(val,node->_left, NULL, node);
						node->_left = newNode;
						_size++;
						return ft::pair<iterator, bool>(iterator(newNode), true);
					}
					else
						node = node->_left;
				}
				else if(_value_comp(node->_value, val))	//val > node->_value
				{
					if (node->_right == NULL || node->_right == &_lastNode)
					{
						node_type *newNode = new node_type(val, NULL, node->_right, node);
						node->_right = newNode;
						_size++;
						return ft::pair<iterator, bool>(iterator(newNode), true);
					}
					else
						node = node->_right;
				}
				else								//val == node->_value
					return ft::pair<iterator, bool>(iterator(node), false);

			}
		}
		iterator insert(iterator position, const value_type &val);
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last);
		void erase(iterator position);
		size_type erase(const key_type &k);
		void erase(iterator first, iterator last);
		void swap(map &x);
		void clear();

		// Observers
		key_compare key_comp() const { return _key_comp; }
		value_compare value_comp() const { return _value_comp; }

		// Operations
		iterator find(const key_type &k);
		const_iterator find(const key_type &k) const;
		size_type count(const key_type &k) const;
		iterator lower_bound(const key_type &k);
		const_iterator lower_bound(const key_type &k) const;
		iterator upper_bound(const key_type &k);
		const_iterator upper_bound(const key_type &k) const;
		ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const;
		ft::pair<iterator, iterator> equal_range(const key_type &k);

		// Allocator
		allocator_type get_allocator() const { return _alloc; }
	};

}

#endif
