#include <iostream>
#include <gtest/gtest.h>
#include <queue>
#include "../lib/st_queue.h"

using namespace st;
TEST(queue, push_pop) {
	std::queue<char> or_val;

	or_val.push('4');
	or_val.push('9');
	or_val.push('1');

	std::queue<char> or_val2(or_val);
	queue<char> my_val;
	
	my_val.push('4');
	my_val.push('9');
	my_val.push('1');	
	
	queue<char> my_val2(my_val);

	ASSERT_EQ(or_val2.front(), my_val2.front());
	ASSERT_EQ(or_val2.back(), my_val2.back());
	ASSERT_EQ(or_val2.size(), my_val2.size());
}

TEST(queue, move_push) {
	std::queue<int> or_val ({1, 4, 6, 7});
	queue<int> my_val ({1, 4, 6, 7});

	ASSERT_EQ(or_val.front(), my_val.front());
	ASSERT_EQ(or_val.back(), my_val.back());
	ASSERT_EQ(or_val.size(), my_val.size());
	ASSERT_EQ(or_val.empty(), my_val.empty());

	std::queue<int> or_val2 (std::move(or_val));
	queue<int> my_val2 (std::move(my_val));

	or_val2.pop();
	my_val2.pop();

	ASSERT_EQ(or_val2.front(), my_val2.front());
	ASSERT_EQ(or_val2.back(), my_val2.back());
	ASSERT_EQ(or_val2.size(), my_val2.size());
	ASSERT_EQ(or_val2.empty(), my_val2.empty());

	or_val = std::move(or_val2);
	my_val = std::move(my_val2);

	ASSERT_EQ(or_val.front(), my_val.front());
	ASSERT_EQ(or_val.back(), my_val.back());
	ASSERT_EQ(or_val.size(), my_val.size());
	ASSERT_EQ(or_val.empty(), my_val.empty());
}

TEST(queue, swap) {
	std::queue<std::string> or_val ({"hello", " ", "my", " ", "name", " ", "is", " Pupa"});
	queue<std::string> my_val ({"hello", " ", "my", " ", "name", " ", "is", " Pupa"});
	
	ASSERT_EQ(or_val.front(), my_val.front());
	ASSERT_EQ(or_val.back(), my_val.back());
	ASSERT_EQ(or_val.size(), my_val.size());
	ASSERT_EQ(or_val.empty(), my_val.empty());

	std::queue<std::string> or_val2;
	queue<std::string> my_val2;

	or_val2.push("Guuuf");
	my_val2.push("Guuuf");

	or_val.swap(or_val2);
	my_val.swap(my_val2);

	ASSERT_EQ(or_val2.front(), my_val2.front());
	ASSERT_EQ(or_val2.back(), my_val2.back());
	ASSERT_EQ(or_val2.size(), my_val2.size());
	ASSERT_EQ(or_val2.empty(), my_val2.empty());

	ASSERT_EQ(or_val.front(), my_val.front());
	ASSERT_EQ(or_val.back(), my_val.back());
	ASSERT_EQ(or_val.size(), my_val.size());
	ASSERT_EQ(or_val.empty(), my_val.empty());
}

TEST(queue, insert_many_back) {
	std::queue<int> or_val ({1, 4});
	queue<int> my_val ({1, 4});

	or_val.push(6);
	or_val.push(7);
	or_val.push(9);

	my_val.insert_many_back(6, 7, 9);
	
	ASSERT_EQ(or_val.front(), my_val.front());
	ASSERT_EQ(or_val.back(), my_val.back());
	ASSERT_EQ(or_val.size(), my_val.size());
	ASSERT_EQ(or_val.empty(), my_val.empty());
}





