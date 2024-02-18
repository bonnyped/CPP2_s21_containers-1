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
  //           vector_b.max_size());  // тест зависимый от платформы и ахитектуры
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
