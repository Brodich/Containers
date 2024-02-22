#ifndef st_MAP_H
#define st_MAP_H

#include "BinaryTree.h"

namespace st {
template <class Key, class T, class Compare = std::less<Key>>
class map {
 private:
  class Comparator;

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using tree_type = BinaryTree<value_type, Comparator>;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;

  map() : tree_() {}
  map(std::initializer_list<value_type> const &items) : tree_(items) {}

  map(const map &mapped) : tree_(mapped.tree_) {}

  map(map &&mapped) : tree_(std::move(mapped.tree_)) {}

  ~map() { clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    return tree_.insert(value);
  }

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return tree_.insert(std::make_pair(key, obj));
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    return tree_.insert_or_assign(std::make_pair(key, obj));
  }

  void swap(map &diff) { std::swap(tree_, diff.tree_); }

  void merge(map &diff) { tree_.merge(diff.tree_); }

  iterator begin() { return tree_.begin(); }

  const_iterator begin() const { return tree_.begin(); }

  iterator end() { return tree_.end(); }

  const_iterator end() const { return tree_.end(); }

  void erase(iterator pos) { tree_.erase(pos); }

  T &at(const Key &key) {
    const mapped_type value{};
    return (tree_.at(std::make_pair(key, value))).second;
  }

  const T &at(const Key &key) const {
    const mapped_type value{};
    return (tree_.at(std::make_pair(key, value))).second;
  }

  T &operator[](const Key &key) {
    mapped_type value{};
    return (tree_[std::make_pair(key, value)]).second;
  }

  map &operator=(map &&mapped) {
    if (this == &mapped) {
      return *this;
    }

    tree_ = std::move(mapped.tree_);
    return *this;
  }

  map &operator=(const map &mapped) {
    if (this == &mapped) {
      return *this;
    }

    tree_ = mapped.tree_;
    return *this;
  }

  iterator find(const Key &key) {
    mapped_type value{};
    return tree_.find(std::make_pair(key, value));
  }

  const_iterator find(const Key &key) const {
    mapped_type value{};
    return tree_.find(std::make_pair(key, value));
  }

  bool contains(const Key &key) const {
    mapped_type value{};
    return tree_.contains(std::make_pair(key, value));
  }

  void clear() { tree_.clear(); }

  bool empty() const { return tree_.empty(); }

  size_type size() const { return tree_.size(); }

  size_type max_size() const { return tree_.max_size(); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> vec;
    for (const auto &arg : {args...}) {
      vec.push_back(insert(arg));
    }
    return vec;
  }

 private:
  tree_type tree_;

  class Comparator {
   public:
    bool operator()(const value_type &left, const value_type &right) const {
      return Compare{}(left.first, right.first);
    }
  };
};
}  // namespace st

#endif  // st_MAP_H
