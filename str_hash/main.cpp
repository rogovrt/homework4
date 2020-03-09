#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "hash_funcs.hpp"

std::pair <char*, unsigned int> generate_string() {
	unsigned int l = 1 + rand() % 100;
	char* c = (char *)malloc(sizeof(char) * l);
	for (unsigned int i = 0; i < l; ++i) {
		*(c + i) = 97 + rand() % 6;
		//std::cout << *(c + i);
	}
	return std::make_pair(c, l);
}

void generate_data(int n, std::vector <std::pair <char*, unsigned int>>&v) {
	srand(time(0));
	for (int i = 0; i < n; ++i)
		v.push_back(generate_string());
}

int main() {
	std::vector <std::pair <char*, unsigned int>> v;
	int n = 1000000;
	generate_data(n, v);
	std::cout << "for " << n << " generated strings: " << std::endl;
	std::set <unsigned int> s;

	for (auto it = v.begin(); it != v.end(); ++it) {
		s.insert(RSHash((*it).first, (*it).second));
	}
	std::cout << " - RSHash has " << n - s.size() << " collisions" << std::endl;
	s.clear();

	for (auto it = v.begin(); it != v.end(); ++it) {
                s.insert(JSHash((*it).first, (*it).second));
        }
        std::cout << " - JSHash has " << n - s.size() << " collisions" << std::endl;
        s.clear();

	for (auto it = v.begin(); it != v.end(); ++it) {
                s.insert(PJWHash((*it).first, (*it).second));
        }
        std::cout << " - PJWHash has " << n - s.size() << " collisions" << std::endl;
        s.clear();        
	
	for (auto it = v.begin(); it != v.end(); ++it) {
                s.insert(ELFHash((*it).first, (*it).second));
        }
        std::cout << " - ELFHash has " << n - s.size() << " collisions" << std::endl;
        s.clear();

        for (auto it = v.begin(); it != v.end(); ++it) {
                s.insert(BKDRHash((*it).first, (*it).second));
        }
        std::cout << " - BKDRHash has " << n - s.size() << " collisions" << std::endl;
        s.clear();

        for (auto it = v.begin(); it != v.end(); ++it) {
                s.insert(SDBMHash((*it).first, (*it).second));
        }
        std::cout << " - SDBMHash has " << n - s.size() << " collisions" << std::endl;
        s.clear();

        for (auto it = v.begin(); it != v.end(); ++it) {
                s.insert(DJBHash((*it).first, (*it).second));
        }
        std::cout << " - DJBHash has " << n - s.size() << " collisions" << std::endl;
        s.clear();

        for (auto it = v.begin(); it != v.end(); ++it) {
                s.insert(DEKHash((*it).first, (*it).second));
        }
        std::cout << " - DEKHash has " << n - s.size() << " collisions" << std::endl;
        s.clear();

        for (auto it = v.begin(); it != v.end(); ++it) {
                s.insert(APHash((*it).first, (*it).second));
        }
        std::cout << " - APHash has " << n - s.size() << " collisions" << std::endl;
        s.clear();

	return 0;
}
