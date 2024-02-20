#include "s21_test_containers.h"

TEST(S21_VECTOR, s21_not_default_constructor_test_0) {
  s21::vector<NotDefaultConstructor> vector;
  EXPECT_EQ(vector.size(), 0U);
  EXPECT_TRUE(vector.empty());
}

TEST(S21_VECTOR, s21_default_constructor_test_1) {
  s21::vector<int> vector;
  EXPECT_EQ(vector.size(), 0U);
  EXPECT_TRUE(vector.empty());
}

TEST(S21_VECTOR, s21_copy_constructor_test_2) {
  s21::vector<int> vector_a;
  EXPECT_EQ(vector_a.size(), 0U);
  EXPECT_TRUE(vector_a.empty());
  vector_a.push_back(999);
  vector_a.push_back(888);
  vector_a.push_back(777);
  s21::vector<int> vector_b(vector_a);
  EXPECT_EQ(vector_a.size(), 3U);
  EXPECT_EQ(vector_b.size(), 3U);
}

TEST(S21_VECTOR, s21_operator_move_copy_test) {
  s21::vector<int> vector_a;
  EXPECT_EQ(vector_a.size(), 0U);
  EXPECT_TRUE(vector_a.empty());
  vector_a.push_back(999);
  vector_a.push_back(888);
  vector_a.push_back(777);
  vector_a = std::move(vector_a);
  vector_a = vector_a;
  EXPECT_EQ(vector_a.size(), 3U);
}

TEST(S21_VECTOR, s21_operator_eq_copy_test_4) {
  s21::vector<int> vector_a;
  EXPECT_EQ(vector_a.size(), 0U);
  EXPECT_TRUE(vector_a.empty());
  vector_a.push_back(999);
  vector_a.push_back(888);
  vector_a.push_back(777);
  s21::vector<int> vector_b;
  vector_b = vector_a;
  EXPECT_EQ(vector_a.size(), 3U);
  EXPECT_EQ(vector_b.size(), 3U);
}

TEST(S21_VECTOR, s21_move_constructor_test_3) {
  s21::vector<int> vector_a;
  EXPECT_EQ(vector_a.size(), 0U);
  EXPECT_TRUE(vector_a.empty());
  vector_a.push_back(999);
  vector_a.push_back(888);
  vector_a.push_back(777);
  s21::vector<int> vector_b(std::move(vector_a));
  EXPECT_EQ(vector_a.size(), 0U);
  EXPECT_EQ(vector_b.size(), 3U);
}

TEST(S21_VECTOR, s21_copy_operator_eq_test_4) {
  s21::vector<int> vector_a;
  EXPECT_EQ(vector_a.size(), 0U);
  EXPECT_TRUE(vector_a.empty());
  vector_a.push_back(999);
  vector_a.push_back(888);
  vector_a.push_back(777);
  s21::vector<int> vector_b = vector_a;
  EXPECT_EQ(vector_a.size(), 3U);
  EXPECT_EQ(vector_b.size(), 3U);
}

TEST(S21_VECTOR, s21_move_operator_eq_test_5) {
  s21::vector<int> vector_a;
  EXPECT_EQ(vector_a.size(), 0U);
  EXPECT_TRUE(vector_a.empty());
  vector_a.push_back(999);
  vector_a.push_back(888);
  vector_a.push_back(777);
  s21::vector<int> vector_b = std::move(vector_a);
  EXPECT_EQ(vector_a.size(), 0U);
  EXPECT_EQ(vector_b.size(), 3U);
}

TEST(S21_VECTOR, s21_insert_test_6) {
  s21::vector<int> vector_a;
  EXPECT_EQ(vector_a.size(), 0U);
  EXPECT_TRUE(vector_a.empty());
  vector_a.push_back(999);
  vector_a.push_back(888);
  vector_a.push_back(777);
  vector_a.insert(++vector_a.begin(), -444);
  EXPECT_EQ(vector_a.size(), 4U);
  EXPECT_EQ(*++vector_a.begin(), -444);
  vector_a.insert(++vector_a.begin(), -333);
  EXPECT_EQ(vector_a.size(), 5U);
  EXPECT_EQ(*++vector_a.begin(), -333);
  vector_a.insert(vector_a.end(), -1000);
  EXPECT_EQ(vector_a.size(), 6U);
  EXPECT_EQ(*--vector_a.end(), -1000);
}

