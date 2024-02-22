#include "tests.h"

template class st::map<int, int>;

TEST(map, ConstructorDefaultMap) {
  st::map<int, int> stEmptyMap;
  std::map<int, int> defaultEmptyMap;
  EXPECT_EQ(stEmptyMap.empty(), defaultEmptyMap.empty());
}

TEST(map, ConstructorInitializerMap) {
  st::map<int, int> stMap({{v1, 'q'}, {v2, 'w'}, {v3, 'e'}, {v4, 'r'}});
  std::map<int, int> defaultMap({{v1, 'q'}, {v2, 'w'}, {v3, 'e'}, {v4, 'r'}});
  EXPECT_EQ(stMap.size(), defaultMap.size());
  auto stIt = stMap.begin();
  auto defaultIt = defaultMap.begin();
  for (; stIt != stMap.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE((*stIt).first == (*defaultIt).first);
    EXPECT_TRUE((*stIt).second == (*defaultIt).second);
  }
}

TEST(map, ConstructorInitializer2Map) {
  st::map<int, int> stMap = {};
  std::map<int, int> defaultMap = {};
  EXPECT_EQ(stMap.size(), defaultMap.size());
  auto stIt = stMap.begin();
  auto defaultIt = defaultMap.begin();
  for (; stIt != stMap.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE((*stIt).first == (*defaultIt).first);
    EXPECT_TRUE((*stIt).second == (*defaultIt).second);
  }
}

TEST(map, ConstructorCopyMap) {
  const st::map<int, int> stMap({{1, 2}, {3, 4}, {5, 6}});
  const std::map<int, int> defaultMap({{1, 2}, {3, 4}, {5, 6}});
  st::map<int, int> stMapCopy = stMap;
  std::map<int, int> defaultMapCopy = defaultMap;
  EXPECT_EQ(stMapCopy.size(), defaultMapCopy.size());
  auto stIt = stMapCopy.begin();
  auto defaultIt = defaultMapCopy.begin();
  for (; stIt != stMapCopy.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE((*stIt).first == (*defaultIt).first);
    EXPECT_TRUE((*stIt).second == (*defaultIt).second);
  }
}

TEST(map, ConstructorMoveMap) {
  st::map<int, int> stMap({{1, 2}, {3, 4}, {5, 6}});
  std::map<int, int> defaultMap({{1, 2}, {3, 4}, {5, 6}});
  st::map<int, int> stMapCopy = std::move(stMap);
  std::map<int, int> defaultMapCopy = std::move(defaultMap);
  EXPECT_EQ(stMap.size(), defaultMap.size());
  EXPECT_EQ(stMapCopy.size(), defaultMapCopy.size());
  auto stIt = stMapCopy.begin();
  auto defaultIt = defaultMapCopy.begin();
  for (; stIt != stMapCopy.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE((*stIt).first == (*defaultIt).first);
    EXPECT_TRUE((*stIt).second == (*defaultIt).second);
  }
}

TEST(map, MapOperator) {
  st::map<int, int> stMap({{10, 1}, {20, 2}, {30, 3}});
  std::map<int, int> defaultMap({{10, 1}, {20, 2}, {30, 3}});
  stMap[10] = 11;
  defaultMap[10] = 11;
  defaultMap[20] = 22;
  EXPECT_TRUE(stMap[10] == defaultMap[10]);
  EXPECT_FALSE(stMap[20] == defaultMap[20]);
  EXPECT_TRUE(stMap[30] == defaultMap[30]);
}

TEST(map, MapAtOperatorException) {
  st::map<int, int> stMap({{10, 1}, {20, 2}, {30, 3}});
  EXPECT_THROW(stMap.at('g') = 1, std::out_of_range);
}

TEST(map, MapAtOperator) {
  st::map<int, int> stMap({{10, 1}, {20, 2}, {30, 3}});
  std::map<int, int> defaultMap({{10, 1}, {20, 2}, {30, 3}});
  stMap.at(10) = 11;
  defaultMap.at(10) = 11;
  defaultMap.at(20) = 22;
  EXPECT_TRUE(stMap[10] == defaultMap[10]);
  EXPECT_FALSE(stMap[20] == defaultMap[20]);
  EXPECT_TRUE(stMap[30] == defaultMap[30]);
}

TEST(map, MapAtConstOperator) {
  const st::map<int, int> stMap({{10, 1}, {20, 2}, {30, 3}});
  const std::map<int, int> defaultMap({{10, 1}, {20, 2}, {30, 3}});
  EXPECT_TRUE(stMap.at(10) == defaultMap.at(10));
  EXPECT_TRUE(stMap.at(20) == defaultMap.at(20));
  EXPECT_TRUE(stMap.at(30) == defaultMap.at(30));
  EXPECT_ANY_THROW(stMap.at(40));
}

TEST(map, MapCapacity) {
  st::map<int, int> stMap;
  std::map<int, int> defaultMap;
  EXPECT_TRUE(stMap.empty() == defaultMap.empty());
  stMap.insert(10, 1);
  EXPECT_FALSE(stMap.empty() == defaultMap.empty());
  EXPECT_EQ(stMap.size(), 1);
}

