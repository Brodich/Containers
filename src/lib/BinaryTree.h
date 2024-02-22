#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>

template <class T, class Compare = std::less<T>>
class BinaryTree {
 private:
  struct Node;

 public:
  using Key = T;
  using size_type = size_t;

  BinaryTree() : root_(nullptr), size_(0) {}

  BinaryTree(std::initializer_list<Key> const &items)
      : root_(nullptr), size_(0) {
    for (const auto &item : items) {
      insert(item);
    }
  }

  BinaryTree(const BinaryTree &diff) : root_(nullptr), size_(0) {
    *this = diff;
  }

  BinaryTree(BinaryTree &&diff) : root_(diff.root_), size_(diff.size_) {
    diff.root_ = nullptr;
    diff.size_ = 0;
  }

  ~BinaryTree() { clear(); }

  struct iterator {
    Node *node_;

    iterator(Node *node) : node_(node) {}

    iterator &operator++() {
      if (node_ == nullptr) {
        return *this;
      }

      if (node_->right_ != nullptr) {
        node_ = node_->right_;
        while (node_->left_ != nullptr) {
          node_ = node_->left_;
        }
        return *this;
      }

      Node *parent = node_->parent_;

      while (parent && node_ == parent->right_) {
        node_ = parent;
        parent = parent->parent_;
      }
      node_ = parent;
      return *this;
    }

    iterator &operator--() {
      if (node_ == nullptr) {
        return *this;
      }

      if (node_->left_ != nullptr) {
        node_ = node_->left_;
        while (node_->right_ != nullptr) {
          node_ = node_->right_;
        }
        return *this;
      }

      Node *parent = node_->parent_;

      while (parent && node_ == parent->left_) {
        node_ = parent;
        parent = parent->parent_;
      }
      node_ = parent;
      return *this;
    }

    bool operator==(const iterator &diff) { return (node_ == diff.node_); }

    bool operator!=(const iterator &diff) { return (node_ != diff.node_); }

    Key &operator*() const { return node_->key_; }
  };

  struct const_iterator {
    const Node *node_;

    const_iterator(Node *node) : node_(node) {}

    const_iterator &operator++() {
      if (node_ == nullptr) {
        return *this;
      }

      if (node_->right_ != nullptr) {
        node_ = node_->right_;

        while (node_->left_ != nullptr) {
          node_ = node_->left_;
        }

        return *this;
      }
      Node *parent = node_->parent_;

      while (parent && node_ == parent->right_) {
        node_ = parent;
        parent = parent->parent_;
      }

      node_ = parent;
      return *this;
    }

    const_iterator &operator--() {
      if (node_ == nullptr) {
        return *this;
      }

      if (node_->left_ != nullptr) {
        node_ = node_->left_;

        while (node_->right_ != nullptr) {
          node_ = node_->right_;
        }
        return *this;
      }

      Node *parent = node_->parent_;

      while (parent && node_ == parent->left_) {
        node_ = parent;
        parent = parent->parent_;
      }

      node_ = parent;
      return *this;
    }

    bool operator==(const const_iterator &diff) { return node_ == diff.node_; }

    bool operator!=(const const_iterator &diff) { return node_ != diff.node_; }

    const Key &operator*() const { return node_->key_; }
  };

  std::pair<iterator, bool> insert(const Key &value) {
    auto new_node = new Node(value);
    auto insertTrue = insert(new_node);

    if (insertTrue) {
      return std::make_pair(iterator(new_node), insertTrue);
    }

    else {
      delete new_node;
      return std::make_pair(find(value), insertTrue);
    }
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key) {
    auto new_node = new Node(key);
    auto insertTrue = insert(new_node);

    if (!insertTrue) {
      auto scenario = find(key);
      erase(scenario);
      insert(new_node);
    }

    return std::make_pair(iterator(new_node), insertTrue);
  }

  void merge(BinaryTree<Key, Compare> &diff) {
    for (auto scenario = diff.begin(); scenario != diff.end();) {
      auto new_node = new Node(*scenario);

      auto next_scenario = scenario;

      ++next_scenario;

      if (insert(new_node)) {
        diff.erase(scenario);
      } else {
        delete new_node;
      }

      scenario = next_scenario;
    }
  }

