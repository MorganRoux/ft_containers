

#include "vector.hpp"
#include "utils.hpp"
#include "metafunctions.hpp"
#include "pair.hpp"


void test_other()
{
	std::cout << "Is Integral" << std::endl;
	std::cout << NAMESPACE::is_integral<ft::vector<int> >::value << '\n';
	std::cout << NAMESPACE::is_integral<float>::value << '\n';
	std::cout << NAMESPACE::is_integral<signed char>::value << '\n';
	std::cout << NAMESPACE::is_integral<const int>::value << '\n';
	std::cout << NAMESPACE::is_integral<bool>::value << '\n';

	std::cout << "Pairs" << std::endl;
	{
		NAMESPACE::pair<int, float> p1, p2(4, 6.8);
		NAMESPACE::pair<long, double> p3(p2);

		p1 = p2;
		std::cout << p1.first << p1.second << std::endl;
		std::cout << p2.first << p2.second << std::endl;
		std::cout << p3.first << p3.second << std::endl;
		std::cout << NAMESPACE::make_pair(7,8).first << NAMESPACE::make_pair(7,8).second << std::endl;
		p1 = NAMESPACE::make_pair(7,8);
		std::cout << (p1 == p2) << std::endl;
		std::cout << (p1 != p2) << std::endl;
		std::cout << (p1 <= p2) << std::endl;
		std::cout << (p1 >= p2) << std::endl;
		std::cout << (p1 < p2 ) << std::endl;
		std::cout << (p1 > p2 ) << std::endl;

	}


}
