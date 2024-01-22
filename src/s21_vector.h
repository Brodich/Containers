#include <iostream>
#include <stdarg.h>
#include <cmath>
#include <initializer_list>
#include <string>

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
        using iterator = T *;
        using pointer = T *;
        using const_iterator = const T *;      
        using size_type = size_t;

        explicit vector(): m_arr(nullptr), m_capacity(0), m_size(0){};
        explicit vector(size_type n) : m_capacity(n), m_size(n), m_arr(new value_type[n]()){};

        explicit vector(std::initializer_list<value_type> const &items) : vector((items.size()))
        {
            int count{0};
            for (auto item : items) {
                m_arr[count] = item;
                ++count;
            }
        };
        explicit vector(const vector& v) {
            m_arr = new value_type[v.m_capacity]();
            m_capacity = v.m_capacity;
            m_size = v.m_size; 
            std::copy(v.m_arr, v.m_arr + v.m_size, m_arr);    
        };
        explicit vector(vector&& v) : m_capacity((v.m_capacity)), m_size((v.m_size)), m_arr(std::move(v.m_arr)) {
            v.m_arr = nullptr;
        };
        ~vector() { if (m_arr) delete[] m_arr; };

        void operator=(vector&& v) {
            delete[] m_arr;
            m_capacity = v.m_capacity;
            m_size = v.m_size;
            m_arr = std::move(v.m_arr);
            v.m_capacity = 0;
            v.m_size = 0;
            v.m_arr = nullptr;
        };


        reference at(size_type pos) {
            if (pos < 0 || pos >= this->m_size) {
                throw std::out_of_range("Out of range");
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
            return (m_arr);
        }
        iterator end() {
            return (m_arr + m_size);
        }

        bool empty() {
            return (begin() == end());
        }
        size_type size() {
            return (m_size);
        }
        size_type max_size() {
            size_type _size = 0;
            if (std::pow(2, 65 - sizeof(value_type)) > std::numeric_limits<long long>::max()) {
                _size = std::pow(2, 65 - sizeof(value_type)) / 2;
            } else {
#ifdef ENVIRONMENT64
            _size = (std::pow(2, 65 - sizeof(value_type)));
#else
            _size = std::pow(2, 33 - sizeof(value_type));
#endif
            }
            _size = _size - 1;
            return _size;
        }
        void reserve(size_type new_size) {
            if (new_size > max_size()) {
                throw std::length_error("New size too much");
            }
            if (new_size > m_capacity) {
                change_size(new_size);
            }
        }
        size_type capacity() {
            return (m_capacity);
        }
        void shrink_to_fit() {
            if (m_capacity > m_size) {
                change_size(m_size);
            }
        }

        void clear() {
            m_size = 0;
        }
        iterator insert(iterator pos, const_reference value) {
            size_type i = end() - pos;
            if (m_size == m_capacity) {
                change_size(m_capacity * 2);
            }
            iterator iter_end = this->end();
            while (i > 0) {
                *iter_end = *(iter_end - 1);
                --iter_end;
                --i;
            }
            *iter_end = value;
            ++m_size;
            return (pos);
        }
        void erase(iterator pos) {
            size_type i = end() - pos;
            while (i > 0) {
                *pos = *(pos + 1);
                ++pos;
                --i;
            }
            --m_size;
        }
        void push_back(value_type element) {
            if (m_size == m_capacity) {
                change_size(m_capacity * 2);
            }
            iterator iter = end();
            *iter = element;
            m_size++;
        }
        void pop_back() {
            --m_size;
        }
        void swap(vector& other) {
            std::swap(other.m_arr, m_arr);
            std::swap(other.m_size, m_size);
            std::swap(other.m_capacity, m_capacity);
        }

        template <typename... Args>
        iterator insert_many(iterator pos, Args&&... args) {
            std::initializer_list arguments = {args...};
            size_type siz = end() - pos;
            size_type count = 0;
            for (auto i = arguments.begin(); i != arguments.end(); ++i, ++count) {
                insert(end() - siz, *i);
            }
            return (end() - siz - count);
        }
        template <typename... Args>
        void insert_many_back(Args &&... args) {
            std::initializer_list arguments = {args...};
            for (auto i = arguments.begin(); i != arguments.end(); ++i) {
                insert(end(), *i);
            }
        }

        void print() {
            std::cout << "start\n";
            for (auto i = begin(); i != end(); ++i) {
                
                std::cout << *i << " ";
            }
            // for (int i = 0; i < m_size; i++) {
            //     std::cout << m_arr[i] << " ";
            // }
            std::cout << "\nend\n";
            std::cout << std::endl;
        }

    private:
        size_type m_capacity;
        size_type m_size;
        value_type* m_arr;

    void change_size(size_type future_size) {
        value_type* new_arr = new value_type[future_size]();
        std::copy(m_arr, m_arr + m_size, new_arr);
        delete[] m_arr;
        m_arr = new_arr;
        m_capacity = future_size;
    }
};

