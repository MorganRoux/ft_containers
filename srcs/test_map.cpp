/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 21:19:57 by mroux             #+#    #+#             */
/*   Updated: 2021/07/19 23:38:34 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include "map.hpp"
#include <iostream>
#include "pair.hpp"

class A
	{
	public:
		A() { std::cout << "Constructor " << std::endl; }
		A(const A &other)
		{
			std::cout << "Copy Constructor " << std::endl;
			(void)other;
		}
		~A() { std::cout << "Destructor " << std::endl; }
	};

void test_map()
{


	// {
	// 	std::cout << "--------constructor destructor of pair" << std::endl;
	// 	A a;
	// 	NAMESPACE::pair<std::string, A> t;
	// 	NAMESPACE::pair<std::string, A> test("hello", a);
	// 	std::cout << "Ending" << std::endl;
	// }
	// {
	// 	std::cout << "-------makepair" << std::endl;
	// 	A a;
	// 	NAMESPACE::pair<std::string, A> test = NAMESPACE::make_pair<std::string, A>("hello", a);
	// }
}
