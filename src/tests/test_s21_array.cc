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
  s21::array<double, 4> d = std::move(c);
  for (auto elem : count) EXPECT_DOUBLE_EQ(b[elem], d[elem]);
}

TEST(Constructors, move_constructor) {
  int count[4]{0, 1, 2, 3};
  array<double, 4> a{1., 2., 3., 4.};
  array<double, 4> b = std::move(a);
  std::array<double, 4> c{1., 2., 3., 4.};
  std::array<double, 4> d = std::move(c);
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
  ASSERT_THROW(b[1] = 2, std::out_of_range);
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

// TEST(Element_Access, data) {
//   s21::array<char, 1> b{15};
//   EXPECT_EQ(b.data().get_ptr(), b.begin().get_ptr());
// }

// TEST(Array_Capacity, emty) {
//   s21::array<std::string, 0> b;
//   EXPECT_TRUE(b.empty());
// }

TEST(Array_Capacity, size) {
  array<string, 10> b;
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

TEST(Array_Modifiers, fill) {
  int count[3]{0, 1, 2};
  s21::array<string, 3> a;
  s21::array<string, 3> b{"number_1", "number_1", "number_1"};
  a.fill("number_1");
  for (auto elem : count) {
    EXPECT_EQ(a[elem], b[elem]);
    std::cout << elem << ' ';
  }
}
