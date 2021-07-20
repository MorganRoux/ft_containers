/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 21:19:57 by mroux             #+#    #+#             */
/*   Updated: 2021/07/20 22:02:01 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include "map.hpp"
#include <iostream>
#include "pair.hpp"



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
		NAMESPACE::map<std::string, std::string> m;
		for (NAMESPACE::map<std::string, std::string>::iterator it = m.begin(); it != m.end(); it++)
		{
			std::cout << (*it).first << (*it).second << std::endl;
		}
		std::cout << m.size() << std::endl;
	}
}
