#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include "../lib/st_vector.h"

using namespace st;
TEST(vector, base) {
    vector<int> v1;
    vector<int> v2 {4 , 6 , 7, 89};
    std::vector<int> std_v2 {4 , 6 , 7, 89};
    vector<char> v3 {'4', 'a', 'b', 'l'};
    vector<char> copyv3(v3);

    ASSERT_EQ(v2.max_size(), std_v2.max_size());

    ASSERT_EQ(v1.empty(), 1);
    ASSERT_EQ(v2.empty(), 0);

    ASSERT_EQ(copyv3[0], '4');
    ASSERT_EQ(copyv3[1], 'a');
    ASSERT_EQ(copyv3[2], 'b');
    ASSERT_EQ(copyv3[3], 'l');
    
    char* ptv3 = v3.data();
    vector<char> movev3(std::move(v3));
    char* ptmovev3 = movev3.data();

    ASSERT_EQ(*ptv3, *ptmovev3);

    ASSERT_EQ(movev3[0], '4');
    ASSERT_EQ(movev3[1], 'a');
    ASSERT_EQ(movev3[2], 'b');
    ASSERT_EQ(movev3[3], 'l');
    
    vector<char> new_move(3);
    new_move[1] = 'O';

    new_move = std::move(movev3);

    ASSERT_EQ(new_move[0], '4');
    ASSERT_EQ(new_move[1], 'a');
    ASSERT_EQ(new_move[2], 'b');
    ASSERT_EQ(new_move[3], 'l');
}

