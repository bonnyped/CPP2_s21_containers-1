#include "s21_test_containers.h"

TEST(SET_CONSTRUCTOR, test_a_1) {
  s21::set<int> set_s21_int;
  s21::set<double> set_s21_double;
  s21::set<std::string> set_s21_string;

  EXPECT_EQ(set_s21_int.size(), 0U);
  EXPECT_EQ(set_s21_double.size(), 0U);
  EXPECT_EQ(set_s21_string.size(), 0U);
}

TEST(SET_CONSTRUCTOR, test_a_2) {
  s21::set<int> set_s21_int{1, 2, 3, 4, 5};
  s21::set<double> set_s21_double{1.30359, 2847.4925, 923.39281};
  s21::set<std::string> set_s21_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(set_s21_int.size(), 5U);
  EXPECT_EQ(set_s21_double.size(), 3U);
  EXPECT_EQ(set_s21_string.size(), 4U);
}

TEST(SET_CONSTRUCTOR, test_a_3) {
  s21::set<int> set_s21_ref_int{1, 2, 3, 4, 5};
  s21::set<int> set_s21_res_int{set_s21_ref_int};

  s21::set<double> set_s21_ref_double{1.30359, 2847.4925, 923.39281};
  s21::set<double> set_s21_res_double{set_s21_ref_double};

  s21::set<std::string> set_s21_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> set_s21_res_string{set_s21_ref_string};

  EXPECT_EQ(set_s21_ref_int.size(), set_s21_res_int.size());
  EXPECT_EQ(set_s21_ref_double.size(), set_s21_res_double.size());
  EXPECT_EQ(set_s21_ref_string.size(), set_s21_res_string.size());
}

TEST(SET_CONSTRUCTOR, test_a_4) {
  s21::set<int> set_s21_ref_int{1, 2, 3, 4, 5};
  s21::set<int> set_s21_res_int = std::move(set_s21_ref_int);

  s21::set<double> set_s21_ref_double{1.30359, 2847.4925, 923.39281};
  s21::set<double> set_s21_res_double = std::move(set_s21_ref_double);

  s21::set<std::string> set_s21_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> set_s21_res_string = std::move(set_s21_ref_string);

  EXPECT_EQ(set_s21_ref_int.size(), 0U);
  EXPECT_EQ(set_s21_res_int.size(), 5U);

  EXPECT_EQ(set_s21_ref_double.size(), 0U);
  EXPECT_EQ(set_s21_res_double.size(), 3U);

  EXPECT_EQ(set_s21_ref_string.size(), 0U);
  EXPECT_EQ(set_s21_res_string.size(), 4U);
}

TEST(SET_CONSTRUCTOR, test_a_5) {
  s21::set<int> set_s21_ref_int{1, 2, 3, 4, 5};
  s21::set<int> set_s21_res_int;
  set_s21_res_int = std::move(set_s21_ref_int);

  s21::set<double> set_s21_ref_double{1.30359, 2847.4925, 923.39281};
  s21::set<double> set_s21_res_double;
  set_s21_res_double = std::move(set_s21_ref_double);

  s21::set<std::string> set_s21_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> set_s21_res_string;
  set_s21_res_string = std::move(set_s21_ref_string);

  EXPECT_EQ(set_s21_ref_int.size(), 0U);
  EXPECT_EQ(set_s21_res_int.size(), 5U);

  EXPECT_EQ(set_s21_ref_double.size(), 0U);
  EXPECT_EQ(set_s21_res_double.size(), 3U);

  EXPECT_EQ(set_s21_ref_string.size(), 0U);
  EXPECT_EQ(set_s21_res_string.size(), 4U);
}

