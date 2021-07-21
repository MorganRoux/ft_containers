/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 19:22:54 by mroux             #+#    #+#             */
/*   Updated: 2021/07/21 21:02:32 by mroux            ###   ########.fr       */
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

		Node(U v, Node *left = NULL, Node *right = NULL, Node *parent = NULL) :
			_value(v), _left(left), _right(right), _parent(parent) {};
		~Node(){};

		U 			getValue() { return _value; }
		U const		getValue() const { return _value; }
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

	// private:
		U 			_value;
		Node*		_left;
		Node*		_right;
		Node*		_parent;

		Node() : _value(U()), _left(NULL), _right(NULL), _parent(NULL) {};
		Node*		prevL()
		{
			if (_left != NULL)
				return (rightmost(_left));
			else
				return NULL;
		}
		Node*		prevU()
		{
			Node* cur, up;
			if (_parent == NULL)		//root node
				return NULL;
			cur = this;
			up = _parent;
			while(up._parent != NULL)
			{
				if (up._right == cur)	//left turn
					return up;
				cur = up;
				up = up._parent;
			}
			return NULL;				// no successor
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
			Node*	cur, up;
			if (_parent == NULL)		//root node
				return NULL;
			cur = this;
			up = _parent;
			while(up._parent != NULL)
			{
				if (up._left == cur)	//right turn
					return up;
				cur = up;
				up = up._parent;
			}
			return NULL;				// no successor
		}
	};


}
#endif
