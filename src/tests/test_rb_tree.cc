#include "s21_test_containers.h"

TEST(DEFAULT_CONSTRUCTOR_RBTREE, test_1) {
  s21::RBTree<NotDefaultConstructor> a;
  EXPECT_EQ(a.Size(), 0U);
  a.Insert({"1", "2", "3"});
  EXPECT_EQ(a.Size(), 1U);
  a.Insert({"9", "8", "7"});
  EXPECT_EQ((*a.begin()).sum(), "123");
  EXPECT_EQ((*++a.begin()).sum(), "987");
}

TEST(CONSTRUCTOR_RBTREE, test_2) {
  s21::RBTree<NotDefaultConstructor> a(NotDefaultConstructor{"a", "b", "c"});
  EXPECT_EQ(a.Begin()->sum(), "abc");
  EXPECT_EQ(a.Size(), 1U);
};

TEST(INSERT_UNIQUE_RBTREE, test_3) {
  s21::RBTree<NotDefaultConstructor> a;
  a.InsertUnique(NotDefaultConstructor{"c", "a", "b"});
  EXPECT_EQ(a.Begin()->sum(), "cab");
  a.InsertUnique(NotDefaultConstructor{"b", "c", "a"});
  EXPECT_EQ(a.Begin()->sum(), "bca");
  a.InsertUnique(NotDefaultConstructor{"a", "b", "c"});
  EXPECT_EQ(a.Begin()->sum(), "abc");
  a.InsertUnique(NotDefaultConstructor{"a", "b", "c"});
  a.InsertUnique(NotDefaultConstructor{"a", "b", "c"});
  a.InsertUnique(NotDefaultConstructor{"a", "b", "c"});
  EXPECT_EQ(a.Size(), 3U);
}

TEST(INSERT_NOT_UNIQUE_RBTREE, test_4) {
  s21::RBTree<NotDefaultConstructor> a;
  a.Insert(NotDefaultConstructor{"c", "a", "b"});
  EXPECT_EQ(a.Begin()->sum(), "cab");
  a.Insert(NotDefaultConstructor{"b", "c", "a"});
  EXPECT_EQ(a.Begin()->sum(), "bca");
  a.Insert(NotDefaultConstructor{"a", "b", "c"});
  EXPECT_EQ(a.Begin()->sum(), "abc");
  a.Insert(NotDefaultConstructor{"a", "b", "c"});
  a.Insert(NotDefaultConstructor{"a", "b", "c"});
  a.Insert(NotDefaultConstructor{"a", "b", "c"});
  EXPECT_EQ((--a.End())->sum(), "cab");
  EXPECT_EQ(a.Size(), 6U);
}

TEST(INSERT_ERASE_RBTREE, test_5) {
  s21::RBTree<int> a;
  for (int i = 1; i <= 1000; ++i) {
    EXPECT_EQ(*a.InsertUnique(i).first, i);
  }
  EXPECT_EQ(a.Size(), 1000U);
  for (int i = 100; i >= -1000; --i) {
    a.Insert(i);
  }
  a.Erase(1000);
  EXPECT_EQ(a.Size(), 2100U);
  while (a.Size()) {
    a.Erase(a.Begin());
  }
  EXPECT_EQ(a.Size(), 0U);
}

TEST(INSERT_ERASE_RBTREE, test_6) {
  s21::RBTree<int> a;
  for (int i = 1; i <= 3; ++i) {
    a.Insert(i);
  }
  a.Erase(2);
  EXPECT_EQ(a.Size(), 2U);
}

TEST(INSERT_ERASE_RBTREE, test_7) {
  s21::RBTree<int> a;
  for (int i = 1; i <= 1000; ++i) {
    a.Insert(i);
    a.Erase(i);
    EXPECT_EQ(a.Size(), 0U);
  }

  EXPECT_EQ(a.Size(), 0U);
}

