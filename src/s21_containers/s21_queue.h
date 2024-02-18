#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_
#include <iostream>

#include "s21_list.h"

namespace s21 {

template <typename T, typename Container = s21::list<T>>
class queue {
 public:
  using container_type = Container;
  using value_type = typename Container::value_type;
  using size_type = typename Container::size_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;

  queue() : container_{} {}
  explicit queue(std::initializer_list<value_type> const &items)
      : container_{} {
    for (auto item : items) {
      container_.push_front(item);
    }
  }
  explicit queue(const queue &other) : container_(other.container_) {}
  explicit queue(queue &&other) : container_(std::move(other.container_)) {}
  ~queue() = default;
  queue &operator=(const queue &other) {
    container_ = other.container_;
    return *this;
  }
  queue &operator=(queue &&other) {
    container_ = std::move(other.container_);
    return *this;
  }

  const_reference front() { return *--container_.cend(); }
  const_reference back() { return *container_.cbegin(); }

  void push(const_reference value) { container_.push_front(value); }
  void pop() { container_.pop_back(); }
  void swap(queue &other) { container_.swap(other.container_); }

  size_type size() { return container_.size(); }
  bool empty() { return container_.empty(); }
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    container_.insert_many_front(std::forward<Args>(args)...);
  }

 private:
  container_type container_;
};

}  // namespace s21
#endif  // S21_QUEUE_H_