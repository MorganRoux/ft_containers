#include "ft_vector.hpp"
#include <vector>

int main(void)
{
	std::vector<int> sv1(6), sv2(6);
	std::vector<int>::iterator it1, it2;
	it1 = sv1.begin();
	it2 = sv2.begin();
	std::cout << it1[2] << " - " << it2[2] << " : " << (it1 == it2) << std::endl;

	std::cout << "========" << std::endl;

	ft::vector<int> v1;
	ft::vector<int> v2(6);
	v2[2] = 7;
	const ft::vector<int> v3(v2);
	std::cout << v2[3] << " - " << v2.at(3) << std::endl;
	std::cout << v2[2] << std::endl;
	std::cout << v3[2] << std::endl;
	try
	{
		v2.at(10);
	}
	catch (std::out_of_range &e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		v3.at(10);
	}
	catch (std::out_of_range &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << v1.max_size() << std::endl;

	std::cout << "=========" << std::endl;
	ft::vector<int>::iterator vt1, vt2;
	for (vt1 = v2.begin(); vt1 != v2.end(); ++vt1)
		std::cout << *vt1 << std::endl;

	return 0;
}
