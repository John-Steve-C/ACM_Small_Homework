//
// Created by Leonard C on 2021/11/20.
//

#include "src.hpp"
#include <cassert>
#include <iostream>
using namespace std;

int main() {
    const shared_ptr p(new int(-1));
    cout << *p << endl;
    shared_ptr pp(p);
    cout << *pp << endl;
    *pp = 6;
    cout << *pp << endl;
    cout << *p << endl;
    pp.reset();


    shared_ptr p2;
    p2.reset( new int(4));
    *p2 = 5;
    cout << *p2 << endl;
    p2.reset();

    shared_ptr p3(new int(1));
    int *x = new int(4);
    shared_ptr p4(x);

    int *y = new int(4);
    shared_ptr p5(y);
    shared_ptr p6(p5);
    shared_ptr p7(shared_ptr(shared_ptr(new int(1))));
    shared_ptr p8(new int(4));
    p8 = p8;
    p8 = p7;
    p8 = p6;
    p8 = p5;


    int *z = new int(4);
    shared_ptr p9(z);
    p9 = p9;
    auto p10 = p9;
    p9 = p10;

    int *a = new int(4);
    shared_ptr p11(a);
    shared_ptr p12(p11);
    *p11 += 1;
    cout << *p12 << endl;
    p12.reset(new int(5));
    *p12 += 2;
    cout << *p12 << endl;
}



#ifdef _GLIBCXX_MEMORY
EXPLODE!
#endif

/* src.hpp
 * // "Wrapper": src.hpp
#ifndef Wrapper_CPP_Wrapper_HPP
#define Wrapper_CPP_Wrapper_HPP

using namespace std;

class shared_ptr {
private:
    int *x, *count;//x存储数据,
    // *count表示一共有几个指针指向该位置,即被引用次数

public:
    //构造函数
    shared_ptr(int *t) {//不能乱用引用传递,这里没有*
        count = new int(1);
        x = t;
    }

    shared_ptr(const shared_ptr &q) {
        x = q.x;
        ++ *(q.count);//注意优先级---'.'是最高的
        count = q.count;//指向同一个位置
    }

    shared_ptr() {
        x = new int;
        count = new int(1);
    }

    //析构函数
    ~shared_ptr() {
        if (*count == 1) {//只剩1个指针,才需要析构
            delete x;
            delete count;
        }
        else{
            -- *count;
        }
    }

    //重载运算符
    shared_ptr &operator=(const shared_ptr &q) {
        if (this == &q) return *this;//比较地址

        -- *count;
        ++ *(q.count);
        if (*count == 0){
            delete x;
            delete count;
        }
        x = q.x;
        count = q.count;
        return *this;
    }

    //重载 *p
    int &operator*() {
        return *x;
    }

    int &operator*() const {
        return *x;
    }

    void reset() {
        if (*count == 1) return ;
        x = new int (*x);//继承该位置原本的数据
        -- *count;//原位置的引用数减少
        count = new int (1);//新位置只有一次引用
    }

    void reset(int *t) {//t为内置指针
        if (*count == 1){
            int *temp = x;
            x = t;
            delete temp;
        }
        else{
            -- *count;
            x = t;
            count = new int (1);
        }
    }

};


#endif //Wrapper_CPP_Wrapper_HPP
 */