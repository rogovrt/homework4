#include <iostream>
#include <string>
#include <algorithm>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>

using namespace boost::multi_index;

typedef struct person {
    std::string name;
    int number;

    bool operator==(const person &rhs) const {
        return number == rhs.number;
    }

    bool operator!=(const person &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const person &rhs) const {
        return number < rhs.number;
    }

    bool operator>(const person &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const person &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const person &rhs) const {
        return !(*this < rhs);
    }
} person;

typedef multi_index_container <
        person,
        indexed_by<
        ordered_non_unique<member<person, std::string, &person::name>>,
        hashed_non_unique<member<person, std::string, &person::name>>,
        random_access<>
        >
        > person_multi;

int main() {
    person_multi persons;
    persons.insert({"A", 4});
    persons.insert({"C", 0});
    persons.insert({"B", 2});

    std::cout << "sorted by name" << std::endl;
    auto &name_index = persons.get<0>();
    for (auto it = name_index.begin(); it != name_index.end(); ++it)
        std::cout << it -> name << " : " << it -> number << std::endl;

    std::cout << "find by name" << std::endl;
    auto &find_name_index = persons.get<1>();
    auto it = find_name_index.find("A");
    std::cout << it -> name << " : " << it -> number << std::endl;

    std::cout << "sort by number" << std::endl;
    auto &rand_index = persons.get<2>();
    rand_index.sort();
    for (auto it = rand_index.begin(); it != rand_index.end(); ++it)
        std::cout << it -> name << " : " << it -> number << std::endl;

    std::cout << "find by number" << std::endl;
    person p;
    p.number = 0;
    auto it1 = std::find(rand_index.begin(), rand_index.end(), p);
    std::cout << it1 -> name << " : " << it1 -> number << std::endl;

    return 0;
}
