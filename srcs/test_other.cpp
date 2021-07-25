

#include "vector.hpp"
#include "utils.hpp"
#include "metafunctions.hpp"
#include "pair.hpp"
#include "compare.hpp"
#include "vector.hpp"
#include <vector>
#include <algorithm>

bool mycomp(int a, int b)
{
	return a < b;
}

bool mypred(int a, int b)
{
	return a == b;
}

class A
	{
	public:
		A() { std::cout << "Constructor " << std::endl; }
		A(const A &other)
		{
			std::cout << "Copy Constructor " << std::endl;
			(void)other;
		}
		~A() { std::cout << "Destructor " << std::endl; }
	};

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
		std::cout << NAMESPACE::make_pair(7, 8).first << NAMESPACE::make_pair(7, 8).second << std::endl;
		p1 = NAMESPACE::make_pair(7, 8);
		std::cout << (p1 == p2) << std::endl;
		std::cout << (p1 != p2) << std::endl;
		std::cout << (p1 <= p2) << std::endl;
		std::cout << (p1 >= p2) << std::endl;
		std::cout << (p1 < p2) << std::endl;
		std::cout << (p1 > p2) << std::endl;
	}

	{
		std::cout << "--------constructor destructor of pair" << std::endl;
		std::string a("hey");
		NAMESPACE::pair<std::string, std::string> t, t2;
		NAMESPACE::pair<std::string, std::string> test("hello", a);
		t = test;
		std::cout << test.first << test.second << t.first << t.second << t2.first << t2.second << std::endl;
	}
	{
		std::cout << "-------makepair" << std::endl;
		NAMESPACE::pair<std::string, std::string> test(NAMESPACE::make_pair<std::string, std::string>("hello", "yay"));
		std::cout << test.first << test.second << std::endl;
	}

	std::cout << "lexical compare" << std::endl;
	{
		NAMESPACE::vector<int> v1, v2;

		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v2.push_back(1);
		v2.push_back(2);
		v2.push_back(5);

		NAMESPACE::vector<int> v3 = v2;
		std::cout << NAMESPACE::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()) << std::endl;
		std::cout << NAMESPACE::lexicographical_compare(v2.begin(), v2.end(), v1.begin(), v1.end(), mycomp) << std::endl;
		std::cout << NAMESPACE::equal(v1.begin(), v1.end(), v2.begin()) << std::endl;
		std::cout << NAMESPACE::equal(v2.begin(), v2.end(), v1.begin()) << std::endl;
		std::cout << NAMESPACE::equal(v3.begin(), v3.end(), v2.begin(), mypred) << std::endl;
	}
}
