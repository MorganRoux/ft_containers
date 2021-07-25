/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metafunctions.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 15:59:55 by mroux             #+#    #+#             */
/*   Updated: 2021/07/25 11:13:02 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMETAFUNCTIONS_HPP
#define FTMETAFUNCTIONS_HPP
#include <cstddef>
#include <typeinfo>
namespace ft
{
	// ======================== enable_if ======================= //
	template <bool B, class T = void>
	struct enable_if
	{
	};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <bool B, class T = void>
	struct enable_if_not
	{
	};

	template <class T>
	struct enable_if_not<false, T>
	{
		typedef T type;
	};


//https://stackoverflow.com/questions/43571962/how-is-stdis-integral-implemented


	// ========================== integral_constant =====================//
	template <class T, T v>
	struct integral_constant
	{
		typedef T value_type;
		typedef integral_constant<T, v> type;
		static const value_type value = v;
		operator value_type() { return v; }
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	// ================================ remove_cv =========================//
	template <class T>
	struct remove_cv
	{
		typedef T type;
	};
	template <class T>
	struct remove_cv<const T>
	{
		typedef T type;
	};
	template <class T>
	struct remove_cv<volatile T>
	{
		typedef T type;
	};
	template <class T>
	struct remove_cv<const volatile T>
	{
		typedef T type;
	};

	// ====================== is_integral ===================== //
	template <typename>
	struct is_integral_base : ft::false_type
	{
	};

	template <>
	struct is_integral_base<bool> : ft::true_type
	{
	};

	template <>
	struct is_integral_base<char> : ft::true_type
	{
	};

	template <>
	struct is_integral_base<wchar_t> : ft::true_type
	{
	};

	template <>
	struct is_integral_base<signed char> : ft::true_type
	{
	};

	template <>
	struct is_integral_base<short int> : ft::true_type
	{
	};

	template <>
	struct is_integral_base<int> : ft::true_type
	{
	};

	template <>
	struct is_integral_base<long int> : ft::true_type
	{
	};

	template <>
	struct is_integral_base<long long int> : ft::true_type
	{
	};

	template <>
	struct is_integral_base<unsigned char> : ft::true_type
	{
	};

	template <>
	struct is_integral_base<unsigned short int> : ft::true_type
	{
	};
	template <>
	struct is_integral_base<unsigned int> : ft::true_type
	{
	};

	template <>
	struct is_integral_base<unsigned long int> : ft::true_type
	{
	};

	template <>
	struct is_integral_base<unsigned long long int> : ft::true_type
	{
	};

	template<class T>
	struct is_integral : is_integral_base<typename ft::remove_cv<T>::type > {};



	// ============================ is_iterator ===========================//
	template <typename isIterator>
	class is_iterator
	{
	public:
		typedef char yes[1];
		typedef char no[2];
		// Types "yes" and "no" are guaranteed to have different sizes,
		// specifically sizeof(yes) == 1 and sizeof(no) == 2.

		template <typename isIter>
		static yes &test(typename ft::iterator_traits<isIter>::iterator_category * = NULL); // selected if C is a class type

		template <typename>
		static no &test(...); // selected otherwise

		// If the "sizeof" of the result of calling test<T>(nullptr) is equal to
		// sizeof(yes), the first overload worked and T has a nested type named
		// iterator_category.
		static bool const value = sizeof(test<isIterator>(NULL)) == sizeof(yes);
	};
};

#endif
