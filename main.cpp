#include "ft_vector.hpp"
#include "ft_iterator.hpp"
#include <vector>

int main(void)
{
	std::vector<int> sv1(6), sv2(6);
	std::vector<int>::iterator it1, it2;
	it1 = sv1.begin();
	it2 = sv2.begin();
	std::cout << it1[2] << " - " << it2[2] << " : " << (it1 == it2) << std::endl;
	std::cout << "diff: " << sv1.end() - sv1.begin() << " - " << sv1.rend() - sv1.rbegin() << std::endl;
	std::cout << "1. ========" << std::endl;

	ft::vector<int> v1;
	ft::vector<int> v2(6);
	v2[1] = 1; v2[2] = 7; v2[3] = 8;
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

	std::cout << "2. =========" << std::endl;
	ft::vector<int>::iterator vt1;
	for (vt1 = v2.begin(); vt1 != v2.end(); ++vt1)
		std::cout << *vt1 << std::endl;

	std::cout << "diff: " << v2.end() - v2.begin() << " - " << v2.rend() - v2.rbegin() << std::endl;
	std::cout << "3. =========" << std::endl;
	ft::vector<int>::reverse_iterator vr1;
	for (vr1 = v2.rbegin(); vr1 != v2.rend(); ++vr1)
		std::cout << *vr1 << std::endl;

	std::cout << "4. =========" << std::endl;
	std::vector<int>::const_iterator cit;
	const ft::vector<int> cv(6);
	cit = sv2.begin();
	cit++;
	std::cout << cit[1] << std::endl;
	ft::vector<int>::const_iterator ft_cit(cv.begin());
	ft_cit = v2.begin();
	ft_cit++;
	std::cout << ft_cit[1] << std::endl;
	return 0;
}