TEST(SET_CONSTRUCTOR, test_a_7) {
  s21::set<int> set_s21_ref_int{1, 2, 3, 4};
  s21::set<int> set_s21_res_int{set_s21_ref_int};

  s21::set<double> set_s21_ref_double{1.30359, 2847.4925, 923.39281, 1.23};
  s21::set<double> set_s21_res_double{set_s21_ref_double};

  s21::set<std::string> set_s21_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> set_s21_res_string{set_s21_ref_string};

  auto it_res_int = set_s21_res_int.begin();
  for (auto it_ref_int = set_s21_ref_int.begin();
       it_ref_int != set_s21_ref_int.end(); ++it_ref_int) {
    EXPECT_EQ(*it_res_int, *it_ref_int);
    it_res_int++;
  }

  auto it_res_double = set_s21_res_double.begin();
  for (auto it_ref_double = set_s21_ref_double.begin();
       it_ref_double != set_s21_ref_double.end(); ++it_ref_double) {
    EXPECT_EQ(*it_res_double, *it_ref_double);
    it_res_double++;
  }

  auto it_res_string = set_s21_res_string.begin();
  for (auto it_ref_string = set_s21_ref_string.begin();
       it_ref_string != set_s21_ref_string.end(); ++it_ref_string) {
    EXPECT_EQ(*it_res_string, *it_ref_string);
    it_res_string++;
  }
}

TEST(SET_INSERT, test_a_1) {
  s21::set<int> set_s21;

  std::pair<s21::set<int>::iterator, bool> insert1 = set_s21.insert(9);
  EXPECT_EQ(*insert1.first, 9);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<int>::iterator, bool> insert2 = set_s21.insert(9);
  std::pair<s21::set<int>::iterator, bool> insert3 = set_s21.insert(9);
  EXPECT_EQ(insert2.second, 0);
  EXPECT_EQ(insert3.second, false);

  std::pair<s21::set<int>::iterator, bool> insert4 = set_s21.insert(23);
  EXPECT_EQ(*insert4.first, 23);
  EXPECT_EQ(insert4.second, true);

  std::pair<s21::set<int>::iterator, bool> insert5 = set_s21.insert(98);
  EXPECT_EQ(*insert5.first, 98);
  EXPECT_EQ(insert5.second, true);

  EXPECT_EQ(set_s21.size(), 3U);
}

TEST(SET_INSERT, test_a_2) {
  s21::set<double> set_s21;

  std::pair<s21::set<double>::iterator, bool> insert1 = set_s21.insert(1.4);
  EXPECT_EQ(*insert1.first, 1.4);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<double>::iterator, bool> insert2 = set_s21.insert(2.77);
  EXPECT_EQ(*insert2.first, 2.77);
  EXPECT_EQ(insert2.second, true);

  std::pair<s21::set<double>::iterator, bool> insert3 = set_s21.insert(3.9);
  EXPECT_EQ(*insert3.first, 3.9);
  EXPECT_EQ(insert3.second, true);

  std::pair<s21::set<double>::iterator, bool> insert4 = set_s21.insert(2.77);
  std::pair<s21::set<double>::iterator, bool> insert5 = set_s21.insert(3.9);
  EXPECT_EQ(insert4.second, false);
  EXPECT_EQ(insert5.second, false);

  EXPECT_EQ(set_s21.size(), 3U);
}

