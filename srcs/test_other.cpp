

#include "vector.hpp"
#include "utils.hpp"
#include "metafunctions.hpp"



void test_other()
{
	std::cout << "Is Integral" << std::endl;
	std::cout << NAMESPACE::is_integral<ft::vector<int> >::value << '\n';
	std::cout << NAMESPACE::is_integral<float>::value << '\n';
	std::cout << NAMESPACE::is_integral<signed char>::value << '\n';
	std::cout << NAMESPACE::is_integral<const int>::value << '\n';
	std::cout << NAMESPACE::is_integral<bool>::value << '\n';


}
