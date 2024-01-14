#include "s21_containers.h"
#include "s21_list.h"
int main() {

	std::cout << "Hello world\n";
	// std::list<char> numbers[7];
	// std::list<char> numbers(7);
    std::list<int> asa;
	std::list<char> numbers {'9', '2', '3', '4', '5', '8'};


    s21_list<int> ican(5);
    // ican.element[2] = 3;
    std::cout << ican.element;

	// int first {numbers.front() };
	// int last {numbers.back() };

	// int b = numbers.back();

	// std::cout << first << std::endl;
	// std::cout << last << std::endl;
	
	for (std::_List_iterator<int> iter = asa.begin(); iter != asa.end(); iter++) {
	// for (auto iter = numbers.begin(); iter != numbers.end(); iter++) {
		std::cout << *iter << std::endl;
	}


}

