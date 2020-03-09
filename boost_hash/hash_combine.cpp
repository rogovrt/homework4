#include <iostream>
#include <ctime>
#include <boost/functional/hash.hpp>

class checker {
private:
    int i;
    int i1;
    int i2;
    double d;
    double d1;
    float f;
    char c;
public:
    checker(int i, int i1, int i2, double d, double d1, float f, char c) : i(i), i1(i1), i2(i2), d(d), d1(d1), f(f), c(c) {}

    friend std::size_t hash_value(checker const& c) {
        std::size_t seed = 0;
        boost::hash_combine(seed, c.i);
        boost::hash_combine(seed, c.d);
        boost::hash_combine(seed, c.f);
        boost::hash_combine(seed, c.c);
        return seed;
    }
};

checker generate_checker() {
    int i = rand();
    int i1 = rand();
    int i2 = rand();
    double d = (double)rand()/(double)RAND_MAX;
    double d1 = (double)rand()/(double)RAND_MAX;
    float f = (float)rand()/(float)RAND_MAX;
    char c = rand() % 255 - 128;
    checker ch(i, i1, i2, d, d1, f, c);
    return ch;
}

void find_collision(int n) {
    boost::hash <checker> hasher;
    std::set <size_t> s;
    srand(time(0));
    int c = 0;
    for (unsigned int i = 0; i < n; ++i) {
        s.insert(hasher(generate_checker()));
        if (i % 10 == 0) {
            if (s.size() - 1 != i) {
                c++;
                std::cout << "there is " << i + 1 << " elements and " << i + 1 - s.size() << " collisions." << std::endl;
            }
        }
    }
}

int main() {
    find_collision(8000000);
    return 0;
}
