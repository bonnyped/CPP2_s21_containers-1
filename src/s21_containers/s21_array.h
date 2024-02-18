#ifndef SRC_S21_CONTAINERS_S21_ARRAY_H_
#define SRC_S21_CONTAINERS_S21_ARRAY_H_
#include <iostream>

// нужно вместе на созвоне разобраться с тем, где нужно поставить конст,
// ноэксепт и почему? чем отличается цбегин от бегин?

namespace s21 {
template <class T, size_t num_>
class array {
 private:
  template <bool IsConst>
  class a_iterator {
   private:
    using value_type = std::conditional_t<IsConst, const T, T>;
    using pointer_type =
        std::conditional_t<IsConst, const value_type *, value_type *>;
    using reference_type =
        std::conditional_t<IsConst, const value_type &, value_type &>;
    pointer_type ptr_;

   public:
    a_iterator(pointer_type ptr) : ptr_(ptr){};
    a_iterator(const a_iterator &) = default;

    bool operator!=(const a_iterator &other) {
      return this->ptr_ != other.ptr_;
    };

    bool operator==(const a_iterator &other) {
      return this->ptr_ == other.ptr_;
    };

    a_iterator &operator++() {
      ++ptr_;
      return *this;
    };
    const a_iterator operator++(int) {
      a_iterator copy = *this;
      ptr_++;
      return copy;
    }

    std::size_t operator-(a_iterator const &rhs) {
      return this->get_ptr() - rhs.ptr_;
    };

    value_type operator*() { return *ptr_; };
    pointer_type get_ptr() { return ptr_; };
    // pointer_type operator->() { return ptr_; };
  };

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using iterator = a_iterator<false>;
  using const_iterator = a_iterator<true>;
  value_type arr_[num_];

  //  основные публичные методы для взаимодействия с классом:
  array() noexcept = default;
  array(std::initializer_list<value_type> const &items) : arr_{} {
    if (size() >= items.size()) {
      auto elem_list = begin();
      for (auto elem = items.begin(); elem != items.end(); ++elem) {
        *elem_list.get_ptr() = *elem;
        ++elem_list;
      }
    } else
      throw std::out_of_range("Слишком много инициализаторов!");
  };
  array(const array &a) { *this = a; };
  array(array &&a) { *this = std::move(a); };
  ~array() = default;

  array &operator=(array &&a) { return a; };

  // публичные методы для доступа к элементам класса:
  reference at(size_type pos) {
    if (pos < 0 || pos > num_ - 1)
      throw std::out_of_range(
          "Введенная позиция находится за пределами массива!");
    return arr_[pos];
  };
  reference operator[](size_type pos) { return at(pos); };
  const_reference front() { return at(0); };
  const_reference back() { return at(size() - 1); };
  iterator data() {
    return begin();
  };  // точно ли этот метод должен копировать логику итератора бегин?

  // публичные методы для итерирования по элементам класса (доступ к
  // итераторам):
  iterator begin() { return arr_; };
  iterator end() { return arr_ + num_; };
  const_iterator begin() const { return arr_; };
  const_iterator end() const { return arr_ + num_; };

  // публичные методы для доступа к информации о наполнении контейнера:
  bool empty() const noexcept { return num_ == 0; };
  size_type size() { return num_; };
  size_type max_size() { return num_; };

  // публичные методы для изменения контейнера:
  void swap(array &other) noexcept {
    array tmp = other;
    other = *this;
    *this = tmp;
  };

  void fill(const_reference value) {
    for (auto it = begin(); it != end(); ++it) *it.get_ptr() = value;
  };

  array &operator=(const array &a) {
    size_type count = 0;
    for (auto elem : a) arr_[count++] = elem;
    return *this;
  }
};
};  // namespace s21_array


#endif  //  SRC_S21_CONTAINERS_S21_ARRAY_H_