TEST(map, MapClear) {
  st::map<int, int> stMap;
  std::map<int, int> defaultMap;
  stMap.clear();
  defaultMap.clear();
  EXPECT_EQ(stMap.empty(), defaultMap.empty());
  stMap.insert(std::make_pair(1, 1));
  defaultMap.insert(std::make_pair(1, 1));
  EXPECT_EQ(stMap.empty(), defaultMap.empty());
  stMap.clear();
  defaultMap.clear();
  EXPECT_EQ(stMap.empty(), defaultMap.empty());
}

TEST(map, MapInsert1) {
  st::map<int, int> stMap;
  std::map<int, int> defaultMap;
  stMap.insert(std::make_pair(v1, 'a'));
  stMap.insert(std::make_pair(v2, 'a'));
  stMap.insert(std::make_pair(v3, 'a'));
  defaultMap.insert(std::make_pair(v1, 'a'));
  defaultMap.insert(std::make_pair(v2, 'a'));
  defaultMap.insert(std::make_pair(v3, 'a'));

  auto stIt = stMap.begin();
  auto defaultIt = defaultMap.begin();
  for (; stIt != stMap.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE((*stIt).first == (*defaultIt).first);
    EXPECT_TRUE((*stIt).second == (*defaultIt).second);
  }

  auto pr1 = stMap.insert(std::make_pair(v1, 'a'));
  auto pr2 = defaultMap.insert(std::make_pair(v1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(map, MapInsert2) {
  st::map<int, int> stMap;
  std::map<int, int> defaultMap;
  stMap.insert(v1, 'a');
  stMap.insert(v2, 'a');
  stMap.insert(v3, 'a');
  defaultMap.insert(std::make_pair(v1, 'a'));
  defaultMap.insert(std::make_pair(v2, 'a'));
  defaultMap.insert(std::make_pair(v3, 'a'));

  auto stIt = stMap.begin();
  auto defaultIt = defaultMap.begin();
  for (; stIt != stMap.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE((*stIt).first == (*defaultIt).first);
    EXPECT_TRUE((*stIt).second == (*defaultIt).second);
  }

  auto pr1 = stMap.insert(v1, 'a');
  auto pr2 = defaultMap.insert(std::make_pair(v1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(map, MapInsert3) {
  st::map<int, int> stMap;
  std::map<int, int> defaultMap;
  stMap.insert(1, 'a');
  stMap.insert(2, 'a');
  stMap.insert(3, 'a');
  defaultMap.insert(std::make_pair(1, 'a'));
  defaultMap.insert(std::make_pair(2, 'a'));
  defaultMap.insert(std::make_pair(3, 'a'));

  auto stIt = stMap.begin();
  auto defaultIt = defaultMap.begin();
  for (; stIt != stMap.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE((*stIt).first == (*defaultIt).first);
    EXPECT_TRUE((*stIt).second == (*defaultIt).second);
  }

  auto pr1 = stMap.insert_or_assign(1, 'b');
  auto i = defaultMap.begin();
  EXPECT_TRUE((*pr1.first).first == (*i).first);
  EXPECT_FALSE((*pr1.first).second == (*i).second);
}

TEST(map, MapErase_1) {
  st::map<int, int> stMap({{v1, 'q'}, {v2, 'w'}, {v3, 'e'}, {v4, 'r'}});
  std::map<int, int> defaultMap({{v1, 'q'}, {v2, 'w'}, {v3, 'e'}, {v4, 'r'}});
  EXPECT_EQ(stMap.size(), defaultMap.size());
  stMap.erase(stMap.begin());
  defaultMap.erase(defaultMap.begin());
  EXPECT_EQ(stMap.size(), defaultMap.size());
  auto stIt = stMap.begin();
  auto defaultIt = defaultMap.begin();
  for (; stIt != stMap.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE((*stIt).first == (*defaultIt).first);
    EXPECT_TRUE((*stIt).second == (*defaultIt).second);
  }
}

TEST(map, MapErase_2) {
  st::map<int, int> stMap({{5, 50},
                             {7, 70},
                             {4, 40},
                             {3, 30},
                             {8, 80},
                             {1, 10},
                             {2, 20},
                             {6, 60},
                             {9, 90}});
  std::map<int, int> defaultMap({{5, 50},
                                 {7, 70},
                                 {4, 40},
                                 {3, 30},
                                 {8, 80},
                                 {1, 10},
                                 {2, 20},
                                 {6, 60},
                                 {9, 90}});
  EXPECT_EQ(stMap.size(), defaultMap.size());
  auto stIt = stMap.begin();
  auto defaultIt = defaultMap.begin();
  for (size_t i = 0; i < 4; ++i, ++stIt, ++defaultIt)
    ;
  stMap.erase(stIt);
  defaultMap.erase(defaultIt);
  EXPECT_EQ(stMap.size(), defaultMap.size());
  stIt = stMap.begin();
  defaultIt = defaultMap.begin();
  for (; stIt != stMap.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE((*stIt).first == (*defaultIt).first);
    EXPECT_TRUE((*stIt).second == (*defaultIt).second);
  }
}

TEST(map, MapErase_3) {
  st::map<int, int> stMap({{5, 50},
                             {7, 70},
                             {4, 40},
                             {3, 30},
                             {8, 80},
                             {1, 10},
                             {2, 20},
                             {6, 60},
                             {9, 90}});
  std::map<int, int> defaultMap({{5, 50},
                                 {7, 70},
                                 {4, 40},
                                 {3, 30},
                                 {8, 80},
                                 {1, 10},
                                 {2, 20},
                                 {6, 60},
                                 {9, 90}});
  EXPECT_EQ(stMap.size(), defaultMap.size());
  auto stIt = stMap.begin();
  auto defaultIt = defaultMap.begin();
  for (size_t i = 0; i < 8; ++i, ++stIt, ++defaultIt)
    ;
  stMap.erase(stIt);
  defaultMap.erase(defaultIt);
  EXPECT_EQ(stMap.size(), defaultMap.size());
  stIt = stMap.begin();
  defaultIt = defaultMap.begin();
  for (; stIt != stMap.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE((*stIt).first == (*defaultIt).first);
    EXPECT_TRUE((*stIt).second == (*defaultIt).second);
  }
}

TEST(map, MapErase_4) {
  st::map<int, int> stMap({{1, 10}, {3, 30}, {2, 20}});
  std::map<int, int> defaultMap({{1, 10}, {3, 30}, {2, 20}});
  EXPECT_EQ(stMap.size(), defaultMap.size());
  auto stIt = stMap.begin();
  auto defaultIt = defaultMap.begin();
  for (size_t i = 0; i < 2; ++i, ++stIt, ++defaultIt)
    ;
  stMap.erase(stIt);
  defaultMap.erase(defaultIt);
  EXPECT_EQ(stMap.size(), defaultMap.size());
  stIt = stMap.begin();
  defaultIt = defaultMap.begin();
  for (; stIt != stMap.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE((*stIt).first == (*defaultIt).first);
    EXPECT_TRUE((*stIt).second == (*defaultIt).second);
  }
}

TEST(map, MapErase_5) {
  st::map<int, int> stMap({{3, 30}, {1, 10}, {2, 20}});
  std::map<int, int> defaultMap({{3, 30}, {1, 10}, {2, 20}});
  EXPECT_EQ(stMap.size(), defaultMap.size());
  auto stIt = stMap.begin();
  auto defaultIt = defaultMap.begin();
  for (size_t i = 0; i < 2; ++i, ++stIt, ++defaultIt)
    ;
  stMap.erase(stIt);
  defaultMap.erase(defaultIt);
  EXPECT_EQ(stMap.size(), defaultMap.size());
  stIt = stMap.begin();
  defaultIt = defaultMap.begin();
  for (; stIt != stMap.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE((*stIt).first == (*defaultIt).first);
    EXPECT_TRUE((*stIt).second == (*defaultIt).second);
  }
}

TEST(map, SwapMap) {
  st::map<int, int> stMap({{1, 1}});
  st::map<int, int> stSwapMap({{3, 3}, {4, 4}});

  stMap.swap(stSwapMap);
  EXPECT_EQ(stMap.size(), 2);
  EXPECT_EQ(stSwapMap.size(), 1);
  auto x = stMap.begin();
  auto y = stSwapMap.begin();
  EXPECT_EQ((*x).first, 3);
  EXPECT_EQ((*y).first, 1);
}

TEST(map, MergeMap) {
  st::map<int, int> stMap({{1, 1}, {4, 4}, {2, 2}});
  st::map<int, int> stMapMerge({{3, 3}, {4, 4}});

  std::map<int, int> defaultMap({{1, 1}, {4, 4}, {2, 2}});
  std::map<int, int> defaultMapMerge({{3, 3}, {4, 4}});

  stMap.merge(stMapMerge);
  defaultMap.merge(defaultMapMerge);

  EXPECT_EQ(stMap.size(), defaultMap.size());
  EXPECT_EQ(stMapMerge.size(), defaultMapMerge.size());

  auto stIt = stMap.begin();
  auto defaultIt = defaultMap.begin();
  for (; stIt != stMap.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE((*stIt).first == (*defaultIt).first);
    EXPECT_TRUE((*stIt).second == (*defaultIt).second);
  }
  EXPECT_TRUE(stMapMerge.contains(4));
  EXPECT_FALSE(stMapMerge.contains(3));
}

TEST(map, ConstBegin) {
  const st::map<int, int> stMap({{1, 2}, {3, 4}, {5, 6}});
  auto stIt = stMap.begin();
  EXPECT_EQ((*stIt).first, 1);
  EXPECT_EQ((*stIt).second, 2);
  ++stIt;
  ++stIt;
  EXPECT_EQ((*stIt).first, 5);
  EXPECT_EQ((*stIt).second, 6);
  --stIt;
  EXPECT_EQ((*stIt).first, 3);
  EXPECT_EQ((*stIt).second, 4);
}

TEST(map, OperatorCopy) {
  const st::map<int, int> m1({{9, 10}, {7, 8}, {5, 6}, {3, 4}, {1, 2}});
  st::map<int, int> m2;
  m2 = m1;
  auto stIt = m2.begin();
  EXPECT_EQ((*stIt).first, 1);
  EXPECT_EQ((*stIt).second, 2);
  ++stIt;
  ++stIt;
  EXPECT_EQ((*stIt).first, 5);
  EXPECT_EQ((*stIt).second, 6);
  --stIt;
  EXPECT_EQ((*stIt).first, 3);
  EXPECT_EQ((*stIt).second, 4);
  --stIt;
  EXPECT_EQ((*stIt).first, 1);
  EXPECT_EQ((*stIt).second, 2);
  auto stIt2 = m1.begin();
  EXPECT_EQ((*stIt2).first, 1);
  EXPECT_EQ((*stIt2).second, 2);
  ++stIt2;
  ++stIt2;
  EXPECT_EQ((*stIt2).first, 5);
  EXPECT_EQ((*stIt2).second, 6);
  --stIt2;
  EXPECT_EQ((*stIt2).first, 3);
  EXPECT_EQ((*stIt2).second, 4);
  --stIt2;
  EXPECT_EQ((*stIt2).first, 1);
  EXPECT_EQ((*stIt2).second, 2);
}

TEST(map, OperatorMove) {
  st::map<int, int> m1({{9, 10}, {7, 8}, {5, 6}, {3, 4}, {1, 2}});
  st::map<int, int> m2;
  m2 = std::move(m1);
  auto it1 = m2.begin();
  EXPECT_EQ((*it1).first, 1);
  EXPECT_EQ((*it1).second, 2);
  ++it1;
  ++it1;
  EXPECT_EQ((*it1).first, 5);
  EXPECT_EQ((*it1).second, 6);
  --it1;
  EXPECT_EQ((*it1).first, 3);
  EXPECT_EQ((*it1).second, 4);
  --it1;
  EXPECT_EQ((*it1).first, 1);
  EXPECT_EQ((*it1).second, 2);

  EXPECT_EQ(m1.size(), 0);
}

TEST(map, Find) {
  st::map<int, int> m1({{1, 2}, {3, 4}, {5, 6}});
  auto itEnd = m1.end();
  auto itAns = m1.begin();
  ++itAns;
  auto it1 = m1.find(3);
  EXPECT_FALSE(it1 == itEnd);
  EXPECT_TRUE(it1 == itAns);
  it1 = m1.find(6);
  EXPECT_TRUE(it1 == itEnd);
}

TEST(map, ConstFind) {
  const st::map<int, int> m1({{1, 2}, {3, 4}, {5, 6}});
  auto itEnd = m1.end();
  auto itAns = m1.begin();
  ++itAns;
  auto it1 = m1.find(3);
  EXPECT_FALSE(it1 == itEnd);
  EXPECT_TRUE(it1 == itAns);
  it1 = m1.find(6);
  EXPECT_TRUE(it1 == itEnd);
}

TEST(map, OperatorBracket) {
  st::map<int, int> m1({{3, 4}, {5, 6}, {1, 2}});
  m1[8] = 80;
  EXPECT_EQ((*(m1.find(8))).second, 80);
}

TEST(map, MaxSize) {
  st::map<int, int> m1({{v1, 2}, {v3, 4}, {v5, 6}});
  st::map<int, int> m2({{v1, 2}, {v3, 4}, {v5, 6}});
  EXPECT_EQ(m1.max_size(), m2.max_size());
}

TEST(map, InsertMany) {
  st::map<int, int> m1({{3, 30}, {5, 50}, {1, 10}});
  m1.insert_many(std::make_pair(2, 20), std::make_pair(4, 40));
  EXPECT_EQ(m1.contains(2), true);
  EXPECT_EQ(m1.contains(4), true);
}

template class st::set<int>;

TEST(set, ConstructorDefaultSet) {
  st::set<int> stEmptySet;
  std::set<int> defaultEmptySet;
  EXPECT_EQ(stEmptySet.empty(), defaultEmptySet.empty());
}

TEST(set, ConstructorInitializerSet) {
  st::set<int> stSet({'q', 'w', 'e', 'r'});
  std::set<int> defaultSet({'q', 'w', 'e', 'r'});
  EXPECT_EQ(stSet.size(), defaultSet.size());
  auto stIt = stSet.begin();
  auto defaultIt = defaultSet.begin();
  for (; stIt != stSet.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE(*defaultIt == *stIt);
  }
}

TEST(set, ConstructorInitializer2Set) {
  st::set<int> stSet = {};
  std::set<int> defaultSet = {};
  EXPECT_EQ(stSet.size(), defaultSet.size());
  auto stIt = stSet.begin();
  auto defaultIt = defaultSet.begin();
  for (; stIt != stSet.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE(*defaultIt == *stIt);
  }
}

TEST(set, ConstructorCopySet) {
  const st::set<int> stSet({v1, v2, v3, v4, v5});
  const std::set<int> defaultSet({v1, v2, v3, v4, v5});
  st::set<int> stSetCopy = stSet;
  std::set<int> defaultSetCopy = defaultSet;
  EXPECT_EQ(stSetCopy.size(), defaultSetCopy.size());
  auto stIt = stSetCopy.begin();
  auto defaultIt = defaultSetCopy.begin();
  for (; stIt != stSetCopy.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE(*defaultIt == *stIt);
  }
}

TEST(set, OperatorCopySet) {
  const st::set<int> stSet({1, 2, 3, 4, 5});
  const std::set<int> defaultSet({1, 2, 3, 4, 5});
  st::set<int> stSetCopy;
  std::set<int> defaultSetCopy;
  stSetCopy = stSet;
  defaultSetCopy = defaultSet;
  EXPECT_EQ(stSetCopy.size(), defaultSetCopy.size());
  auto stIt = stSetCopy.begin();
  auto defaultIt = defaultSetCopy.begin();
  for (; stIt != stSetCopy.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE(*defaultIt == *stIt);
  }
}

TEST(set, ConstructorMoveSet) {
  st::set<int> stSet({1, 2, 3, 4, 5});
  std::set<int> defaultSet({1, 2, 3, 4, 5});
  st::set<int> stSetCopy = std::move(stSet);
  std::set<int> defaultSetCopy = std::move(defaultSet);
  EXPECT_EQ(stSet.size(), defaultSet.size());
  EXPECT_EQ(stSetCopy.size(), defaultSetCopy.size());
  auto stIt = stSetCopy.begin();
  auto defaultIt = defaultSetCopy.begin();
  for (; stIt != stSetCopy.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE(*defaultIt == *stIt);
  }
}

TEST(set, OperatorMoveSet) {
  st::set<int> stSet({1, 2, 3, 4, 5});
  std::set<int> defaultSet({1, 2, 3, 4, 5});
  st::set<int> stSetCopy;
  std::set<int> defaultSetCopy;
  stSetCopy = std::move(stSet);
  defaultSetCopy = std::move(defaultSet);
  EXPECT_EQ(stSet.size(), defaultSet.size());
  EXPECT_EQ(stSetCopy.size(), defaultSetCopy.size());
  auto stIt = stSetCopy.begin();
  auto defaultIt = defaultSetCopy.begin();
  for (; stIt != stSetCopy.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE(*defaultIt == *stIt);
  }
}

TEST(set, SetIteratorsSet) {
  st::set<int> stSet({1, 2, 3, 4, 5});
  std::set<int> defaultSet({1, 2, 3, 4, 5});
  auto stIt = stSet.begin();
  auto defaultIt = defaultSet.begin();
  EXPECT_TRUE(*defaultIt == *stIt);
}

TEST(set, CapacitySet) {
  st::set<int> stEmptySet;
  std::set<int> defaultEmptySet;
  EXPECT_EQ(stEmptySet.empty(), defaultEmptySet.empty());
  EXPECT_EQ(stEmptySet.size(), defaultEmptySet.size());
  stEmptySet.insert('b');
  defaultEmptySet.insert('c');
  EXPECT_EQ(stEmptySet.empty(), defaultEmptySet.empty());
  EXPECT_EQ(stEmptySet.size(), defaultEmptySet.size());
}

TEST(set, ClearSet) {
  st::set<int> stEmptySet;
  std::set<int> defaultEmptySet;
  stEmptySet.clear();
  defaultEmptySet.clear();
  EXPECT_EQ(stEmptySet.empty(), defaultEmptySet.empty());
  EXPECT_EQ(stEmptySet.size(), defaultEmptySet.size());
  stEmptySet.insert('a');
  defaultEmptySet.insert('b');
  EXPECT_EQ(stEmptySet.empty(), defaultEmptySet.empty());
  EXPECT_EQ(stEmptySet.size(), defaultEmptySet.size());
  stEmptySet.clear();
  defaultEmptySet.clear();
  EXPECT_EQ(stEmptySet.empty(), defaultEmptySet.empty());
  EXPECT_EQ(stEmptySet.size(), defaultEmptySet.size());
}

TEST(set, InsertSet) {
  st::set<int> stSet({1, 2, 3, 4, 5});
  std::set<int> defaultSet({1, 2, 3, 4, 5});
  auto stPr = stSet.insert(6);
  auto defaultPr = defaultSet.insert(6);
  EXPECT_TRUE(stPr.second == defaultPr.second);
  EXPECT_TRUE(*stPr.first == *defaultPr.first);
  stPr = stSet.insert(7);
  defaultPr = defaultSet.insert(7);
  EXPECT_TRUE(stPr.second == defaultPr.second);
  EXPECT_TRUE(*stPr.first == *defaultPr.first);
}

TEST(set, EraseSet) {
  st::set<int> stSet({5, 4, 3, 2, 7, 8, 9});
  std::set<int> defaultSet({5, 4, 3, 2, 7, 8, 9});
  auto size = stSet.size();
  stSet.erase(stSet.end());
  auto new_size = stSet.size();
  EXPECT_EQ(size, new_size);
  stSet.erase(stSet.begin());
  defaultSet.erase(defaultSet.begin());
  auto stIt = stSet.begin();
  auto defaultIt = defaultSet.begin();
  for (; stIt != stSet.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE(*defaultIt == *stIt);
  }
}

TEST(set, SwapSet) {
  st::set<int> stSet({1});
  st::set<int> stSwapSet({3, 4, 5});

  stSet.swap(stSwapSet);
  EXPECT_EQ(stSet.size(), 3);
  EXPECT_EQ(stSwapSet.size(), 1);
  auto stSetIt = stSet.begin();
  auto stSwapSet_it = stSwapSet.begin();
  EXPECT_EQ(*stSetIt, 3);
  EXPECT_EQ(*stSwapSet_it, 1);
}

TEST(set, MergeSet) {
  st::set<int> stSet({1});
  st::set<int> stMergeSet({3, 4, 5});
  stSet.merge(stMergeSet);

  std::set<int> defaultSet({1});
  std::set<int> defaultMergeSet({3, 4, 5});
  defaultSet.merge(defaultMergeSet);
  auto stIt = stSet.begin();
  auto defaultIt = defaultSet.begin();
  for (; stIt != stSet.end(); ++stIt, ++defaultIt) {
    EXPECT_TRUE(*defaultIt == *stIt);
  }
  EXPECT_EQ(defaultSet.size(), stSet.size());
  EXPECT_EQ(stMergeSet.size(), defaultMergeSet.size());
}

TEST(set, FindSet) {
  st::set<int> stSet({1, 2, 3, 4, 5});
  std::set<int> defaultSet({1, 2, 3, 4, 5});
  auto stIt = stSet.find(4);
  auto defaultIt = defaultSet.find(4);
  EXPECT_TRUE(*defaultIt == *stIt);
}

TEST(set, ContainsSet) {
  st::set<int> stSet({1, 2, 3, 4, 5});
  EXPECT_FALSE(stSet.contains(8));
  EXPECT_TRUE(stSet.contains(2));
}

TEST(set, Find) {
  st::set<int> s1({1, 2, 3});
  auto itEnd = s1.end();
  auto itAns = s1.begin();
  ++itAns;
  auto it1 = s1.find(2);
  EXPECT_FALSE(it1 == itEnd);
  EXPECT_TRUE(it1 == itAns);
  it1 = s1.find(6);
  EXPECT_TRUE(it1 == itEnd);
}

TEST(set, ConstFind) {
  const st::set<int> s1({1, 2, 3});
  auto itEnd = s1.end();
  auto itAns = s1.begin();
  ++itAns;
  auto it1 = s1.find(2);
  EXPECT_FALSE(it1 == itEnd);
  EXPECT_TRUE(it1 == itAns);
  it1 = s1.find(6);
  EXPECT_TRUE(it1 == itEnd);
}

TEST(set, MaxSize) {
  st::set<int> s1({1, 2, 3});
  st::set<int> s2({1, 2, 3});
  EXPECT_EQ(s1.max_size(), s2.max_size());
}

TEST(set, InsertMany) {
  st::set<int> s1({1, 2, 3});
  s1.insert_many(4, 5, 6);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
  EXPECT_TRUE(s1.contains(6));
}

template class st::multiset<int>;

TEST(multiset, ConstructorDefaultSet) {
  st::multiset<int> stEmptySet;
  std::multiset<int> defaultEmptySet;
  EXPECT_EQ(stEmptySet.empty(), defaultEmptySet.empty());
}

TEST(multiset, ConstructorInitializerSet) {
  st::multiset<int> stSet({2, 2, 2, 9, 9, 8, 7, 7, 7, 6});
  std::multiset<int> defaultSet({2, 2, 2, 9, 9, 8, 7, 7, 7, 6});
  EXPECT_EQ(stSet.size(), defaultSet.size());
  auto stIt = stSet.begin();
  auto defaultIt = defaultSet.begin();
  for (size_t i = 0, n = defaultSet.size(); i < n; ++i, ++stIt, ++defaultIt) {
    EXPECT_TRUE(*defaultIt == *stIt);
  }
}

TEST(multiset, ConstructorInitializer2Set) {
  st::multiset<int> stSet = {};
  std::multiset<int> defaultSet = {};
  EXPECT_EQ(stSet.size(), defaultSet.size());
  auto stIt = stSet.begin();
  auto defaultIt = defaultSet.begin();
  for (size_t i = 0, n = defaultSet.size(); i < n; ++i, ++stIt, ++defaultIt) {
    EXPECT_TRUE(*defaultIt == *stIt);
  }
}

TEST(multiset, ConstructorCopySet) {
  const st::multiset<int> stSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  const std::multiset<int> defaultSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  st::multiset<int> stSetCopy = stSet;
  std::multiset<int> defaultSetCopy = defaultSet;
  EXPECT_EQ(stSetCopy.size(), defaultSetCopy.size());
  auto stIt = stSetCopy.begin();
  auto defaultIt = defaultSetCopy.begin();
  for (size_t i = 0, n = defaultSet.size(); i < n; ++i, ++stIt, ++defaultIt) {
    EXPECT_TRUE(*defaultIt == *stIt);
  }
}

TEST(multiset, OperatorCopySet) {
  const st::multiset<int> stSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  const std::multiset<int> defaultSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  st::multiset<int> stSetCopy;
  std::multiset<int> defaultSetCopy;
  stSetCopy = stSet;
  defaultSetCopy = defaultSet;
  EXPECT_EQ(stSetCopy.size(), defaultSetCopy.size());
  auto stIt = stSetCopy.begin();
  auto defaultIt = defaultSetCopy.begin();
  for (size_t i = 0, n = defaultSet.size(); i < n; ++i, ++stIt, ++defaultIt) {
    EXPECT_TRUE(*defaultIt == *stIt);
  }
}

TEST(multiset, ConstructorMoveSet) {
  st::multiset<int> stSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> defaultSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  st::multiset<int> stSetCopy = std::move(stSet);
  std::multiset<int> defaultSetCopy = std::move(defaultSet);
  EXPECT_EQ(stSet.size(), defaultSet.size());
  EXPECT_EQ(stSetCopy.size(), defaultSetCopy.size());
  auto stIt = stSetCopy.begin();
  auto defaultIt = defaultSetCopy.begin();
  for (size_t i = 0, n = defaultSetCopy.size(); i < n;
       ++i, ++stIt, ++defaultIt) {
    EXPECT_TRUE(*defaultIt == *stIt);
  }
}

TEST(multiset, OperatorMoveSet) {
  st::multiset<int> stSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> defaultSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  st::multiset<int> stSetCopy;
  std::multiset<int> defaultSetCopy;
  stSetCopy = std::move(stSet);
  defaultSetCopy = std::move(defaultSet);
  EXPECT_EQ(stSet.size(), defaultSet.size());
  EXPECT_EQ(stSetCopy.size(), defaultSetCopy.size());
  auto stIt = stSetCopy.begin();
  auto defaultIt = defaultSetCopy.begin();
  for (size_t i = 0, n = defaultSetCopy.size(); i < n;
       ++i, ++stIt, ++defaultIt) {
    EXPECT_TRUE(*defaultIt == *stIt);
  }
}

TEST(multiset, SetIteratorsSet) {
  st::multiset<int> stSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> defaultSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto stIt = stSet.begin();
  auto defaultIt = defaultSet.begin();
  EXPECT_TRUE(*defaultIt == *stIt);
}

TEST(multiset, CapacitySet) {
  st::multiset<int> stEmptySet;
  std::multiset<int> defaultEmptySet;
  EXPECT_EQ(stEmptySet.empty(), defaultEmptySet.empty());
  EXPECT_EQ(stEmptySet.size(), defaultEmptySet.size());
  stEmptySet.insert('b');
  defaultEmptySet.insert('c');
  EXPECT_EQ(stEmptySet.empty(), defaultEmptySet.empty());
  EXPECT_EQ(stEmptySet.size(), defaultEmptySet.size());
}

TEST(multiset, ClearSet) {
  st::multiset<int> stEmptySet;
  std::multiset<int> defaultEmptySet;
  stEmptySet.clear();
  defaultEmptySet.clear();
  EXPECT_EQ(stEmptySet.empty(), defaultEmptySet.empty());
  EXPECT_EQ(stEmptySet.size(), defaultEmptySet.size());
  stEmptySet.insert('a');
  defaultEmptySet.insert('b');
  EXPECT_EQ(stEmptySet.empty(), defaultEmptySet.empty());
  EXPECT_EQ(stEmptySet.size(), defaultEmptySet.size());
  stEmptySet.clear();
  defaultEmptySet.clear();
  EXPECT_EQ(stEmptySet.empty(), defaultEmptySet.empty());
  EXPECT_EQ(stEmptySet.size(), defaultEmptySet.size());
}

TEST(multiset, InsertSet) {
  st::multiset<int> stSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> defaultSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto stIt = stSet.insert(6);
  auto defaultIt = defaultSet.insert(6);
  EXPECT_TRUE(*stIt == *defaultIt);
  stIt = stSet.insert(7);
  defaultIt = defaultSet.insert(7);
  EXPECT_TRUE(*stIt == *defaultIt);
}

TEST(multiset, EraseSet) {
  st::multiset<int> stSet({5, 5, 4, 4, 4, 3, 2, 2, 7, 7, 7, 8, 9, 9});
  std::multiset<int> defaultSet({5, 5, 4, 4, 4, 3, 2, 2, 7, 7, 7, 8, 9, 9});
  auto size = stSet.size();
  stSet.erase(stSet.end());
  auto new_size = stSet.size();
  EXPECT_EQ(size, new_size);
  auto stIt = stSet.begin();
  auto defaultIt = defaultSet.begin();
  for (size_t i = 0; i < 4; ++i, ++stIt, ++defaultIt)
    ;
  stSet.erase(stIt);
  defaultSet.erase(defaultIt);
  EXPECT_EQ(stSet.size(), defaultSet.size());
  stIt = stSet.begin();
  defaultIt = defaultSet.begin();
  for (size_t i = 0, n = defaultSet.size(); i < n; ++i, ++stIt, ++defaultIt) {
    EXPECT_TRUE(*defaultIt == *stIt);
  }
}

TEST(multiset, SwapSet) {
  st::multiset<int> stSet({1, 1, 1});
  st::multiset<int> stSwapSet({3, 3, 3, 4, 4, 5});

  stSet.swap(stSwapSet);
  EXPECT_EQ(stSet.size(), 6);
  EXPECT_EQ(stSwapSet.size(), 3);
  auto stSetIt = stSet.begin();
  auto stSwapSet_it = stSwapSet.begin();
  EXPECT_EQ(*stSetIt, 3);
  EXPECT_EQ(*stSwapSet_it, 1);
}

TEST(multiset, MergeSet) {
  st::multiset<int> stSet({1, 1, 1});
  st::multiset<int> stMergeSet({3, 3, 3, 4, 4, 5});
  stSet.merge(stMergeSet);

  std::multiset<int> defaultSet({1, 1, 1});
  std::multiset<int> defaultMergeSet({3, 3, 3, 4, 4, 5});
  defaultSet.merge(defaultMergeSet);

  auto stIt = stSet.begin();
  auto defaultIt = defaultSet.begin();
  EXPECT_EQ(stMergeSet.size(), defaultMergeSet.size());
  ASSERT_EQ(defaultSet.size(), stSet.size());
  for (size_t i = 0, n = defaultSet.size(); i < n; ++i, ++stIt, ++defaultIt)
    EXPECT_TRUE(*defaultIt == *stIt);
}

TEST(multiset, FindSet) {
  st::multiset<int> stSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> defaultSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto stIt = stSet.find(4);
  auto defaultIt = defaultSet.find(4);
  EXPECT_TRUE(*defaultIt == *stIt);
}

TEST(multiset, ContainsSet) {
  st::multiset<int> stSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  EXPECT_FALSE(stSet.contains(8));
  EXPECT_TRUE(stSet.contains(2));
}

TEST(multiset, Find) {
  st::multiset<int> s1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itEnd = s1.end();
  auto itAns = s1.begin();
  for (size_t i = 0; i < 4; ++i, ++itAns)
    ;
  auto it1 = s1.find(3);
  EXPECT_FALSE(it1 == itEnd);
  EXPECT_TRUE(it1 == itAns);
  it1 = s1.find(6);
  EXPECT_TRUE(it1 == itEnd);
}

TEST(multiset, ConstFind) {
  const st::multiset<int> s1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itEnd = s1.end();
  auto itAns = s1.begin();
  for (size_t i = 0; i < 4; ++i, ++itAns)
    ;
  auto it1 = s1.find(3);
  EXPECT_FALSE(it1 == itEnd);
  EXPECT_TRUE(it1 == itAns);
  it1 = s1.find(6);
  EXPECT_TRUE(it1 == itEnd);
}

TEST(multiset, Count) {
  st::multiset<int> stSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> defaultSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  EXPECT_EQ(stSet.count(1), defaultSet.count(1));
  EXPECT_EQ(stSet.count(2), defaultSet.count(2));
  EXPECT_EQ(stSet.count(3), defaultSet.count(3));
  EXPECT_EQ(stSet.count(4), defaultSet.count(4));
  EXPECT_EQ(stSet.count(5), defaultSet.count(5));
  EXPECT_EQ(stSet.count(8), defaultSet.count(8));
}

TEST(multiset, EqualRange_1) {
  const st::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto range1 = ms1.equal_range(3);
  auto itAns1 = ms1.begin();
  for (size_t i = 0; i < 4; ++i, ++itAns1)
    ;
  auto itAns2 = ms1.begin();
  for (size_t i = 0; i < 6; ++i, ++itAns2)
    ;
  EXPECT_TRUE(range1.first == itAns1);
  EXPECT_TRUE(range1.second == itAns2);
}

TEST(multiset, EqualRange_2) {
  st::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto range1 = ms1.equal_range(5);
  auto itAns1 = ms1.begin();
  for (size_t i = 0; i < 7; ++i, ++itAns1)
    ;
  EXPECT_TRUE(range1.first == itAns1);
  EXPECT_TRUE(range1.second == ms1.end());
}

TEST(multiset, EqualRange_3) {
  const st::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto range1 = ms1.equal_range(1);
  auto itAns2 = ms1.begin();
  for (size_t i = 0; i < 3; ++i, ++itAns2)
    ;
  EXPECT_TRUE(range1.first == ms1.begin());
  EXPECT_TRUE(range1.second == itAns2);
}

TEST(multiset, LowerBound_1) {
  const st::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itRes = ms1.lower_bound(3);
  auto itAns = ms1.begin();
  for (size_t i = 0; i < 4; ++i, ++itAns)
    ;
  EXPECT_TRUE(itRes == itAns);
}

TEST(multiset, LowerBound_2) {
  st::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itRes = ms1.lower_bound(1);
  auto itAns = ms1.begin();
  EXPECT_TRUE(itRes == itAns);
}

TEST(multiset, UpperBound_1) {
  const st::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itRes = ms1.upper_bound(3);
  auto itAns = ms1.begin();
  for (size_t i = 0; i < 6; ++i, ++itAns)
    ;
  EXPECT_TRUE(itRes == itAns);
}

TEST(multiset, UpperBound_2) {
  st::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itRes = ms1.upper_bound(1);
  auto itAns = ms1.begin();
  for (size_t i = 0; i < 3; ++i, ++itAns)
    ;
  EXPECT_TRUE(itRes == itAns);
}

TEST(multiset, UpperBound_3) {
  st::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itRes = ms1.upper_bound(5);
  auto itAns = ms1.end();
  EXPECT_TRUE(itRes == itAns);
}

TEST(multiset, MaxSize) {
  st::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  st::multiset<int> ms2({1, 1, 1, 2, 3, 3, 4, 5, 5});
  EXPECT_EQ(ms1.max_size(), ms2.max_size());
}

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }