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
    vector<int> v2 (4);
    // v1.reserve(6);

    v1[0] = 3;
    v1[1] = 2;
    v1[2] = 49;    
    
    v2[0] = 13;
    v2[1] = 12;
    v2[2] = 149;

    // v1[3] = 58;
    // auto my_iter = v1.begin();
    // cout << my_iter << "my iter\n";
    // auto my_iter2 = v2.begin();
    // cout << my_iter2 << "my iter2\n";

    // v1.print();
    // auto tt = v1.capacity();
    // cout << tt << endl;

    // auto jj = v1.size();
    // cout << jj << endl;

    // v1.swap(v2);

    //  my_iter = v1.begin();
    // cout << my_iter << "my iter\n";
    //  my_iter2 = v2.begin();
    // cout << my_iter2 << "my iter2\n";

    // v1.pop_back();
    // v1.pop_back();
    // v1.pop_back();
    // v1.push_back(87);
    auto hh = v1.capacity();
    cout << hh << endl;

    auto rr = v1.size();
    cout << rr << endl;

    vector<int>::iterator itz = v1.begin();
        std::cout << "Type of num: " << typeid(itz).name() << std::endl;
    v1.print();
    auto it = v1.insert_many(v1.begin(), 8, 9, 10, 12, 55);
    cout << *it << " it\n";



    cout << endl;

// Expected equality of these values:
//   v99.max_size()
//     Which is: 9223372036854775807
//   std_v99.max_size()
//     Which is: 9223372036854775744

    cout << "eeeeeeeeee\n";

    // 
    std::vector<int> v4 (3);
    std::vector<char> v45 {'f'};
    cout << v45.max_size() << endl;
    v4.reserve(6);
    v4[0] = 5;
    v4[1] = 6;
    v4[2] = 7;
    v4[5] = 9;
    std::vector<int> cpv4 (2);
    cpv4[0] = 44;
    cpv4 = std::move(v4);
    // cout << v4.data() << "data\n";
    for (int i: v4)
        std::cout << i << ' ';
    cout << endl;
    auto gg = v4.capacity();
    cout << gg << endl;
    auto zz = v4.size();
    cout << zz << endl;


    for (int i: cpv4)
        std::cout << i << ' ';
    cout << endl;
    cout << cpv4[5] << "ctpv4\n";
    auto mm = cpv4.capacity();
    cout << mm << endl;

    auto nn = cpv4.size();
    cout << nn << endl;



    cout << endl;


    auto iter = v4.insert(v4.end(), 99);
    cout << *iter << "iter\n";
        // v4.pop_back();
        // v4.pop_back();
        // v4.pop_back();
    //     v4.push_back(9);
    //     v4.push_back(9);
    //     v4.push_back(9);
    // v4.clear();
    
    // v4.insert_many_back(4);
    for (int i: v4)
        std::cout << i << "| ";
    cout << endl;


    auto bb = v4.capacity();
    cout << bb << endl;

    auto aa = v4.size();
    cout << aa << endl;

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


