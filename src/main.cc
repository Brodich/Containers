#include <iostream>
#include <vector>
#include "s21_vector.h"

using std::cin;
using std::cout;
using std::endl;



int main() {
    // std::vector<int> numbers;

    // vector<int> f(5);
    vector<int> v1 {1, 2, 3};
    vector<int> v2;

    v1.print();
    v2 = std::move(v1);
    v2.print();

// std::vector<std::vector<int>> v1{{{{{}}}}}; 
    // std::vector<int> v2(5);
    // std::vector<int> v3({5});
    // std::vector<int> v4{5};


    // const std::type_info& type = typeid(v2);
    // std::cout << type.name() << std::endl;
    
    // numbers.push_back(5);
    // cout << numbers[0];
    // numbers.push_back(8);
    // cout << numbers[1];
    // numbers.push_back(9);
    // cout << numbers[2];
    

    // vector<int> vt = {1, 2, 3, 4};
    
    // cout << vt.size();

}


