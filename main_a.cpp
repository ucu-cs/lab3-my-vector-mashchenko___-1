#include <complex>
#include <iostream>
#include "my_array.h"

template <typename T, size_t N>
void print_v(const my_array<T, N>& v) {
    for (size_t i = 0; i < N; i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}
int main() {
    std::cout << "====================== CONSTRUCTORS ====================" << std::endl;
    my_array<int, 0> v1;
    std::cout << "Default constructor array ";
    print_v(v1);

    my_array<int, 5> v2( 42);
    std::cout << "v2 filled with 42: ";
    print_v(v2);

    my_array<int, 4> v3{1, 2, 3, 4};
    std::cout << "v3 from {1, 2, 3, 4}: ";
    print_v(v3);

    my_array<int, 10> v4(v3.begin() + 1, v3.end());
    std::cout << "v4 (from v3.begin + 1 till end range): ";
    print_v(v4);

    my_array<int, 10> v5(v4);
    std::cout << "v5 (copy of v4): ";
    print_v(v5);

    my_array<int, 10> v6(std::move(v5));
    std::cout << "v6 (moved from v5): ";
    print_v(v6);

    std::cout << "v5 after move" << std::endl;
    print_v(v5);

    std::cout << "=========================== ELEMENT ACCESS ======================" << std::endl;
    my_array<int, 10> v7 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    print_v(v7);

    std::cout << "[3] = " << v7[3] << std::endl;
    std::cout << "[20] = " << v7[20] << std::endl;

    try {
        std::cout << "at(3) = " << v7.at(3) << std::endl;
        std::cout << "at(20) = " << v7.at(20) << std::endl;
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "Front: " << v7.front() << std::endl;
    std::cout << "Back: " << v7.back() << std::endl;

    std::cout << "=============================== COMPARISON ======================" << std::endl;
    my_array<std::string, 3> v8 {"i", "love", "a" };
    my_array<std::string, 3> v9 {"i", "love", "b" };

    print_v(v8);
    print_v(v9);

    std::cout << "Equals: " << (v8 == v9) << std::endl;
    std::cout << "Not equals: " << (v8 != v9) << std::endl;
    std::cout << "Less: " << (v8 < v9) << std::endl;
    std::cout << "Greater: " << (v8 > v9) << std::endl;

    print_v(v4);
    print_v(v6);

    std::cout << "Equals: " << (v4 == v6) << std::endl;
    std::cout << "Not equals: " << (v4 != v6) << std::endl;
    std::cout << "Less: " << (v4 < v6) << std::endl;
    std::cout << "Greater: " << (v4 > v6) << std::endl;
    std::cout << "Greater or equals: " << (v4 >= v6) << std::endl;

    std::cout << "====================== ADDITIONAL ======================" << std::endl;
    std::cout << "Vector before clear" << std::endl;
    print_v(v2);
    v2.clear();
    std::cout << "Vector after clear" << std::endl;
    print_v(v2);
    std::cout << "is_empty on this vector: " << v2.is_empty() << std::endl;

    std::cout << "========================= SWAP ==========================" << std::endl;
    my_array<int, 5> v11 {1, 2, 3};
    my_array<int, 5> v12 {4, 5, 6, 7, 8};

    std::cout << "Before swap" << std::endl;
    std::cout << "v1" << std::endl;
    print_v(v11);
    std::cout << "v2" << std::endl;
    print_v(v12);

    v11.swap(v12);

    std::cout << "After swap" << std::endl;
    std::cout << "v1" << std::endl;
    print_v(v11);
    std::cout << "v2" << std::endl;
    print_v(v12);

    std::cout << "==================== ELEMENT MANIPULATION ==================" << std::endl;
    my_array<int, 10> v13 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    my_array<int, 10> v14 {10, 20, 30, 40, 50};
    std::cout << "Vector" << std::endl;
    print_v(v13);

    v13.insert(v13.begin() + 4, 123);
    std::cout << "After inserting 123 at v13.begin() + 4" << std::endl;
    print_v(v13);

    std::cout << "Vector to insert" << std::endl;
    print_v(v14);

    v13.insert(v13.begin() + 5, v14.cbegin(), v14.cend());
    std::cout << "After inserting v14 at v13.begin() + 5" << std::endl;
    print_v(v13);

    std::cout << "Before erasing" << std::endl;
    print_v(v13);

    v13.erase(v13.begin() + 4);
    std::cout << "After erasing at v13.begin() + 4" << std::endl;
    print_v(v13);

    std::cout << "============================= ITERATORS ==================================" << std::endl;
    my_array<std::string, 6> words {"one", "two", "three", "four", "five", "six"};
    std::cout << "Regular print" << std::endl;
    print_v(words);

    std::cout << "Print using iterators" << std::endl;
    for (auto it = words.begin(); it != words.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    *words.begin() = "MODIFIED";
    std::cout << "After modification of first element" << std::endl;

    print_v(words);

    return 0;
}
