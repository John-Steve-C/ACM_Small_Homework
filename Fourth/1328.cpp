//
// Created by Leonard C on 2021/10/26.
//
#include <bits/stdc++.h>
using namespace std;

void debugPrint() {
    std::cout<<std::endl;
}
template<typename Type, typename... Types>
void debugPrint(const Type& arg, const Types&... args)
{
    std::cout << arg <<' ';
    debugPrint(args...);
}
int main(){

    std::string str("test message");
    debugPrint("Hello, Happy World!", 19260817, false, str);
    debugPrint("debug");
    return 0;
}