/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 21:19:57 by mroux             #+#    #+#             */
/*   Updated: 2021/07/23 17:37:25 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include "map.hpp"
#include <iostream>
#include "pair.hpp"

template<class Key, class Value>
void print_map(NAMESPACE::map<Key, Value> const& m)
{
	if (m.empty())
		return;
	for (typename NAMESPACE::map<Key, Value>::const_iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << " - " << it->second << std::endl;
	std::cout << m.size() << std::endl;
}

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
	for (cit = m.begin(); cit != m.end(); cit++)
		std::cout << (*cit).first << cit->second << std::endl;
	it->second = 1000;
	// Should not compile
	// cit->second = 3;
	std::cout << "operator ->" << std::endl;
	std::cout << it->second << cit->second << std::endl;

	std::cout << "erase " << std::endl;
	print_map(m);
	it = m.begin();
	it++;
	m.erase(it);
	m.erase(3);
	std::cout << "---" << std::endl;
	print_map(m);

	it = m.insert(NAMESPACE::pair<int,int>(14, 4)).first;
	std::cout << (*it).second << std::endl;
	it = m.insert(NAMESPACE::make_pair<int,int>(11, 1)).first;
	std::cout << (*it).second << std::endl;
	it = m.insert(NAMESPACE::make_pair<int,int>(18, 8)).first;
	std::cout << (*it).second << std::endl;
	it = m.insert(NAMESPACE::make_pair<int,int>(15, 5)).first;
	std::cout << (*it).second << std::endl;
	it = m.insert(NAMESPACE::make_pair<int,int>(13, 3)).first;
	std::cout << (*it).second << std::endl;
	it = m.insert(NAMESPACE::make_pair<int,int>(12, 2)).first;
	std::cout << (*it).second << std::endl;
	it = m.insert(NAMESPACE::make_pair<int,int>(13, 6)).first;
	std::cout << (*it).second << std::endl;

	std::cout << "---" << std::endl;
	print_map(m);
	std::cout << "==" << std::endl;
	it = m.begin();
	m.erase(it);
	print_map(m);
	std::cout << "---" << std::endl;
	it = m.begin();
	m.erase(it);
	print_map(m);
	std::cout << "---" << std::endl;
	it = m.begin();
	m.erase(it);
	print_map(m);
	std::cout << "---" << std::endl;
	it = m.begin();
	m.erase(it);
	print_map(m);
	std::cout << "---" << std::endl;
	it = m.begin();
	m.erase(it);
	print_map(m);
	std::cout << "---" << std::endl;
	it = m.begin();
	m.erase(it);
	print_map(m);
	std::cout << "---" << std::endl;
	it = m.begin();
	m.erase(it);
	print_map(m);
	std::cout << "---" << std::endl;
	it = m.begin();
	m.erase(it);
	print_map(m);
	std::cout << "---" << std::endl;
	it = m.begin();
	m.erase(it);
	print_map(m);
	std::cout << "---" << std::endl;
	it = m.begin();
	m.erase(it);
	print_map(m);

	// Bug of the std::map
	// std::cout << "---" << std::endl;
	// it = m.begin();
	// m.erase(it);
	// print_map(m);
	// std::cout << "already empty---" << std::endl;
	// it = m.begin();
	// m.erase(it);
	// print_map(m);

	std::cout << "erasing root" << std::endl;
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
	it = m.insert(NAMESPACE::make_pair<int,int>(9, 9)).first;
	std::cout << (*it).second << std::endl;
	print_map(m);
	m.erase(5);
	print_map(m);

	}
}