TEST(SET_INSERT, test_a_3) {
  s21::set<std::string> set_s21;

  std::pair<s21::set<std::string>::iterator, bool> insert1 =
      set_s21.insert("hello");
  EXPECT_EQ(*insert1.first, "hello");
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert2 =
      set_s21.insert("hi");
  EXPECT_EQ(*insert2.first, "hi");
  EXPECT_EQ(insert2.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert3 =
      set_s21.insert("hi");
  EXPECT_EQ(insert3.second, false);

  std::pair<s21::set<std::string>::iterator, bool> insert4 =
      set_s21.insert("holli");
  EXPECT_EQ(*insert4.first, "holli");
  EXPECT_EQ(insert4.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert5 =
      set_s21.insert("hello");
  EXPECT_EQ(insert5.second, false);

  EXPECT_EQ(set_s21.size(), 3U);
}

TEST(SET_INSERT, test_a_4) {
  s21::set<int> set_s21;

  std::pair<s21::set<int>::iterator, bool> insert1 = set_s21.insert(9);
  EXPECT_EQ(*insert1.first, 9);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<int>::iterator, bool> insert2 = set_s21.insert(9);
  std::pair<s21::set<int>::iterator, bool> insert3 = set_s21.insert(9);
  EXPECT_EQ(insert2.second, false);
  EXPECT_EQ(insert3.second, false);

  EXPECT_EQ(set_s21.size(), 1U);
}

TEST(SET_INSERT, test_a_5) {
  s21::set<double> set_s21 = {21};

  std::pair<s21::set<double>::iterator, bool> insert1 = set_s21.insert(1.4);
  EXPECT_EQ(insert1.second, true);

  EXPECT_EQ(set_s21.size(), 2U);
}

TEST(SET_INSERT, test_a_6) {
  s21::set<std::string> set_s21 = {"hello"};

  std::pair<s21::set<std::string>::iterator, bool> insert1 =
      set_s21.insert("hi");
  EXPECT_EQ(*insert1.first, "hi");
  EXPECT_EQ(insert1.second, true);

  EXPECT_EQ(set_s21.size(), 2U);
}

TEST(SET_BEGIN, test_a_1) {
  s21::set<int> set_s21 = {9, 15, 7, 23, 2};

  EXPECT_EQ(*set_s21.begin(), 2);
}

TEST(SET_BEGIN, test_a_2) {
  s21::set<double> set_s21 = {11.4, 2.770001, 3.901, 2.77, 3.9};

  EXPECT_EQ(*set_s21.begin(), 2.77);
}

TEST(SET_BEGIN, test_a_3) {
  s21::set<std::string> set_s21 = {"hello", "hi", "hi-hi", "holli",
                                   "hello, hamlet"};

  EXPECT_EQ(*set_s21.begin(), "hello");
}

TEST(SET_BEGIN, test_a_5) {
  s21::set<double> set_s21 = {1.4, 1.4};

  EXPECT_EQ(*set_s21.begin(), 1.4);
}

TEST(SET_BEGIN, test_a_6) {
  s21::set<std::string> set_s21 = {"hello", "hello", "hello"};

  EXPECT_EQ(*set_s21.begin(), "hello");
}

TEST(SET_END, test_a_1) {
  s21::set<int> set_s21 = {9, 15, 7, 23, 2};

  EXPECT_EQ(*--set_s21.end(), 23);
}

TEST(SET_END, test_a_2) {
  s21::set<double> set_s21 = {11.4, 2.770001, 3.901, 11.400000001, 3.9};

  EXPECT_EQ(*--set_s21.end(), 11.400000001);
}

TEST(SET_END, test_a_3) {
  s21::set<std::string> set_s21 = {"hello", "hi", "holliwood", "holli",
                                   "hello, hamlet"};

  EXPECT_EQ(*--set_s21.end(), "holliwood");
}

TEST(SET_END, test_a_5) {
  s21::set<double> set_s21 = {1.4, 1.4};

  EXPECT_EQ(*--set_s21.end(), 1.4);
}

TEST(SET_END, test_a_6) {
  s21::set<std::string> set_s21 = {"hello", "hello", "hello"};

  EXPECT_EQ(*--set_s21.end(), "hello");
}

TEST(SET_BALANCE, test_a_1) {
  s21::set<int> set_s21 = {1, 15, 5};

  EXPECT_EQ(*--set_s21.end(), 15);
  EXPECT_EQ(set_s21.size(), 3U);
}

TEST(SET_BALANCE, test_a_2) {
  s21::set<double> set_s21 = {11.4, 2.770001, 3.901};

  EXPECT_EQ(*--set_s21.end(), 11.4);
  EXPECT_EQ(set_s21.size(), 3U);
}

TEST(SET_BALANCE, test_a_3) {
  s21::set<std::string> set_s21 = {"hello", "hi", "holliwood", "holli",
                                   "hello, hamlet"};

  EXPECT_EQ(*--set_s21.end(), "holliwood");
  EXPECT_EQ(set_s21.size(), 5U);
}

TEST(SET_BALANCE, test_a_4) {
  s21::set<int> set_s21 = {10, 5, 20, 30, 1543};

  EXPECT_EQ(*--set_s21.end(), 1543);
  EXPECT_EQ(*set_s21.begin(), 5);
  EXPECT_EQ(set_s21.size(), 5U);
}

TEST(SET_BALANCE, test_a_5) {
  s21::set<int> set_s21 = {30, 5, 43, 1, 20, 40, 60, 35, 32, 32, 35};

  EXPECT_EQ(*--set_s21.end(), 60);
  EXPECT_EQ(*set_s21.begin(), 1);
  EXPECT_EQ(set_s21.size(), 9U);
}

TEST(SET_ERASE, test_a_1) {
  std::set<int> set_s21 = {10, 5, 15, 4, 18, 13, 16};

  auto it = set_s21.begin();
  it++;
  it++;
  it++;
  it++;
  set_s21.erase(it);
  EXPECT_EQ(*set_s21.begin(), 4);
  EXPECT_EQ(*--set_s21.end(), 18);
  EXPECT_EQ(set_s21.size(), 6U);

  it = set_s21.begin();
  set_s21.erase(it);
  EXPECT_EQ(*set_s21.begin(), 5);
  EXPECT_EQ(*--set_s21.end(), 18);
  EXPECT_EQ(set_s21.size(), 5U);

  it = set_s21.begin();
  it++;
  set_s21.erase(it);
  EXPECT_EQ(*set_s21.begin(), 5);
  EXPECT_EQ(*--set_s21.end(), 18);
  EXPECT_EQ(set_s21.size(), 4U);

  it = --set_s21.end();
  set_s21.erase(it);
  EXPECT_EQ(*set_s21.begin(), 5);
  EXPECT_EQ(*--set_s21.end(), 16);
  EXPECT_EQ(set_s21.size(), 3U);

  it = set_s21.begin();
  it++;
  set_s21.erase(it);

  it = set_s21.begin();
  it++;
  set_s21.erase(it);

  it = set_s21.begin();
  set_s21.erase(it);

  EXPECT_EQ(set_s21.size(), 0U);
}

TEST(SET_ERASE, test_a_2) {
  s21::set<int> set_s21 = {30, 1543};

  auto it = set_s21.begin();
  ++it;
  set_s21.erase(it);
  it = set_s21.begin();
  set_s21.erase(it);

  EXPECT_EQ(set_s21.size(), 0U);
}

TEST(SET_ERASE, test_a_3) {
  s21::set<std::string> set_s21 = {"hello", "hi", "holliwood", "holli",
                                   "hello, hamlet"};

  auto it = --set_s21.end();
  set_s21.erase(it);
  EXPECT_EQ(*--set_s21.end(), "holli");
  EXPECT_EQ(set_s21.size(), 4U);

  it = --set_s21.end();
  set_s21.erase(it);
  EXPECT_EQ(*--set_s21.end(), "hi");
  EXPECT_EQ(set_s21.size(), 3U);

  set_s21.insert("holliwood");
  set_s21.insert("holli");
  it = --set_s21.end();
  set_s21.erase(it);
  EXPECT_EQ(*--set_s21.end(), "holli");
  EXPECT_EQ(set_s21.size(), 4U);
}

TEST(SET_ERASE, test_a_4) {
  s21::set<double> set_s21 = {22.2, 12.4457, 56.84, 941.44, 45.11};

  auto it = --set_s21.end();
  it--;
  set_s21.erase(it);
  it = --set_s21.end();
  EXPECT_EQ(*it, 941.44);
  EXPECT_EQ(set_s21.size(), 4U);

  it = set_s21.begin();
  ++it;
  ++it;
  ++it;
  set_s21.erase(it);
  it = set_s21.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*--set_s21.end(), 45.11);
  EXPECT_EQ(set_s21.size(), 3U);
}

TEST(SET_ERASE, test_a_5) {
  s21::set<double> set_s21 = {22.2, 45.11, 12.4457, 1.44};

  auto it = set_s21.begin();
  --it;
  --it;
  --it;
  set_s21.erase(it);
  it = set_s21.begin();
  ++it;
  ++it;
  EXPECT_EQ(*it, 45.11);
  EXPECT_EQ(set_s21.size(), 3U);
}

TEST(SET_ERASE, test_a_6) {
  s21::set<double> set_s21 = {22.2, 45.11, 12.4457, 6.84, 1.44};

  auto it = set_s21.begin();
  ++it;
  ++it;
  ++it;
  set_s21.erase(it);
  it = set_s21.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*it, 45.11);
  EXPECT_EQ(set_s21.size(), 4U);
}

