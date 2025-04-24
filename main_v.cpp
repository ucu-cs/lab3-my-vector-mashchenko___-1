#include <complex>
#include <iostream>
#include "my_vector.h"

template <typename T>
void print_v(const my_vector<T>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Size: " << v.size() << ", capacity: " << v.capacity() << std::endl;
}
int main() {
    std::cout << "====================== CONSTRUCTORS ====================" << std::endl;
    my_vector<int> v1;
    std::cout << "Default constructor vector ";
    print_v(v1);

    my_vector<int> v2(5, 42);
    std::cout << "v2 (5, 42): ";
    for (const auto& x : v2) std::cout << x << ' ';
    print_v(v2);

    my_vector<int> v3{1, 2, 3, 4};
    std::cout << "v3 from {1, 2, 3, 4}: ";
    for (const auto& x : v3) std::cout << x << ' ';
    print_v(v3);

    // 4. Range constructor (from v3)
    my_vector<int> v4(v3.begin() + 1, v3.end());
    std::cout << "v4 (from v3.begin + 1 till end range): ";
    for (const auto& x : v4) std::cout << x << ' ';
    print_v(v4);

    // 5. Copy constructor
    my_vector<int> v5(v4);
    std::cout << "v5 (copy of v4): ";
    for (const auto& x : v5) std::cout << x << ' ';
    print_v(v5);

    // 6. Move constructor
    my_vector<int> v6(std::move(v5));
    std::cout << "v6 (moved from v5): ";
    for (const auto& x : v6) std::cout << x << ' ';
    print_v(v6);

    std::cout << "v5 (after move): size = " << v5.size() << ", capacity = " << v5.capacity() << '\n';

    std::cout << "=========================== ELEMENT ACCESS ======================" << std::endl;
    my_vector<int> v7 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
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

    std::cout << "=============================== ITERATORS ======================" << std::endl;

    std::cout << "=============================== COMPARISON ======================" << std::endl;
    my_vector<std::string> v8 {"i", "love", "a" };
    my_vector<std::string> v9 {"i", "love", "b" };

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

    std::cout << "================== MEMORY MANAGMENT ==================" << std::endl;
    my_vector<int> v10 {10};
    print_v(v10);

    std::cout << "Resize to 5" << std::endl;
    v10.resize(5);
    print_v(v10);

    std::cout << "Reserve 20" << std::endl;
    v10.reserve(20);
    print_v(v10);

    std::cout << "After shrink to fit" << std::endl;
    v10.shrink_to_fit();
    print_v(v10);

    std::cout << "========================= SWAP ==========================" << std::endl;
    my_vector<int> v11 {1, 2, 3};
    my_vector<int> v12 {4, 5, 6, 7, 8};

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
    my_vector<int> v13 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    my_vector<int> v14 {10, 20, 30, 40, 50};
    std::cout << "Vector" << std::endl;
    print_v(v13);

    v13.insert(v13.begin(), 123);
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

    std::cout << "vector before pop_back, emplace_back, push_back" << std::endl;
    print_v(v13);

    v13.pop_back();
    std::cout << "After pop_back" << std::endl;
    print_v(v13);

    v13.push_back(1000);
    std::cout << "After push_back 1000" << std::endl;
    print_v(v13);

    my_vector<std::complex<double>> v_complex;

    v_complex.emplace_back(1.0, 2.0);
    v_complex.emplace_back(4.0, 3.5);
    v_complex.emplace_back(10.0, -2.0);

    print_v(v_complex);

    std::cout << "============================= ITERATORS ==================================" << std::endl;
    my_vector<std::string> words {"one", "two", "three", "four", "five", "six"};
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
