/* Copyright 2023 bonnyped professo */
#ifndef SRC_S21_CONTAINERS_S21_ARRAY_H_
#define SRC_S21_CONTAINERS_S21_ARRAY_H_
#include <iostream>

namespace s21 {

template <class T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;
  struct array_n;

  //  основные публичные методы для взаимодействия с классом:
  array() noexcept = default;

  array(std::initializer_list<value_type> const &items) : arr_{} {
    if (size() >= items.size()) {
      auto elem_list = begin();
      for (auto elem = items.begin(); elem != items.end(); ++elem) {
        *elem_list = *elem;
        ++elem_list;
      }
    } else {
      throw std::out_of_range("There are too many initializers!");
    }
  }

  array(const array &a) {
    size_type count = 0;
    for (auto elem : a) {
      arr_[count++] = elem;
    }
  }

  array(array &&a) noexcept {
    if (this != &a) {
      *this = std::move(a);
    }
  }

  ~array() = default;

  array &operator=(array &&a) {
    if (this != &a) {
      for (size_t i = 0U; i < size(); ++i) {
        this->arr_[i] = std::move(a.arr_[i]);
      }
    }
    return *this;
  }

  // публичные методы для доступа к элементам класса:
  reference at(size_type pos) {
    if (size() == 0U || pos > N - 1)
      throw std::out_of_range(
          "Введенная позиция находится за пределами массива!");
    return arr_[pos];
  }

  reference operator[](size_type pos) { return arr_[pos]; }

  const_reference front() { return at(0); }

  const_reference back() { return at(size() - 1); }

  iterator data() { return arr_; }

  // публичные методы для итерирования по элементам класса (доступ к
  // итераторам):
  iterator begin() noexcept { return arr_; }
  iterator end() noexcept { return arr_ + N; }
  const_iterator begin() const noexcept { return arr_; }
  const_iterator end() const noexcept { return arr_ + N; }

  // публичные методы для доступа к информации о наполнении контейнера:
  bool empty() const noexcept { return N == 0; };

  size_type size() const noexcept { return N; }

  size_type max_size() const noexcept { return N; }

  // публичные методы для изменения контейнера:
  void swap(array &other) noexcept {  // NOLINT
    std::swap_ranges<iterator, iterator>(other.begin(), other.end(), begin());
  }

  void fill(const_reference value) {
    for (auto it = begin(); it != end(); ++it) *it = value;
  }

 public:
  value_type arr_[N];
};

template <typename T>
class array<T, 0> {
 public:
  using value_type = T;
  using value_type_pointer = T *;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  struct Type {};
  value_type_pointer arr_;
  array() {}
  bool empty() const noexcept { return true; }
  size_type size() const noexcept { return 0; }
  size_type max_size() const noexcept { return 0; }
  iterator data() { return 0; }
  void fill(const_reference &) {}
  void swap(array &) {}  // NOLINT
  reference operator[](size_type pos) { return at(pos); }
  reference at(size_type pos) {
    throw std::out_of_range(
        "Введенная позиция находится за пределами массива!");
    return *(static_cast<value_type_pointer>(nullptr));
  }
  const_reference front() {
    return at(0);
  }  // не разобрался как отловить тестом сегу
  const_reference back() { return at(0); }
  iterator begin() noexcept { return 0; }
  iterator end() noexcept { return 0; }
  iterator cbegin() noexcept { return 0; }
  iterator cend() noexcept { return 0; }
  const_iterator begin() const noexcept { return 0; }
  const_iterator end() const noexcept { return 0; }
};

}  // namespace s21

#endif  //  SRC_S21_CONTAINERS_S21_ARRAY_H_