TEST(SET_ERASE, test_a_7) {
  s21::set<double> set_s21 = {22.2, 12.4457, 56.84, 941.44, 45.11};

  auto it = set_s21.begin();
  ++it;
  set_s21.erase(it);
  it = set_s21.begin();
  ++it;
  EXPECT_EQ(*it, 45.11);
  EXPECT_EQ(set_s21.size(), 4U);
}

TEST(SET_ERASE, test_a_8) {
  s21::set<double> set_s21 = {22.2, 45.11, 12.4457, 1.44};

  auto it = set_s21.begin();
  ++it;
  set_s21.erase(it);
  it = set_s21.begin();
  ++it;
  EXPECT_EQ(*it, 22.2);
  EXPECT_EQ(set_s21.size(), 3U);
}

TEST(SET_ERASE, test_a_9) {
  s21::set<double> set_s21 = {22.2,  45.11, 12.4457, 32.45,
                              65.12, 66.32, 40.54,   6.4};

  auto it = --set_s21.end();
  --it;
  --it;
  --it;
  --it;
  set_s21.erase(it);
  it = set_s21.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*it, 40.54);
  EXPECT_EQ(set_s21.size(), 7U);
}

TEST(SET_ERASE, test_a_10) {
  s21::set<double> set_s21 = {22.2};

  auto it = --set_s21.end();
  --it;
  ++it;
  set_s21.erase(it);
  EXPECT_EQ(set_s21.size(), 0U);
}

