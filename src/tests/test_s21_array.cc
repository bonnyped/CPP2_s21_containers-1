#include <array>

#include "s21_test_containers.h"
using namespace std;

TEST(Constructors, default_constuctor_1) {
  array<string, 10> a;
s21:
  array<string, 10> b;
  EXPECT_EQ(a, b);
}

TEST(Constructors, default_constuctor_2) {
  array<string, 10> a{};
s21:
  array<string, 10> b{};
  EXPECT_EQ(a, b);
}

TEST(Constructors, init_list_constructor_1) {
  int count[4]{0, 1, 2, 3};
  array<string, 4> a{"number_1", "number_2", "number_3"};
  s21::array<std::string, 4> b{"number_1", "number_2", "number_3"};
  for (auto elem : count) EXPECT_EQ(a[elem], b[elem]);
}

TEST(Constructors, init_list_constructor_2) {
  int count[4]{0, 1, 2, 3};
  array<string, 4> a{"number_1", "number_2", "number_3", " "};
  s21::array<string, 4> b{"number", "number"};
  for (auto elem : count) EXPECT_NE(a[elem], b[elem]);
}

TEST(Constructors, copy_constructor) {
  int count[4]{0, 1, 2, 3};
  array<double, 4> a{1.1233123112314, 2.12312312, 3.425363, 4.2335436};
  array<double, 4> b = a;
  s21::array<double, 4> c{1.1233123112314, 2.12312312, 3.425363, 4.2335436};
  s21::array<double, 4> d = c;
  for (auto elem : count) EXPECT_DOUBLE_EQ(b[elem], d[elem]);
}

TEST(Constructors, move_constructor) {
  int count[4]{0, 1, 2, 3};
  array<double, 4> a{1., 2., 3., 4.};
  array<double, 4> b = a;
  s21::array<double, 4> c{1., 2., 3., 4.};
  s21::array<double, 4> d = c;
  for (auto elem : count) EXPECT_EQ(b[elem], d[elem]);
}

TEST(Element_Access, at_1) {
  int count[3]{0, 1, 2};
  array<char, 3> a;
  s21::array<char, 3> b;
  a[0] = 11;
  a[1] = 22;
  a[2] = 33;
  b[0] = 11;
  b[1] = 22;
  b[2] = 33;
  for (auto elem : count) EXPECT_EQ(a[elem], b[elem]);
}

TEST(Element_Access, at_2) {
  s21::array<char, 1> b;
  ASSERT_THROW(b.at(1), std::out_of_range);
}

TEST(Element_Access, at_3) {
  s21::array<char, 1> b{15};
  EXPECT_EQ(b.at(0), 15);
}

TEST(Element_Access, squere_braces) {
  s21::array<char, 1> b{15};
  EXPECT_EQ(&b[0], b.arr_);
}

TEST(Element_Access, front) {
  s21::array<char, 1> b{15};
  EXPECT_EQ(&b.front(), b.arr_);
}

TEST(Element_Access, back_1) {
  s21::array<char, 1> b{15};
  EXPECT_EQ(&b.back(), b.arr_);
}

TEST(Element_Access, back_2) {
  s21::array<char, 3> b{15, 17, 17};
  EXPECT_EQ(&b.back(), &b.arr_[2]);
}

TEST(Element_Access, data) {
  s21::array<char, 1> b{15};
  EXPECT_EQ(b.data(), b.begin());
}

TEST(Array_Capacity, emty) {
  s21::array<int, 0> b;
  s21::array<NotDefaultConstructor, 0> const c{};
  auto it = b.begin();
  auto it2 = b.end();
  EXPECT_TRUE(it == it2);
  std::cout << sizeof(b) << '\n';
  std::cout << sizeof(c) << '\n';
  EXPECT_TRUE(b.empty());
  ASSERT_THROW(b.at(0), std::out_of_range);
  ASSERT_TRUE(c.begin() == c.end());
  ASSERT_THROW(b.front(), std::out_of_range);
  ASSERT_THROW(b.back(), std::out_of_range);
  ASSERT_TRUE(c.size() == 0U);
  for (auto elem : b) {
    std::cout << elem << ' ';
  }
  // b[0] = 12;
}

TEST(Array_Capacity, size) {
  s21::array<std::string, 10> b;
  EXPECT_TRUE(b.size() == 10);
}

TEST(Array_Capacity, max_size) {
  s21::array<string, 10> b;
  EXPECT_TRUE(b.max_size() == 10);
}

TEST(Array_Modifiers, swap) {
  int count[3]{0, 1, 2};
  s21::array<string, 3> a{"number_1", "number_2", "number_3"};
  s21::array<string, 3> b{"number_1", "number_2", "number_3"};
  s21::array<string, 3> c;
  c.swap(a);
  for (auto elem : count) EXPECT_EQ(b[elem], c[elem]);
}

TEST(Zero_Array, test_1) {
  array<string, 0> a;
  s21::array<string, 0> b;
  EXPECT_THROW(b.at(0), exception);
  EXPECT_EQ(a.begin(), b.begin());
  EXPECT_EQ(a.end(), b.end());
  EXPECT_EQ(a.cbegin(), b.cbegin());
  EXPECT_EQ(a.cend(), b.cend());
  EXPECT_THROW(b.front(), exception);
  EXPECT_THROW(b.back(), exception);
  EXPECT_EQ(a.data(), b.data());
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(a.max_size(), b.max_size());
  EXPECT_EQ(a.size(), b.size());
  s21::array<std::string, 0> c;
  b.swap(c);
  b.fill("ldv");
  s21::array<std::string, 0> const d;
  EXPECT_TRUE(d.begin() == d.end());
  EXPECT_THROW(c[9], exception);
}

TEST(ARRAY, test_list_init_exception_1) {
  try {
    s21::array<std::string, 4U> a{"1", "2", "3", "4", "5"};
  } catch (std::out_of_range& e) {
    ASSERT_STREQ("There are too many initializers!", e.what());
  }
}

TEST(ARRAY, test_move_constructor_1) {
  s21::array<std::string, 4U> a{"1", "2", "3", "4"};
  s21::array<std::string, 4U> b(std::move(a));
  EXPECT_EQ(a.size(), 4U);
  EXPECT_EQ(a[0], "");
  EXPECT_EQ(b.size(), 4U);
  EXPECT_EQ(b[0], "1");
  s21::array<std::string, 4U> c(std::move(b));
  EXPECT_EQ(b.size(), 4U);
  EXPECT_EQ(b[0], "");
  EXPECT_EQ(c.size(), 4U);
  EXPECT_EQ(c[0], "1");
}

TEST(ARRAY, test_operator_eq_move__1) {
  s21::array<std::string, 4U> a{"1", "2", "3", "4"};
  s21::array<std::string, 4U> b;
  b = std::move(a);
  EXPECT_EQ(a.size(), 4U);
  EXPECT_EQ(a[0], "");
  EXPECT_EQ(b.size(), 4U);
  EXPECT_EQ(b[0], "1");
  s21::array<std::string, 4U> c;
  c = (std::move(b));
  EXPECT_EQ(b.size(), 4U);
  EXPECT_EQ(b[0], "");
  EXPECT_EQ(c.size(), 4U);
  EXPECT_EQ(c[0], "1");
  EXPECT_TRUE(!b.empty());
}
