/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 19:22:54 by mroux             #+#    #+#             */
/*   Updated: 2021/07/22 01:21:32 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTNODE_HPP
#define FTNODE_HPP

#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <typeinfo>

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
			while(n->_left != NULL)
				n = n->_left;
			return n;
		}
		static Node*	rightmost(Node *n)
		{
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


}
#endif