TEST(SET_EMPTY, test_a_1) {
  s21::set<double> set_s21 = {22.2, 45.11, 12.4457, 1.44};

  EXPECT_EQ(set_s21.empty(), 0);
}

TEST(SET_EMPTY, test_a_2) {
  s21::set<double> set_s21;

  EXPECT_EQ(set_s21.empty(), 1);
}

TEST(SET_SWAP, test_a_1) {
  s21::set<double> set_s21_ref = {22.2, 45.11};
  s21::set<double> set_s21_res = {12.4457, 1.44, 22.2};

  set_s21_ref.swap(set_s21_res);

  EXPECT_EQ(set_s21_ref.size(), 3U);
  EXPECT_EQ(*set_s21_ref.begin(), 1.44);

  EXPECT_EQ(set_s21_res.size(), 2U);
  EXPECT_EQ(*set_s21_res.begin(), 22.2);
}

TEST(SET_SWAP, test_a_2) {
  s21::set<double> set_s21_ref = {22.2, 45.11};
  s21::set<double> set_s21_res;

  set_s21_ref.swap(set_s21_res);

  EXPECT_EQ(set_s21_ref.size(), 0U);

  EXPECT_EQ(set_s21_res.size(), 2U);
  EXPECT_EQ(*set_s21_res.begin(), 22.2);
}

TEST(SET_SWAP, test_a_3) {
  s21::set<double> set_s21_ref;
  s21::set<double> set_s21_res = {12.4457, 1.44, 22.2};

  set_s21_ref.swap(set_s21_res);

  EXPECT_EQ(set_s21_ref.size(), 3U);
  EXPECT_EQ(*set_s21_ref.begin(), 1.44);

  EXPECT_EQ(set_s21_res.size(), 0U);
}

TEST(SET_SWAP, test_a_4) {
  s21::set<double> set_s21_ref;
  s21::set<double> set_s21_res;

  set_s21_ref.swap(set_s21_res);

  EXPECT_EQ(set_s21_ref.size(), 0U);
  EXPECT_EQ(set_s21_res.size(), 0U);
}

