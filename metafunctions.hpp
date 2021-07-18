/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metafunctions.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 15:59:55 by mroux             #+#    #+#             */
/*   Updated: 2021/07/18 10:08:12 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef METAFUNCTIONS_HPP
#define METAFUNCTIONS_HPP
#include "ft_iterator.hpp"

namespace ft
{
	template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> {
        typedef T type;
    };

    template<typename isIterator>
    class is_iterator {
        public:
            typedef char yes[1];
            typedef char no [2];
            // Types "yes" and "no" are guaranteed to have different sizes,
            // specifically sizeof(yes) == 1 and sizeof(no) == 2.

            template<typename isIter>
            static yes& test(typename ft::iterator_traits<isIter>::iterator_category* = NULL);    // selected if C is a class type

            template<typename>
            static no&  test(...);                         // selected otherwise

            // If the "sizeof" of the result of calling test<T>(nullptr) is equal to
            // sizeof(yes), the first overload worked and T has a nested type named
            // iterator_category.
            static bool const value = sizeof(test<isIterator>(NULL)) == sizeof(yes);
    };


};


#endif
