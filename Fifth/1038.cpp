//
// Created by Leonard C on 2021/11/15.
//
#include <iostream>
#include <cstring>

using namespace std;

int n;

// 写出两个函数的声明
int *&funA(int **&t);

void *funB(int *t, int **p, int **q);

int main() {
    int a[100], b[100], c[100];
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
        cin >> b[i];
    int **p, **q;

//    int d = 10,*x;
//    x = &d;

    funA(p) = a;
    funA(q) = b;
    funB(c, p, q);
    for (int i = 0; i < n; ++i)
        cout << c[i] << " ";
    return 0;
}

// 写出两个函数的定义
int *&funA(int **&t) {
    //funA前面的&是为了让函数充当左值
    //t前面的&则是引用传递
//    int *k = new int[100];错误写法
    t = new int *;
//    delete *t;
    return *t;
}

void *funB(int *t, int **p, int **q) {
    for (int i = 0; i < n; ++i) {
        t[i] = (*p)[i] * (*q)[i];
    }
    delete p;
    delete q;

    return t;
}