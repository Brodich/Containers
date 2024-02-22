#ifndef LIST
#define LIST

namespace st {
template <class T>
class list {
 private:
  class ListIterator;
  class ListConstIterator;
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef ListIterator iterator;
  typedef ListConstIterator const_iterator;
  typedef size_t size_type;
  friend ListIterator;

 public:
  explicit list() : m_size(0) {
    node* newnode = new node();

    newnode->next = newnode;
    newnode->prev = newnode;
    m_tail = newnode;
    m_head = newnode;
  };

  explicit list(size_type n) : list() {
    size_type i = 0;
    while (i < n) {
      push_back(0);
      ++i;
    }
  };
  explicit list(std::initializer_list<value_type> const& items) : list() {
    for (auto& item : items) {
      push_back(item);
    }
  };

  explicit list(const list& l) : list() {
    list<value_type>::const_iterator temp(l.m_head);
    while (temp.m_current != l.m_tail) {
      insert(end(), temp.m_current->data);
      ++temp;
    }
  };
  explicit list(list&& l)
      : m_head(std::move(l.m_head)),
        m_tail(std::move(l.m_tail)),
        m_size(std::move(l.m_size)) {
    l.m_head = nullptr;
    l.m_tail = nullptr;
    l.m_size = 0;
  }

  ~list() {
    while (m_size > 0) {
      erase(begin());
    }
    if (m_tail) delete m_tail;
  };

  list& operator=(list&& l) {
    if (m_head != l.m_head && m_tail != l.m_tail) {
      while (m_size > 0) {
        erase(begin());
      }
      if (m_tail) {
        delete m_tail;
      }
      m_head = std::move(l.m_head);
      m_tail = std::move(l.m_tail);
      m_size = std::move(l.m_size);

      l.m_head = nullptr;
      l.m_tail = nullptr;
      l.m_size = 0;
    }
    return *this;
  }

  inline const_reference front() { return m_head->data; };
  inline const_reference back() { return m_tail->prev->data; };

  iterator begin() { return iterator(m_head); };
  iterator end() { return iterator(m_tail); };
  const_iterator cbegin() { return const_iterator(m_head); };
  const_iterator cend() { return const_iterator(m_tail); };

  bool empty() { return begin() == end(); }

  size_type size() { return m_size; }

  size_type max_size() {
    std::allocator<node> A;
    return A.max_size();
  }

  void clear() {
    while (!empty()) {
      erase(begin());
    }
  }

  iterator insert(iterator pos, const_reference value) {
    node* newnode = new node(value);

    newnode->next = pos.m_current;
    newnode->prev = pos.m_current->prev;
    pos.m_current->prev->next = newnode;
    pos.m_current->prev = newnode;

    if (pos == begin()) {
      m_head = newnode;
    }
    ++m_size;
    return iterator(newnode);
  }

  void erase(iterator pos) {
    if (pos != end()) {
      if (pos == begin()) {
        m_head = pos.m_current->next;
      }
      pos.m_current->prev->next = pos.m_current->next;
      pos.m_current->next->prev = pos.m_current->prev;
      delete pos.m_current;
      --m_size;
    }
  }

  void push_back(const_reference value) { insert(end(), value); };
  void pop_back() { erase(--(end())); };
  void push_front(const_reference value) { insert(begin(), value); };
  void pop_front() { erase(begin()); }

  void swap(list& other) {
    std::swap(other.m_head, m_head);
    std::swap(other.m_tail, m_tail);
    std::swap(other.m_size, m_size);
  }

  void merge(list& other) {
    iterator i = other.begin();
    iterator e = other.end();
    iterator j = begin();

    while (i != e) {
      if (i.m_current->data < j.m_current->data) {
        insert(j, i.m_current->data);
        ++i;
      }
      while (i.m_current->data > j.m_current->data) {
        ++j;
      }
    }
    other.clear();
  }

  void splice(const_iterator pos, list& other) {
    iterator it(const_cast<node*>(pos.m_current));

    other.begin().m_current->prev = it.m_current->prev;
    it.m_current->prev->next = other.begin().m_current;

    auto en = --(other.end());
    en.m_current->next = it.m_current;
    it.m_current->prev = en.m_current;
    if (it == begin()) {
      m_head = other.begin().m_current;
    }
    m_size += other.m_size;
    other.m_head = other.m_tail;
    other.m_size = 0;
  }

  void reverse() {
    iterator it_beg = begin();
    iterator it_end = --(end());

    size_type s = m_size / 2;
    while (s > 0) {
      std::swap(it_beg.m_current->data, it_end.m_current->data);
      ++it_beg;
      --it_end;
      --s;
    }
  }

  void unique() {
    iterator i = begin();

    while (i != end()) {
      if (i.m_current->data == i.m_current->next->data) {
        erase(iterator(i.m_current->next));
      } else {
        ++i;
      }
    }
  };

  void sort() {
    iterator i = begin();
    iterator e = end();
    iterator j;

    while (i != e) {
      j = i;
      while (j != e) {
        if (i.m_current->data > j.m_current->data) {
          std::swap(i.m_current->data, j.m_current->data);
        }
        ++j;
      }
      ++i;
    }
  };

  template <typename... Args>
  iterator insert_many(iterator pos, Args&&... args) {
    std::initializer_list<value_type> arguments = {args...};
    list tmp{arguments};
    splice(const_iterator(pos.m_current), tmp);
    return (pos - arguments.size());
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    std::initializer_list<value_type> arguments = {args...};
    list tmp{arguments};
    splice(cend(), tmp);
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    std::initializer_list<value_type> arguments = {args...};
    list tmp{arguments};
    splice(cbegin(), tmp);
  }

 private:
  struct node {
    value_type data;
    node* next;
    node* prev;

    node() = default;
    // node () {};
    node(value_type item) noexcept : data(item), next(nullptr), prev(nullptr) {}
  };

  node* m_head;  // first
  node* m_tail;  // last
  size_type m_size;

  class ListConstIterator {
    friend list;

   public:
    explicit ListConstIterator(){};
    explicit ListConstIterator(node* ptr) noexcept : m_current(ptr) {}
    const_iterator operator++() {
      m_current = m_current->next;
      return (*this);
    }
    const_iterator operator--() {
      m_current = m_current->prev;
      return (*this);
    }
    const_iterator operator-(long move) {
      while (move > 0) {
        this->operator--;
        --move;
      }
      return (*this);
    }
    const_iterator operator+(long move) {
      while (move > 0) {
        this->operator++;
        --move;
      }
      return (*this);
    }
    bool operator==(iterator other) {
      return (this->m_current == other.m_current);
    }
    bool operator!=(iterator other) {
      return (this->m_current != other.m_current);
    }
    reference operator*() { return (m_current->data); }

   private:
    const node* m_current;
  };

  class ListIterator {
    friend list;

   public:
    explicit ListIterator(){};
    explicit ListIterator(node* ptr) noexcept : m_current(ptr) {}
    iterator operator++() {
      m_current = m_current->next;
      return (*this);
    }
    iterator operator--() {
      m_current = m_current->prev;
      return (*this);
    }
    iterator operator-(long move) {
      iterator temp(*this);
      while (move > 0) {
        --temp;
        --move;
      }
      return (temp);
    }
    iterator operator+(long move) {
      while (move > 0) {
        this->operator++;
        --move;
      }
      return (*this);
    }
    bool operator==(iterator other) {
      return (this->m_current == other.m_current);
    }
    bool operator!=(iterator other) {
      return (this->m_current != other.m_current);
    }
    reference operator*() { return (m_current->data); }

   private:
    node* m_current;
  };
};
}  // namespace st

#endif
