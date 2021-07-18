/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 09:47:54 by mroux             #+#    #+#             */
/*   Updated: 2021/07/18 09:53:19 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTSTACK_HPP
#define FTSTACK_HPP
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <typeinfo>
#include "ft_iterator.hpp"
#include "metafunctions.hpp"
#include "vector.hpp"

namespace ft
{

	template <class U>
	class ra_iterator : public ft::iterator<random_access_iterator_tag, U>
	{
	};

	template <class T, class Container = ft::vector<T>>
	class stack
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_type typename container_type::size_type;

		explicit stack(const container_type &ctnr = container_type());
		bool empty() const;
		size_type size() const;
		value_type &top();
		const value_type &top() const;
		void push(const value_type &val);
		void pop();
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs);

	template <class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs);

	template <class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs);

	template <class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs);

	template <class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs);

	template <class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs);
}
