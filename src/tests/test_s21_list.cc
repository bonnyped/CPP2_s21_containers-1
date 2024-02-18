#include <list>

#include "s21_test_containers.h"

TEST(LIST_FUNCTIONS, test_1) {
  std::list<std::string> a;
  s21::list<std::string> b;
  EXPECT_EQ(a.size(), b.size());
}

TEST(LIST_FUNCTIONS, test_2) {
  s21::list<std::string> b(0);
  EXPECT_EQ(b.size(), 0);
}

TEST(LIST_FUNCTIONS, test_3) {
  std::list<std::string> a{"number_1", "number_2", "number_3"};
  s21::list<std::string> b{"number_1", "number_2", "number_3"};
  int count[3]{0, 1, 2};
  auto a_it = a.begin();
  auto b_it = b.begin();
  for (auto elem : count) EXPECT_EQ(*a_it++, *b_it++);
}

TEST(LIST_FUNCTIONS, test_4) {
  s21::list<std::string> a{"number_1", "number_2", "number_3"};
  s21::list<std::string> b = s21::list<std::string>(a);
  int count[3]{0, 1, 2};
  auto a_it = a.begin();
  auto b_it = b.begin();
  for (auto elem : count) EXPECT_EQ(*a_it++, *b_it++);
}

TEST(LIST_FUNCTIONS, test_5) {
  s21::list<std::string> a{"number_1", "number_2", "number_3"};
  s21::list<std::string> b{"number_1", "number_2", "number_3"};
  s21::list<std::string> c(std::move(a));
  int count[3]{0, 1, 2};
  auto c_it = c.begin();
  auto b_it = b.begin();
  for (auto elem : count) EXPECT_EQ(*c_it++, *b_it++);
}

TEST(LIST_FUNCTIONS, test_6) {
  s21::list<std::string> a{"number_1", "number_2", "number_3"};
  s21::list<std::string> b{"number_1", "number_2", "number_3"};
  s21::list<std::string> c;
  c = std::move(a);
  int count[3]{0, 1, 2};
  auto c_it = c.begin();
  auto b_it = b.begin();
  for (auto elem : count) EXPECT_EQ(*c_it++, *b_it++);
}

TEST(LIST_ELEMENT_ACCESS, test_7) {
  s21::list<std::string> a{"number_1", "number_2", "number_3"};
  EXPECT_EQ(a.front(), *a.begin());
  EXPECT_EQ(a.back(), *(--a.end()));
}

TEST(List_Capacity, test_8) {
  s21::list<std::string> a;
  s21::list<std::string> b{"number_1"};
  EXPECT_EQ(a.empty(), true);
  EXPECT_NE(b.empty(), true);
}

TEST(List_Capacity, test_9) {
  std::list<std::string> a{"number_1"};
  s21::list<std::string> b{"number_1"};
  EXPECT_EQ(a.size(), b.size());
  EXPECT_TRUE(a.max_size() <= b.max_size());
}

TEST(LIST_MODIFIERS, test_10) {
  std::list<std::string> a{"number_1"};
  s21::list<std::string> b{"number_1"};
  a.clear();
  b.clear();
  EXPECT_EQ(a.size(), b.size());
}

TEST(LIST_MODIFIERS, test_11) {
  std::list<std::string> a{"number_1", "number_3"};
  s21::list<std::string> b{"number_1", "number_3"};
  auto a_it = ++a.begin();
  auto b_it = ++b.begin();
  a.insert(a_it, "number_2");
  b.insert(b_it, "number_2");
  EXPECT_EQ(*a_it, *b_it);
  EXPECT_EQ(*--a_it, *--b_it);
  EXPECT_EQ(*--a_it, *--b_it);
}

TEST(LIST_MODIFIERS, test_12) {
  std::list<std::string> a{"number_1", "number_3"};
  s21::list<std::string> b{"number_1", "number_3"};
  a.erase(a.begin());
  b.erase(b.begin());
  EXPECT_EQ(*a.begin(), *b.begin());
  a.erase(a.begin());
  b.erase(b.begin());
  EXPECT_EQ(a.size(), b.size());
}

