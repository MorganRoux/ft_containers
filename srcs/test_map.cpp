/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 21:19:57 by mroux             #+#    #+#             */
/*   Updated: 2021/07/25 13:03:57 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include "map.hpp"
#include <iostream>
#include "pair.hpp"
#include <cstdio>

template <class Key, class Value>
void print_map(NAMESPACE::map<Key, Value> const &m)
{
	if (m.empty())
		return;
	for (typename NAMESPACE::map<Key, Value>::const_iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << " - " << it->second << std::endl;
	//std::cout << m.size() << std::endl;
}

void test_map()
{
	std::cout << "constructor / desctructor" << std::endl;
	{
		NAMESPACE::map<std::string, std::string> m;
		for (NAMESPACE::map<std::string, std::string>::iterator it = m.begin(); it != m.end(); it++)
		{
			std::cout << (*it).first << (*it).second << std::endl;
		}
		std::cout << m.size() << std::endl;
	}
	{
		NAMESPACE::map<int, int> m;
		NAMESPACE::map<int, int>::iterator it;
		NAMESPACE::map<int, int>::reverse_iterator rit;

		it = m.insert(NAMESPACE::pair<int, int>(4, 4)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(1, 1)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(8, 8)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(5, 5)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(3, 3)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(2, 2)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(3, 6)).first;
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

		std::cout << "erase by position and erase by key" << std::endl;
		print_map(m);
		it = m.begin();
		it++;
		m.erase(it);
		m.erase(3);
		std::cout << "---" << std::endl;
		print_map(m);

		it = m.insert(NAMESPACE::pair<int, int>(14, 4)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(11, 1)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(18, 8)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(15, 5)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(13, 3)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(12, 2)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(13, 6)).first;
		std::cout << (*it).second << std::endl;

		print_map(m);
		//m.analyse_map(10);
		std::cout << "-1--" << std::endl;
		it = m.begin();
		std::cout << "delete " << it->first << std::endl;
		m.erase(it);
		print_map(m);
		//m.analyse_map(10);
		std::cout << "-2--" << std::endl;
		it = m.begin();
		std::cout << "delete " << it->first << std::endl;
		m.erase(it);
		print_map(m);
		//m.analyse_map(10);
		std::cout << "-3--" << std::endl;
		it = m.begin();
		std::cout << "delete " << it->first << std::endl;
		m.erase(it);
		print_map(m);
		//m.analyse_map(10);
		std::cout << "--4-" << std::endl;
		it = m.begin();
		std::cout << "delete " << it->first << std::endl;
		m.erase(it);
		print_map(m);
		//m.analyse_map(10);
		std::cout << "-5--" << std::endl;
		it = m.begin();
		std::cout << "delete " << it->first << std::endl;
		m.erase(it);
		print_map(m);
		//m.analyse_map(10);
		std::cout << "-6--" << std::endl;
		it = m.begin();
		std::cout << "delete " << it->first << std::endl;
		m.erase(it);
		print_map(m);
		//m.analyse_map(10);
		std::cout << "--7-" << std::endl;
		it = m.begin();
		std::cout << "delete " << it->first << std::endl;
		m.erase(it);
		print_map(m);
		std::cout << "-8--" << std::endl;
		it = m.begin();
		std::cout << "delete " << it->first << std::endl;
		m.erase(it);
		print_map(m);
		std::cout << "--9-" << std::endl;
		it = m.begin();
		m.erase(it);
		print_map(m);
		//m.analyse_map(10);
		std::cout << "-10--" << std::endl;
		it = m.begin();
		m.erase(it);
		print_map(m);
		//m.analyse_map(10);

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
		it = m.insert(NAMESPACE::pair<int, int>(4, 4)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(1, 1)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(8, 8)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(5, 5)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(3, 3)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(2, 2)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(9, 9)).first;
		std::cout << (*it).second << std::endl;
		print_map(m);
		m.erase(5);
		print_map(m);

		std::cout << "erase range" << std::endl;
		it = m.insert(NAMESPACE::pair<int, int>(14, 4)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(11, 1)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(18, 8)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(15, 5)).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<int, int>(13, 3)).first;
		print_map(m);
		{
			NAMESPACE::map<int, int>::iterator itkb = m.begin();
			NAMESPACE::map<int, int>::iterator itke = m.end();
			itkb++;
			itkb++;
			itke--;
			itke--;
			itke--;
			std::cout << "---" << std::endl;
			m.erase(itkb, itke);
			print_map(m);
		}

		std::cout << "bounds" << std::endl;
		std::cout << (*(m.lower_bound(3))).second << std::endl;
		std::cout << (*(m.upper_bound(3))).second << std::endl;
		std::cout << (*(m.equal_range(3).first)).second << std::endl;
		std::cout << m.count(5) << m.count(10) << std::endl;
		std::cout << m[5] << m[10] << std::endl;

		std::cout << "clear" << std::endl;
		{
			NAMESPACE::map<int, int> m2 = m;
			m2.clear();
			print_map(m2);
		}

		std::cout << "swap" << std::endl;
		{
			NAMESPACE::map<int, int> m2;
			it = m2.insert(NAMESPACE::pair<int, int>(8, 8)).first;
			std::cout << (*it).second << std::endl;
			it = m2.insert(NAMESPACE::make_pair<int, int>(11, 1)).first;
			std::cout << (*it).second << std::endl;
			it = m2.insert(NAMESPACE::make_pair<int, int>(81, 8)).first;
			std::cout << (*it).second << std::endl;
			it = m2.insert(NAMESPACE::make_pair<int, int>(51, 5)).first;
			std::cout << (*it).second << std::endl;
			it = m2.insert(NAMESPACE::make_pair<int, int>(31, 3)).first;
			std::cout << (*it).second << std::endl;
			it = m2.insert(NAMESPACE::make_pair<int, int>(12, 2)).first;
			std::cout << (*it).second << std::endl;
			it = m2.insert(NAMESPACE::make_pair<int, int>(19, 9)).first;

			print_map(m);
			print_map(m2);
			m.swap(m2);
			std::cout << "ok" << std::endl;
			print_map(m);
			print_map(m2);
		}
		std::cout << "operator=" << std::endl;
		{
			std::map<char, int> first;
			std::map<char, int> second;

			first['x'] = 8;
			first['y'] = 16;
			first['z'] = 32;

			second = first;				   // second now contains 3 ints
			first = std::map<char, int>(); // and first is now empty

			std::cout << "Size of first: " << first.size() << '\n';
			std::cout << "Size of second: " << second.size() << '\n';
		}
	}

	std::cout << "=============== with strings =============" << std::endl;
	{
		NAMESPACE::map<std::string, std::string> m;
		NAMESPACE::map<std::string, std::string>::iterator it;
		NAMESPACE::map<std::string, std::string>::reverse_iterator rit;

		it = m.insert(NAMESPACE::pair<std::string, std::string>("4", "4")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("1", "1")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("8", "8")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("5", "5")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("3", "3")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("2", "2")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("3", "6")).first;
		std::cout << (*it).second << std::endl;

		std::cout << "iterator" << std::endl;
		for (it = m.begin(); it != m.end(); it++)
			std::cout << (*it).first << (*it).second << std::endl;
		std::cout << "reverse iterator" << std::endl;

		for (rit = m.rbegin(); rit != m.rend(); rit++)
			std::cout << (*rit).first << (*rit).second << std::endl;

		NAMESPACE::map<std::string, std::string>::const_iterator cit(it);
		for (cit = m.begin(); cit != m.end(); cit++)
			std::cout << (*cit).first << cit->second << std::endl;
		it->second = "1000";
		// Should not compile
		// cit->second = 3;
		std::cout << "operator ->" << std::endl;
		std::cout << it->second << cit->second << std::endl;

		std::cout << "erase by position and erase by key" << std::endl;
		print_map(m);
		it = m.begin();
		it++;
		m.erase(it);
		m.erase("3");
		std::cout << "---" << std::endl;
		print_map(m);

		it = m.insert(NAMESPACE::pair<std::string, std::string>("14", "4")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("11", "1")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("18", "8")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("15", "5")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("13", "3")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("12", "2")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("13", "6")).first;
		std::cout << (*it).second << std::endl;

		print_map(m);
		//m.analyse_map(10);
		std::cout << "-1--" << std::endl;
		it = m.begin();
		std::cout << "delete " << it->first << std::endl;
		m.erase(it);
		print_map(m);
		//m.analyse_map(10);
		std::cout << "-2--" << std::endl;
		it = m.begin();
		std::cout << "delete " << it->first << std::endl;
		m.erase(it);
		print_map(m);
		//m.analyse_map(10);
		std::cout << "-3--" << std::endl;
		it = m.begin();
		std::cout << "delete " << it->first << std::endl;
		m.erase(it);
		print_map(m);
		//m.analyse_map(10);
		std::cout << "--4-" << std::endl;
		it = m.begin();
		std::cout << "delete " << it->first << std::endl;
		m.erase(it);
		print_map(m);
		//m.analyse_map(10);
		std::cout << "-5--" << std::endl;
		it = m.begin();
		std::cout << "delete " << it->first << std::endl;
		m.erase(it);
		print_map(m);
		//m.analyse_map(10);
		std::cout << "-6--" << std::endl;
		it = m.begin();
		std::cout << "delete " << it->first << std::endl;
		m.erase(it);
		print_map(m);
		//m.analyse_map(10);
		std::cout << "--7-" << std::endl;
		it = m.begin();
		std::cout << "delete " << it->first << std::endl;
		m.erase(it);
		print_map(m);
		std::cout << "-8--" << std::endl;
		it = m.begin();
		std::cout << "delete " << it->first << std::endl;
		m.erase(it);
		print_map(m);
		std::cout << "--9-" << std::endl;
		it = m.begin();
		m.erase(it);
		print_map(m);
		//m.analyse_map(10);
		std::cout << "-10--" << std::endl;
		it = m.begin();
		m.erase(it);
		print_map(m);
		//m.analyse_map(10);

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
		it = m.insert(NAMESPACE::pair<std::string, std::string>("4", "4")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("1", "1")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("8", "8")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("5", "5")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("3", "3")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("2", "2")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("9", "9")).first;
		std::cout << (*it).second << std::endl;
		print_map(m);
		m.erase("5");
		print_map(m);

		std::cout << "erase range" << std::endl;
		it = m.insert(NAMESPACE::pair<std::string, std::string>("14", "4")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("11", "1")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("18", "8")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("15", "5")).first;
		std::cout << (*it).second << std::endl;
		it = m.insert(NAMESPACE::make_pair<std::string, std::string>("13", "3")).first;
		print_map(m);
		{
			NAMESPACE::map<std::string, std::string>::iterator itkb = m.begin();
			NAMESPACE::map<std::string, std::string>::iterator itke = m.end();
			itkb++;
			itkb++;
			itke--;
			itke--;
			itke--;
			std::cout << "---" << std::endl;
			m.erase(itkb, itke);
			print_map(m);
		}

		std::cout << "bounds" << std::endl;
		std::cout << (*(m.lower_bound("3"))).second << std::endl;
		std::cout << (*(m.upper_bound("3"))).second << std::endl;
		std::cout << (*(m.equal_range("3").first)).second << std::endl;
		std::cout << m.count("5") << m.count("10") << std::endl;
		std::cout << m["5"] << m["10"] << std::endl;

		std::cout << "clear" << std::endl;
		{
			NAMESPACE::map<std::string, std::string> m2 = m;
			m2.clear();
			print_map(m2);
		}

		std::cout << "swap" << std::endl;
		{
			NAMESPACE::map<std::string, std::string> m2;
			it = m2.insert(NAMESPACE::pair<std::string, std::string>("8", "8")).first;
			std::cout << (*it).second << std::endl;
			it = m2.insert(NAMESPACE::make_pair<std::string, std::string>("11", "1")).first;
			std::cout << (*it).second << std::endl;
			it = m2.insert(NAMESPACE::make_pair<std::string, std::string>("81", "8")).first;
			std::cout << (*it).second << std::endl;
			it = m2.insert(NAMESPACE::make_pair<std::string, std::string>("51", "5")).first;
			std::cout << (*it).second << std::endl;
			it = m2.insert(NAMESPACE::make_pair<std::string, std::string>("31", "3")).first;
			std::cout << (*it).second << std::endl;
			it = m2.insert(NAMESPACE::make_pair<std::string, std::string>("12", "2")).first;
			std::cout << (*it).second << std::endl;
			it = m2.insert(NAMESPACE::make_pair<std::string, std::string>("19", "9")).first;

			print_map(m);
			print_map(m2);
			m.swap(m2);
			std::cout << "ok" << std::endl;
			print_map(m);
			print_map(m2);
		}
		std::cout << "operator=" << std::endl;
		{
			std::map<std::string, std::string> first;
			std::map<std::string, std::string> second;

			first["x"] = "8";
			first["y"] = "16";
			first["z"] = "32";

			second = first;								  // second now contains 3 ints
			first = std::map<std::string, std::string>(); // and first is now empty

			std::cout << "Size of first: " << first.size() << '\n';
			std::cout << "Size of second: " << second.size() << '\n';
		}
	}

	std::cout << "---------- with const -------------"<< std::endl;
	std::cout << "constructor / desctructor" << std::endl;
	{
		const NAMESPACE::map<std::string, std::string> m;
		for (NAMESPACE::map<std::string, std::string>::const_iterator it = m.begin(); it != m.end(); it++)
		{
			std::cout << (*it).first << (*it).second << std::endl;
		}
		std::cout << m.size() << std::endl;
	}
	{
		NAMESPACE::map<int, int> m0;
		NAMESPACE::map<int, int>::const_iterator it;
		NAMESPACE::map<int, int>::const_reverse_iterator rit;

		m0.insert(NAMESPACE::pair<int, int>(4, 4));
		m0.insert(NAMESPACE::make_pair<int, int>(1, 1));
		m0.insert(NAMESPACE::make_pair<int, int>(8, 8));
		m0.insert(NAMESPACE::make_pair<int, int>(5, 5));
		m0.insert(NAMESPACE::make_pair<int, int>(3, 3));
		m0.insert(NAMESPACE::make_pair<int, int>(2, 2));
		m0.insert(NAMESPACE::make_pair<int, int>(3, 6));

		const NAMESPACE::map<int, int> m(m0);

		std::cout << "iterator" << std::endl;
		for (it = m.begin(); it != m.end(); it++)
			std::cout << (*it).first << (*it).second << std::endl;
		std::cout << "iterator" << std::endl;
		for (it = m0.begin(); it != m0.end(); it++)
			std::cout << (*it).first << (*it).second << std::endl;

		std::cout << "reverse iterator" << std::endl;

		// m.analyse_map(10);
		// m0.analyse_map(10);
		for (rit = m.rbegin(); rit != m.rend(); rit++)
			std::cout << (*rit).first << (*rit).second << std::endl;
		for (rit = m0.rbegin(); rit != m0.rend(); rit++)
			std::cout << (*rit).first << (*rit).second << std::endl;

		NAMESPACE::map<int, int>::const_iterator cit(it);
		for (cit = m.begin(); cit != m.end(); cit++)
			std::cout << (*cit).first << cit->second << std::endl;
		for (cit = m0.begin(); cit != m0.end(); cit++)
			std::cout << (*cit).first << cit->second << std::endl;

		std::cout << "operator ->" << std::endl;
		// std::cout << it->second << cit->second << std::endl;

		std::cout << "bounds" << std::endl;
		std::cout << (*(m.lower_bound(3))).second << std::endl;
		std::cout << (*(m.upper_bound(3))).second << std::endl;
		std::cout << (*(m.equal_range(3).first)).second << std::endl;
		std::cout << m.count(5) << m.count(10) << std::endl;

	}
}
