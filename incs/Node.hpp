/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 19:22:54 by mroux             #+#    #+#             */
/*   Updated: 2021/07/23 17:31:57 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTNODE_HPP
#define FTNODE_HPP

#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <typeinfo>
#include "ft_iterator.hpp"
#include "pair.hpp"

namespace ft
{
	template <class U>
	class Node
	{
	public:

		U 			_value;
		Node*		_left;
		Node*		_right;
		Node*		_parent;

		static Node*	leftmost(Node *n)
		{
			if (n == NULL)
				return NULL;
			while(n->_left != NULL)
				n = n->_left;
			return n;
		}
		static Node*	rightmost(Node *n)
		{
			if (n == NULL)
				return NULL;
			while(n->_right != NULL)
				n = n->_right;
			return n;
		}

		Node() : _value(U()), _left(NULL), _right(NULL), _parent(NULL) {};
		Node(U v, Node *left = NULL, Node *right = NULL, Node *parent = NULL) :
			_value(v), _left(left), _right(right), _parent(parent) {};
		~Node(){};

		Node &operator=(Node const &other)
		{
			_value = other._value;
			_left = other._left;
			_right = other._right;
			_parent = other._parent;
		}

		Node*		prev(){
			Node* newNode = prevL();
			if (newNode == NULL)
				newNode = prevU();
			return newNode;
		}
		Node*		next() {
			Node* newNode = nextR();
			if (newNode == NULL)
				newNode = nextU();
			return newNode;
		}

	private:
		Node*		prevL()
		{
			if (_left != NULL)
				return (rightmost(_left));
			else
				return NULL;
		}
		Node*		prevU()
		{
			Node *cur, *up;
			if (_parent == NULL)		//root node
				return NULL;
			up = this;
			while(up->_parent != NULL)
			{
				cur = up;
				up = up->_parent;
				if (up->_right == cur)	//left turn
					return up;
			}
			return NULL;		// no successor
		}

		Node*		nextR()
		{
			if (_right != NULL)
				return leftmost(_right);
			else
				return NULL;
		}
		Node*		nextU()
		{
			Node	*cur, *up;
			if (_parent == NULL)		//root node
				return NULL;
			up = this;
			while(up->_parent != NULL)
			{
				cur = up;
				up = up->_parent;
				if (up->_left == cur)	//right turn
					return up;
			}
			return NULL;				// no successor
		}
	};

	template <class U>
	class const_node_iterator;

	template <class U>
	class node_iterator : public ft::iterator<bidirectional_iterator_tag, U>
	{



	public:
		typedef typename ft::iterator<bidirectional_iterator_tag, U>::value_type value_type;
		typedef typename ft::iterator<bidirectional_iterator_tag, U>::reference reference;

		friend class const_node_iterator<U>;
		template <class Key, class T, class Compare, class Alloc>
		friend class map;

	private:
		typedef ft::iterator<bidirectional_iterator_tag, U> base_iterator;
		Node<value_type> *getNode() { return _p; }

	public:
		node_iterator(Node<value_type> *p = NULL) : _p(p) {};
		~node_iterator(){};
		node_iterator(node_iterator const &other) : _p(other._p){};
		//operator const_node_iterator<const U>() const { return const_node_iterator<const U>(_p); };

		node_iterator &operator=(node_iterator const &other)
		{
			_p = other._p;
			return *this;
		}
		node_iterator &operator++()
		{
			_p = _p->next();
			return *this;
		}
		node_iterator operator++(int)
		{
			node_iterator retval = *this;
			++(*this);
			return retval;
		}
		node_iterator &operator--()
		{
			_p = _p->prev();
			return *this;
		}
		node_iterator operator--(int)
		{
			node_iterator retval = *this;
			--(*this);
			return retval;
		}
		bool operator==(node_iterator const &other) const { return ( _p == other._p) ; }
		bool operator!=(node_iterator const &other) const { return !this->operator==(other); }
		value_type &operator*() { return _p->_value; }
		value_type const &operator*() const { return _p->_value; }
		value_type *operator->() {return &(_p->_value); }
		value_type const *operator->() const {return &(_p->value); }

		protected:
		Node<value_type>* _p;

	};

	template <class U>
	class const_node_iterator : public ft::iterator<bidirectional_iterator_tag, U>
	{

	private:
		typedef ft::iterator<bidirectional_iterator_tag, U> base_iterator;
	public:
		typedef typename ft::iterator<bidirectional_iterator_tag, U>::value_type value_type;
		typedef typename ft::iterator<bidirectional_iterator_tag, U>::reference reference;

		const_node_iterator(Node<value_type> *p = NULL) : _p(p) {};
		~const_node_iterator(){};
		const_node_iterator(const_node_iterator const &other) : _p(other._p){};
		const_node_iterator(node_iterator<U> const &other) : _p(other._p){};

		const_node_iterator &operator=(const_node_iterator const &other)
		{
			_p = other._p;
			return *this;
		}
		const_node_iterator &operator++()
		{
			_p = _p->next();
			return *this;
		}
		const_node_iterator operator++(int)
		{
			const_node_iterator retval = *this;
			++(*this);
			return retval;
		}
		const_node_iterator &operator--()
		{
			_p = _p->prev();
			return *this;
		}
		const_node_iterator operator--(int)
		{
			const_node_iterator retval = *this;
			--(*this);
			return retval;
		}
		bool operator==(const_node_iterator const &other) const { return ( _p == other._p) ; }
		bool operator!=(const_node_iterator const &other) const { return !this->operator==(other); }
		value_type const &operator*() { return _p->_value; }
		value_type const &operator*() const { return _p->_value; }
		value_type const *operator->() {return &(_p->_value); }
		value_type const *operator->() const {return &(_p->value); }

		protected:
		Node<value_type>* _p;

	};

}
#endif
