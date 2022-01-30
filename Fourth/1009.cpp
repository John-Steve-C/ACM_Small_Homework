//
// Created by Leonard C on 2021/11/3.
//
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n,m,a[maxn],b[maxn];
int find(int l,int r,int t){
    if (a[n] < t) return -1;

    while (l <= r){//二分不要用递归,直接while,而且一般写 <=
        int mid = (l + r) >> 1;
        if (a[mid] >= t) r = mid;
        else l = mid + 1;

        if (l == r) return l;
    }
    return -1;
}
int main(){

    cin>>n>>m;
    for (int i = 1;i <= n;++i) cin>>a[i];
    for (int i = 1;i <= m;++i) cin>>b[i];

    for (int i = 1;i <= m;++i){
        int t = find(1,n,b[i]);
        if (t == -1) cout<<t<<endl;
        else cout<<a[t]<<endl;
    }
    return 0;
}