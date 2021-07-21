/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_node.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 20:19:00 by mroux             #+#    #+#             */
/*   Updated: 2021/07/21 22:37:33 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.hpp"

void test_node()
{
	ft::Node<int> a(1), b(2), c(3), d(4), e(5), f(6), g(7), h(8);

	a._parent = &c;
	a._right = &b;

	b._parent = &a;

	c._left = &a;
	c._right = &f;

	d._parent = &f;
	d._right = &e;

	e._parent = &d;

	f._parent = &c;
	f._left = &d;
	f._right = &h;

	g._parent = &f;

	h._left = &g;
	h._parent = &f;

	std::cout << a._value << b._value << c._value << d._value;
	std::cout << e._value <<f._value << g._value << h._value << std::endl;

	std::cout << ft::Node<int>::leftmost(&c)->_value << std::endl;		//1
	std::cout << ft::Node<int>::leftmost(&f)->_value << std::endl;		//4
	std::cout << ft::Node<int>::rightmost(&c)->_value << std::endl;		//8
	std::cout << ft::Node<int>::rightmost(&f)->_value << std::endl;		//8
	std::cout << ft::Node<int>::rightmost(&d)->_value << std::endl;		//5
	std::cout << "--------" << std::endl;
	std::cout << f.next()->_value << std::endl;							//7
	std::cout << d.prev()->_value << std::endl;							//3
	std::cout << e.next()->_value << std::endl;							//6
	std::cout << c.prev()->_value << std::endl;							//2
}
