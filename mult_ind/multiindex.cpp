#include <iostream>
#include <string>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>

using namespace boost::multi_index;

typedef struct person {
    std::string name;
    double number;
} person;

typedef multi_index_container <
        person,
        indexed_by<
        ordered_non_unique<member<person, double, &person::number>>,
        ordered_non_unique<member<person, std::string, &person::name>>,
        hashed_non_unique<member<person, std::string, &person::name>>,
        hashed_non_unique<member<person, double, &person::number>>
        >
        > person_multi;

int main() {
    person_multi persons;
    persons.insert({"A", 4});
    persons.insert({"C", 3});
    persons.insert({"B", 2});

    std::cout << "sorted by name" << std::endl;
    auto &name_index = persons.get<1>();
    for (auto it = name_index.begin(); it != name_index.end(); ++it)
        std::cout << it -> name << " : " << it -> number << std::endl;

    std::cout << "sorted by number" << std::endl;
    auto &number_index = persons.get<0>();
    for (auto it = number_index.begin(); it != number_index.end(); ++it)
        std::cout << it -> name << " : " << it -> number << std::endl;

    std::cout << "find by name" << std::endl;
    auto &find_name_index = persons.get<2>();
    auto it = find_name_index.find("A");
    std::cout << it -> name << " : " << it -> number << std::endl;

    std::cout << "find by number" << std::endl;
    auto &find_num_index = persons.get<3>();
    auto it1 = find_num_index.find(3);
    std::cout << it1 -> name << " : " << it1 -> number << std::endl;

    return 0;
}
