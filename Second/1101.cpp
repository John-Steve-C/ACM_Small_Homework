//
// Created by Leonard C on 2021/10/7.
//
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e6 + 10;
int n,a,b,c,f[maxn];
int sum[maxn],Q[maxn],head=0,tail=0;

double F(int t){
    return t*t*a + t*b +c;
}
double cal(int j,int k){ //斜率计算
    return ( (f[j] - b*sum[j] + a*sum[j]*sum[j]) - (f[k] - b*sum[k] + a*sum[k]*sum[k]) )
            / ( 2.0*a*(sum[j] - sum[k]) );
}
signed main(){

    cin>>n>>a>>b>>c;
    for (int i = 1;i <= n;++i){
       int x;
        cin>>x;
        sum[i] = sum[i-1] + x;
    }

    for (int i = 1;i <= n;++i){
        while ( (head < tail) && ( cal(Q[head],Q[head+1]) <= sum[i] ) )
            head++;  //单调队列,保证斜率递增(上凸)
        f[i] = f[ Q[head] ] + F(sum[i] - sum[ Q[head] ]);
        while ( (head < tail) && ( cal(Q[tail-1],Q[tail]) >= cal(Q[tail],i) ) )
            tail--;
        Q[++tail] = i;
    }

    printf("%lld",f[n]);
    return 0;
}