#ifndef MY_VECTOR_H
#define MY_VECTOR_H
#include <iterator>


template <typename T>
class my_vector {
    T* data_m;
    size_t size_m;
    size_t capacity_m;

    [[nodiscard]] static size_t align_to_16 (const size_t num) {
        return (num + 15) / 16 * 16;
    }

    void allocate_and_copy (const T* src, const size_t data_size) {
        size_m = data_size;
        capacity_m = align_to_16 (data_size);
        data_m = new T[capacity_m];
        for (size_t i = 0; i < size_m; i++) {
            data_m[i] = src[i];
        }
    }

public:
    // constructors
    my_vector () : data_m(nullptr), size_m (0), capacity_m (0) {}
    my_vector (const size_t n, const T& value) {
        capacity_m = align_to_16 (n);
        size_m = n;
        data_m = new T[capacity_m];
        for (size_t i = 0; i < size_m; i++) {
            data_m[i] = value;
        }
    }
    my_vector (std::initializer_list<T> init) {
        allocate_and_copy(init.begin(), init.size());
    }
    template<typename InputIt, typename = std::enable_if_t<!std::is_integral_v<InputIt>>>
    my_vector (InputIt first, InputIt last) {
        allocate_and_copy(first, last - first);
    }

    // copy
    my_vector (const my_vector& other) {
        allocate_and_copy(other.data_m, other.size_m);
    }
    my_vector& operator=(const my_vector& other) {
        if (this != &other) {
            delete [] data_m;
            allocate_and_copy(other.data_m, other.size_m);
        }
        return *this;
    }

    // move
    my_vector (my_vector&& other)  noexcept : data_m (other.data_m), size_m (other.size_m), capacity_m (other.capacity_m) {
        other.data_m = nullptr;
        other.size_m = 0;
        other.capacity_m = 0;
    }
    my_vector& operator=(my_vector&& other) noexcept {
        if (this != &other) {
            delete [] data_m;
            data_m = other.data_m;
            size_m = other.size_m;
            capacity_m = other.capacity_m;
            other.data_m = nullptr;
            other.capacity_m = 0;
        }
        return *this;
    }

    // destructor
    ~my_vector() {
        delete [] data_m;
    }

    // access operators
    T& operator[](size_t index) {
        return data_m[index];
    }
    const T& operator[](size_t index) const {
        return data_m[index];
    }

    T& at(size_t index) {
        if (index >= size_m) {
            throw std::out_of_range("Index out of range in at()");
        }

        return data_m[index];
    }
    const T& at(size_t index) const {
        if (index >= size_m) {
            throw std::out_of_range("Index out of range in at()");
        }

        return data_m[index];
    }

    T& back() {
        if (size_m == 0) {
            throw std::out_of_range("Accessing empty vector in back()");
        }

        return data_m[size_m - 1];
    }
    const T& back() const {
        if (size_m == 0) {
            throw std::out_of_range("Accessing empty vector in back()");
        }

        return data_m[size_m - 1];
    }
    T& front() {
        if (size_m == 0) {
            throw std::out_of_range("Accessing empty vector in front()");
        }

        return data_m[0];
    }
    const T& front() const {
        if (size_m == 0) {
            throw std::out_of_range("Accessing empty vector in front()");
        }

        return data_m[0];
    }

    // iterators
    T* begin() {
        return data_m;
    }
    T* end() {
        return data_m + size_m;
    }

    const T* begin() const {
        return data_m;
    }
    const T* end() const {
        return data_m + size_m;
    }

    const T* cbegin() const {
        return data_m;
    }
    const T* cend() const {
        return data_m + size_m;
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
        return size_m == 0;
    }
    [[nodiscard]] size_t size() const {
        return size_m;
    }
    void reserve (size_t new_capacity) {
        if (new_capacity == 0) {
            new_capacity = 2;
        }
        if (new_capacity > capacity_m) {
            new_capacity = align_to_16 (new_capacity);
            T* new_data_m = new T[new_capacity];
            for (size_t i = 0; i < size_m; i++) {
                new_data_m[i] = data_m[i];
            }
            delete [] data_m;
            data_m = new_data_m;
            capacity_m = new_capacity;
        }
    }
    [[nodiscard]] size_t capacity() const {
        return capacity_m;
    }
    void shrink_to_fit () {
        capacity_m = size_m;
        T* new_data_m = new T[capacity_m];
        for (size_t i = 0; i < size_m; i++) {
            new_data_m[i] = data_m[i];
        }
        delete [] data_m;
        data_m = new_data_m;
    }

