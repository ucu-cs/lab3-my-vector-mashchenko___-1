#ifndef MY_ARRAY_H
#define MY_ARRAY_H

#include <iterator>

template <typename T, std::size_t N>
class my_array {
    T data_m[N];

public:
    // constructors
    my_array () {
        for (size_t i = 0; i < N; i++) {
            data_m[i] = T();
        }
    }
    explicit my_array (const T& value) {
        for (size_t i = 0; i < N; i++) {
            data_m[i] = value;
        }
    }
    my_array(std::initializer_list<T> init) {
        size_t i = 0;
        for (auto& value : init) {
            if (i < N) {
                data_m[i++] = value;
            }
        }
        for (; i < N; i++) {
            data_m[i] = T();
        }
    }
    template<typename InputIt, typename = std::enable_if_t<!std::is_integral_v<InputIt>>>
    my_array (InputIt first, InputIt last) {
        size_t i = 0;
        for (InputIt it = first; it != last && i < N; ++it, ++i) {
            data_m[i] = *it;
        }
        for (; i < N; i++) {
            data_m[i] = T();
        }
    }

    // copy
    my_array (const my_array& other) {
        for (size_t i = 0; i < N; i++) {
            data_m[i] = other.data_m[i];
        }
    }
    my_array& operator=(const my_array& other) {
        if (this != &other) {
            for (size_t i = 0; i < N; i++) {
                data_m[i] = other.data_m[i];
            }
        }
        return *this;
    }

    // move
    my_array (my_array&& other)  noexcept {
        for (size_t i = 0; i < N; i++) {
            data_m[i] = other.data_m[i];
        }
        other.clear();
    }
    my_array& operator=(my_array&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < N; i++) {
                data_m[i] = other.data_m[i];
            }
            other.clear();
        }
        return *this;
    }

    // destructor
    ~my_array() = default;

    // access operators
    T& operator[](size_t index) {
        return data_m[index];
    }
    const T& operator[](size_t index) const {
        return data_m[index];
    }

    T& at(size_t index) {
        if (index >= N) {
            throw std::out_of_range("Index out of range in at()");
        }

        return data_m[index];
    }
    const T& at(size_t index) const {
        if (index >= N) {
            throw std::out_of_range("Index out of range in at()");
        }

        return data_m[index];
    }

    T& back() {
        if (N == 0) {
            throw std::out_of_range("Accessing empty vector in back()");
        }

        return data_m[N - 1];
    }
    const T& back() const {
        if (N == 0) {
            throw std::out_of_range("Accessing empty vector in back()");
        }

        return data_m[N - 1];
    }
    T& front() {
        if (N == 0) {
            throw std::out_of_range("Accessing empty vector in front()");
        }

        return data_m[0];
    }
    const T& front() const {
        if (N == 0) {
            throw std::out_of_range("Accessing empty vector in front()");
        }

        return data_m[0];
    }

    // iterators
    T* begin() {
        return data_m;
    }
    T* end() {
        return data_m + N;
    }

    const T* begin() const {
        return data_m;
    }
    const T* end() const {
        return data_m + N;
    }

    const T* cbegin() const {
        return data_m;
    }
    const T* cend() const {
        return data_m + N;
    }

    std::reverse_iterator<T*> rbegin() {
        return std::reverse_iterator<T*>(end());
    }
    std::reverse_iterator<T*> rend() {
        return std::reverse_iterator<T*>(begin());
    }

    std::reverse_iterator<const T*> rcbegin() const {
        return std::reverse_iterator<const T*>(cend());
    }
    std::reverse_iterator<const T*> rcend() const {
        return std::reverse_iterator<const T*>(cbegin());
    }

    // additional methods
    [[nodiscard]] bool is_empty() const {
        return N == 0;
    }
    [[nodiscard]] size_t size() const {
        return N;
    }
    T* data() {
        return data_m;
    }

    // swap
    void swap (my_array& other) noexcept {
        std::swap (data_m, other.data_m);
    }

    // clear, resize
    void clear () {
        for (size_t i = 0; i < N; i++) {
            data_m[i] = T();
        }
    }
    void fill(const T& value) {
        for (size_t i = 0; i < N; i++) {
            data_m[i] = value;
        }
    }

    // inserts
    T* insert(T* it, const T& value) {
        size_t index = it - data_m;

        if (index >= N) return nullptr;

        for (size_t i = N - 1; i > index; --i) {
            data_m[i] = std::move(data_m[i - 1]);
        }

        data_m[index] = value;
        return data_m + index;
    }

    template<typename InputIt>
    T* insert(T* it, InputIt first, InputIt last) {
        size_t index = it - data_m;
        const size_t count = std::distance(first, last);
        const size_t limit = std::min(N - index, count);

        if (index >= N) return nullptr;

        for (size_t i = N - 1; i >= index + limit; --i) {
            data_m[i] = std::move(data_m[i - limit]);
        }

        for (size_t i = 0; i < limit; ++i) {
            data_m[index + i] = *(first + i);
        }

        return data_m + index;
    }

    // erase
    T* erase(T* pos) {
        size_t index = pos - data_m;

        if (index >= N) return nullptr;

        for (size_t i = index; i < N - 1; ++i) {
            data_m[i] = std::move(data_m[i + 1]);
        }

        return data_m + index;
    }
    T* erase(T* first, T* last) {
        size_t start = first - data_m;
        size_t end = last - data_m;
        size_t count = end - start;

        if (start >= N || end > N) return nullptr;

        for (size_t i = start; i < N - count; ++i) {
            data_m[i] = std::move(data_m[i + count]);
        }

        return data_m + start;
    }

    friend bool operator==(const my_array& a, const my_array& b) {
        return std::equal(a.begin(), a.end(), b.begin());
    }

    friend bool operator!=(const my_array& a, const my_array& b) {
        return !(a == b);
    }

    friend bool operator<(const my_array& a, const my_array& b) {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }

    friend bool operator>(const my_array& a, const my_array& b) {
        return b < a;
    }

    friend bool operator<=(const my_array& a, const my_array& b) {
        return !(b < a);
    }

    friend bool operator>=(const my_array& a, const my_array& b) {
        return !(a < b);
    }

};



#endif //MY_ARRAY_H
