/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metafunctions.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 15:59:55 by mroux             #+#    #+#             */
/*   Updated: 2021/07/19 20:16:33 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	// ========================== integral_constant =====================//
	template <class T, T v>
	struct integral_constant
	{
		typedef T value_type;
		typedef integral_constant<T, v> type;
		static constexpr value_type value = v;
		constexpr operator value_type() { return v; }
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

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

	// ====================== is_integral ===================== //
	template <typename>
	struct is_integral
	{
		typedef bool value_type;
		typedef false_type type;
	};

	template <>
	struct is_integral<bool>
	{
		typedef bool value_type;
		typedef true_type type;
	};

	template <>
	struct is_integral<char>
	{
		typedef bool value_type;
		typedef true_type type;
	};

	template <>
	struct is_integral<char16_t>
	{
		typedef bool value_type;
		typedef true_type type;
	};

	template <>
	struct is_integral<char32_t>
	{
		typedef bool value_type;
		typedef true_type type;
	};

	template <>
	struct is_integral<wchar_t>
	{
		typedef bool value_type;
		typedef true_type type;
	};

	template <>
	struct is_integral<signed char>
	{
		typedef bool value_type;
		typedef true_type type;
	};

	template <>
	struct is_integral<short int>
	{
		typedef bool value_type;
		typedef true_type type;
	};

	template <>
	struct is_integral<int>
	{
		typedef bool value_type;
		typedef true_type type;
	};

	template <>
	struct is_integral<long int>
	{
		typedef bool value_type;
		typedef true_type type;
	};
	template <>
	struct is_integral<long long int>
	{
		typedef bool value_type;
		typedef true_type type;
	};

	template <>
	struct is_integral<unsigned char>
	{
		typedef bool value_type;
		typedef true_type type;
	};

	template <>
	struct is_integral<unsigned short int>
	{
		typedef bool value_type;
		typedef true_type type;
	};

	template <>
	struct is_integral<unsigned int>
	{
		typedef bool value_type;
		typedef true_type type;
	};

	template <>
	struct is_integral<unsigned long int>
	{
		typedef bool value_type;
		typedef true_type type;
	};

	template <>
	struct is_integral<unsigned long long int>
	{
		typedef bool value_type;
		typedef true_type type;
	};


	// ================================ equal ================================ //
	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1,
			   InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	// ============================== lexicographical_compare ==================================== //

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2,
								 Compare comp)
	{
		while (comp(first1, last1) || comp(last1, first1))
		{
			if (
				(!comp(first2, last2) && !comp(last2, first2)) // first2 == last2
				||
				comp(*first2, *first1) //*first2 < *first1
			)
				return false;
			else if (comp(*first1, *first2)) // //*first1 < *first2
				return true;
			++first1;
			++first2;
		}
		return (comp(first2, last2) || comp(last2, first2)); //first2 != last2);
	}
};
