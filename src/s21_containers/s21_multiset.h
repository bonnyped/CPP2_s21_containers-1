/* Copyright 2023 professo bonnypad */
#ifndef SRC_S21_CONTAINERS_S21_MULTISET_H_
#define SRC_S21_CONTAINERS_S21_MULTISET_H_
// #pragma once
#include <functional>
#include <utility>
#include <vector>

#include "../s21_containers/s21_rb_tree.h"

namespace s21 {
template <class Key, typename Comp = std::less<Key>>
class multiset {
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
  multiset() : tree_(new tree_type{}) {}

  multiset(initializer_list_type const &items) : multiset{} {
    for (auto item : items) {
      insert(item);
    }
  }

  multiset(const multiset &other) : tree_(new tree_type{*other.tree_}) {}

  multiset(const multiset &&other) noexcept
      : tree_(new tree_type(std::move(*other.tree_))) {}

  multiset &operator=(const multiset &other) {
    *this->tree_ = *other.tree_;
    return *this;
  }

  multiset &operator=(multiset &&other) {
    *this->tree_ = std::move(*other.tree_);
    return *this;
  }

  ~multiset() {
    delete tree_;
    tree_ = nullptr;
  }

  iterator begin() noexcept { return tree_->Begin(); }

  iterator end() noexcept { return tree_->End(); }

  const_iterator end() const noexcept { return tree_->Cend(); }

  const_iterator begin() const noexcept { return tree_->Cbegin(); }

  const_iterator cend() const noexcept { return tree_->Cend(); }

  const_iterator cbegin() const noexcept { return tree_->Cbegin(); }

  size_type size() const noexcept { return tree_->Size(); }

  size_type max_size() const noexcept { return tree_->MaxSize(); }

  bool empty() const noexcept { return tree_->Empty(); }

  bool contains(const key_type &key) { return tree_->Find(key) != end(); }

  size_type count(const_reference key) { return tree_->Count(key); }

  void clear() {  // noexcept ?
    tree_->Clear();
  }

  iterator lower_bound(const_reference key) noexcept {
    return tree_->LowerBound(key);
  }

  iterator upper_bound(const_reference key) noexcept {
    return tree_->UpperBound(key);
  }

  std::pair<iterator, iterator> equal_range(const_reference key) noexcept {
    return tree_->EqualRange(key);
  }

  std::pair<iterator, bool> insert(const_reference value) {
    return tree_->Insert(value);
  }

  void erase(iterator position) { tree_->Erase(position); }

  void erase(const_reference value) {
    iterator del_node = find(value);
    while (del_node != end()) {
      tree_->Erase(del_node);
      del_node = find(value);
    }
  }

  void merge(multiset &other) noexcept { tree_->Merge(*other.tree_); }

  void swap(multiset &other) noexcept { tree_->Swap(*other.tree_); }

  iterator find(const key_type &key) noexcept { return tree_->Find(key); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    return tree_->InsertMany(std::forward<Args>(args)...);
  }

 private:
  tree_type *tree_;
};

}  // namespace s21

#endif  // SRC_S21_CONTAINERS_S21_MULTISET_H_
