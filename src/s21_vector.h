#include <iostream>
#include <initializer_list>

template <typename T>
class vector{
    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using iterator = T *;
        using const_iterator = const T *;      
        using size_type = size_t;

        vector(): m_arr(nullptr), m_capacity(0), m_size(0){};
        explicit vector(size_type n) : m_capacity(n), m_size(n), m_arr(new value_type[n]){};
        vector(std::initializer_list<value_type> const &items) : vector((items.size()))
        {
            int count{0};
            for (auto item : items) {
                m_arr[count] = item;
                ++count;
            }
        };
        vector(const vector& v) { 
            m_capacity = v.m_capacity;
            m_size = v.m_size; 
            std::copy(v.m_arr, v.m_arr + v.size, m_arr);    
        };
        vector(vector&& v) : m_capacity((v.m_capacity)), m_size((v.m_size)), m_arr(std::move(v.m_arr)) {};
        ~vector() { if (m_arr) delete[] m_arr; };

        void operator=(vector&& v) { 
            this->m_capacity = v.m_capacity;
            this->m_size = v.m_size;
            std::swap(this->m_arr, v.m_arr);
        };

        // operator=(vector&& v) : (std::move(v)) {};
        // operator=(vector&& v) : (std::move(v)) {};

        void print() {
            for (int i =0; i < m_size; i++) {
                std::cout << m_arr[i];
            }
        }

        // size_type size() {return m_size;};

    private:
        size_type m_capacity;
        size_type m_size;
        value_type* m_arr;

};

