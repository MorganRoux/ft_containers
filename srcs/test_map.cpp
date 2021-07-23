/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 21:19:57 by mroux             #+#    #+#             */
/*   Updated: 2021/07/23 14:49:07 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include "map.hpp"
#include <iostream>
#include "pair.hpp"



void test_map()
{
	// std::cout << "constructor / desctructor" << std::endl;
	// {
	// 	NAMESPACE::map<std::string, std::string> m;
	// 	for (NAMESPACE::map<std::string, std::string>::iterator it = m.begin(); it != m.end(); it++)
	// 	{
	// 		std::cout << (*it).first << (*it).second << std::endl;
	// 	}
	// 	std::cout << m.size() << std::endl;
	// }
	// {
	// 	NAMESPACE::map<std::string, std::string> m;
	// 	for (NAMESPACE::map<std::string, std::string>::iterator it = m.begin(); it != m.end(); it++)
	// 	{
	// 		std::cout << (*it).first << (*it).second << std::endl;
	// 	}
	// 	std::cout << m.size() << std::endl;
	// }
	{
	NAMESPACE::map<int, int> m;
	NAMESPACE::map<int, int>::iterator it;
	NAMESPACE::map<int, int>::reverse_iterator rit;

	it = m.insert(NAMESPACE::pair<int,int>(4, 4)).first;
	std::cout << (*it).second << std::endl;
	it = m.insert(NAMESPACE::make_pair<int,int>(1, 1)).first;
	std::cout << (*it).second << std::endl;
	it = m.insert(NAMESPACE::make_pair<int,int>(8, 8)).first;
	std::cout << (*it).second << std::endl;
	it = m.insert(NAMESPACE::make_pair<int,int>(5, 5)).first;
	std::cout << (*it).second << std::endl;
	it = m.insert(NAMESPACE::make_pair<int,int>(3, 3)).first;
	std::cout << (*it).second << std::endl;
	it = m.insert(NAMESPACE::make_pair<int,int>(2, 2)).first;
	std::cout << (*it).second << std::endl;
	it = m.insert(NAMESPACE::make_pair<int,int>(3, 6)).first;
	std::cout << (*it).second << std::endl;

	std::cout << "iterator" << std::endl;
	for (it = m.begin(); it != m.end(); it++)
		std::cout << (*it).first << (*it).second << std::endl;
	std::cout << "reverse iterator" << std::endl;

	for (rit = m.rbegin(); rit != m.rend(); rit++)
		std::cout << (*rit).first << (*rit).second << std::endl;

	NAMESPACE::map<int, int>::const_iterator cit(it);
	for (; cit != m.end(); cit++)
		std::cout << (*cit).first << std::endl;

	}
}
