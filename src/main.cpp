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
    // v1.reserve(6);

    v1[0] = 3;
    v1[1] = 2;
    v1[2] = 49;
    // v1[3] = 58;
    v1.print();
    auto tt = v1.capacity();
    cout << tt << endl;

    auto jj = v1.size();
    cout << jj << endl;
    cout << "beg" << v1.begin() << endl;
    cout << "end" << (v1.end()-4) << endl;
    v1.insert(v1.end(), 69);
    // v1.pop_back();
    // v1.pop_back();
    // v1.pop_back();
    // v1.push_back(87);

    v1.print();

    auto hh = v1.capacity();
    cout << hh << endl;

    auto rr = v1.size();
    cout << rr << endl;

    // auto ww = v1.end();
    // cout << *(ww ) << endl;

    cout << endl;



    cout << "eeeeeeeeee\n";

    // 
    std::vector<int> v4 (4);
    // v4.reserve(6);
    
    v4[0] = 5;
    v4[1] = 6;
    v4[2] = 7;
    for (int i: v4)
        std::cout << i << ' ';
    cout << endl;
    auto gg = v4.capacity();
    cout << gg << endl;

    auto zz = v4.size();
    cout << zz << endl;


    cout << endl;


    std::vector<int>::iterator iter = v4.begin();
    cout << static_cast<void*>(&(*iter))  << " v4 beg\n"; 
    v4.insert(iter, 66);
    iter = v4.begin();
    cout << static_cast<void*>(&(*iter))  << " v4 beg\n"; 

    cout << "insert done\n";
        // v4.pop_back();
        // v4.pop_back();
        // v4.pop_back();
    //     v4.push_back(9);
    //     v4.push_back(9);
    //     v4.push_back(9);
    // v4.clear();

    for (int i: v4)
        std::cout << i << "| ";
    cout << endl;
    auto bb = v4.capacity();
    cout << bb << endl;

    auto aa = v4.size();
    cout << aa << endl;

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


