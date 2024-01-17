#include <iostream>
#include <initializer_list>
#include <cstdlib>
#include <cmath>

#if _WIN32 || _WIN64
#if _WIN64
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

template <typename T>
class vector{
    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        // using iterator = T *;
        using pointer = T *;
        using const_iterator = const T *;      
        using size_type = size_t;

        class VectorIterator {
            public:
                explicit VectorIterator(pointer ptr) : m_ptr(ptr) {};
                reference operator*() { return *m_ptr; };
                VectorIterator operator-(int move) { return (m_ptr - move); }
                VectorIterator operator+(int move) { return (m_ptr + move); }
                VectorIterator operator++() { ++m_ptr; return *this; }
                VectorIterator operator++(int) { return VectorIterator(m_ptr++); }
                VectorIterator operator--() { --m_ptr; return *this; }
                VectorIterator operator--(int) { return VectorIterator(m_ptr--); }
                bool operator==(VectorIterator other) { if (m_ptr == other.m_ptr) return true; return false;}
            private:
                pointer m_ptr;
        };

        // template <typename T>
        using iterator = VectorIterator;

        explicit vector(): m_arr(nullptr), m_capacity(0), m_size(0){};
        explicit vector(size_type n) : m_capacity(n), m_size(n), m_arr(new value_type[n]){};
        explicit vector(std::initializer_list<value_type> const &items) : vector((items.size()))
        {
            int count{0};
            for (auto item : items) {
                m_arr[count] = item;
                ++count;
            }
        };
        explicit vector(const vector& v) { 
            m_capacity = v.m_capacity;
            m_size = v.m_size; 
            std::copy(v.m_arr, v.m_arr + v.size, m_arr);    
        };
        explicit vector(vector&& v) : m_capacity((v.m_capacity)), m_size((v.m_size)), m_arr(std::move(v.m_arr)) {};
        ~vector() { if (m_arr) delete[] m_arr; };

        void operator=(vector&& v) { 
            this->m_capacity = v.m_capacity;
            this->m_size = v.m_size;
            std::swap(this->m_arr, v.m_arr);
        };


        reference at(size_type pos) {
            if (pos < 0 || pos > this->m_capacity) {
                std::out_of_range("Out of range");
            }
            return (m_arr[pos]);
        }
        reference operator[] (size_type pos) {
            return (m_arr[pos]);
        }
        const_reference front() {
            return (m_arr[0]);
        }
        const_reference back() {
            return (m_arr[--m_capacity]);
        }
        T* data() {
            return m_arr;
        }

        iterator begin() {
            return iterator(m_arr);
        }
        iterator end() {
            return iterator(m_arr + m_capacity);
        }

        bool empty() {
            return (begin() == end());
        }
        size_type size() {
            return (m_size);
        }
        size_type max_size() {
            // _size = sizeof(value_type);
            size_type _size = 0;
#ifdef ENVIRONMENT64
            _size = std::pow(2, 65 - sizeof(value_type));
#else
            _size = std::pow(2, 33 - sizeof(value_type));
#endif
            _size = _size - 1;
            return _size;
        }
        void reserve(size_type new_size) {
            if (new_size > m_capacity) {
                value_type* new_arr = new value_type[new_size];
                std::copy(m_arr, m_arr + m_size, new_arr);
                delete[] m_arr;
                m_arr = new_arr;
                m_capacity = new_size;
            }
        }
        size_type capacity() {
            return (m_capacity);
        }
        void shrink_to_fit() {
            if (m_capacity > m_size) {
                value_type* new_arr = new value_type[m_size];
                std::copy(m_arr, m_arr + m_size, new_arr);
                delete[] m_arr;
                m_arr = new_arr;
                m_capacity = m_size;
            }
        }
        



        value_type pop_back() {

        }
        void print() {
            for (int i = 0; i < m_size; i++) {
                std::cout << m_arr[i];
            }
            std::cout << std::endl;

        }

        // size_type size() {return m_size;};

    private:
        size_type m_capacity;
        size_type m_size;
        value_type* m_arr;

};