TEST(SET_CONTAINS, test_a_1) {
  s21::set<double> set_s21 = {22.2, 45.11};

  EXPECT_EQ(set_s21.contains(22.2), true);
  EXPECT_EQ(set_s21.contains(45.11), true);
}

TEST(SET_CONTAINS, test_a_2) {
  s21::set<double> set_s21_ref = {22.2, 45.11};
  s21::set<double> set_s21_res;

  set_s21_ref.swap(set_s21_res);

  EXPECT_EQ(set_s21_ref.size(), 0U);
  EXPECT_EQ(set_s21_ref.contains(22.2), false);
  EXPECT_EQ(set_s21_ref.contains(45.11), false);

  EXPECT_EQ(set_s21_res.size(), 2U);
  EXPECT_EQ(set_s21_res.contains(22.2), true);
  EXPECT_EQ(set_s21_res.contains(45.11), true);
}

TEST(SET_CONTAINS, test_a_3) {
  s21::set<double> set_s21_ref;
  s21::set<double> set_s21_res = {12.4457, 1.44, 22.2};

  set_s21_ref.swap(set_s21_res);

  EXPECT_EQ(set_s21_ref.size(), 3U);
  EXPECT_EQ(set_s21_ref.contains(12.4457), true);
  EXPECT_EQ(set_s21_ref.contains(1.44), true);
  EXPECT_EQ(set_s21_ref.contains(22.2), true);

  EXPECT_EQ(set_s21_res.size(), 0U);
  EXPECT_EQ(set_s21_res.contains(12.4457), false);
  EXPECT_EQ(set_s21_res.contains(1.44), false);
  EXPECT_EQ(set_s21_res.contains(22.2), false);
}

TEST(SET_CONTAINS, test_a_4) {
  s21::set<double> set_s21;

  EXPECT_EQ(set_s21.size(), 0U);
  EXPECT_EQ(set_s21.contains(12.4457), false);
}

TEST(SET_FIND, test_a_1) {
  std::set<double> set_s21;

  EXPECT_TRUE(set_s21.find(23.4) == set_s21.end());
}

TEST(SET_FIND, test_a_2) {
  s21::set<double> set_s21 = {12.4457, 1.44, 22.2};

  auto it = set_s21.begin();
  ++it;
  EXPECT_EQ(*set_s21.find(12.4457), *it);

  it--;
  EXPECT_EQ(*set_s21.find(1.44), *it);

  ++it;
  ++it;
  EXPECT_EQ(*set_s21.find(22.2), *it);
}

TEST(SET_EMPLACE, test_a_1) {
  s21::set<int> set_s21;

  std::vector<std::pair<s21::set<int>::iterator, bool>> emplace1 =
      set_s21.insert_many(99, 99, 99, 230, 98);

  EXPECT_EQ(*emplace1[1].first, 230);
  EXPECT_EQ(emplace1[1].second, true);
  EXPECT_EQ(set_s21.size(), 3U);
}

TEST(SET_EMPLACE, test_a_2) {
  s21::set<double> set_s21;

  std::vector<std::pair<s21::set<double>::iterator, bool>> emplace1 =
      set_s21.insert_many(11.4, 27., 39., 27., 39.);

  EXPECT_EQ(*emplace1[1].first, 27);
  EXPECT_EQ(emplace1[1].second, true);
  EXPECT_EQ(set_s21.size(), 3U);
}

TEST(SET_EMPLACE, test_a_3) {
  s21::set<std::string> set_s21;

  std::vector<std::pair<s21::set<std::string>::iterator, bool>> emplace1 =
      set_s21.insert_many("hello", "hi", "hi", "holli", "hello");

  EXPECT_EQ(*emplace1[1].first, "hi");
  EXPECT_EQ(emplace1[0].second, true);
  EXPECT_EQ(set_s21.size(), 3U);
}

