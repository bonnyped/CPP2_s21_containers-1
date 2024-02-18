#include "s21_test_containers.h"

TEST(TEST_S21_MAP, constructor_default_test_1) {
  s21::map<int, NotDefaultConstructor> a;
  EXPECT_EQ(a.size(), 0U);
}

TEST(TEST_S21_MAP, constructor_init_list_test_2) {
  s21::map<int, char> a{
      {1, 'a'},
      {2, 'b'},
      {3, 'c'},
  };
  EXPECT_EQ(a.size(), 3U);
  EXPECT_EQ((*a.begin()).second, 'a');
  EXPECT_EQ((*a.begin()).first, 1);
}

TEST(TEST_S21_MAP, constructor_copy_test_3) {
  s21::map<int, char> a{
      {1, 'a'},
      {2, 'b'},
      {3, 'c'},
  };
  s21::map<int, char> b(a);
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(b.size(), 3U);
  EXPECT_EQ((*a.begin()).first, 1);
  EXPECT_EQ((*b.begin()).first, 1);
  EXPECT_EQ((*a.begin()).second, 'a');
  EXPECT_EQ((*++b.begin()).second, 'b');
}

TEST(TEST_S21_MAP, constructor_copy_test_4) {
  s21::map<int, char> const a{
      {1, 'a'},
      {2, 'b'},
      {3, 'c'},
  };
  s21::map<int, char> const b(a);
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(b.size(), 3U);
  EXPECT_EQ((*--a.cend()).first, 3);
  EXPECT_EQ((*--b.cend()).first, 3);
  EXPECT_EQ((*--a.cend()).second, 'c');
  EXPECT_EQ((*--b.cend()).second, 'c');
}

TEST(TEST_S21_MAP, constructor_move_test_5) {
  s21::map<int, char> a{
      {1, 'a'},
      {2, 'b'},
      {3, 'c'},
  };
  s21::map<int, char> const b(std::move(a));
  EXPECT_TRUE(a.size() != b.size());
  EXPECT_EQ(b.size(), 3U);
  EXPECT_EQ(a.size(), 0U);
  EXPECT_EQ((*--b.cend()).first, 3);
  EXPECT_TRUE(a.end() == a.begin());
  EXPECT_EQ((*--b.cend()).second, 'c');
}

TEST(TEST_S21_MAP, operator_eq_copy_test_6) {
  s21::map<int, char> const a{
      {1, 'a'},
      {2, 'b'},
      {3, 'c'},
  };
  s21::map<int, char> b;
  b = a;
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(b.size(), 3U);
  EXPECT_EQ((*--a.cend()).first, 3);
  EXPECT_EQ((*--b.cend()).first, 3);
  EXPECT_EQ((*--a.cend()).second, 'c');
  EXPECT_EQ((*--b.end()).second, 'c');
}

TEST(TEST_S21_MAP, operator_eq_move_test_7) {
  s21::map<int, char> a{
      {1, 'a'},
      {2, 'b'},
      {3, 'c'},
  };
  s21::map<int, char> b;
  b = std::move(a);
  EXPECT_TRUE(a.size() != b.size());
  EXPECT_EQ(b.size(), 3U);
  EXPECT_EQ(a.size(), 0U);
  EXPECT_EQ((*++b.cbegin()).first, 2);
  EXPECT_EQ((*b.cbegin()++).first, 1);
  EXPECT_EQ((*++b.cbegin()).second, 'b');
  EXPECT_EQ((*b.cbegin()++).second, 'a');
}

TEST(TEST_S21_MAP, operator_eq_move_const_test_8) {
  s21::map<int, char> const a{
      {1, 'a'},
      {2, 'b'},
      {3, 'c'},
  };
  s21::map<int, char> b;
  b = std::move(a);
  EXPECT_TRUE(a.size() == b.size());
  EXPECT_EQ(b.size(), 3U);
  EXPECT_EQ(a.size(), 3U);
  EXPECT_EQ((*++b.cbegin()).first, 2);
  EXPECT_EQ((*b.cbegin()++).first, 1);
  EXPECT_EQ((*++b.cbegin()).second, 'b');
  EXPECT_EQ((*b.cbegin()++).second, 'a');
  EXPECT_EQ((*++a.cbegin()).first, 2);
  EXPECT_EQ((*a.cbegin()++).first, 1);
  EXPECT_EQ((*++a.cbegin()).second, 'b');
  EXPECT_EQ((*a.cbegin()++).second, 'a');
}