TEST(vector, front_back) {
    vector<char> v3 {'4', 'a', 'b', 'l'};
    std::vector<char> std_v3 {'4', 'a', 'b', 'l'};
    vector<int> v5;
    std::vector<int> std_v5;
    vector<unsigned char> v9 {'4', 'a', 'b', 'l'};
    std::vector<unsigned char> std_v9 {'4', 'a', 'b', 'l'};
    vector<bool> v99;
    std::vector<bool> std_v99;

    ASSERT_EQ(v3.front(), '4');
    ASSERT_EQ(v3.back(), 'l');
    ASSERT_EQ(v3.at(2), 'b');
    EXPECT_THROW(v3.at(4), std::out_of_range);

    ASSERT_EQ(*(v3.begin()), '4');
    ASSERT_EQ(*(v3.begin() + 2), 'b');
    ASSERT_EQ(*(v3.end() - 1), 'l');

    EXPECT_EQ(v3.max_size(), std_v3.max_size());
    EXPECT_EQ(v9.max_size(), std_v9.max_size());
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

TEST(vector, insert) {
    vector<int> vec {1, 5, 6, 9};
    std::vector<int> std_vec {1, 5, 6, 9};
    ASSERT_THROW(vec.reserve(-1), std::length_error);
    
    vec.insert(vec.begin(), 44);
    std_vec.insert(std_vec.begin(), 44);

    auto pt = vec.insert(vec.end() - 2, 36);
    auto std_pt = std_vec.insert(std_vec.end() - 2, 36);

    ASSERT_EQ(*pt, *std_pt);

    vec.insert_many(vec.begin(), 4, 5, 9, 9);
    std_vec.insert(std_vec.begin(), 9);
    std_vec.insert(std_vec.begin(), 9);
    std_vec.insert(std_vec.begin(), 5);
    std_vec.insert(std_vec.begin(), 4);

    vec.insert_many_back(2, 7, 35, 75);
    std_vec.insert(std_vec.end(), 2);
    std_vec.insert(std_vec.end(), 7);
    std_vec.insert(std_vec.end(), 35);
    std_vec.insert(std_vec.end(), 75);


    ASSERT_EQ(vec.at(0), std_vec.at(0));
    ASSERT_EQ(vec.at(1), std_vec.at(1));
    ASSERT_EQ(vec.at(2), std_vec.at(2));
    ASSERT_EQ(vec.at(3), std_vec.at(3)); 
    ASSERT_EQ(vec.at(4), std_vec.at(4));
    ASSERT_EQ(vec.at(5), std_vec.at(5));    
    ASSERT_EQ(vec.at(6), std_vec.at(6));
    ASSERT_EQ(vec.at(7), std_vec.at(7)); 
    ASSERT_EQ(vec.at(8), std_vec.at(8));
    ASSERT_EQ(vec.at(9), std_vec.at(9));
    ASSERT_EQ(vec.at(10), std_vec.at(10));
    ASSERT_EQ(vec.at(11), std_vec.at(11)); 
    ASSERT_EQ(vec.at(12), std_vec.at(12));
    ASSERT_EQ(vec.at(13), std_vec.at(13));

    ASSERT_EQ(vec.size(), std_vec.size());
    ASSERT_EQ(vec.capacity(), std_vec.capacity());

    vec.clear();
    std_vec.clear();

    ASSERT_EQ(vec.size(), std_vec.size());
    ASSERT_EQ(vec.capacity(), std_vec.capacity());
}

TEST(vector, push_pop) {
    vector<int> vec {1, 5, 6, 9};
    vec.reserve(5);
    std::vector<int> std_vec {1, 5, 6, 9};
    std_vec.reserve(5);


    vec.push_back(34);
    vec.push_back(11);
    std_vec.push_back(34);
    std_vec.push_back(11);

    ASSERT_EQ(vec.at(0), std_vec.at(0));
    ASSERT_EQ(vec.at(1), std_vec.at(1));
    ASSERT_EQ(vec.at(2), std_vec.at(2));
    ASSERT_EQ(vec.at(3), std_vec.at(3)); 
    ASSERT_EQ(vec.at(4), std_vec.at(4));
    ASSERT_EQ(vec.at(5), std_vec.at(5));

    ASSERT_EQ(vec.size(), std_vec.size());
    ASSERT_EQ(vec.capacity(), std_vec.capacity());

    vec.pop_back();
    vec.pop_back();
    std_vec.pop_back();
    std_vec.pop_back();

    ASSERT_EQ(vec.at(0), std_vec.at(0));
    ASSERT_EQ(vec.at(1), std_vec.at(1));
    ASSERT_EQ(vec.at(2), std_vec.at(2));
    ASSERT_EQ(vec.at(3), std_vec.at(3)); 
    ASSERT_EQ(vec.size(), std_vec.size());
    ASSERT_EQ(vec.capacity(), std_vec.capacity());

}

TEST(vector, erase_swap) {
    vector<int> vec {1, 5, 6, 9};
    vec.reserve(5);
    std::vector<int> std_vec {1, 5, 6, 9};
    std_vec.reserve(5);


    vec.erase(vec.begin() + 1);
    std_vec.erase(std_vec.begin() + 1);

    ASSERT_EQ(vec.at(0), std_vec.at(0));
    ASSERT_EQ(vec.at(1), std_vec.at(1));
    ASSERT_EQ(vec.at(2), std_vec.at(2));
    
    ASSERT_EQ(vec.size(), std_vec.size());
    ASSERT_EQ(vec.capacity(), std_vec.capacity());


    vector<int> vec_copy {32, 1, 7};
    std::vector<int> std_copy {32, 1, 7};

    vec.swap(vec_copy);
    std_vec.swap(std_copy);

    ASSERT_EQ(vec.at(0), std_vec.at(0));
    ASSERT_EQ(vec.at(1), std_vec.at(1));
    ASSERT_EQ(vec.at(2), std_vec.at(2));
    
    ASSERT_EQ(vec.size(), std_vec.size());
    ASSERT_EQ(vec.capacity(), std_vec.capacity());

    ASSERT_EQ(vec_copy.at(0), std_copy.at(0));
    ASSERT_EQ(vec_copy.at(1), std_copy.at(1));
    ASSERT_EQ(vec_copy.at(2), std_copy.at(2));
    
    ASSERT_EQ(vec_copy.size(), std_copy.size());
    ASSERT_EQ(vec_copy.capacity(), std_copy.capacity());

}
