#include <iostream>
#include <vector>
#include "s21_vector.h"

using std::cin;
using std::cout;
using std::endl;



int main() {
    // std::vector<int> numbers;

    // vector<int> f(5);
    vector<int> v1 (4);
    v1.reserve(6);

    v1[0] = 3;
    // v1[1] = 2;
    // v1[2] = 49;
    // v1[3] = 58;

    // v1.print();
    // v1.shrink_to_fit();
    auto b = v1.capacity();
    std::cout << "Type of num: " << typeid(b).name() << std::endl;

    cout << b << endl;

    // vector<int>::VectorIterator gh = v1.begin();
    // std::cout << "Type of num: " << typeid(gh).name() << std::endl;
    // cout << *(gh++) << "begin";
    // cout << *(gh) << "begin";



    // 
    std::vector<int> v4 (4);
    v4.reserve(6);
    
    v4[0] = 5;
    v4[1] = 6;
    v4[2] = 7;
    v4[3] = 0;
    // v4.shrink_to_fit();
    

    auto gg = v4.capacity();
    std::cout << "Type of num: " << typeid(gg).name() << std::endl;
    cout << gg << endl;

    cout << endl;

    // std::vector<int>::iterator iter = v4.begin();
    //     std::cout << "Type of num: " << typeid(iter).name() << std::endl;
    // cout << *(iter++) << "begin" << endl;
    // std::vector<int> v6;
    // auto c = v6.front();
    // cout << c;

    // v4.at(3) = 55;
    // auto b = v4.at(3);
    // cout << b;
    // auto a = v4.data();
    // cout << *a;

    // const std::type_info& type = typeid(v2);
    // std::cout << type.name() << std::endl;
    
    

}


