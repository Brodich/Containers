#ifndef QUEUE
#define QUEUE

namespace st {

template <class T>
class queue {
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef size_t size_type;

 public:
  explicit queue() : m_head(nullptr){};

  explicit queue(std::initializer_list<value_type> const& items) : queue() {
    for (auto i : items) {
      push(i);
    }
  }

  explicit queue(const queue& other) : queue() {
    node* pt = other.m_head;
    while (pt) {
      push(pt->data);
      pt = pt->next;
    }
  }

  explicit queue(queue&& other) : m_head(std::move(other.m_head)) {
    other.m_head = nullptr;
  }

  ~queue() { queue_free(); }

  queue* operator=(queue&& other) {
    queue_free();
    m_head = other.m_head;
    other.m_head = nullptr;
    return (this);
  }

  const_reference front() { return m_head->data; }
  const_reference back() {
    node* tail = get_tail();

    return tail->data;
  }

  inline bool empty() { return (!m_head); }

  size_type size() {
    size_type s = 0;
    node* pt = m_head;
    while (pt) {
      ++s;
      pt = pt->next;
    }
    return s;
  }

  void push(const_reference value) {
    node* newnode = new node(value);
    if (m_head) {
      node* tail = get_tail();
      tail->next = newnode;
    } else {
      m_head = newnode;
    }
  }

  void pop() {
    if (m_head) {
      node* tmp = m_head;
      m_head = m_head->next;
      delete tmp;
    }
  };

  void swap(queue& other) { std::swap(m_head, other.m_head); }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    std::initializer_list<value_type> arguments = {args...};

    for (auto i : arguments) {
      push(i);
    }
  }

 private:
  struct node {
    value_type data;
    node* next;

    node() = default;
    // node() {}
    explicit node(const_reference value) : data(value), next(nullptr){};
  };
  node* m_head;  // point to the left node

  node* get_tail() {
    node* tmp = m_head;
    while (tmp->next) {
      tmp = tmp->next;
    }
    return (tmp);
  }

  void queue_free() {
    while (m_head) {
      pop();
    }
  }
};
}  // namespace st
#endif