TEST(S21_VECTOR, s21_insert_string_test_7) {
  s21::vector<std::string> vector_a;
  EXPECT_EQ(vector_a.size(), 0U);
  EXPECT_TRUE(vector_a.empty());
  vector_a.push_back("999");
  vector_a.push_back("888");
  vector_a.push_back("777");
  vector_a.insert(++vector_a.begin(), "-444");
  EXPECT_EQ(vector_a.size(), 4U);
  EXPECT_EQ(*++vector_a.begin(), "-444");
  vector_a.insert(++vector_a.begin(), "-333");
  EXPECT_EQ(vector_a.size(), 5U);
  EXPECT_EQ(*++vector_a.begin(), "-333");
  vector_a.insert(vector_a.end(), "-1000");
  EXPECT_EQ(vector_a.size(), 6U);
  EXPECT_EQ(*--vector_a.end(), "-1000");
}

TEST(S21_VECTOR, s21_insert_double_test_8) {
  s21::vector<double> vector_a;
  EXPECT_EQ(vector_a.size(), 0U);
  EXPECT_TRUE(vector_a.empty());
  vector_a.push_back(999.);
  vector_a.push_back(888.);
  vector_a.push_back(777.);
  vector_a.insert(++vector_a.begin(), -444.);
  EXPECT_EQ(vector_a.size(), 4U);
  EXPECT_EQ(*++vector_a.begin(), -444.);
  vector_a.insert(++vector_a.begin(), -333.);
  EXPECT_EQ(vector_a.size(), 5U);
  EXPECT_EQ(*++vector_a.begin(), -333.);
  vector_a.insert(vector_a.end(), -1000.);
  EXPECT_EQ(vector_a.size(), 6U);
  EXPECT_EQ(*--vector_a.end(), -1000.);
}

TEST(S21_VECTOR, s21_insert_double_test_9) {
  s21::vector<double> vector_a;
  EXPECT_EQ(vector_a.size(), 0U);
  EXPECT_TRUE(vector_a.empty());
  vector_a.push_back(999.);
  vector_a.push_back(888.);
  vector_a.push_back(777.);
  vector_a.insert(++vector_a.begin(), -444.);
  EXPECT_EQ(vector_a.size(), 4U);
  EXPECT_EQ(*++vector_a.begin(), -444.);
  vector_a.insert(++vector_a.begin(), -333.);
  EXPECT_EQ(vector_a.size(), 5U);
  EXPECT_EQ(*++vector_a.begin(), -333.);
  vector_a.insert(vector_a.end(), -1000.);
  EXPECT_EQ(vector_a.size(), 6U);
  EXPECT_EQ(*--vector_a.end(), -1000.);
}

TEST(S21_VECTOR, s21_pop_back_test_10) {
  s21::vector<int> vector_a{1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_EQ(vector_a.size(), 9U);
  EXPECT_TRUE(!vector_a.empty());
  vector_a.push_back(999);
  vector_a.push_back(888);
  vector_a.push_back(777);
  EXPECT_EQ(*--vector_a.end(), 777);
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), 888);
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), 999);
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), 9);
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), 8);
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), 7);
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), 6);
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), 5);
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), 4);
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), 3);
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), 2);
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), 1);
  vector_a.pop_back();
  EXPECT_TRUE(vector_a.empty());
}

TEST(S21_VECTOR, s21_pop_back_string_test_11) {
  s21::vector<std::string> vector_a{"1", "2", "3", "4", "5",
                                    "6", "7", "8", "9"};
  EXPECT_EQ(vector_a.size(), 9U);
  EXPECT_TRUE(!vector_a.empty());
  vector_a.push_back("999");
  vector_a.push_back("888");
  vector_a.push_back("777");
  EXPECT_EQ(*--vector_a.end(), "777");
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), "888");
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), "999");
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), "9");
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), "8");
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), "7");
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), "6");
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), "5");
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), "4");
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), "3");
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), "2");
  vector_a.pop_back();
  EXPECT_EQ(*--vector_a.end(), "1");
  vector_a.pop_back();
  EXPECT_TRUE(vector_a.empty());
}

