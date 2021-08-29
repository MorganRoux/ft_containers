/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 12:04:27 by mroux             #+#    #+#             */
/*   Updated: 2021/08/29 15:10:52 by mroux            ###   ########.fr       */
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
#include "compare.hpp"

namespace ft
{

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
		typedef node_iterator<value_type> iterator;
		typedef const_node_iterator<value_type> const_iterator;
		// TODO : disable function definition of reverse iterator depending on the type of iterator
		typedef ReverseIterator<iterator, const_iterator> reverse_iterator;
		typedef ConstReverseIterator<const_iterator> const_reverse_iterator;
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
		typedef typename std::allocator<node_type> node_allocator_type;
		node_type *_root;
		node_type _lastNode;
		allocator_type _alloc;
		node_allocator_type _node_alloc;
		key_compare _key_comp;
		value_compare _value_comp;

		void recursive_insert(node_type const *n, node_type const *last)
		{
			if (n == NULL || n == last)
				return;
			insert(n->_value);
			recursive_insert(n->_left, last);
			recursive_insert(n->_right, last);
		}

		void recursive_delete(node_type *n)
		{
			if (n == NULL || n == &_lastNode)
				return;
			node_type *left = n->_left;
			node_type *right = n->_right;
			_node_alloc.destroy(n);
			_node_alloc.deallocate(n, 1);
			n = NULL;
			recursive_delete(left);
			recursive_delete(right);
		}

		void eraseLeaf(node_type *n)
		{
			if (n->_parent == NULL)
				_root = NULL;
			else if (n->_parent->_left == n)
				n->_parent->_left = NULL;
			else if (n->_parent->_right == n)
				n->_parent->_right = NULL;
			_node_alloc.destroy(n);
			_node_alloc.deallocate(n, 1);
		}

		void eraseWithOneChild(node_type *n, node_type *child)
		{
			if (n->_parent == NULL)
			{
				if (child == &_lastNode)
					_root = NULL;
				else
					_root = child;
			}
			else if (n->_parent->_left == n)
				n->_parent->_left = child;
			else if (n->_parent->_right == n)
				n->_parent->_right = child;
			child->_parent = n->_parent;
			_node_alloc.destroy(n);
			_node_alloc.deallocate(n, 1);
		}

		node_type *getPredecessor(node_type *n)
		{
			iterator it(n);
			it--;
			return it.getNode();
		}
		node_type *getSuccessor(node_type *n)
		{
			iterator it(n);
			it++;
			return it.getNode();
		}

		void eraseWithTwoChilds(node_type *n)
		{
			node_type *pred = getPredecessor(n);
			if (pred != NULL)
				replaceByPredecessor(n, pred);
			else
			{
				node_type *succ = getSuccessor(n);
				if (succ != &_lastNode)
					replaceBySuccessor(n, succ);
				else
				{
					_root = NULL;
				}
			}
			_node_alloc.destroy(n);
			_node_alloc.deallocate(n, 1);
		}
		void replaceByPredecessor(node_type *n, node_type *pred)
		{
			// by definition, the predecessor has NO right child
			if (pred->_parent != n)
			{
				if (pred->_left != NULL)
					pred->_left->_parent = pred->_parent;
				pred->_parent->_right = pred->_left;
				pred->_left = n->_left;
				n->_left->_parent = pred;
			}
			if (n->_parent == NULL)
				_root = pred;
			else if (n->_parent->_left == n)
				n->_parent->_left = pred;
			else
				n->_parent->_right = pred;

			pred->_parent = n->_parent;
			pred->_right = n->_right;
			n->_right->_parent = pred;
		}
		void replaceBySuccessor(node_type *n, node_type *succ)
		{
			// by definition, the successor has NO left child
			if (succ->_parent != n)
			{
				if (succ->_right != NULL)
					succ->_right->_parent = succ->_parent;
				succ->_parent->_left = succ->_right;
				succ->_right = n->_right;
				n->_right->_parent = succ;
			}
			if (n->_parent == NULL)
			{
				if (succ != &_lastNode)
					_root = succ;
			}
			else if (n->_parent->_right == n)
				n->_parent->_right = succ;
			else
				n->_parent->_left = succ;

			succ->_parent = n->_parent;
			succ->_left = n->_left;
			n->_left->_parent = succ;
		}