TEST(TEST_S21_MAP, operator_sq_test_9) {
  s21::map<char, std::string> a{{'a', "Adler"},  {'b', "Berlin"},
                                {'c', "Ctoto"},  {'d', "Dublin"},
                                {'e', "Erevan"}, {'f', "Florecia?"}};
  s21::map<char, std::string> b{{'g', "Grey town"}, {'h', "Hollywood"}};
  EXPECT_TRUE(a.size() == 6U);
  EXPECT_TRUE(a['c'] == "Ctoto");
  EXPECT_TRUE(a['t'] == "");
  EXPECT_TRUE(a.size() == 7U);
  EXPECT_TRUE(b['g'] == "Grey town");

  std::string town = a['t'] = "Tomsk";
  EXPECT_TRUE(town == "Tomsk");
  EXPECT_FALSE(a['t'] == "");
}

TEST(TEST_S21_MAP, at_insert_not_exception_test_10) {
  s21::map<char, std::string> a{{'a', "Adler"},  {'b', "Berlin"},
                                {'c', "Ctoto"},  {'d', "Dublin"},
                                {'e', "Erevan"}, {'f', "Florecia?"}};
  s21::map<char, std::string> b{{'g', "Grey town"}, {'h', "Hollywood"}};
  EXPECT_TRUE(a.size() == 6U);
  EXPECT_TRUE(a.at('c') == "Ctoto");
  EXPECT_TRUE(b.size() == 2U);
  EXPECT_TRUE(b.at('g') == "Grey town");
}

TEST(TEST_S21_MAP, at_insert_exception_test_11) {
  s21::map<char, std::string> a{{'a', "Adler"},  {'b', "Berlin"},
                                {'c', "Ctoto"},  {'d', "Dublin"},
                                {'e', "Erevan"}, {'f', "Florecia?"}};
  s21::map<char, std::string> b{{'g', "Grey town"}, {'h', "Hollywood"}};
  EXPECT_THROW(a.at('r'), std::out_of_range);
  EXPECT_TRUE(b.size() == 2U);
  EXPECT_TRUE(b.at('g') == "Grey town");
}

TEST(TEST_S21_MAP, insert_12) {
  s21::map<char, std::string> a{{'a', "Adler"},  {'b', "Berlin"},
                                {'c', "Ctoto"},  {'d', "Dublin"},
                                {'e', "Erevan"}, {'f', "Florecia?"}};
  s21::map<char, std::string> b{{'g', "Grey town"}, {'h', "Hollywood"}};
  a.insert('n', "New-York");
  a.insert('l', "London");
  auto [it, status] = b.insert('p', "Porto");
  EXPECT_TRUE(status);
  EXPECT_EQ((*it).second, "Porto");
  EXPECT_TRUE(b.size() == 3U);
  EXPECT_TRUE(a.size() == 8U);
  auto [it2, status2] = b.insert('p', "Penza");
  EXPECT_FALSE(status2);
  EXPECT_EQ((*it2).second, "Porto");
  EXPECT_TRUE(b.size() == 3U);
  EXPECT_TRUE(a.size() == 8U);
}

TEST(TEST_S21_MAP, insert_assign_13) {
  s21::map<char, std::string> a{{'a', "Adler"},  {'b', "Berlin"},
                                {'c', "Ctoto"},  {'d', "Dublin"},
                                {'e', "Erevan"}, {'f', "Florecia?"}};
  s21::map<char, std::string> b{{'g', "Grey town"}, {'h', "Hollywood"}};
  a.insert({'n', "New-York"});
  a.insert({'l', "London"});
  auto [it, status] = b.insert({'p', "Porto"});
  EXPECT_TRUE(status);
  EXPECT_EQ((*it).second, "Porto");
  EXPECT_TRUE(b.size() == 3U);
  EXPECT_TRUE(a.size() == 8U);
  auto [it2, status2] = b.insert_or_assign('p', "Penza");
  EXPECT_FALSE(status2);
  EXPECT_EQ((*it2).second, "Penza");
  EXPECT_TRUE(b.size() == 3U);
  EXPECT_TRUE(a.size() == 8U);
}

