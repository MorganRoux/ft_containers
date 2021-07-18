/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 09:47:54 by mroux             #+#    #+#             */
/*   Updated: 2021/07/18 09:59:32 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTSTACK_HPP
#define FTSTACK_HPP
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <typeinfo>
#include "metafunctions.hpp"
#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T>>
	class stack
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_type typename container_type::size_type;

		explicit stack(const container_type &ctnr = container_type()): _cntr(cntr) {};
		bool empty() const { return cntr.empty();}
		size_type size() const { return cntr.size();}
		value_type &top() { return cntr.back(); }
		const value_type &top() const { return cntr.back(); }
		void push(const value_type &val) { cntr.push_back(val); }
		void pop() { cntr.pop_back(); }

	private:
		container_type cntr;
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return (lhs.cntr == rhs.cntr); }

	template <class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return !(lhs == rhs); }

	template <class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return (lhs.cntr < rhs.cntr); }

	template <class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return !(lhs > rhs); }

	template <class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return (rhs < lhs); }

	template <class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return !(lhs < rhs); }
}
