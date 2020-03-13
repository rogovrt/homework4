#include <iostream>
#include <set>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <random>
#include "hash_funcs.hpp"

char* generate_string(unsigned int l) {
	char* c = (char *)malloc(sizeof(char)* l);
	for (unsigned int i = 0; i < l; ++i) {
		c[i] = 97 + i % l;
	}
	return c;
}

void generate_data(unsigned int l, std::vector <std::pair <char*, unsigned int>>&v) {
	auto str = generate_string(l);
	v.push_back(std::make_pair(str, l));
	while (std::next_permutation(str, str + l)) {
		char* str_new = (char *)malloc(sizeof(char) * l);
		for (int i = 0; i < l; ++i) {
			str_new[i] = str[i];
		}
		v.push_back(std::make_pair(str_new, l));
	}
	std::shuffle(v.begin(), v.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
}

void test_func(const std::vector <std::pair <char*, 
		unsigned int>>& v, std::set <unsigned int>& s, 
		unsigned int (*hash_func)(const char*, unsigned int),
		std::ofstream& koll, std::ofstream& dat, bool b) {
	int c = 0;
        for (auto it = v.begin(); it != v.end(); ++it) {
                s.insert((*hash_func)((*it).first, (*it).second));
		if (c % 1000 == 0) {
			if (b)
				dat << c << std::endl;
			koll << c - s.size() << std::endl;
		}
		c++;
        }
        s.clear();
}

int main() {
	std::vector <std::pair <char*, unsigned int>> v;
	int n = 1000000;
	generate_data(n, v);
	std::cout << "for " << n << " generated strings: " << std::endl;
	std::set <unsigned int> s;
	std::ofstream dat("dat.txt");
	std::ofstream rs("rs.txt");
        std::ofstream js("js.txt");
	std::ofstream pjw("pjw.txt");
        std::ofstream elf("elf.txt");
        std::ofstream bkdr("bkrd.txt");
        std::ofstream sdbm("sdbm.txt");
        std::ofstream djb("/djb.txt");
        std::ofstream dek("/dek.txt");
        std::ofstream ap("/ap.txt");

	generate_data(10, v);

		test_func(v, s, RSHash, rs, dat, 1);
		test_func(v, s, JSHash, js, dat, 0);
		test_func(v, s, PJWHash, pjw, dat, 0);
                test_func(v, s, ELFHash, elf, dat, 0);
                test_func(v, s, BKDRHash, bkdr, dat, 0);
                test_func(v, s, SDBMHash, sdbm, dat, 0);
                test_func(v, s, DJBHash, djb, dat, 0);
                test_func(v, s, DEKHash, dek, dat, 0);
                test_func(v, s, APHash, ap, dat, 0);

	dat.close();
	rs.close();
	js.close();
	pjw.close();
	elf.close();
	bkdr.close();
	sdbm.close();
	djb.close();
	dek.close();
	ap.close();

	return 0;
}
