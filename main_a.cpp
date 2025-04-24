#include <complex>
#include <iostream>
#include "my_array.h"

template <typename T, size_t N>
void print_a(const my_array<T, N>& a) {
    for (size_t i = 0; i < N; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}
int main() {
    std::cout << "====================== CONSTRUCTORS ====================" << std::endl;
    my_array<int, 0> a1;
    std::cout << "Default constructor array ";
    print_a(a1);

    my_array<int, 5> a2( 42);
    std::cout << "a2 filled with 42: ";
    print_a(a2);

    my_array<int, 4> a3{1, 2, 3, 4};
    std::cout << "a3 from {1, 2, 3, 4}: ";
    print_a(a3);

    my_array<int, 10> a4(a3.begin() + 1, a3.end());
    std::cout << "a4 (from a3.begin + 1 till end range): ";
    print_a(a4);

    my_array<int, 10> a5(a4);
    std::cout << "a5 (copy of a4): ";
    print_a(a5);

    my_array<int, 10> a6(std::move(a5));
    std::cout << "a6 (moaed from a5): ";
    print_a(a6);

    std::cout << "a5 after moae" << std::endl;
    print_a(a5);

    std::cout << "=========================== ELEMENT ACCESS ======================" << std::endl;
    my_array<int, 10> a7 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    print_a(a7);

    std::cout << "[3] = " << a7[3] << std::endl;
    std::cout << "[20] = " << a7[20] << std::endl;

    try {
        std::cout << "at(3) = " << a7.at(3) << std::endl;
        std::cout << "at(20) = " << a7.at(20) << std::endl;
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "Front: " << a7.front() << std::endl;
    std::cout << "Back: " << a7.back() << std::endl;

    std::cout << "=============================== COMPARISON ======================" << std::endl;
    my_array<std::string, 3> a8 {"i", "loae", "a" };
    my_array<std::string, 3> a9 {"i", "loae", "b" };

    print_a(a8);
    print_a(a9);

    std::cout << "Equals: " << (a8 == a9) << std::endl;
    std::cout << "Not equals: " << (a8 != a9) << std::endl;
    std::cout << "Less: " << (a8 < a9) << std::endl;
    std::cout << "Greater: " << (a8 > a9) << std::endl;

    print_a(a4);
    print_a(a6);

    std::cout << "Equals: " << (a4 == a6) << std::endl;
    std::cout << "Not equals: " << (a4 != a6) << std::endl;
    std::cout << "Less: " << (a4 < a6) << std::endl;
    std::cout << "Greater: " << (a4 > a6) << std::endl;
    std::cout << "Greater or equals: " << (a4 >= a6) << std::endl;

    std::cout << "====================== ADDITIONAL ======================" << std::endl;
    std::cout << "Array before clear" << std::endl;
    print_a(a2);
    a2.clear();
    std::cout << "Array after clear" << std::endl;
    print_a(a2);
    std::cout << "is_empty on this array: " << a2.is_empty() << std::endl;

    std::cout << "========================= SWAP ==========================" << std::endl;
    my_array<int, 5> a11 {1, 2, 3};
    my_array<int, 5> a12 {4, 5, 6, 7, 8};

    std::cout << "Before swap" << std::endl;
    std::cout << "a1" << std::endl;
    print_a(a11);
    std::cout << "a2" << std::endl;
    print_a(a12);

    a11.swap(a12);

    std::cout << "After swap" << std::endl;
    std::cout << "a1" << std::endl;
    print_a(a11);
    std::cout << "a2" << std::endl;
    print_a(a12);

    std::cout << "==================== ELEMENT MANIPULATION ==================" << std::endl;
    my_array<int, 10> a13 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    my_array<int, 10> a14 {10, 20, 30, 40, 50};
    std::cout << "Array" << std::endl;
    print_a(a13);

    a13.insert(a13.begin() + 4, 123);
    std::cout << "After inserting 123 at a13.begin() + 4" << std::endl;
    print_a(a13);

    std::cout << "Array to insert" << std::endl;
    print_a(a14);

    a13.insert(a13.begin() + 5, a14.cbegin(), a14.cend());
    std::cout << "After inserting a14 at a13.begin() + 5" << std::endl;
    print_a(a13);

    std::cout << "Before erasing" << std::endl;
    print_a(a13);

    a13.erase(a13.begin() + 4);
    std::cout << "After erasing at a13.begin() + 4" << std::endl;
    print_a(a13);

    std::cout << "============================= ITERATORS ==================================" << std::endl;
    my_array<std::string, 6> words {"one", "two", "three", "four", "fiae", "six"};
    std::cout << "Regular print" << std::endl;
    print_a(words);

    std::cout << "Print using iterators" << std::endl;
    for (auto it = words.begin(); it != words.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    *words.begin() = "MODIFIED";
    std::cout << "After modification of first element" << std::endl;

    print_a(words);

    std::cout << "==================== SPECIAL CASES ==========================" << std::endl;
    std::cout << "Embedded array" << std::endl;
    my_array<my_array<int, 10>, 10> embed;
    for (auto & it : embed) {
        print_a(it);
    }

    std::cout << "Embedded array after insert" << std::endl;
    embed[0] = a4;
    for (auto & it : embed) {
        print_a(it);
    }

    return 0;
}
