/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_node.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 20:19:00 by mroux             #+#    #+#             */
/*   Updated: 2021/07/21 21:05:45 by mroux            ###   ########.fr       */
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

	std::cout << a.getValue() << b.getValue() << c.getValue() << d.getValue();
	std::cout << e.getValue() <<f.getValue() << g.getValue() << h.getValue() << std::endl;

	std::cout << ft::Node<int>::leftmost(&c)->getValue() << std::endl;		//1
	std::cout << ft::Node<int>::leftmost(&f)->getValue() << std::endl;		//4
	std::cout << ft::Node<int>::rightmost(&c)->getValue() << std::endl;		//8
	std::cout << ft::Node<int>::rightmost(&f)->getValue() << std::endl;		//8
	std::cout << ft::Node<int>::rightmost(&d)->getValue() << std::endl;		//5

}