  iterator begin() {
    if (root_ == nullptr) {
      return iterator(nullptr);
    }

    Node *current = root_;

    while (current->left_ != nullptr) {
      current = current->left_;
    }
    return iterator(current);
  }

  const_iterator begin() const {
    if (root_ == nullptr) {
      return const_iterator(nullptr);
    }

    Node *current = root_;

    while (current->left_ != nullptr) {
      current = current->left_;
    }
    return const_iterator(current);
  }

  iterator end() { return iterator(nullptr); }

  const_iterator end() const { return const_iterator(nullptr); }

  void erase(iterator pos) {
    if (pos.node_ == nullptr) {
      return;
    }

    Node *node_to_delete = pos.node_;

    if (node_to_delete->left_ == nullptr) {
      transplant(node_to_delete, node_to_delete->right_);
    }

    else if (node_to_delete->right_ == nullptr) {
      transplant(node_to_delete, node_to_delete->left_);
    }

    else {
      Node *successor = minimum(node_to_delete->right_);

      if (successor->parent_ != node_to_delete) {
        transplant(successor, successor->right_);
        successor->right_ = node_to_delete->right_;
        successor->right_->parent_ = successor;
      }

      transplant(node_to_delete, successor);
      successor->left_ = node_to_delete->left_;
      successor->left_->parent_ = successor;
    }

    delete node_to_delete;
    --size_;
  }

  void transplant(Node *u, Node *v) {
    if (u->parent_ == nullptr) {
      root_ = v;
    } else if (u == u->parent_->left_) {
      u->parent_->left_ = v;
    } else {
      u->parent_->right_ = v;
    }

    if (v != nullptr) {
      v->parent_ = u->parent_;
    }
  }

  Node *minimum(Node *node) const {
    while (node->left_ != nullptr) {
      node = node->left_;
    }
    return node;
  }

  Key &at(const Key &key) {
    auto scenario = find(key);

    if (scenario != end()) {
      return (*scenario);
    }

    throw std::out_of_range("Key not found in BinaryTree");
  }

  const Key &at(const Key &key) const {
    auto scenario = find(key);

    if (scenario != end()) {
      return (*scenario);
    }

    throw std::out_of_range("Key not found in BinaryTree");
  }

  iterator find(const Key &key) {
    auto cmp = Compare{};
    auto current = root_;

    while (current && (cmp(current->key_, key) || cmp(key, current->key_))) {
      if (cmp(current->key_, key)) {
        current = current->right_;
      } else {
        current = current->left_;
      }
    }

    if (current == nullptr) {
      return iterator(nullptr);
    } else {
      return iterator(current);
    }
  }

  const_iterator find(const Key &key) const {
    auto cmp = Compare{};
    auto current = root_;

    while (current && (cmp(current->key_, key) || cmp(key, current->key_))) {
      if (cmp(current->key_, key)) {
        current = current->right_;
      } else {
        current = current->left_;
      }
    }

    if (current == nullptr) {
      return const_iterator(nullptr);
    } else {
      return const_iterator(current);
    }
  }

  bool contains(const Key &key) const { return find(key) != end(); }

  void clear() {
    iterator scenario = begin();

    while (scenario != end()) {
      iterator current = scenario;
      ++scenario;
      erase(current);
    }

    root_ = nullptr;
  }

  Key &operator[](const Key &key) {
    auto scenario = find(key);

    if (scenario != end()) {
      return *scenario;
    }

    auto new_node = new Node(key);
    insert(new_node);
    return new_node->key_;
  }

  BinaryTree &operator=(const BinaryTree &diff) {
    if (this == &diff) {
      return *this;
    }
    clear();

    for (const auto &item : diff) {
      interation_sequence(item);
    }

    size_ = diff.size_;
    return *this;
  }