TEST(INSERT_MANY_UNIQUE_ERASE_ITERATOR_RBTREE, test_8) {
  s21::RBTree<int> a;
  a.InsertManyUnique(1, 2, 3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  auto it = a.Begin();
  EXPECT_EQ(*(it++), 0);
  EXPECT_EQ(*(++it), 2);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 4);
  EXPECT_EQ(*(it--), 4);
  EXPECT_EQ(*(--it), 2);
  EXPECT_EQ(*(--it), 1);
  EXPECT_EQ(*(--it), 0);
  --it;
  EXPECT_EQ(*(--it), 9);
  EXPECT_EQ(*(it++), 9);
  EXPECT_EQ(a.Size(), 10U);
}

TEST(ERASE_BALANCE_RBTREE, test_9) {
  s21::RBTree<int> a;
  a.InsertManyUnique(30, 50, 70, 90, 110, 140);
  a.Erase(140);
  a.Erase(110);

  EXPECT_EQ(a.Size(), 4U);
}

TEST(ERASE_BALANCE_RBTREE, test_10) {
  s21::RBTree<int> a;
  a.InsertManyUnique(30, 50, 70, 90, 110, 140, 60);
  a.Erase(140);
  a.Erase(110);

  EXPECT_EQ(a.Size(), 5U);
}

TEST(ERASE_BALANCE_RBTREE, test_11) {
  s21::RBTree<int> a;
  a.InsertManyUnique(30, 50, 70, 90, 110, 140, 75);
  a.Erase(140);
  a.Erase(110);

  EXPECT_EQ(a.Size(), 5U);
}

TEST(ERASE_BALANCE_RBTREE, test_12) {
  s21::RBTree<int> a;
  a.InsertManyUnique(30, 50, 70, 90, 110, 140, 60, 55, 170, 180, 190, 150, 148,
                     147, 100, 97, 145, 143);
  a.Erase(145);
  a.Erase(143);
  a.Erase(148);
  a.Erase(147);

  EXPECT_EQ(a.Size(), 14U);
}

TEST(ERASE_BALANCE_RBTREE, test_13) {
  s21::RBTree<int> a;
  a.InsertManyUnique(30, 50, 70, 90, 110, 140, 60, 55, 170, 180, 190, 150, 148,
                     147, 100, 97, 145, 143);
  a.Erase(145);
  a.Erase(143);
  a.Erase(148);
  a.Erase(97);
  a.Erase(147);

  EXPECT_EQ(a.Size(), 13U);
}

TEST(ERASE_BALANCE_RBTREE, test_14) {
  s21::RBTree<int> a;
  a.InsertManyUnique(30, 50, 70, 90, 110, 140, 60, 55, 170, 180, 190, 150, 148,
                     147, 100, 97, 145, 143, 96);
  a.Erase(145);
  a.Erase(143);
  a.Erase(148);
  a.Erase(97);
  a.Erase(147);

  EXPECT_EQ(a.Size(), 14U);
}

TEST(ERASE_BALANCE_RBTREE, test_15) {
  s21::RBTree<int> a;
  for (int i = 1; i <= 20; ++i) {
    a.Insert(i);
  }
  a.Erase(8);

  EXPECT_EQ(a.Size(), 19U);
}

TEST(ERASE_BALANCE_RBTREE, test_16) {
  s21::RBTree<int> a;
  for (int i = 1; i <= 20; ++i) {
    a.Insert(i);
  }
  EXPECT_EQ(*a.Insert(6).first, 6);
  a.Erase(8);
  a.Erase(7);

  EXPECT_EQ(a.Size(), 19U);
}

