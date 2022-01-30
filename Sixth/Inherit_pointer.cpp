//
// Created by Leonard C on 2022/1/11.
// Program designing I
// I was confused by the transformation of 继承类的指针
// And my final exam was really awful.
//
//参考:https://www.cnblogs.com/xinxue/p/5471708.html
//    https://blog.csdn.net/foreverhuylee/article/details/38128081

#include <bits/stdc++.h>

using namespace std;

class A {
private:
    int x;
public:
    A(){
        x = 0;
    }
    virtual void foo(const int &t) {
        x = t;
    }
    virtual void show() const {
        cout << x << endl;
    }
};

class B : public A {
public:
    int y;
    B(){
        y = -1;
    }
    virtual void foo(const int &t) {//也可以去掉virtual,在末尾加上override
        y = t + 2;
    }
    virtual void show() const {
        cout << y << endl;
    }
};

class C : public A {

};

int main() {
    A *pa, *pa_2, *pa_3;
    B *pb, *pb_2, *pb_3;
    C *pc;
    pa = new A;
    pb = new B;

    pa->foo(2);    pa->show();
    pb->foo(4);     pb->show();
    cout << endl;

    //前提:定义了虚函数
    pb_2 = dynamic_cast<B *>(pa); //fail
    // 虽然 pb_2 可以指向 A 空间，但是 *pb_2 中的 y 是未定义的,会造成非法访问
    pa_2 = dynamic_cast<A *>(pb); //succeed
    // pa_2 也指向了 pb指向的 B 空间,但是无法直接访问 *pb 中的 y

    cout << "transfer A* to B* : ";
    if (pa_2) cout << "succeed!" << endl, pa_2->show();
    else cout << "failed!" << endl;
    //如果show没有定义为virtual,调用的是A类的show,输出的是基类的x(= 0)
    //定义为virtual,才能实现相当于"类中重载"的功能,可以调用指向的B中的show

    cout << "transfer B* to A* : ";
    if (pb_2) cout << "succeed!" << endl, pb_2->show();
    else cout << "failed!" << endl;

    //一个基类的不同派生类,转换失败
    pc = dynamic_cast<C *>(pb);
    if (!pc) cout << "transfer B* to C* : failed!" << endl;

    delete pa;
    delete pb;

    cout << endl;
    pa_3 = new B; //succeed,*A 可以指向 B 空间
//    pb_3 = new A; // fail,*B 不能指向 A 空间

    pa_3->foo(5);
    pa_3->show();
    delete pa_3;

    return 0;
}
