#include <iostream>
#include <gtest/gtest.h>
#include <stack>
#include "../lib/st_stack.h"

using namespace st;
TEST(stack, pop_push) {
	std::stack<int> or_val;
	stack<int> my_val;

	std::stack<int> or_val2 {{5, 9, 2, 11}};
	stack<int> my_val2 {{5, 9, 2, 11}};

	std::stack<int> or_val3(std::move(or_val2));
	stack<int> my_val3(std::move(my_val2));

	std::stack<int> or_val4;
	stack<int> my_val4;

	or_val4 = std::move(or_val3);
	my_val4 = std::move(my_val3);
	
	ASSERT_EQ(or_val4.top(), my_val4.top());
	ASSERT_EQ(or_val4.size(), my_val4.size());

	or_val4.pop();
	my_val4.pop();
	or_val4.pop();
	my_val4.pop();
	or_val4.pop();
	my_val4.pop();

	ASSERT_EQ(or_val4.top(), my_val4.top());

	or_val4.pop();
	my_val4.pop();
	
	ASSERT_EQ(or_val4.empty(), my_val4.empty());
}

TEST(stack, swap) {
	std::stack<char> or_val {{'1', 'a', 'l', 'f'}};
	stack<char> my_val {{'1', 'a', 'l', 'f'}};
	std::stack<char> or_val2 {{'5', '9', '2', '1'}};
	stack<char> my_val2 {{'5', '9', '2', '1'}};

	or_val.swap(or_val2);
	my_val.swap(my_val2);
	

	ASSERT_EQ(or_val.top(), my_val.top());
	ASSERT_EQ(or_val.size(), my_val.size());

	ASSERT_EQ(or_val2.top(), my_val2.top());
	ASSERT_EQ(or_val2.size(), my_val2.size());

	std::stack<char> or_val3 (or_val2);
	stack<char> my_val3 (my_val2);

	ASSERT_EQ(or_val3.top(), my_val2.top());
	ASSERT_EQ(or_val3.size(), my_val2.size());
}

TEST(stack, insert_many_front) {
	std::stack<std::string> or_val {{"hi", " im ", "biba"}};
	stack<std::string> my_val {{"hi", " im ", "biba"}};

	or_val.push(" no ");
	or_val.push(" it ");
	or_val.push(" is you biba ");
	
	my_val.insert_many_front(" no ", " it ", " is you biba ");

	ASSERT_EQ(or_val.top(), my_val.top());
	ASSERT_EQ(or_val.size(), my_val.size());
}

