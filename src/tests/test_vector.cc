#include <gtest/gtest.h>
#include <vector>
#include "../s21_vector.h"

TEST(vector, base) {
    vector<int> v1;
    vector<int> v2(5);
    vector<char> v3 {'4', 'a', 'b', 'l'};

    
}

TEST(vector, reserve_and_shrink) {
    vector<int> v1(6);
    v1.reserve(8);
    v1[0] = 5;
    ASSERT_EQ(v1.capacity(), 8);
    ASSERT_EQ(v1.size(), 6);

    v1.shrink_to_fit();
    ASSERT_EQ(v1.capacity(), 6);
    ASSERT_EQ(v1.size(), 6);
}



int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}