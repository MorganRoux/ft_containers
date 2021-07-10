#include "ft_vector.hpp"

int main(void)
{
	ft::vector<int> v1;
	ft::vector<int> v2(6);
	v2[2] = 7;
	const ft::vector<int>v3(v2);
	std::cout << v2[3] << " - " << v2.at(3) << std::endl;
	std::cout << v2[2] << std::endl;
	std::cout << v3[2] << std::endl;
	try {
		v2.at(10);
	}
	catch(std::out_of_range& e) {
		std::cout << e.what() << std::endl;
	}
	try {
		v3.at(10);
	}
	catch(std::out_of_range& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << v1.max_size() << std::endl;
	return 0;
}
