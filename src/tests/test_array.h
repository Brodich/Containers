#include <iostream>
#include <gtest/gtest.h>
#include <array>
#include "../lib/st_array.h"

using namespace st;
TEST(array, construct) {
	std::array<int, 4> or_val {4, 5, 8, 9};
	std::array<int, 4> or_val2 (std::move(or_val));

	array<int, 4> my_val {4, 5, 8, 9};
	array<int, 4> my_val2(std::move(my_val));
    
    ASSERT_EQ(*my_val.data(), *or_val.data());
    ASSERT_EQ(my_val.empty(), or_val.empty());

    auto it_or = or_val2.begin();
    auto it_my = my_val2.begin();


    for(; it_my != my_val2.end(); it_or++, it_my++) {
        // std::cout << "orval " << *it_or << " myval - " << *it_my << std::endl;
        ASSERT_EQ(*it_or, *it_my);
    } 

    ASSERT_EQ(*my_val2.data(), *or_val2.data());
    ASSERT_EQ(my_val2.empty(), or_val2.empty());
    ASSERT_EQ(my_val2.max_size(), or_val2.max_size());
}

TEST(array, char_test) {
	std::array<char, 4> or_val {'4', '5', '8', '9'};
	std::array<char, 4> or_val2 (or_val);

	array<char, 4> my_val {'4', '5', '8', '9'};
	array<char, 4> my_val2(my_val);


    ASSERT_EQ(my_val.front(), or_val.front());
    ASSERT_EQ(my_val.back(), or_val.back());    
    
    ASSERT_EQ(my_val2.front(), or_val2.front());
    ASSERT_EQ(my_val2.back(), or_val2.back());
    
    
    ASSERT_EQ(*my_val.data(), *or_val.data());
    ASSERT_EQ(my_val.empty(), or_val.empty());
    ASSERT_EQ(my_val.size(), or_val.size());

    ASSERT_EQ(*my_val2.data(), *or_val2.data());
    ASSERT_EQ(my_val2.empty(), or_val2.empty());
    ASSERT_EQ(my_val2.size(), or_val2.size());


    for(long unsigned int i = 0, j = 0; i < or_val.size(); i++, j++) {
        ASSERT_EQ(my_val[i], or_val[j]);
    }

    auto it_or = or_val2.begin();
    auto it_my = my_val2.begin();


    for(; it_or != or_val2.end(); it_or++, it_my++) {
        ASSERT_EQ(*it_or, *it_my);
    } 

}

TEST(array, swap_fill) {
	std::array<std::string, 4> or_val ;
	array<std::string, 4> my_val ;

	std::array<std::string, 4> or_val2 ;
	array<std::string, 4> my_val2 ;


    or_val.at(0) = "Hi";
    or_val.at(1) = " what is ";
    or_val.at(2) = "your";
    or_val.at(3) = " Name?";

    my_val.at(0) = "Hi";
    my_val.at(1) = " what is ";
    my_val.at(2) = "your";
    my_val.at(3) = " Name?";


    or_val2.at(0) = "Pupa";
    or_val2.at(1) = " and ";
    or_val2.at(2) = "Lupa";
    or_val2.at(3) = " go to store";

    my_val2.at(0) = "Pupa";
    my_val2.at(1) = " and ";
    my_val2.at(2) = "Lupa";
    my_val2.at(3) = " go to store";

    or_val.swap(or_val2);
    my_val.swap(my_val2);


    for(long unsigned int i = 0; i < my_val.size(); i++) {
        ASSERT_EQ(or_val.at(i), my_val.at(i));
    }
    for(long unsigned int i = 0; i < my_val2.size(); i++) {
        ASSERT_EQ(or_val2.at(i), my_val2.at(i));
    }

    EXPECT_THROW(my_val.at(4), std::out_of_range);
    EXPECT_THROW(or_val.at(4), std::out_of_range);

    or_val.fill("Pupa");
    my_val.fill("Pupa");
    
    for(long unsigned int i = 0; i < my_val.size(); i++) {
        ASSERT_EQ(or_val.at(i), my_val.at(i));
    }
    // std::cout << *my_val2.cend() << " cbegin\n";
    ASSERT_EQ(*or_val2.cbegin(), *my_val2.cbegin());
    ASSERT_EQ(*(or_val2.cend() - 1), *(my_val2.cend() - 1));


    ASSERT_EQ(*or_val.begin(), *my_val.begin());
    ASSERT_EQ(*(or_val.end() - 1), *(my_val.end() - 1));

	std::array<std::string, 4> or_val3 ;
	array<std::string, 4> my_val3 ;

    or_val3 = std::move(or_val2);
    my_val3 = std::move(my_val2);
    
    for(long unsigned int i = 0; i < my_val3.size(); i++) {
        ASSERT_EQ(or_val3.at(i), my_val3.at(i));
    }


}