TEST(S21_VECTOR, s21_erase_string_test_12) {
  s21::vector<std::string> vector_a{"1", "2", "3", "4", "5",
                                    "6", "7", "8", "9"};
  EXPECT_EQ(vector_a.size(), 9U);
  EXPECT_TRUE(!vector_a.empty());
  vector_a.push_back("999");
  vector_a.push_back("888");
  vector_a.push_back("777");
  EXPECT_EQ(vector_a.size(), 12U);
  EXPECT_EQ(*vector_a.begin(), "1");
  vector_a.erase(vector_a.begin());
  EXPECT_EQ(*vector_a.begin(), "2");
  EXPECT_EQ(vector_a.size(), 11U);
  EXPECT_EQ(*++vector_a.begin(), "3");
  EXPECT_EQ(*(vector_a.begin()++), "2");
  vector_a.erase(++vector_a.begin());
  EXPECT_EQ(*++vector_a.begin(), "4");
  EXPECT_EQ(vector_a.size(), 10U);
  EXPECT_EQ(*vector_a.begin(), "2");
  EXPECT_EQ(*(vector_a.begin()++), "2");
  vector_a.erase(vector_a.begin());
  EXPECT_EQ(*vector_a.begin(), "4");
  EXPECT_EQ(vector_a.size(), 9U);
  EXPECT_EQ(*--vector_a.end(), "777");
  vector_a.erase(--vector_a.end());
  EXPECT_EQ(*--vector_a.end(), "888");
  EXPECT_EQ(vector_a.size(), 8U);
  EXPECT_EQ(*(vector_a.end() - 1), "888");
  vector_a.erase(--vector_a.end());
  EXPECT_EQ(*(vector_a.end() - 1), "999");
  EXPECT_EQ(vector_a.size(), 7U);
  vector_a.clear();
  EXPECT_EQ(vector_a.size(), 0U);
}

TEST(S21_VECTOR, s21_at_test_13) {
  s21::vector<std::string> vector_a{"1", "2", "3", "4", "5",
                                    "6", "7", "8", "9"};
  std::vector<std::string> vector_b{"1", "2", "3", "4", "5",
                                    "6", "7", "8", "9"};
  // EXPECT_EQ(vector_a.max_size(),
  //           vector_b.max_size());  // тест зависимый от платформы и
  //           ахитектуры
  EXPECT_EQ(vector_a.at(4U), "5");
  EXPECT_THROW(vector_a.at(10U), std::out_of_range);
  EXPECT_EQ(vector_b.at(4U), "5");
  EXPECT_THROW(vector_b.at(10U), std::out_of_range);
}

