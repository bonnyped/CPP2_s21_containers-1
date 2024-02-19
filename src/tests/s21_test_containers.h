#ifndef SRC_TESTS_S21_TEST_CONTAINERS_H_
#define SRC_TESTS_S21_TEST_CONTAINERS_H_
#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "../s21_containers/s21_array.h"
#include "../s21_containers/s21_list.h"
#include "../s21_containers/s21_map.h"
#include "../s21_containers/s21_multiset.h"
#include "../s21_containers/s21_queue.h"
#include "../s21_containers/s21_rb_tree.h"
#include "../s21_containers/s21_set.h"
#include "../s21_containers/s21_stack.h"
#include "../s21_containers/s21_vector.h"

class NotDefaultConstructor {
 public:
  NotDefaultConstructor() = delete;
  NotDefaultConstructor(std::string x, std::string y, std::string z)
      : x_(x), y_(y), z_(z) {}
  void print() const { std::cout << x_ << ' ' << y_ << ' ' << z_ << '\n'; }
  bool operator<(const NotDefaultConstructor &other) const {
    return x_ < other.x_;
  }
  std::string sum() noexcept { return x_ + y_ + z_; }

 private:
  std::string x_;
  std::string y_;
  std::string z_;
};

#endif  //  SRC_TESTS_S21_TEST_CONTAINERS_H_
