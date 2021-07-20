/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 20:31:38 by mroux             #+#    #+#             */
/*   Updated: 2021/07/20 21:59:42 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "utils.hpp"
#include "metafunctions.hpp"
#include <vector>

void test_other();
void test_vector();
void test_map();

int main(void)
{

	std::cout << "=================OTHERS =================" << std::endl;
	test_other();
	std::cout << "==================VECTORS ====================" << std::endl;
	test_vector();
	std::cout << "================== MAP =======================" << std::endl;
	test_map();
	return 0;
}