TEST(TEST_S21_MAP, merge_14) {
  s21::map<char, std::string> a{{'a', "Adler"},  {'b', "Berlin"},
                                {'c', "Ctoto"},  {'d', "Dublin"},
                                {'e', "Erevan"}, {'f', "Florecia?"}};
  s21::map<char, std::string> b{{'g', "Grey town"}, {'h', "Hollywood"}};
  a.insert({'n', "New-York"});
  a.insert({'l', "London"});
  b.insert({'d', "Dublin"});
  a.merge(b);
  EXPECT_EQ(b.size(), 1U);
  auto [it, status] = b.insert({'p', "Porto"});
  EXPECT_TRUE(status);
  EXPECT_EQ((*it).second, "Porto");
  EXPECT_TRUE(b.size() == 2U);
  EXPECT_TRUE(a.size() == 10U);
  auto [it2, status2] = b.insert_or_assign('p', "Penza");
  EXPECT_FALSE(status2);
  EXPECT_EQ((*it2).second, "Penza");
  EXPECT_TRUE(b.size() == 2U);
  EXPECT_TRUE(a.size() == 10U);
}

TEST(TEST_S21_MAP, count_15) {
  s21::map<char, std::size_t> a{{'x', 12U}};
  std::size_t max_size_s21 = a.max_size();
  EXPECT_EQ(a['x'], 12U);
  a.insert_or_assign('x', std::move(max_size_s21));
  EXPECT_EQ(a['x'], max_size_s21);
  EXPECT_EQ(a.contains('a'), false);
  EXPECT_EQ(a.contains('x'), true);
  EXPECT_FALSE(a.empty());
  a.clear();
  EXPECT_TRUE(a.empty());
}

TEST(TEST_S21_MAP, swap_16) {
  s21::map<char, std::string> a{{'a', "Adler"},  {'b', "Berlin"},
                                {'c', "Ctoto"},  {'d', "Dublin"},
                                {'e', "Erevan"}, {'f', "Florecia?"}};
  s21::map<char, std::string> b{{'g', "Grey town"}, {'h', "Hollywood"}};
  b.swap(a);
  b.insert({'d', "Dublin"});
  EXPECT_EQ(b.size(), 6U);
  EXPECT_EQ(a.size(), 2U);
}

TEST(TEST_S21_MAP, s21_erase_test_17) {
  s21::map<char, std::string> a{{'a', "Adler"},  {'b', "Berlin"},
                                {'c', "Ctoto"},  {'d', "Dublin"},
                                {'e', "Erevan"}, {'f', "Florecia?"}};
  s21::map<char, std::string> b{{'g', "Grey town"}, {'h', "Hollywood"}};
  a.erase({'a', "Adler"});
  EXPECT_EQ(b.size(), 2U);
  a.erase(a.begin());
  EXPECT_TRUE((*a.begin()).first != 'a');
  a.erase(a.begin());
  EXPECT_EQ((*a.begin()).first, 'd');
}

TEST(TEST_S21_MAP, s21_insert_many_18) {
  s21::map<char, std::string> a;
  std::pair<char, std::string> aa = {'a', "Adler"};
  std::pair<char, std::string> bb = {'b', "Berlin"};
  std::pair<char, std::string> cc = {'c', "Ctoto"};
  std::pair<char, std::string> dd = {'d', "Dublin"};
  std::pair<char, std::string> ee = {'e', "Erevan"};
  std::pair<char, std::string> ff = {'f', "Florecia?"};
  a.insert_many(std::move(aa), std::move(bb), std::move(cc), std::move(dd),
                std::move(ee), std::move(ff));
  s21::map<char, std::string> b{{'g', "Grey town"}, {'h', "Hollywood"}};
  a.erase({'a', "Adler"});
  EXPECT_EQ(b.size(), 2U);
  a.erase(a.begin());
  EXPECT_TRUE((*a.begin()).first != 'a');
  a.erase(a.begin());
  EXPECT_EQ((*a.begin()).first, 'd');
}

TEST(TEST_S21_MAP, s21_erase_test_18) {
  s21::map<char, std::string> const a{{'a', "Adler"},  {'b', "Berlin"},
                                      {'c', "Ctoto"},  {'d', "Dublin"},
                                      {'e', "Erevan"}, {'f', "Florecia?"}};
  ;
  EXPECT_TRUE((*a.begin()).first == 'a');
  EXPECT_TRUE((*--a.end()).first == 'f');
}