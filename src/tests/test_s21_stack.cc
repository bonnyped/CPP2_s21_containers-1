#include <stack>

#include "s21_test_containers.h"

TEST(S21_STACK, s21_default_constructor_test_1) {
  s21::stack<int> a;
  EXPECT_EQ(a.size(), 0U);
  EXPECT_TRUE(a.empty());
}

TEST(S21_STACK, s21_init_list_constructor_test_2) {
  s21::stack<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_EQ(a.size(), 9U);
}

TEST(S21_STACK, s21_move_constructor_test_3) {
  s21::stack<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_EQ(a.size(), 9U);
  s21::stack<int> b(std::move(a));
  EXPECT_EQ(a.size(), 0U);
  EXPECT_EQ(b.size(), 9U);
}

TEST(S21_STACK, s21_copy_constructor_test_4) {
  s21::stack<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_EQ(a.size(), 9U);
  s21::stack<int> b(a);
  EXPECT_EQ(a.size(), 9U);
  EXPECT_EQ(b.size(), 9U);
}

TEST(S21_STACK, s21_move_operator_eq_test_5) {
  s21::stack<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_EQ(a.size(), 9U);
  s21::stack<int> b;
  b = std::move(a);
  EXPECT_EQ(a.size(), 0U);
  EXPECT_EQ(b.size(), 9U);
}

TEST(S21_STACK, s21_copy_operator_eq_test_6) {
  s21::stack<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_EQ(a.size(), 9U);
  s21::stack<int> b;
  b = a;
  EXPECT_EQ(a.size(), 9U);
  EXPECT_EQ(b.size(), 9U);
}

TEST(S21_STACK, s21_top_test_7) {
  s21::stack<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_FALSE(a.empty());
  EXPECT_EQ(a.top(), 9);
}

TEST(S21_STACK, s21_push_test_8) {
  s21::stack<int> a;  //{1,2,3,4,5,6,7,8,9};
  a.push(1);
  a.push(2);
  a.push(3);
  a.push(4);
  a.push(5);
  a.push(6);
  a.push(7);
  a.push(8);
  a.push(9);
  EXPECT_FALSE(a.empty());
  EXPECT_EQ(a.top(), 9);
}

TEST(S21_STACK, s21_push_test_9) {
  s21::stack<int> a;  //{1,2,3,4,5,6,7,8,9};
  a.push(3);
  a.push(4);
  a.push(5);
  a.push(6);
  a.push(7);
  a.push(8);
  a.push(9);
  a.push(1);
  a.push(2);
  EXPECT_FALSE(a.empty());
  EXPECT_EQ(a.top(), 2);
}

TEST(S21_STACK, s21_swap_test_7) {
  s21::stack<int> a;
  a.push(3);
  a.push(4);
  a.push(5);
  a.push(6);
  a.push(7);
  a.push(8);
  a.push(9);
  a.push(1);
  a.push(2);
  EXPECT_FALSE(a.empty());
  EXPECT_EQ(a.top(), 2);
  s21::stack<int> b;
  b.push(777);
  a.swap(b);
  EXPECT_EQ(a.top(), 777);
  EXPECT_EQ(b.top(), 2);
  EXPECT_EQ(a.size(), 1U);
  EXPECT_EQ(b.size(), 9U);
}

TEST(S21_STACK, s21_pop_test_10) {
  s21::stack<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_FALSE(a.empty());
  EXPECT_EQ(a.top(), 9);
  a.pop();
  EXPECT_EQ(a.top(), 8);
  a.pop();
  EXPECT_EQ(a.top(), 7);
  a.pop();
  EXPECT_EQ(a.top(), 6);
  a.pop();
  EXPECT_EQ(a.top(), 5);
  a.pop();
  EXPECT_EQ(a.top(), 4);
  a.pop();
  EXPECT_EQ(a.top(), 3);
  a.pop();
  EXPECT_EQ(a.top(), 2);
  a.pop();
  EXPECT_EQ(a.top(), 1);
  a.pop();
  EXPECT_TRUE(a.empty());
}

TEST(S21_STACK, s21_empty_test_11) {
  s21::stack<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_FALSE(a.empty());
}

TEST(S21_STACK, s21_insert_many_front_test_12) {
  s21::stack<char> a{'a', 'b', 'c', 'd', 'e', '6', '7', '8', '9'};
  EXPECT_FALSE(a.empty());
  a.insert_many_front('s', '2', '1');
  EXPECT_EQ(a.top(), '1');
}

TEST(S21_STACK, s21_insert_many_front_test_13) {
  s21::stack<char> a{'a', 'b', 'c', 'd', 'e', '6', '7', '8', '9'};
  EXPECT_FALSE(a.empty());
  a.insert_many_front('1', '2', 's');
  EXPECT_EQ(a.top(), 's');
}

TEST(S21_STACK, PushPop_14) {
  s21::stack<int> a;
  std::stack<int> b;
  for (int i = 0; i < 1000; i++) {
    a.push(i);
    b.push(i);
  }

  for (int i = 1000 - 1; i >= 0; i--) {
    ASSERT_EQ(a.top(), b.top());
    a.pop();
    b.pop();
  }
}
