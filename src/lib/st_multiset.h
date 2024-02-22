#ifndef st_MULTISET_H
#define st_MULTISET_H

#include "BinaryTree.h"

namespace st {
template <class Key, class Compare = std::less<Key>>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using tree_type = BinaryTree<key_type, Compare>;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;

  multiset() : tree_() {}
  multiset(std::initializer_list<value_type> const &items) : tree_() {
    for (const auto &item : items) {
      tree_.interation_sequence(item);
    }
  }

  multiset(const multiset &ms) : tree_(ms.tree_) {}

  multiset(multiset &&ms) : tree_(std::move(ms.tree_)) {}

  ~multiset() { clear(); }

  iterator begin() { return tree_.begin(); }

  const_iterator begin() const { return tree_.begin(); }

  iterator end() { return tree_.end(); }

  const_iterator end() const { return tree_.end(); }

  bool empty() const { return tree_.empty(); }

  size_type size() const { return tree_.size(); }

  size_type max_size() const { return tree_.max_size(); }

  void clear() { tree_.clear(); }

  iterator insert(const value_type &key) {
    return tree_.interation_sequence(key);
  }

  iterator find(const Key &key) { return tree_.find(key); }

  const_iterator find(const Key &key) const { return tree_.find(key); }

  bool contains(const Key &key) const { return tree_.contains(key); }

  void swap(multiset &diff) { std::swap(tree_, diff.tree_); }

  void merge(multiset &diff) {
    for (const auto &item : diff) {
      insert(item);
    }
    diff.clear();
  }

  void erase(iterator pos) { tree_.erase(pos); }

  size_type count(const Key &key) const { return tree_.count(key); }

  multiset &operator=(multiset &&ms) {
    if (this == &ms) {
      return *this;
    }

    tree_ = std::move(ms.tree_);
    return *this;
  }

  multiset &operator=(const multiset &ms) {
    if (this == &ms) {
      return *this;
    }

    tree_ = ms.tree_;
    return *this;
  }

  std::pair<iterator, iterator> equal_range(const Key &key) {
    return tree_.equal_range(key);
  }

  std::pair<const_iterator, const_iterator> equal_range(const Key &key) const {
    return tree_.equal_range(key);
  }

  iterator lower_bound(const Key &key) { return tree_.lower_bound(key); }

  const_iterator lower_bound(const Key &key) const {
    return tree_.lower_bound(key);
  }

  iterator upper_bound(const Key &key) { return tree_.upper_bound(key); }

  const_iterator upper_bound(const Key &key) const {
    return tree_.upper_bound(key);
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

#endif  // st_MULTISET_H
