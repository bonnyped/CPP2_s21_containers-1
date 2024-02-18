#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include <functional>
#include <iostream>
#include <utility>
#include <vector>

#include "s21_rb_tree.h"

namespace s21 {
template <class Key, typename Comp = std::less<Key>>
class set {
 public:
  using key_type = Key;
  using value_type = key_type;
  using reference = key_type &;
  using const_reference = const value_type &;
  using tree_type = RBTree<Key, Comp>;
  using iterator = RBTreeIterator<Key, false>;
  using const_iterator = RBTreeIterator<Key, true>;
  using size_type = std::size_t;
  using initializer_list_type = std::initializer_list<value_type>;

 public:
  set() : tree_(new tree_type) {}

  set(initializer_list_type const &items) : set() {
    for (auto item : items) {
      insert(item);
    }
  }

  set(const set &other) : tree_(new tree_type(*other.tree_)) {}

  set(const set &&other) noexcept
      : tree_(new tree_type(std::move(*other.tree_))) {}

  set &operator=(const set &other) {
    *this->tree_ = *other.tree_;
    return *this;
  }

  set &operator=(set &&other) {
    *this->tree_ = std::move(*other.tree_);
    return *this;
  }

  ~set() {
    delete tree_;
    tree_ = nullptr;
  }

  iterator begin() noexcept { return tree_->Begin(); }

  iterator end() noexcept { return tree_->End(); }

  iterator end() const noexcept { return tree_->End(); }

  iterator begin() const noexcept { return tree_->Begin(); }

  const_iterator cend() const noexcept { return tree_->Cend(); }

  const_iterator cbegin() const noexcept { return tree_->Cbegin(); }

  size_type size() const noexcept { return tree_->Size(); }

  size_type max_size() const noexcept { return (tree_->MaxSize()); }

  bool empty() const noexcept { return tree_->Empty(); }

  bool contains(const key_type &key) { return tree_->Find(key) != end(); }

  void clear() {  // noexcept ?
    tree_->Clear();
  }

  std::pair<iterator, bool> insert(const_reference value) {
    return tree_->InsertUnique(value);
  }

  void erase(iterator position) { tree_->Erase(position); }

  void erase(const_reference value) { tree_->Erase(value); }

  void merge(set &other) noexcept { tree_->MergeUnique(*other.tree_); }

  void swap(set &other) noexcept { tree_->Swap(*other.tree_); }

  iterator find(const key_type &key) noexcept { return tree_->Find(key); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    return tree_->InsertManyUnique(std::forward<Args>(args)...);
  }

 private:
  tree_type *tree_;
};

}  // namespace s21
#endif  // SRC_S21_SET_H_