TEST(ERASE_BALANCE_RBTREE, test_17) {
  s21::RBTree<int> a;
  for (int i = 1; i <= 20; ++i) {
    a.Insert(i);
  }
  a.Insert(6);
  a.Erase(8);
  a.Erase(7);
  for (int i = 1; i <= 20; ++i) {
    a.Insert(i);
  }
  a.Erase(12);
  a.Erase(4);
  a.Erase(3);
  a.Erase(20);
  a.Erase(19);
  a.Erase(11);
  a.Erase(12);
  a.Erase(13);
  a.Erase(10);
  a.Erase(6);
  for (int i = 1; i <= 20; ++i) {
    a.Insert(i);
  }
  for (int i = 10; i >= -20; --i) {
    a.Insert(i);
  }
  while (a.Size() > 50) {
    a.Erase(a.Begin());
  }
  while (a.Size() > 30) {
    a.Erase(++a.Begin());
  }
  while (a.Size() > 5) {
    a.Erase(--a.End());
  }
  a.Erase(a.End());
  EXPECT_EQ(a.Size(), 5U);
}

TEST(ERASE_SWAP_RBTREE, test_18) {
  s21::RBTree<int> a;
  for (int i = -10000; i <= 2000; ++i) {
    a.Insert(i);
  }
  s21::RBTree<int> b(std::move(a));
  for (int i = -1; i <= 200; ++i) {
    b.Erase(i);
  }
  for (int i = -10000; i <= -100; ++i) {
    b.Erase(i);
  }

  EXPECT_EQ(a.Size(), 0U);
}

TEST(OPERATOR_EQ_RBTREE, test_19) {
  s21::RBTree<int> a;
  for (int i = -10000; i <= 2000; ++i) {
    a.Insert(i);
  }
  s21::RBTree<int> b;
  b = a;
  for (int i = -10000; i <= -100; ++i) {
    b.Erase(i);
    a.Erase(i + 3);
  }
  while (a.Size() > 3) {
    a.Erase(--a.End());
    b.Erase(b.Begin());
  }
  EXPECT_EQ(a.Size(), b.Size());
}

TEST(MERGE_UNIQUE_RBTREE, test_20) {
  s21::RBTree<int> a;
  s21::RBTree<int> b;
  for (int i = -10000; i <= 2000; ++i) {
    a.Insert(i);
    b.InsertUnique(-i);
  }

  a.MergeUnique(b);

  EXPECT_EQ(a.Size(), b.Size() + 16000);
}

TEST(MERGE_RBTREE, test_21) {
  s21::RBTree<int> a;
  s21::RBTree<int> b;
  for (int i = -10000; i <= 2000; ++i) {
    a.Insert(i);
    b.InsertUnique(-i);
  }

  a.Merge(b);

  EXPECT_EQ(b.Size(), 0U);
}

TEST(INSERT_MANY_RBTREE, test_22) {
  s21::RBTree<int> a;
  a.InsertMany(1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5,
               5, 5, 5);
  EXPECT_EQ(a.Size(), 25U);
}

TEST(COUNT_RBTREE, test_23) {
  s21::RBTree<std::string> a;
  a.InsertMany("hello", "HELLO", "Hamlet", "Hello", "hamlet", "hello", "HeLlo",
               "to be", "or not", "to be");
  EXPECT_EQ(a.Count("hello"), 2U);
  EXPECT_EQ(a.Count("to be"), 2U);
  EXPECT_EQ(a.Count("Hamlet"), 1U);
}

TEST(UPPER_BOUND_RBTREE, test_24) {
  std::multiset<std::string> b{"aaaaaaa", "bbbbbb", "cccccc", "eeeeeee",
                               "xxxxxx",  "ffffff", "bbbbbb", "cccccc",
                               "cccccc",  "ddddd"};
  s21::RBTree<std::string> a;
  a.InsertMany("aaaaaaa", "bbbbbb", "cccccc", "eeeeeee", "xxxxxx", "ffffff",
               "bbbbbb", "cccccc", "cccccc", "ddddd");
  EXPECT_EQ(*a.UpperBound("hamlet"), "xxxxxx");
  EXPECT_EQ(*b.upper_bound("hamlet"), "xxxxxx");
  EXPECT_EQ(*a.UpperBound("cccccc"), "ddddd");
  EXPECT_EQ(*b.upper_bound("cccccc"), "ddddd");
  EXPECT_EQ(*a.UpperBound("aaaaaaa"), "bbbbbb");
  EXPECT_EQ(*b.upper_bound("aaaaaaa"), "bbbbbb");
}

