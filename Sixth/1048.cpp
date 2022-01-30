//
// Created by Leonard C on 2021/12/9.
//

#include "DeferClass.hpp"
using namespace std;

void hello()
{
    std::cout << "Hello world!" << std::endl;
}

int main()
{
    int *p = new int [2];
    Defer defer([&](){delete [] p;});//参数是一个lambda表达式
    defer([&](){std::cout << p[0] << " " << p[1] << std::endl;});
    defer([&](){p[0] = 0, p[1] = 1;});
    defer(hello);
    p[0] = 2, p[1] = 3;
    return 0;
}