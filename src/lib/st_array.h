#ifndef ARRAY
#define ARRAY

#include <cstddef>

namespace st {
template <class T, size_t N>
class array {
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T* iterator;
  typedef const T* const_iterator;
  typedef size_t size_type;

 public:
  explicit array() = default;

  explicit array(std::initializer_list<value_type> const& items) {
    size_type j = 0;
    for (auto i : items) {
      m_elems[j] = i;
      ++j;
    }
  }

  explicit array(const array& a) = default;

  explicit array(array&& a) = default;

  ~array() = default;

  array& operator=(array&& a) = default;

  reference at(size_type pos) {
    if (pos >= this->m_size) {
      throw std::out_of_range("Out of range");
    }
    return m_elems[pos];
  }

  reference operator[](size_type pos) { return (m_elems[pos]); }

  const_reference front() { return m_elems[0]; }
  const_reference back() { return m_elems[m_size - 1]; }

  iterator data() { return m_elems; }

  iterator begin() { return m_elems; }
  iterator end() { return (m_elems + m_size); }
  const_iterator cbegin() const { return m_elems; }
  const_iterator cend() const { return (m_elems + m_size); }

  bool empty() { return m_size == 0; }

  size_type size() { return m_size; }

  size_type max_size() { return m_size; }

  void swap(array& other) { std::swap(m_elems, other.m_elems); }

  void fill(const_reference value) {
    size_type i = 0;
    while (i != m_size) {
      operator[](i) = value;
      ++i;
    }
  }

 private:
  value_type m_elems[N];
  size_type m_size = N;
};
}  // namespace st

#endif