//
// Created by Leonard C on 2021/10/27.
//
#include <bits/stdc++.h>
using namespace std;
int n,a[1010][1010],dp[1010][1010];
int main(){

    scanf("%d",&n);
    for (int i = 1;i <= n;++i)
        for (int j = 1;j <= i;++j)
            scanf("%d",&a[i][j]);

    for (int i = n;i >= 2;--i)
        for (int j = 2;j <= i;++j){
            a[i - 1][j - 1] += max(a[i][j],a[i][j - 1]);
        }

    cout<<a[1][1];
    return 0;
}