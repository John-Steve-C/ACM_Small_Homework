//
// Created by Leonard C on 2021/12/9.
//

#ifndef SRC_HPP_DEFERCLASS_HPP
#define SRC_HPP_DEFERCLASS_HPP

#include <bits/stdc++.h>
using namespace std;
typedef std::function<void()> funcPointer;
//STL(functional库)中的函数指针
class Defer{
private:
    vector<funcPointer> f_list;//模拟栈

public:
    Defer(funcPointer f){
        f_list.push_back(f);
    }
//    Defer(Defer &&rhs){}
    ~Defer(){
        while (!f_list.empty()){
            f_list.back()();//执行尾部
            f_list.pop_back();//后进先出
        }
    }
    void operator()(const funcPointer &f){
        f_list.push_back(f);
    }

};

#endif //SRC_HPP_DEFERCLASS_HPP
