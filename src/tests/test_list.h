#include <iostream>
#include <gtest/gtest.h>
#include <list>
#include "../lib/st_list.h"

using namespace st;
TEST(list, construct) {
    std::list<int> or_val;
    list<int> i_val;
    ASSERT_EQ(or_val.empty(), i_val.empty());

    std::list<int> or_val2(500);
    list<int> i_val2(500);

    list<int> i_val3 {1, 4, 6, 4, 9};
    list<int> i_val4(i_val2);
    std::list<int> or_val5(std::move(or_val2));
    list<int> i_val5(std::move(i_val2));
    
    ASSERT_EQ(or_val2.empty(), i_val2.empty());
    ASSERT_EQ(*or_val5.begin(), *i_val5.begin());
    ASSERT_EQ(*or_val5.begin(), *i_val5.begin());
    
    i_val4 = std::move(i_val3);
}

TEST(list, insert_erase) {
    std::list<char> or_val3 {'1', '4', '6', '4', '9'};
    list<char> my_val3 {'1', '4', '6', '4', '9'};

    ASSERT_EQ(or_val3.back(), my_val3.back());
    ASSERT_EQ(or_val3.front(), my_val3.front());

    or_val3.pop_back();
    or_val3.pop_front();
    my_val3.pop_back();
    my_val3.pop_front();
    
    auto my_it = my_val3.begin();
    auto or_it = or_val3.begin();
    
    for(; my_it != my_val3.end(); ++my_it, ++or_it) {
        ASSERT_EQ(*my_it, *or_it);
    }

    my_val3.insert(my_val3.begin(), '9');
    or_val3.insert(or_val3.end(), '8');
    my_val3.insert(my_val3.end(), '8');
    or_val3.insert(or_val3.begin(), '9');

    my_val3.push_front('1');
    or_val3.push_front('1');
    
    my_it = my_val3.begin();
    or_it = or_val3.begin();
    
    for(; or_it != or_val3.end(); ++my_it, ++or_it) {
        ASSERT_EQ(*my_it, *or_it);
    }

    list<char> my_val4(std::move(my_val3));
    std::list<char> or_val4(std::move(or_val3));

    my_it = my_val3.begin();
    or_it = or_val3.begin();
    for(; or_it != or_val3.end(); ++my_it, ++or_it) {
        ASSERT_EQ(*my_it, *or_it);
    }
    my_it = my_val4.begin();
    or_it = or_val4.begin();
    for(; or_it != or_val4.end(); ++my_it, ++or_it) {
        ASSERT_EQ(*my_it, *or_it);
    }

    ASSERT_EQ(my_val3.size(), or_val3.size());
    ASSERT_EQ(my_val3.max_size(), or_val3.max_size());
        
    ASSERT_EQ(my_val4.size(), or_val4.size());
    ASSERT_EQ(my_val4.max_size(), or_val4.max_size());
    
    my_val4.clear();
    or_val4.clear();
    
    ASSERT_EQ(my_val4.size(), or_val4.size());
    ASSERT_EQ(my_val4.max_size(), or_val4.max_size());
}

TEST(list, swap) {
    std::list<double> or_val {42, 49, 989, 4.45};
    list<double> my_val {42, 49, 989, 4.45};
    
    std::list<double> or_swap {99, 84, 99, 4.4541};
    list<double> my_swap {99, 84, 99, 4.4541};

    or_val.swap(or_swap);
    my_val.swap(my_swap);

    auto my_it = my_val.begin();
    auto or_it = or_val.begin();
    
    for(; my_it != my_val.end(); ++my_it, ++or_it) {
        ASSERT_EQ(*my_it, *or_it);
    }

    my_it = my_swap.begin();
    or_it = or_swap.begin();
    
    for(; my_it != my_swap.end(); ++my_it, ++or_it) {
        ASSERT_EQ(*my_it, *or_it);
    }
}

TEST(list, merge) {
    std::list<double> or_val {42, 49, 989, 4.45};
    list<double> my_val {42, 49, 989, 4.45};
    
    std::list<double> or_merge {99, 84, 99, 4.4541};
    list<double> my_merge {99, 84, 99, 4.4541};

    or_val.merge(or_merge);
    my_val.merge(my_merge);
    
        // std::cout << or_merge.empty() << "empty" << std::endl;

    auto my_it = my_val.begin();
    auto or_it = or_val.begin();
    for(; my_it != my_val.end(); ++my_it, ++or_it) {
        ASSERT_EQ(*my_it, *or_it);
    }

    my_it = my_merge.begin();
    or_it = or_merge.begin();
    for(; my_it != my_merge.end(); ++my_it, ++or_it) {
        // std::cout << *or_it << std::endl;
        ASSERT_EQ(*my_it, *or_it);
    }

    ASSERT_EQ(my_merge.size(), or_merge.size());
    ASSERT_EQ(my_val.size(), or_val.size());
}