TEST(LOWER_BOUND_RBTREE, test_24) {
  std::multiset<std::string> b{"aaaaaaa", "bbbbbb", "cccccc", "eeeeeee",
                               "xxxxxx",  "ffffff", "bbbbbb", "cccccc",
                               "cccccc",  "ddddd"};
  s21::RBTree<std::string> a;
  a.InsertMany("aaaaaaa", "bbbbbb", "cccccc", "eeeeeee", "xxxxxx", "ffffff",
               "bbbbbb", "cccccc", "cccccc", "ddddd");
  EXPECT_EQ(*a.LowerBound("hamlet"), "xxxxxx");
  EXPECT_EQ(*b.lower_bound("hamlet"), "xxxxxx");
  EXPECT_EQ(*a.LowerBound("cccccc"), "cccccc");
  EXPECT_EQ(*b.lower_bound("cccccc"), "cccccc");
  EXPECT_EQ(*a.LowerBound("aaaaaaa"), "aaaaaaa");
  EXPECT_EQ(*b.lower_bound("aaaaaaa"), "aaaaaaa");
}

TEST(LOWER_BOUND_RBTREE, test_25) {
  std::set<std::string> b{"aaaaaaa", "bbbbbb", "cccccc", "eeeeeee", "xxxxxx",
                          "ffffff",  "bbbbbb", "cccccc", "cccccc",  "ddddd"};
  s21::RBTree<std::string> a;
  a.InsertManyUnique("aaaaaaa", "bbbbbb", "cccccc", "eeeeeee", "xxxxxx",
                     "ffffff", "bbbbbb", "cccccc", "cccccc", "ddddd");
  EXPECT_EQ(*a.LowerBound("hamlet"), "xxxxxx");
  EXPECT_EQ(*b.lower_bound("hamlet"), "xxxxxx");
  EXPECT_EQ(*a.LowerBound("cccccc"), "cccccc");
  EXPECT_EQ(*b.lower_bound("cccccc"), "cccccc");
  EXPECT_EQ(*a.LowerBound("aaaaaaa"), "aaaaaaa");
  EXPECT_EQ(*b.lower_bound("aaaaaaa"), "aaaaaaa");
}

TEST(UPPER_BOUND_RBTREE, test_26) {
  std::set<std::string> b{"aaaaaaa", "bbbbbb", "cccccc", "eeeeeee", "xxxxxx",
                          "ffffff",  "bbbbbb", "cccccc", "cccccc",  "ddddd"};
  s21::RBTree<std::string> a;
  a.InsertManyUnique("aaaaaaa", "bbbbbb", "cccccc", "eeeeeee", "xxxxxx",
                     "ffffff", "bbbbbb", "cccccc", "cccccc", "ddddd");
  EXPECT_EQ(*a.UpperBound("hamlet"), "xxxxxx");
  EXPECT_EQ(*b.upper_bound("hamlet"), "xxxxxx");
  EXPECT_EQ(*a.UpperBound("cccccc"), "ddddd");
  EXPECT_EQ(*b.upper_bound("cccccc"), "ddddd");
  EXPECT_EQ(*a.UpperBound("aaaaaaa"), "bbbbbb");
  EXPECT_EQ(*b.upper_bound("aaaaaaa"), "bbbbbb");
}

TEST(CONST_RBTREE, test_27) {
  s21::RBTree<int> const a(1);

  EXPECT_EQ(*a.Begin(), 1);
  EXPECT_TRUE(a.End() != a.Begin());
}