    // swap
    void swap (my_vector& other) noexcept {
        std::swap (data_m, other.data_m);
        std::swap (size_m, other.size_m);
        std::swap (capacity_m, other.capacity_m);
    }

    // clear, resize
    void clear () {
        size_m = 0;
    }
    void resize(const size_t new_size) {
        resize(new_size, T());
    }
    void resize(size_t new_size, const T& value) {
        if (new_size < size_m) {
            size_m = new_size;
        } else if (new_size > size_m && new_size < capacity_m) {
            for (size_t i = size_m; i < new_size; ++i) {
                data_m[i] = value;
            }
            size_m = new_size;
        }
        else {
            reserve (new_size);
            for (size_t i = size_m; i < new_size; ++i) {
                data_m[i] = value;
            }
            size_m = new_size;
        }
    }

    // inserts
    T* insert(T* it, const T& value) {
        size_t index = it - data_m;
        if (size_m == capacity_m) {
            reserve(align_to_16(size_m * 2));
            it = data_m + index;
        }

        for (size_t i = size_m; i > index; i--) {
            data_m[i] = std::move(data_m[i - 1]);
        }

        data_m[index] = value;
        ++size_m;
        return data_m + index;
    }

    template<typename InputIt>
    T* insert(T* it, InputIt first, InputIt last) {
        size_t index = it - data_m;
        const size_t count = std::distance(first, last);
        if (size_m + count > capacity_m) {
            reserve(align_to_16(size_m * 2 + count));
            it = data_m + index;
        }

        for (size_t i = size_m + count; i-- > index + count; ) {
            data_m[i] = std::move(data_m[i - count]);
        }

        std::copy(first, last, data_m + index);
        size_m += count;
        return data_m + index;
    }

    // erase
    T* erase(T* pos) {
        size_t index = pos - data_m;

        for (size_t i = index; i + 1 < size_m; ++i) {
            data_m[i] = std::move(data_m[i + 1]);
        }

        size_m--;
        return data_m + index;
    }
    T* erase(T* first, T* last) {
        size_t start = first - data_m;
        const size_t count = last - first;
        for (size_t i = start; i < last; ++i)
            data_m[i] = std::move(data_m[i + count]);
        size_m -= count;
        return data_m + start;
    }

    // pop, push, emplace
    void pop_back() {
        if (size_m > 0) {
            size_m--;
        }
    }

    void push_back(const T& value) {
        if (size_m == capacity_m) {
            reserve((size_m) * 2);
        }
        data_m[size_m++] = value;
    }
    void push_back(T&& value) {
        if (size_m == capacity_m) {
            reserve(size_m * 2);
        }
        data_m[size_m++] = std::move(value);
    }

    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (size_m == capacity_m) {
            reserve((size_m == 0 ? 1 : size_m) * 2);
        }
        data_m[size_m++] = T(std::forward<Args>(args)...);
    }

    friend bool operator==(const my_vector& a, const my_vector& b) {
        return a.size_m == b.size_m && std::equal(a.begin(), a.end(), b.begin());
    }

    friend bool operator!=(const my_vector& a, const my_vector& b) {
        return !(a == b);
    }

    friend bool operator<(const my_vector& a, const my_vector& b) {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }

    friend bool operator>(const my_vector& a, const my_vector& b) {
        return b < a;
    }

    friend bool operator<=(const my_vector& a, const my_vector& b) {
        return !(b < a);
    }

    friend bool operator>=(const my_vector& a, const my_vector& b) {
        return !(a < b);
    }

};



#endif //MY_VECTOR_H