TEST(list, splice) {
    std::list<double> or_val {42, 49, 989, 4.45};
    list<double> my_val {42, 49, 989, 4.45};
    
    std::list<double> or_merge {99, 84, 99, 4.4541};
    list<double> my_merge {99, 84, 99, 4.4541};

    // auto bb = or_val.begin();
    or_val.splice(or_val.cbegin(), or_merge);
    my_val.splice(my_val.cbegin(), my_merge);
    
    // for (auto i : my_val) {
    //     std::cout << i << " i \n";
    // }
    auto my_it = my_val.begin();
    auto or_it = or_val.begin();
    for(; my_it != my_val.end(); ++my_it, ++or_it) {
        ASSERT_EQ(*my_it, *or_it);
    }

    my_it = my_merge.begin();
    or_it = or_merge.begin();
    for(; my_it != my_merge.end(); ++my_it, ++or_it) {
        // std::cout << *or_it << std::endl;
        ASSERT_EQ(*my_it, *or_it);
    }

    ASSERT_EQ(my_merge.size(), or_merge.size());
    ASSERT_EQ(my_val.size(), or_val.size());
}

TEST(list, reverse) {
	std::list<std::string> or_val  {"hi", " ", "my", " ", "name", " ", "is", " ", "George" };
	list<std::string> my_val  {"hi", " ", "my", " ", "name", " ", "is", " ", "George" };

    or_val.reverse();
    my_val.reverse();

    auto my_it = my_val.begin();
    auto or_it = or_val.begin();
    for(; my_it != my_val.end(); ++my_it, ++or_it) {
        ASSERT_EQ(*my_it, *or_it);
    }
}

TEST(list, unique) {
    std::list<double> or_val {11, 11, 11, 2, 3, 2, 4, 4, 4, 4, 8};
    list<double> my_val {11, 11, 11, 2, 3, 2, 4, 4, 4, 4, 8};

    or_val.unique();
    my_val.unique();

    auto my_it = my_val.begin();
    auto or_it = or_val.begin();

    for(; my_it != my_val.end(); ++my_it, ++or_it) {
        ASSERT_EQ(*my_it, *or_it);
    }
}

TEST(list, sort1) {
    std::list<double> or_val {11.53, 11.53, 11.53, 2, 3, 2, 4, 4, 4, 4, 8, 11.53};
    list<double> my_val {11.53, 11.53, 11.53, 2, 3, 2, 4, 4, 4, 4, 8, 11.53};

    or_val.sort();
    my_val.sort();

    auto my_it = my_val.begin();
    auto or_it = or_val.begin();
    for(; my_it != my_val.end(); ++my_it, ++or_it) {
        ASSERT_EQ(*my_it, *or_it);
    }
}

TEST(list, sort2) {
    std::list<std::string> or_val {"hi", " ", "my", " ", "name", " ", "is", " ", "George" };
    list<std::string> my_val {"hi", " ", "my", " ", "name", " ", "is", " ", "George" };

    or_val.sort();
    my_val.sort();

    auto my_it = my_val.begin();
    auto or_it = or_val.begin();
    for(; my_it != my_val.end(); ++my_it, ++or_it) {
        ASSERT_EQ(*my_it, *or_it);
    }
}

TEST(list, insert_many_front) {
    std::list<int> or_val {42, 49, 989};
    list<int> my_val {42, 49, 989};

    std::list<int> or_merge {99, 84, 9941};
    list<int> my_merge {99, 84, 9941};

    or_val.splice(or_val.begin(), or_merge);
    my_val.insert_many_front(99, 84, 9941);

    // for (auto i : my_val) {
    //     std::cout << i << " i\n";
    // }
    auto my_it = my_val.begin();
    auto or_it = or_val.begin();
    for(; my_it != my_val.end(); ++my_it, ++or_it) {
        ASSERT_EQ(*my_it, *or_it);
    }

    ASSERT_EQ(my_val.size(), or_val.size());
}

TEST(list, insert_many_back) {
    std::list<int> or_val {42, 49, 989};
    list<int> my_val {42, 49, 989};

    std::list<int> or_merge {99, 84, 9941};
    list<int> my_merge {99, 84, 9941};

    or_val.splice(or_val.end(), or_merge);
    my_val.insert_many_back(99, 84, 9941);

    auto my_it = my_val.begin();
    auto or_it = or_val.begin();
    for(; my_it != my_val.end(); ++my_it, ++or_it) {
        ASSERT_EQ(*my_it, *or_it);
    }

    ASSERT_EQ(my_val.size(), or_val.size());
}

TEST(list, insert_many) {
    std::list<int> or_val {42, 49, 989};
    list<int> my_val {42, 49, 989};

    std::list<int> or_merge {99, 84, 9941};
    list<int> my_merge {99, 84, 9941};

    or_val.splice(++or_val.begin(), or_merge);
    my_val.insert_many(++my_val.begin(), 99, 84, 9941);

    auto my_it = my_val.begin();
    auto or_it = or_val.begin();
    for(; my_it != my_val.end(); ++my_it, ++or_it) {
        ASSERT_EQ(*my_it, *or_it);
    }

    ASSERT_EQ(my_val.size(), or_val.size());
}




