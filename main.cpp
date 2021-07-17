#include "vector.hpp"
#include "utils.hpp"
#include <vector>

int main(void)
{
	{
		std::vector<int> sv1(6), sv2(6);
		std::vector<int>::iterator it1, it2;
		it1 = sv1.begin();
		it2 = sv2.begin();
		std::cout << it1[2] << " - " << it2[2] << " : " << (it1 == it2) << std::endl;
		std::cout << "diff: " << sv1.end() - sv1.begin() << " - " << sv1.rend() - sv1.rbegin() << std::endl;

		std::cout << "========= 1. ========" << std::endl;

		ft::vector<int> v1;
		ft::vector<int> v2(6, 8);
		v2[1] = 1;
		v2[2] = 7;
		v2[3] = 8;
		const ft::vector<int> v3(v2);
		std::cout << v2[3] << " - " << v2.at(3) << std::endl;
		std::cout << v2[2] << std::endl;
		std::cout << v3[2] << std::endl;
		std::cout << (v1 == v2) << std::endl;
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

		std::cout << "========= 2. =========" << std::endl;
		ft::vector<int>::iterator vt1;
		for (vt1 = v2.begin(); vt1 != v2.end(); ++vt1)
			std::cout << *vt1 << std::endl;

		std::cout << "diff: " << v2.end() - v2.begin() << " - " << v2.rend() - v2.rbegin() << std::endl;
		std::cout << "========= 3. =========" << std::endl;
		ft::vector<int>::reverse_iterator vr1;
		for (vr1 = v2.rbegin(); vr1 != v2.rend(); ++vr1)
			std::cout << *vr1 << std::endl;

		std::cout << "========= 4. =========" << std::endl;
		std::vector<int>::const_iterator cit;
		const ft::vector<int> cv(6);
		cit = sv2.begin();
		cit++;
		std::cout << cit[1] << std::endl;
		ft::vector<int>::const_iterator ft_cit(cv.begin());
		ft_cit = v2.begin();
		ft_cit++;
		std::cout << ft_cit[1] << std::endl;

		std::cout << "========= 5. =========" << std::endl;
		ft::vector<int> v4(v2.begin(), v2.end());
		for (ft::vector<int>::iterator it = v4.begin(); it != v4.end(); it++)
			std::cout << *it << std::endl;
	}

	std::cout << "======== TESTS =========" << std::endl;
	NAMESPACE::vector<int> vect(6, 8);
	NAMESPACE::vector<int>::iterator iter = vect.begin();
	NAMESPACE::vector<int>::reverse_iterator riter = vect.rbegin();
	std::cout << "get_allocator()" << std::endl;
	std::cout << vect.get_allocator().max_size() << std::endl;
	std::cout << "Iter" << std::endl;
	for (; iter != vect.end(); iter++)
		*iter = *iter + (iter - vect.begin());
	std::cout << "Riter" << std::endl;
	for (; riter != vect.rend(); riter++)
		std::cout << *riter << std::endl;
	std::cout << "front()" << std::endl;
	{
		std::cout << vect.front() << std::endl;

		const int i = vect.front();
		std::cout << i << std::endl;
	}
	std::cout << "back()" << std::endl;
	{
		std::cout << vect.back() << std::endl;

		const int i = vect.back();
		std::cout << i << std::endl;
	}
	std::cout << "[] and at()" << std::endl;
	{
		std::cout << vect[4] << vect.at(4) << std::endl;

		const int i = vect[3];
		const int j = vect.at(3);
		std::cout << i << j << std::endl;
	}
	std::cout << "empty()" << std::endl;
	{
		std::cout << vect.empty() << std::endl;
		NAMESPACE::vector<int> e;
		std::cout << e.empty() << std::endl;
		std::cout << vect.capacity() << vect.size() << std::endl;
	}
	std::cout << "reserve()" << std::endl;
	{
		vect.reserve(100);
		std::cout << vect.capacity() << vect.size() << std::endl;
	}
	std::cout << "resize()" << std::endl;
	{
		vect.resize(3);
		std::cout << vect.capacity() << vect.size() << std::endl;
		print_container(vect);
	}
	std::cout << "Maxsize" << std::endl;
	{
		std::cout << vect.max_size() << std::endl;
	}
	std::cout << "push_back()" << std::endl;
	{
		vect.push_back(100);
		vect.push_back(-8);
		print_container(vect);
	}
	std::cout << "pop_back()" << std::endl;
	{
		vect.pop_back();
		print_container(vect);
	}
	std::cout << "clear" << std::endl;
	//from cplusplus
	{
		NAMESPACE::vector<int> myvector;
		myvector.push_back(100);
		myvector.push_back(200);
		myvector.push_back(300);

		std::cout << "myvector contains:";
		for (unsigned i = 0; i < myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';

		myvector.clear();
		myvector.push_back(1101);
		myvector.push_back(2202);

		std::cout << "myvector contains:";
		for (unsigned i = 0; i < myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
	}
	std::cout << "assign" << std::endl;
	{
		vect.assign(2, 50);
		print_container(vect);
		vect.assign(200, 6);
		print_container(vect);
		NAMESPACE::vector<int> count(25);
		for (NAMESPACE::vector<int>::iterator it = count.begin(); it != count.end(); it++)
			*it = (it - count.begin());
		vect.assign(vect.begin(), vect.end());
		print_container(vect);
		print_container(count);
	}
	//cplusplus.com
	{
		NAMESPACE::vector<int> first;
		NAMESPACE::vector<int> second;
		NAMESPACE::vector<int> third;
		first.assign(7, 100); // 7 ints with a value of 100
		NAMESPACE::vector<int>::iterator it;
		it = first.begin() + 1;
		second.assign(it, first.end() - 1); // the 5 central values of first
		int myints[] = {1776, 7, 4};
		third.assign(myints, myints + 3); // assigning from array.
		std::cout << "Size of first: " << int(first.size()) << '\n';
		std::cout << "Size of second: " << int(second.size()) << '\n';
		std::cout << "Size of third: " << int(third.size()) << '\n';
	}

	std::cout << "Erase" << std::endl;
	{
		vect.clear();
		for (int i = 0; i < 10; i++)
			vect.push_back(i);
		print_container(vect);
		std::cout << "-" << std::endl;
		NAMESPACE::vector<int>::iterator it = vect.erase(vect.begin() + 2);
		std::cout << *it << std::endl;
		print_container(vect);
		it = vect.erase(vect.end() - 1);
		std::cout << *it << std::endl;
		print_container(vect);
	}
	{
		std::cout << "Erase2" << std::endl;
		vect.clear();
		for (int i = 0; i < 20; i++)
			vect.push_back(i);
		NAMESPACE::vector<int>::iterator it = vect.erase(vect.begin() + 2, vect.begin() + 8);
		std::cout << *it << std::endl;
		print_container(vect);
		vect.clear();
		for (int i = 0; i < 20; i++)
			vect.push_back(i);
		it = vect.erase(vect.begin() + 6, vect.end());
		std::cout << *it << std::endl;
		print_container(vect);
	}
	std::cout << "Swap" << std::endl;
	{
		NAMESPACE::vector<int> foo(3, 100); // three ints with a value of 100
		NAMESPACE::vector<int> bar(5, 200); // five ints with a value of 200

		foo.swap(bar);

		std::cout << "foo contains:";
		for (unsigned i = 0; i < foo.size(); i++)
			std::cout << ' ' << foo[i];
		std::cout << '\n';

		std::cout << "bar contains:";
		for (unsigned i = 0; i < bar.size(); i++)
			std::cout << ' ' << bar[i];
		std::cout << '\n';

		swap(bar, foo);
		print_container(bar);
		print_container(foo);
	}

	NAMESPACE::vector<int>::reverse_iterator rit = vect.rend() - 1;
	std::cout << *rit << std::endl;

	std::cout << "Insert" << std::endl;
	{
		//from cppreference
		NAMESPACE::vector<int> myvector(3, 100);
		NAMESPACE::vector<int>::iterator it;
		print_container(myvector);
		std::cout << "insert1" << std::endl;
		it = myvector.begin();
		it = myvector.insert(it, 200);
		print_container(myvector);

		std::cout << "insert2" << std::endl;
		it = myvector.begin();
		myvector.insert(it, 2, 300);
		print_container(myvector);

		// "it" no longer valid, get a new one:
		std::cout << "insert3" << std::endl;
		it = myvector.begin();
		NAMESPACE::vector<int> anothervector(2, 400);
		myvector.insert(it + 2, anothervector.begin(), anothervector.end());

		int myarray[] = {501, 502, 503};
		myvector.insert(myvector.begin(), myarray, myarray + 3);

		std::cout << "myvector contains:";
		for (it = myvector.begin(); it < myvector.end(); it++)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	return 0;
}