TEST(LIST_MODIFIERS, test_13) {
  std::list<std::string> a{"number_1", "number_3"};
  s21::list<std::string> b{"number_1", "number_3"};
  a.push_back("number_4");
  b.push_back("number_4");
  EXPECT_EQ(a.back(), b.back());
  a.pop_back();
  b.pop_back();
  EXPECT_EQ(a.back(), b.back());
  a.push_front("number_0");
  b.push_front("number_0");
  EXPECT_EQ(a.back(), b.back());
  a.pop_front();
  b.pop_front();
  EXPECT_EQ(a.back(), b.back());
}

TEST(LIST_MODIFIERS, test_14) {
  s21::list<std::string> a{"number_1", "number_2", "number_3"};
  s21::list<std::string> b{"number_1", "number_2", "number_3"};
  s21::list<std::string> c;
  c.swap(a);
  auto b_it = b.begin();
  for (auto elem : c) EXPECT_EQ(elem, *b_it++);
  EXPECT_EQ(a.size(), 0);
}

TEST(LIST_MODIFIERS, test_15) {
  std::list<std::string> a{"number_2", "number_3", "number_1"};
  std::list<std::string> b{"number_5", "number_6", "number_4"};
  a.merge(b);
  s21::list<std::string> c{"number_2", "number_3", "number_1"};
  s21::list<std::string> d{"number_5", "number_6", "number_4"};
  c.merge(d);
  auto a_it = a.begin();
  for (auto elem : c) EXPECT_EQ(elem, *a_it++);
}

TEST(LIST_MODIFIERS, test_16) {
  std::list<std::string> a{"number_2", "number_3", "number_1"};
  std::list<std::string> b{"number_5", "number_6", "number_4"};
  a.splice(++a.begin(), b);  // тут нет конст
  s21::list<std::string> c{"number_2", "number_3", "number_1"};
  s21::list<std::string> d{"number_5", "number_6", "number_4"};
  c.splice(++c.cbegin(), d);  // тут должен быть конст?
  auto c_it = c.begin();
  for (auto elem : a) EXPECT_EQ(elem, *c_it++);
}

TEST(LIST_MODIFIERS, test_17) {
  std::list<std::string> a{"number_2", "number_3", "number_1"};
  s21::list<std::string> b{"number_2", "number_3", "number_1"};
  a.reverse();
  b.reverse();
  auto b_it = b.begin();
  for (auto elem : a) EXPECT_EQ(elem, *b_it++);
}

TEST(LIST_PUBLIC, test_18) {
  s21::list<std::string> a(30);
  EXPECT_EQ(a.size(), 30U);
}

TEST(LIST_PUBLIC, test_19) {
  s21::list<std::string> a{
      "hello", "hi", "Hello", "Hi",
      "asasaasasasasasasasasasasasasasasasasasasassaasssssssssssiiiiin"};
  EXPECT_TRUE(a.size() == 5U);
  s21::list<std::string> b;
  b = a;
  EXPECT_EQ(*--a.end(), *--b.end());
  EXPECT_EQ(b.size(), 5U);
}

TEST(LIST_PUBLIC, test_20) {
  s21::list<std::string> a{
      "hello", "hi", "Hello", "Hi",
      "asasaasasasasasasasasasasasasasasasasasasassaasssssssssssiiiiin"};
  EXPECT_TRUE(a.size() == 5U);
  s21::list<std::string> b;
  b = a;
  EXPECT_EQ(*--a.end(), *--b.end());
  EXPECT_EQ(b.size(), 5U);
}

TEST(LIST_PUBLIC, test_21) {
  s21::list<std::string> a{
      "hello", "hi", "Hello", "Hi",
      "asasaasasasasasasasasasasasasasasasasasasassaasssssssssssiiiiin"};
  EXPECT_TRUE(a.size() == 5U);
  s21::list<std::string> b{
      "aaaaaaaaaaaaaaayyyyyyyyyyy", "bbbbbbbbbbbbbbbbbbyyyyyyyyyyyyyy",
      "ttttttttttttttttttttyyyyyyyyyyyyyyyyy",
      "sssssssssssssssssssyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy"};
  EXPECT_EQ(b.size(), 4U);
  a.merge(b);
  EXPECT_EQ(b.size(), 0U);
  EXPECT_EQ(a.size(), 9U);
}

