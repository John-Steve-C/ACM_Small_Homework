//
// Created by Leonard C on 2021/11/15.
//

#include "src.hpp"
#include <iostream>
using namespace std;

int main(){
    BigIndexArray a;
//    a[-80] = 123; a[99] = 1;
//    cout << a[-80] << ' '<< a[99] <<endl;
    a[-922337203685477580] = 9223372036854775807;
    cout << a[-922337203685477580] << endl;

}
/*The contents of src.cpp
#ifndef SRC_HPP_SRC_HPP
#define SRC_HPP_SRC_HPP

#include <unordered_map>

using namespace std;

class BigIndexArray {
private:
    unordered_map<long long, long long> num;
//    static const long long len = 230584300921369395;
    // 922337203685477580/4,分成四段

public:
    BigIndexArray() {

    }

    long long &operator[](long long index) {
//        long long cnt,k;
        if (num.find(index) == num.end())//找不到才要初始化
            num.insert(pair<long long, long long>(index, 0));

        return num.at(index);
    }

};


#endif //SRC_HPP_SRC_HPP
*/