	public:
		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type()) : _root(NULL), _lastNode(node_type()), _alloc(alloc), _key_comp(comp), _value_comp(comp){};

		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : _root(NULL), _lastNode(node_type()), _alloc(alloc), _key_comp(comp), _value_comp(comp)
		{
			for (iterator it = first; it != last; it++)
				insert(*it);
			// node_type *lastNode = node_type::rightmost(_root);
			// it--;
			// node_type *lastNode = it.getNode();
			// lastNode->_right = &_lastNode;
			// _lastNode._parent = lastNode;
		}

		map(const map &x) : _root(NULL), _lastNode(node_type()), _alloc(x._alloc), _key_comp(x._key_comp), _value_comp(x._value_comp)
		{
			*this = x;
		}

		~map()
		{
			clear();
		}

		map &operator=(const map &x)
		{

			_alloc = x._alloc;
			_key_comp = x._key_comp;
			_value_comp = x._value_comp;
			clear();
			recursive_insert(x._root, &x._lastNode);
			// node_type *last = node_type::rightmost(_root);
			// last->_right = &_lastNode;
			// _lastNode._parent = last;

			return *this;
		}

		// Iterators
		iterator begin()
		{
			if (_root == NULL)
				return iterator(&_lastNode);
			return iterator(node_type::leftmost(_root));
		}
		const_iterator begin() const
		{
			if (_root == NULL)
				return const_iterator(&_lastNode);
			return const_iterator(node_type::leftmost(_root));
		}
		iterator end() { return iterator(&_lastNode); }
		const_iterator end() const { return const_iterator(&_lastNode); }
		reverse_iterator rbegin() { return reverse_iterator(&_lastNode); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(&_lastNode); }
		reverse_iterator rend()
		{
			if (_root == NULL)
				return reverse_iterator(&_lastNode);
			return reverse_iterator(node_type::leftmost(_root));
		}
		const_reverse_iterator rend() const
		{
			if (_root == NULL)
				return const_reverse_iterator(&_lastNode);
			return const_reverse_iterator(node_type::leftmost(_root));
		}

		// Capacity
		bool empty() const { return (size() == 0); }
		size_type size() const
		{
			if (_root == NULL)
				return 0;
			size_type i = 0;
			for (const_iterator it = begin(); it != end(); it++)
				i++;
			return (i);
		}

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
		mapped_type &operator[](const key_type &k)
		{
			return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
		}

		// Modifiers
		ft::pair<iterator, bool> insert(const value_type &val)
		{
			if (_root == NULL)
			{
				_root = _node_alloc.allocate(1, 0);
				_node_alloc.construct(_root, node_type(val, NULL, &_lastNode, NULL));
				_lastNode._parent = _root;
				return ft::pair<iterator, bool>(iterator(_root), true);
			}
			node_type *node = _root;
			while (1) //node->_left != NULL || node->_right != NULL)
			{
				if (_value_comp(val, node->_value)) //val < node->_value
				{
					if (node->_left == NULL) // || node->_left == &_lastNode)
					{
						node_type *newNode = _node_alloc.allocate(1, 0);
						_node_alloc.construct(newNode, node_type(val, node->_left, NULL, node));
						node->_left = newNode;
						return ft::pair<iterator, bool>(iterator(newNode), true);
					}
					else
						node = node->_left;
				}
				else if (_value_comp(node->_value, val)) //val > node->_value
				{
					if (node->_right == NULL || node->_right == &_lastNode)
					{
						node_type *newNode = _node_alloc.allocate(1, 0);
						_node_alloc.construct(newNode, node_type(val, NULL, node->_right, node));
						if (node->_right == &_lastNode)
							_lastNode._parent = newNode;
						node->_right = newNode;
						return ft::pair<iterator, bool>(iterator(newNode), true);
					}
					else
						node = node->_right;
				}
				else //val == node->_value
					return ft::pair<iterator, bool>(iterator(node), false);
			}
		}
		iterator insert(iterator position, const value_type &val)
		{
			node_type *node = position.getNode();
			while (1) //node->_left != NULL || node->_right != NULL)
			{
				if (_value_comp(val, node->_value)) //val < node->_value
				{
					if (node->_left == NULL) // || node->_left == &_lastNode)
					{
						node_type *newNode = _node_alloc.allocate(1, 0);
						_node_alloc.construct(newNode, node_type(val, node->_left, NULL, node));
						node->_left = newNode;
						return iterator(newNode);
					}
					else
						node = node->_left;
				}
				else if (_value_comp(node->_value, val)) //val > node->_value
				{
					if (node->_right == NULL || node->_right == &_lastNode)
					{
						node_type *newNode = _node_alloc.allocate(1, 0);
						_node_alloc.construct(newNode, node_type(val, NULL, node->_right, node));
						if (node->_right == &_lastNode)
							_lastNode._parent = newNode;
						node->_right = newNode;
						return iterator(newNode);
					}
					else
						node = node->_right;
				}
				else //val == node->_value
					return iterator(node);
			}
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			for (InputIterator it = first; it != last; it++)
				insert(value_type(*it));
		}

		void erase(iterator position)
		{
			if (position == NULL)
				return;
			node_type *n = position.getNode();
			if (n == NULL)
				return;

			if (n->_left == NULL && n->_right == NULL)
				eraseLeaf(n);
			else if (n->_left == NULL || n->_right == NULL)
				eraseWithOneChild(n, n->_left != NULL ? n->_left : n->_right);
			else
				eraseWithTwoChilds(n);
		}

		size_type erase(const key_type &k)
		{
			iterator position = find(k);
			if (position == NULL)
				return (0);
			erase(position);
			return (1);
		}
		void erase(iterator first, iterator last)
		{
			key_type first_key = first->first;
			key_type last_key = last->first;
			key_type k = first_key;
			// std::cout << "===go: from " << first_key << " to " << last_key << std::endl;
			while (_key_comp(k, last_key) || _key_comp(last_key, k))
			{
				// std::cout << k << std::endl;
				key_type next_key = (++find(k))->first;
				erase(k);

				// std::cout << "..............." << std::endl;
				// analyse_map(20);
				// std::cout << "..............." << std::endl;
				k = next_key;
			}
			// std::cout << "out" << std::endl;
		}
		void swap(map &x)
		{
			map tmp = x;
			x = *this;
			*this = tmp;
		}
		void clear()
		{
			recursive_delete(_root);
			_root = NULL;
			_lastNode._left = NULL;
			_lastNode._right = NULL;
			_lastNode._parent = NULL;
		}

		// Observers
		key_compare key_comp() const { return _key_comp; }
		value_compare value_comp() const { return _value_comp; }

		// Operations
		iterator find(const key_type &k)
		{
			for (iterator it = begin(); it != end(); it++)
			{
				if (it->first == k)
					return it;
			}
			return NULL;
		}
		const_iterator find(const key_type &k) const
		{
			for (const_iterator it = begin(); it != end(); it++)
			{
				if (it->first == k)
					return it;
			}
			return NULL;
		}
		size_type count(const key_type &k) const { return (find(k) == NULL ? 0 : 1); }
		iterator lower_bound(const key_type &k)
		{
			iterator it = begin();
			while (it != end() && _key_comp((*it).first, k))
				it++;
			return it;
		}
		const_iterator lower_bound(const key_type &k) const
		{
			const_iterator it = begin();
			while (it != end() && _key_comp((*it).first, k))
				it++;
			return it;
		}
		iterator upper_bound(const key_type &k)
		{
			iterator it = begin();
			while (it != end() && !_key_comp(k, (*it).first))
				it++;
			return it;
		}
		const_iterator upper_bound(const key_type &k) const
		{
			const_iterator it = begin();
			while (it != end() && !_key_comp(k, (*it).first))
				it++;
			return it;
		}
		ft::pair<iterator, iterator> equal_range(const key_type &k)
		{
			return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
		}
		ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
		}

		// Allocator
		allocator_type get_allocator() const { return _alloc; }

		private:
		void print_map() const
		{
			print_node(_root);
			if (empty())
				return;
			for (iterator it = begin(); it != end(); it++)
				std::cout << it->first << " - " << it->second << std::endl;
			std::cout << size() << std::endl;
		}
		void analyse_map(int height) const
		{
			std::cout << "Analyse map" << std::endl;
			for (int i = 1; i < height; i++)
			{
				std::cout << i << ".." << std::endl;
				print_level(_root, i);
				std::cout << "..." << std::endl;
			}
		}
		void print_node(node_type *n) const
		{
			if (n == NULL)
			{
				std::cout << "Self = null" << std::endl;
				std::cout << "--" << std::endl;
				return;
			}
			std::cout << "Self: " << n << std::endl;
			std::cout << n->_value.first << "-" << n->_value.second << std::endl;
			std::cout << "L: " << n->_left << std::endl;
			std::cout << "R: " << n->_right << std::endl;
			std::cout << "P: " << n->_parent << std::endl;
			std::cout << "--" << std::endl;
		}
		void print_level(node_type *n, int level) const
		{
			if (n == NULL)
				return;
			if (level == 1)
				print_node(n);
			else
			{
				print_level(n->_left, level - 1);
				print_level(n->_right, level - 1);
			}
		}
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;

		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs,
				   const map<Key, T, Compare, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs > rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs,
				   const map<Key, T, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}
}

#endif
