/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 13:18:19 by mroux             #+#    #+#             */
/*   Updated: 2021/07/25 14:42:06 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stack>
#include "stack.hpp"

void test_stack()
{

	{
		NAMESPACE::stack<int> mystack;
		int sum(0);
		for (int i = 1; i <= 10; i++)
			mystack.push(i);
		while (!mystack.empty())
		{
			sum += mystack.top();
			mystack.pop();
		}
		std::cout << "total: " << sum << '\n';
	}
	{
		std::cout << "Size" << std::endl;
		NAMESPACE::stack<int> myints;
		std::cout << "0. size: " << myints.size() << '\n';

		for (int i = 0; i < 5; i++)
			myints.push(i);
		std::cout << "1. size: " << myints.size() << '\n';

		myints.pop();
		std::cout << "2. size: " << myints.size() << '\n';
	}
	{

		NAMESPACE::stack<int> mystack;

		mystack.push(10);
		mystack.push(20);

		mystack.top() -= 5;

		std::cout << "mystack.top() is now " << mystack.top() << '\n';
	}
	{

		NAMESPACE::stack<int> mystack;

		for (int i = 0; i < 5; ++i)
			mystack.push(i);

		std::cout << "Popping out elements...";
		while (!mystack.empty())
		{
			std::cout << ' ' << mystack.top();
			mystack.pop();
		}
		std::cout << '\n';
	}

	{
		std::cout << "!====" << std::endl;
		NAMESPACE::stack<std::string> mystacks;
		mystacks.push("hello");
		mystacks.push("1");
		mystacks.push("2");
		mystacks.push("3");
		NAMESPACE::stack<std::string> mystack2(mystacks);

		std::cout << mystacks.size() << mystack2.size() << std::endl;

		std::cout << "---comp" << std::endl;
		std::cout << (mystack2 == mystacks) << std::endl;
		std::cout << (mystack2 != mystacks) << std::endl;
		std::cout << (mystack2 >= mystacks) << std::endl;
		std::cout << (mystack2 <= mystacks) << std::endl;
		std::cout << (mystack2 < mystacks) << std::endl;
		std::cout << (mystack2 > mystacks) << std::endl;

		mystacks.push("new");

		std::cout << "---comp2" << std::endl;
		std::cout << (mystack2 == mystacks) << std::endl;
		std::cout << (mystack2 != mystacks) << std::endl;
		std::cout << (mystack2 >= mystacks) << std::endl;
		std::cout << (mystack2 <= mystacks) << std::endl;
		std::cout << (mystack2 < mystacks) << std::endl;
		std::cout << (mystack2 > mystacks) << std::endl;

		while (!mystacks.empty())
		{
			std::cout << mystacks.top() << std::endl;
			std::cout << mystacks.size() << std::endl;
			mystacks.pop();
		}

		//comparaison between empty

		NAMESPACE::stack<std::string> mystack3(mystacks);
		std::cout << mystacks.size() << mystack3.size() << std::endl;
		std::cout << "---comp" << std::endl;
		std::cout << (mystack3 == mystacks) << std::endl;
		std::cout << (mystack3 != mystacks) << std::endl;
		std::cout << (mystack3 >= mystacks) << std::endl;
		std::cout << (mystack3 <= mystacks) << std::endl;
		std::cout << (mystack3 < mystacks) << std::endl;
		std::cout << (mystack3 > mystacks) << std::endl;

		mystacks.push("new");

		std::cout << "---comp2" << std::endl;
		std::cout << (mystack2 == mystacks) << std::endl;
		std::cout << (mystack2 != mystacks) << std::endl;
		std::cout << (mystack2 >= mystacks) << std::endl;
		std::cout << (mystack2 <= mystacks) << std::endl;
		std::cout << (mystack2 < mystacks) << std::endl;
		std::cout << (mystack2 > mystacks) << std::endl;
	}
}
