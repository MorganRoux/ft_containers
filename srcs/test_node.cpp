/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_node.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 20:19:00 by mroux             #+#    #+#             */
/*   Updated: 2021/07/21 21:19:26 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.hpp"

void test_node()
{
	ft::Node<int> a(1), b(2), c(3), d(4), e(5), f(6), g(7), h(8);

	a.setParent(&c);
	a.setRight(&b);

	b.setParent(&a);

	c.setLeft(&a);
	c.setRight(&f);

	d.setParent(&f);
	d.setRight(&e);

	e.setParent(&d);

	f.setParent(&c);
	f.setLeft(&d);
	f.setRight(&h);

	g.setParent(&f);

	h.setLeft(&g);
	h.setParent(&f);

	std::cout << a.getValue() << b.getValue() << c.getValue() << d.getValue();
	std::cout << e.getValue() <<f.getValue() << g.getValue() << h.getValue() << std::endl;

	std::cout << ft::Node<int>::leftmost(&c)->getValue() << std::endl;		//1
	std::cout << ft::Node<int>::leftmost(&f)->getValue() << std::endl;		//4
	std::cout << ft::Node<int>::rightmost(&c)->getValue() << std::endl;		//8
	std::cout << ft::Node<int>::rightmost(&f)->getValue() << std::endl;		//8
	std::cout << ft::Node<int>::rightmost(&d)->getValue() << std::endl;		//5
	std::cout << "--------" << std::endl;
	std::cout << f.next()->getValue() << std::endl;							//7
	std::cout << d.prev()->getValue() << std::endl;							//3
	std::cout << e.next()->getValue() << std::endl;							//6
	std::cout << c.prev()->getValue() << std::endl;							//2
}
