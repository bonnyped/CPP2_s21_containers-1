#ifndef S21_CONTAINERS_S21_CONTAINERS_S21_MAP_H_
#define S21_CONTAINERS_S21_CONTAINERS_S21_MAP_H_

#include <iostream>
#include <utility>
#include <vector>

#include "s21_rb_tree.h"

namespace s21 {
template <typename Key, typename T, typename Comp = std::less<Key>>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  // using Args = value_type;

 private:
  struct MapComparator {
    bool operator()(const_reference left, const_reference right) {
      return left.first < right.first;
    }
  };

 public:
  using tree_type = RBTree<value_type, MapComparator>;
  using iterator = RBTreeIterator<value_type, false>;
  using const_iterator = RBTreeIterator<value_type, true>;
  using size_type = std::size_t;
  using initializer_list_type = std::initializer_list<value_type>;

 public:
  map() : tree_(new tree_type()) {}

  map(initializer_list_type const &items) : map() {
    for (auto item : items) {
      insert(item);
    }
  }

  map(const map &other) : tree_(new tree_type(*other.tree_)) {}

  map(const map &&other) noexcept
      : tree_(new tree_type(std::move(*other.tree_))) {}

  map &operator=(const map &other) {
    *this->tree_ = *other.tree_;
    return *this;
  }

  map &operator=(map &&other) {
    *this->tree_ = std::move(*other.tree_);
    return *this;
  }

  ~map() {
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

  bool contains(const key_type &key) {
    return tree_->Find({key, mapped_type{}}) != end();
  }

  mapped_type &at(const key_type &key) {
    iterator status = tree_->Find({key, mapped_type{}});
    if (status == end()) {
      throw std::out_of_range("s21::map::at: key not found");
    }
    return (*status).second;
  }

  mapped_type &operator[](const key_type &key) {
    return (*tree_->InsertUnique({key, mapped_type{}}).first).second;
  }

  void clear() {  // noexcept ?
    tree_->Clear();
  }

  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             mapped_type &&obj) {
    auto [it, status] = tree_->InsertUnique({key, obj});
    if (status == false) {
      it->second = std::forward<mapped_type>(obj);
    }
    return {it, status};
  }

  std::pair<iterator, bool> insert(const_reference value) {
    return tree_->InsertUnique(value);
  }

  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &obj) {
    return tree_->InsertUnique({key, obj});
  }

  void erase(iterator position) { tree_->Erase(position); }

  void erase(const_reference value) { tree_->Erase(value); }

  void merge(map &other) noexcept { tree_->MergeUnique(*other.tree_); }

  void swap(map &other) noexcept { tree_->Swap(*other.tree_); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    return tree_->InsertManyUnique(std::forward<Args>(args)...);
  }

 private:
  tree_type *tree_;
};

}  // namespace s21

#endif  // S21_CONTAINERS_S21_CONTAINERS_S21_map_H_