  iterator interation_sequence(const Key &key) {
    auto new_node = new Node(key);

    if (root_ == nullptr) {
      root_ = new_node;
      ++size_;
      return iterator(new_node);
    }

    Node *current = root_;
    Node *parent = nullptr;

    while (current != nullptr) {
      parent = current;
      current = Compare{}(new_node->key_, current->key_) ? current->left_
                                                         : current->right_;
    }

    if (parent != nullptr) {
      if (Compare{}(new_node->key_, parent->key_)) {
        parent->left_ = new_node;
      } else {
        parent->right_ = new_node;
      }
      new_node->parent_ = parent;
      ++size_;
    }

    return iterator(new_node);
  }

  BinaryTree &operator=(BinaryTree &&diff) {
    if (this == &diff) {
      return *this;
    }

    clear();
    root_ = diff.root_;
    size_ = diff.size_;
    diff.root_ = nullptr;
    diff.size_ = 0;
    return *this;
  }

  bool empty() const { return root_ == nullptr; }

  size_type size() const { return size_; }

  size_type max_size() const { return SIZE_MAX / sizeof(Node) / 2; }

  std::pair<iterator, iterator> equal_range(const Key &key) {
    auto last = find(key);
    auto first = last;

    if (last == end()) {
      return std::make_pair(last, last);
    }

    while (first != begin()) {
      auto prev = first;
      --prev;
      if (Compare{}(*prev, key) || Compare{}(key, *prev)) {
        break;
      }
      first = prev;
    }

    while (last != end() && !Compare{}(*last, key) && !Compare{}(key, *last)) {
      ++last;
    }

    return std::make_pair(first, last);
  }

  std::pair<const_iterator, const_iterator> equal_range(const Key &key) const {
    auto last = find(key);
    auto first = last;

    if (last == end()) {
      return std::make_pair(last, last);
    }

    while (first != begin()) {
      auto prev = first;
      --prev;
      if (Compare{}(*prev, key) || Compare{}(key, *prev)) {
        break;
      }
      first = prev;
    }

    while (last != end() && !Compare{}(*last, key) && !Compare{}(key, *last)) {
      ++last;
    }

    return std::make_pair(first, last);
  }

  iterator lower_bound(const Key &key) {
    auto current = root_;

    while (current != nullptr && Compare{}(current->key_, key)) {
      current = current->right_;
    }
    return iterator(current);
  }

  const_iterator lower_bound(const Key &key) const {
    auto current = root_;

    while (current != nullptr && Compare{}(current->key_, key)) {
      current = current->right_;
    }
    return const_iterator(current);
  }

  iterator upper_bound(const Key &key) {
    auto current = root_;

    while (current != nullptr && !Compare{}(key, current->key_)) {
      current = current->right_;
    }
    return iterator(current);
  }

  const_iterator upper_bound(const Key &key) const {
    auto current = root_;

    while (current != nullptr && !Compare{}(key, current->key_)) {
      current = current->right_;
    }
    return const_iterator(current);
  }

  size_type count(const Key &key) const {
    auto scenario = find(key);
    size_type result = 0;

    while (scenario != end() &&
           !(Compare{}(*scenario, key) || Compare{}(key, *scenario))) {
      ++result;
      ++scenario;
    }
    return result;
  }

 private:
  struct Node {
    Key key_;
    Node *left_;
    Node *right_;
    Node *parent_;

    Node(Key key, Node *left = nullptr, Node *right = nullptr,
         Node *parent = nullptr)
        : key_(key), left_(left), right_(right), parent_(parent) {}
  };

  Node *root_;
  size_type size_;

  bool insert(Node *new_node) {
    auto cmp = Compare{};
    if (root_ == nullptr) {
      root_ = new_node;
      ++size_;
      return true;
    }

    Node *current = root_;
    Node *parent = root_;

    while (current != nullptr) {
      parent = current;
      bool lessThan = cmp(new_node->key_, current->key_);
      bool greaterThan = cmp(current->key_, new_node->key_);

      if (!(lessThan || greaterThan)) {
        return false;
      }
      current = lessThan ? current->left_ : current->right_;
    }

    if (cmp(new_node->key_, parent->key_)) {
      parent->left_ = new_node;
    } else {
      parent->right_ = new_node;
    }

    new_node->parent_ = parent;
    ++size_;
    return true;
  }
};

#endif  //  BINARYTREE_H