TEST(S21_VECTOR, s21_max_size_test_14) {
  s21::vector<std::size_t> vector_a{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  size_t max_size = vector_a.max_size();
  vector_a.push_back(max_size);
  EXPECT_EQ(*--vector_a.end(), max_size);
}

TEST(S21_VECTOR, s21_constructor_test_15) {
  s21::vector<std::string> vector_a{1000, "Hello!"};
  EXPECT_EQ(*--vector_a.end(), "Hello!");
  EXPECT_EQ(*vector_a.begin(), "Hello!");
  EXPECT_EQ(vector_a.size(), 1000U);
}

TEST(S21_VECTOR, s21_not_default_constructor_test_16) {
  s21::vector<int> vector_a;
  EXPECT_EQ(vector_a.size(), 0U);
  EXPECT_TRUE(vector_a.empty());
}

TEST(S21_VECTOR, reserve_test_17) {
  s21::vector<std::string> vector_a{"number_1", "number_2", "number_3"};
  std::size_t size__ = vector_a.size();
  vector_a.reserve(101);
  EXPECT_EQ(size__, vector_a.size());
  EXPECT_EQ(vector_a.capacity(), 202);
  vector_a.shrink_to_fit();
  EXPECT_EQ(vector_a.capacity(), size__);
  EXPECT_EQ(size__, vector_a.size());
}

TEST(S21_VECTOR, iter_test_18) {
  s21::vector<int> vector_a{};
  vector_a.push_back(9);
  vector_a.push_back(8);
  vector_a.push_back(7);
  vector_a.push_back(6);
  vector_a.push_back(5);
  vector_a.push_back(4);
  vector_a.push_back(3);
  vector_a.push_back(2);
  vector_a.push_back(1);
  vector_a.push_back(0);
  vector_a.push_back(-1);
  auto it = ++vector_a.begin();
  EXPECT_EQ(*it--, *++vector_a.begin());
  s21::vector<int> vector_b{};
  EXPECT_TRUE(vector_b.cbegin() == vector_b.cend());
  EXPECT_EQ((vector_a.end() - (++vector_a.begin())), 10U);
  EXPECT_EQ((vector_a.end() - (vector_a.begin())), 11U);
  EXPECT_EQ(vector_a.front(), 9);
  s21::vector<int> vector_c(100);
  EXPECT_TRUE(vector_c.cbegin() != vector_c.cend());
  // EXPECT_EQ(vector_a.capacity(), size__);
  // EXPECT_EQ(size__, vector_a.size());
}

TEST(S21_VECTOR, iter_test_19) {
  s21::vector<int> vector_a{};
  vector_a.push_back(9);
  vector_a.push_back(8);
  vector_a.push_back(7);
  vector_a.push_back(6);
  vector_a.push_back(5);
  vector_a.push_back(4);
  vector_a.push_back(3);
  vector_a.push_back(2);
  vector_a.push_back(1);
  vector_a.push_back(0);
  vector_a.push_back(-1);
  vector_a.swap(vector_a);
  EXPECT_EQ(vector_a.back(), -1);
}

TEST(S21_VECTOR, front_back_at_1) {
  std::vector<std::string> a;
  s21::vector<std::string> b;
  EXPECT_EQ(&a.front(), &b.front());
  EXPECT_EQ(&a.back(), &b.back());
  EXPECT_THROW(b.at(1), std::exception);
}

TEST(S21_VECTOR, data_1) {
  s21::vector<s21::array<std::string, 10>> a{};
  std::vector<std::array<std::string, 10>> b{};
  EXPECT_EQ(a.data()->size(), b.data()->size());
  EXPECT_EQ(a.data()->max_size(), b.data()->max_size());
}

TEST(S21_VECTOR, insert_many) {
  s21::vector<std::string> a;
  a.insert_many(a.cbegin(), "a", "b", "c");
  EXPECT_EQ(a[0], "a");
  EXPECT_EQ(a[1], "b");
  EXPECT_EQ(a[2], "c");
  a.insert_many(a.cbegin() + 2, "r", "t", "e");
  EXPECT_EQ(a[0], "a");
  EXPECT_EQ(a[1], "b");
  EXPECT_EQ(a[2], "r");
  a.insert_many(a.cend(), "1", "2", "3");
  EXPECT_EQ(a[6], "1");
  EXPECT_EQ(a[7], "2");
  EXPECT_EQ(a[8], "3");
}

TEST(S21_VECTOR, insert_many_18) {
  s21::vector<int> vector_a;
  vector_a.insert_many(vector_a.cbegin(), 1, 2, 3, 4, 5, 6, 7, 8, 9, 0);
  EXPECT_EQ(vector_a[0], 1);
}

TEST(S21_VECTOR, s21_constructor_test_19) {
  s21::vector<std::string> vector_a{"Hello!", "Hamlet!", "Hello!", "Hamlet"};
  s21::vector<std::string> vector_b(++vector_a.begin(), --vector_a.end());
  EXPECT_EQ(*vector_b.begin(), "Hamlet!");
  EXPECT_EQ(*--vector_b.end(), "Hello!");
  s21::vector<std::string> vector_c(vector_a.begin(), vector_a.end());
  for (std::size_t index = 0; index < vector_a.size(); ++index)
    EXPECT_EQ(vector_a[index], vector_c[index]);
  s21::vector<int> a;
  s21::vector<int> b(a.begin(), a.end());
  EXPECT_EQ(a.size(), b.size());
  EXPECT_TRUE(b.empty());
  for (int index = 0; index < 1000; ++index) a.push_back(index);
  for (int index = 0; index < 1000; ++index) {
    a.pop_back();
    a.shrink_to_fit();
  }
}