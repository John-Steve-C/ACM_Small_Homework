//
// Created by Leonard C on 2021/11/15.
//
// "Wrapper": example.cpp
#include <bits/stdc++.h>
#include "src.hpp"
using namespace std;

void foo(string id) { cout << id << endl; }
void before() { cout << "before foo" << endl; }
void after() { cout << "after foo" << endl; }

int main(){
    Wrapper *f = create(foo, before, after);
    run(f, "Hello");
    Wrapper *g = create(foo, after, before);
//    Wrapper *h = create(foo, after, before);
    run(g, "World!");
    remove(g);
//    run(h,"zzz");
//    run(f,"swe");
    destroy();
    return 0;
}

/* src:
// "Wrapper": src.hpp
#ifndef Wrapper_CPP_Wrapper_HPP
#define Wrapper_CPP_Wrapper_HPP

#include <string>

using namespace std;

struct Wrapper {//Node
    // todo: add definitions here
    void (*a)(string), (*b)(), (*c)();//函数指针
    Wrapper *next,*pre;//后继和前继

} *head , *p, *rear ;
int f = 0;
// todo: add definition for link list

// todo: initialize
void init(){
    head = new Wrapper;
    rear = new Wrapper;
    head->pre = nullptr;
    head->next = rear;
    rear->pre = head;
    rear->next = nullptr;

    f = 1;
}

// todo: create()
Wrapper *create(void (*x)(string), void (*y)(), void (*z)()) {
    //可以认为是直接在rear之前的insert
    //倘若这么写，rear中就不存储数据了

    p = new Wrapper;

    if (f == 0) init();

    Wrapper *temp = rear->pre;
    p->a = x;
    p->b = y;
    p->c = z;
    p->pre = temp;
    p->next = rear;

    temp->next = p;
    rear->pre = p;

    return p;
}

// todo: remove()
void remove(Wrapper *t) {
    //同run，不用从头开始，直接删除t即可
    Wrapper *tp;
    tp = t->pre;
    tp->next = t->next;
    t->next->pre = tp;
    delete t;
}

// todo: run()
void run(Wrapper *t, string s) {

    //不需要从head开始遍历，直接修改t即可？
    //因为节点的位置已经知道
    t->b();//调用函数
    t->a(s);
    t->c();
}

// todo: destroy()
void destroy() {
    f = 0;
    p = head;
    Wrapper *t;

    while (p != nullptr) {
        t = p->next;
        delete p;
        p = t;
    }
}

#endif //Wrapper_CPP_Wrapper_HPP

 */