TEST(LIST_PUBLIC, test_22) {
  s21::list<std::string> a{"Hi", "hi", "hi", "hi", "hi", "hi"};
  EXPECT_TRUE(a.size() == 6U);
  a.unique();
  EXPECT_EQ(a.size(), 2U);
}

TEST(LIST_PUBLIC, test_23) {
  s21::list<std::string> a{"Hi"};
  EXPECT_TRUE(a.size() == 1U);
  a.unique();
  EXPECT_EQ(a.size(), 1U);
}
TEST(LIST_PUBLIC, test_24) {
  s21::list<std::string> a{};
  EXPECT_TRUE(a.size() == 0U);
  a.unique();
  EXPECT_EQ(a.size(), 0U);
}

TEST(LIST_PUBLIC, test_25) {
  s21::list<char> a{'x', 'e', 'y', 'g', 't', 'a', 's', 'x', 'f'};
  std::list<char> b{'x', 'e', 'y', 'g', 't', 'a', 's', 'x', 'f'};
  EXPECT_TRUE(a.size() == 9U);
  a.sort();
  b.sort();
  auto j = --b.cend();
  for (auto i = --a.cend(); i != a.cend() && j != b.cend(); --i, --j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(LIST_PUBLIC, test_26) {
  s21::list<int> a;
  std::list<int> b;
  for (int i = 400; i >= -400; --i) {
    a.push_front(-i);
    a.push_back(i);
    b.push_front(-i);
    b.push_back(i);
  }
  auto it = ++a.begin();
  EXPECT_EQ(*it, 399);
  EXPECT_TRUE(a.size() == 1602U);
  a.sort();
  b.sort();
  auto j = --b.cend();
  for (auto i = --a.cend(); i != a.cend() && j != b.cend(); i--, j--) {
    EXPECT_EQ(*i, *j);
  }
  EXPECT_EQ(*it, 399);
}

TEST(LIST_PUBLIC, test_27) {
  s21::list<int> a{1, 2, 3};
  EXPECT_EQ(*a.insert_many(++a.cbegin(), 6, 7, 8, 9), 6);
}

TEST(LIST_PUBLIC, test_28) {
  s21::list<int> a{};
  EXPECT_EQ(*a.insert_many(++a.cbegin(), 6, 7, 8, 9), 6);
}

TEST(LIST_PUBLIC, test_29) {
  s21::list<int> a{1, 2, 3};
  auto it = a.insert_many(a.cend(), 6, 7, 8, 9);
  EXPECT_EQ(*it, 6);
  EXPECT_EQ(*--it, 3);
}

TEST(LIST_PUBLIC, test_30) {
  s21::list<int> a{1, 2, 3};
  a.insert_many_back(6, 7, 8, 9);
  EXPECT_EQ(*--a.end(), 9);
}

TEST(LIST_PUBLIC, test_31) {
  s21::list<int> a{};
  a.insert_many_back(6, 7, 8, 9);
  EXPECT_EQ(*--a.end(), 9);
  EXPECT_EQ(*a.begin(), 6);
}

TEST(LIST_PUBLIC, test_32) {
  s21::list<int> a{1, 2, 3};
  a.insert_many_front(6, 7, 8, 9);
  EXPECT_EQ(*--a.end(), 3);
  EXPECT_EQ(*a.begin(), 9);
  EXPECT_EQ(*++a.begin(), 8);
}

TEST(LIST_PUBLIC, test_33) {
  s21::list<int> a{};
  a.insert_many_front(6, 7, 8, 9);
  EXPECT_EQ(*--a.end(), 6);
  EXPECT_EQ(*a.begin(), 9);
}