TEST(SET_EMPLACE, test_a_4) {
  s21::set<int> set_s21;

  std::vector<std::pair<s21::set<int>::iterator, bool>> emplace1 =
      set_s21.insert_many(9);

  EXPECT_EQ(*emplace1[0].first, 9);
  EXPECT_EQ(emplace1[0].second, true);
  EXPECT_EQ(set_s21.size(), 1U);
}

TEST(SET_EMPLACE, test_a_5) {
  s21::set<double> set_s21 = {1.4};

  std::vector<std::pair<s21::set<double>::iterator, bool>> emplace1 =
      set_s21.insert_many(1.4);

  EXPECT_EQ(emplace1[0].second, 0);
  EXPECT_EQ(set_s21.size(), 1U);
}

TEST(SET_EMPLACE, test_a_6) {
  s21::set<std::string> set_s21 = {"hello"};

  std::vector<std::pair<s21::set<std::string>::iterator, bool>> emplace1 =
      set_s21.insert_many("hi");

  EXPECT_EQ(*emplace1[0].first, "hi");
  EXPECT_EQ(emplace1[0].second, true);
  EXPECT_EQ(set_s21.size(), 2U);
}

TEST(SET, DEFAULT_CONSTRUCTOR_TEST_1) {
  s21::set<NotDefaultConstructor> a;
  EXPECT_EQ(a.size(), 0U);
}

TEST(SET, CONSTRUCTOR_INIT_LIST_TEST_2) {
  s21::set<int> a{12, 13, 14, 15, 16, 17};
  EXPECT_EQ(a.size(), 6U);
  EXPECT_EQ(*a.begin(), 12);
}

TEST(SET, CONSTRUCTOR_COPY_TEST_3) {
  s21::set<int> a{12, 13, 14, 15, 16, 17};
  s21::set<int> b(a);
  EXPECT_EQ(a.size(), 6U);
  EXPECT_EQ(*a.begin(), 12);
  EXPECT_EQ(b.size(), 6U);
  EXPECT_EQ(*b.begin(), 12);
}

TEST(SET, CONSTRUCTOR_MOVE_TEST_4) {
  s21::set<int> a{12, 13, 14, 15, 16, 17};
  s21::set<int> b(std::move(a));
  const auto it_begin = a.begin();
  const auto it_end = a.end();
  EXPECT_EQ(a.size(), 0U);
  EXPECT_TRUE(a.begin() == a.end());
  EXPECT_TRUE(it_begin == it_end);
  EXPECT_TRUE(a.cbegin() == a.cend());
  EXPECT_EQ(b.size(), 6U);
  EXPECT_EQ(*b.begin(), 12);
}

TEST(SET, OPERATOR_EQ_MOVE_TEST_5) {
  s21::set<int> a{12, 13, 14, 15, 16, 17};
  s21::set<int> b;
  b = std::move(a);
  const auto it_begin = a.begin();
  const auto it_end = a.end();
  EXPECT_EQ(a.size(), 0U);
  EXPECT_TRUE(a.empty());
  EXPECT_TRUE(a.begin() == a.end());
  EXPECT_TRUE(it_begin == it_end);
  EXPECT_TRUE(a.cbegin() == a.cend());
  EXPECT_EQ(b.size(), 6U);
  EXPECT_EQ(*b.begin(), 12);
}

TEST(SET, OPERATOR_EQ_COPY_TEST_6) {
  s21::set<int> a{12, 13, 14, 15, 16, 17};
  s21::set<int> b;
  b = a;
  EXPECT_EQ(a.size(), 6U);
  EXPECT_EQ(*a.begin(), 12);
  EXPECT_EQ(b.size(), 6U);
  EXPECT_EQ(*b.begin(), 12);
}

TEST(SET, INSERT_TEST_7) {
  s21::set<int> a{12, 13, 14, 15, 16, 17, 4, -1000, 8};
  s21::set<int> b;
  s21::set<int> c;
  for (auto item : a) {
    b.insert(item);
  }
  for (auto i = (--b.end()); i != b.end(); --i) {
    c.insert(*i - 1);
  }
  EXPECT_EQ(a.size(), 9U);
  EXPECT_EQ(*a.begin(), -1000);
  EXPECT_EQ(b.size(), 9U);
  EXPECT_EQ(*b.begin(), -1000);
  EXPECT_EQ(*c.begin(), -1001);
  EXPECT_TRUE(++b.end() == b.begin());
}

