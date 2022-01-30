//
// Created by Leonard C on 2021/10/26.
//
#include <iostream>
using namespace std;
template <class T>
T pow(T base,int exp,T MOD = 19260817){
    //在读入时给变量赋初值,如果没有输入该参数的值,则直接取该值
    T t;//统计答案一定要用long long

    if (base == 0) return 0;
    if (base == 1) return 1 % MOD;
    if (exp == 0) return 1 % MOD;
    if (exp == 1) return base % MOD;

    if (exp % 2 == 1) {
        exp--;
        t = pow(base,exp/2,MOD) % MOD;
        return ( ((base % MOD) * t) % MOD * t ) % MOD;
    }
    else{
        t = pow(base,exp/2,MOD) % MOD;
        return t * t % MOD;
    }
}
int main() {

    long long a,b,c;
    cin>>a>>b>>c;
    cout<<pow(a,b)<<endl<<pow(a,b,c);
    //第一个直接 % 19260817,第二个就% c
    return 0;
}