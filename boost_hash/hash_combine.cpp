#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <boost/functional/hash.hpp>
#include <fstream>

class checker {
private:
    int i;
    float f;
    char c;
public:
    checker(int i, float f, char c) : i(i), f(f), c(c) {}

    friend std::size_t hash_value(checker const& c) {
        std::size_t seed = 31;
        boost::hash_combine(seed, c.i);
        boost::hash_combine(seed, c.f);
        boost::hash_combine(seed, c.c);
        return seed;
    }
};

void find_collision(int n, std::ofstream& output, std::ofstream& output1) {
    boost::hash <checker> hasher;
    std::vector <checker> v;
    int j;
    float f;
    char c;
    for (j = 0; j < n; ++j) {
        for (f = 0; f < n; f += 4.953) {
            c = j % 79 + 48;
            checker ch(j, f, c);
            v.push_back(ch);
        }
    }
    std::shuffle(v.begin(), v.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));

    std::set <int> s;
    for (auto it = v.begin(); it != v.end(); ++it) {
        s.insert(hasher(*it));
    }
    output << v.size() << std::endl; //вывод количества экземпляров и коллизий
    output1 << v.size() - s.size() << std::endl;
}

int main() {
    std::ofstream output;
    std::ofstream output1;
    output.open("out.txt");
    output1.open("out1.txt");
    for (int i = 0; i < 4000; i += 10)
        find_collision(i, output, output1);
    output.close();
    return 0;
}
