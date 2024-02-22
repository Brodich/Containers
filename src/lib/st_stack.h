#ifndef STACK
#define STACK

namespace st {
template <class T>
class stack {
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef size_t size_type;

 public:
  explicit stack() : m_head(nullptr){};

  explicit stack(std::initializer_list<value_type> const& items) : stack() {
    for (auto i : items) {
      push(i);
    }
  }

  explicit stack(const stack& other) : stack() {
    stack reverse;
    node* pt = other.m_head;
    while (pt != nullptr) {
      reverse.push(pt->data);
      pt = pt->prev;
    }

    while (reverse.m_head) {
      this->push(reverse.top());
      reverse.pop();
    }
  }

  explicit stack(stack&& other) : m_head(std::move(other.m_head)) {
    other.m_head = nullptr;
  };

  ~stack() { stack_free(); }

  stack& operator=(stack&& other) {
    stack_free();
    m_head = std::move(other.m_head);
    other.m_head = nullptr;
    return (*this);
  }

  inline value_type top() { return m_head->data; };

  bool empty() { return (!m_head); };

  size_type size() {
    size_type s = 0;
    node* pt = m_head;
    while (pt) {
      pt = pt->prev;
      ++s;
    }
    return (s);
  }
  void push(const_reference value) {
    node* newnode = new node(value);
    newnode->prev = m_head;
    m_head = newnode;
  }

  void pop() {
    if (m_head) {
      node* tmp = m_head;
      m_head = m_head->prev;
      delete tmp;
    }
  };

  void swap(stack& other) {
    stack reverse;
    while (other.m_head) {
      reverse.push(other.top());
      other.pop();
    }
    other.m_head = std::move(m_head);
    m_head = nullptr;
    while (reverse.m_head) {
      push(reverse.top());
      reverse.pop();
    }
  }

  // ... but not front, this is back
  template <typename... Args>
  void insert_many_front(Args&&... args) {
    std::initializer_list<value_type> arguments = {args...};
    for (auto i : arguments) {
      push(i);
    }
  }

 private:
  struct node {
    node(const_reference value) : data(value){};
    node* prev;
    value_type data;
  };
  node* m_head;  // point to the right node

  void stack_free() {
    while (m_head) {
      pop();
    }
  }
};
}  // namespace st

#endif
