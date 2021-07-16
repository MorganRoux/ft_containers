/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:12:50 by mroux             #+#    #+#             */
/*   Updated: 2021/07/16 09:56:54 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template<class Container>
void print_container(Container c)
{
	std::cout << "=== Container ===" << std::endl;
	for (typename Container::iterator it = c.begin(); it != c.end(); it++)
		std::cout << *it << std::endl;
		std::cout << "======" << std::endl;
}
