#ifndef st_SET_H
#define st_SET_H

#include "BinaryTree.h"

namespace st {
template <class Key, class Compare = std::less<Key>>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using tree_type = BinaryTree<key_type, Compare>;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;

  set() : tree_() {}
  explicit set(std::initializer_list<value_type> const &items) : tree_(items) {}

  set(const set &setted) : tree_(setted.tree_) {}

  set(set &&setted) : tree_(std::move(setted.tree_)) {}

  ~set() { clear(); }

  iterator begin() { return tree_.begin(); }

  const_iterator begin() const { return tree_.begin(); }

  iterator end() { return tree_.end(); }

  const_iterator end() const { return tree_.end(); }

  bool empty() const { return tree_.empty(); }

  size_type size() const { return tree_.size(); }

  size_type max_size() const { return tree_.max_size(); }

  void clear() { tree_.clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    return tree_.insert(value);
  }

  iterator find(const Key &key) { return tree_.find(key); }

  const_iterator find(const Key &key) const { return tree_.find(key); }

  bool contains(const Key &key) const { return tree_.contains(key); }

  void swap(set &diff) { std::swap(tree_, diff.tree_); }

  void merge(set &diff) { tree_.merge(diff.tree_); }

  void erase(iterator pos) { tree_.erase(pos); }

  set &operator=(set &&setted) {
    if (this == &setted) {
      return *this;
    }

    tree_ = std::move(setted.tree_);
    return *this;
  }

  set &operator=(const set &setted) {
    if (this == &setted) {
      return *this;
    }

    tree_ = setted.tree_;
    return *this;
  }

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
};
}  // namespace st

#endif  // st_SET_H