TEST(SET, ERASE_TEST_8) {
  s21::set<int> a{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  EXPECT_EQ(a.size(), 1U);
  for (int i = -1000; i <= 1000; ++i) {
    a.insert(i);
  }
  while (!a.empty()) {
    a.erase(a.begin());
    a.erase(*--a.end());
  }
  EXPECT_EQ(a.size(), 0U);
}

TEST(SET, BINARY_EQ_STD_SET_TEST_9) {
  s21::set<int> set_s21;
  std::set<int> std_set;
  for (int i = -100; i <= 100; ++i) {
    std_set.insert(i);
    set_s21.insert(-i);
  }
  for (int i = 100; i <= 300; ++i) {
    std_set.insert(i);
    set_s21.insert(i);
  }
  auto it_s21 = set_s21.begin();
  for (auto it = std_set.begin(); it != std_set.end(); ++it, ++it_s21) {
    EXPECT_EQ(*it_s21, *it);
  }
}

TEST(SET, MERGE_TEST_10) {
  s21::set<int> set_s21_a;
  s21::set<int> set_s21_b;
  for (int i = -100; i <= 100; ++i) {
    set_s21_a.insert(-i);
    set_s21_b.insert(-i);
  }
  set_s21_a.merge(set_s21_b);
  EXPECT_EQ(set_s21_a.size(), set_s21_b.size());
  set_s21_a.erase(set_s21_a.begin());
  EXPECT_EQ(*set_s21_b.begin(), -100);
  EXPECT_EQ(*set_s21_a.begin(), -99);
  set_s21_a.merge(set_s21_b);
  EXPECT_EQ(set_s21_a.size(), set_s21_b.size() + 1U);
  EXPECT_EQ(*set_s21_b.begin(), -99);
}

TEST(SET, INSERT_MANY_TEST_11) {
  s21::set<int> a;
  a.insert_many(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 8,
                9, 10);
  s21::set<char> b;
  b.insert_many('c', 'd', 'e', 'f', 'g', 'a', 'c');
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(a.size(), 12U);
  EXPECT_EQ(b.size(), 6U);
  EXPECT_TRUE(a.contains(12));
  EXPECT_TRUE(!a.contains(13));
  a.clear();
  EXPECT_FALSE(a.contains(12));
  EXPECT_TRUE(a.size() == 0U);
  EXPECT_TRUE(b.contains('f'));
  EXPECT_TRUE(!b.contains('h'));
  b.clear();
  b.clear();
  EXPECT_TRUE(b.size() == 0U);
}

TEST(SET, SWAP_TEST_12) {
  s21::set<int> set_s21_a;
  s21::set<int> set_s21_b;
  for (int i = -100; i <= 100; ++i) {
    set_s21_a.insert(-i);
  }
  EXPECT_EQ(set_s21_a.size(), 201U);
  set_s21_a.swap(set_s21_b);
  EXPECT_EQ(*set_s21_b.begin(), -100);
  EXPECT_EQ(set_s21_b.size(), 201U);
  EXPECT_EQ(set_s21_a.size(), 0U);
  EXPECT_TRUE(set_s21_a.empty());
}

TEST(SET, FIND_TEST_13) {
  s21::set<std::size_t> set_s21_a;
  for (std::size_t i = 100; i <= 3000; ++i) {
    set_s21_a.insert(i);
  }
  std::size_t max_s = set_s21_a.max_size();
  set_s21_a.insert(max_s);
  EXPECT_EQ(*(--set_s21_a.end()), max_s);
  EXPECT_TRUE(set_s21_a.contains(max_s));
  set_s21_a.erase(set_s21_a.find(max_s));
  EXPECT_TRUE(!set_s21_a.contains(max_s));
  s21::set<int> const c{1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (const auto i : c) {
    EXPECT_TRUE(i);
  }
}