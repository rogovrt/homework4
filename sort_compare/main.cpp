#include <iostream>
#include <set>
#include <vector>
#include <array>
#include <chrono>
#include <ctime>
#include <algorithm>
#include "timer.hpp"

int main() {
	srand(time(0));
	std::array <int, 2000> a;
	for (int i = 0; i < a.size(); ++i)
		a[i] = rand();
	std::cout << "for N = " << a.size() << std::endl;
	{
		std::set <int> s;
		Timer t;
		for (int i = 0; i < a.size(); ++i)
			s.insert(a[i]);
		t.stop();
		std::cout << "set result = ";
	}
	{
		std::vector <int> v;
		for (int i = 0; i < a.size(); ++i)
			v.push_back(a[i]);
		Timer t;
		std::sort(v.begin(), v.end());
		t.stop();
		std::cout << "vector result = ";
	}
	{
		Timer t;
		std::sort(a.begin(), a.end());
		t.stop();
		std::cout << "array result = ";
	}
	return 0;
}
