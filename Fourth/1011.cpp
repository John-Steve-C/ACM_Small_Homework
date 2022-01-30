//
// Created by Leonard C on 2021/11/4.
//
//
// Created by Leonard C on 2021/11/3.
//
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n,m,a[maxn],ans = 0;
int check(int t){
//    t /= 2;
    for (int i = 1;i <= n;++i){//O(nt) = 1e5 * t
        if (!a[i]){
            int cnt = 0;
            for (int j = max(i - t,1);j <= min(i + t,n);++j){
                if (!a[j]) cnt++;
            }
            if (cnt >= m + 1) return 1;
        }
    }
    return 0;
}
int find(int l,int r){//binary-search answer!
    while (l <= r){
        int mid = (l + r) >> 1;
        if ( check(mid) ) r = mid;
        else l = mid + 1;

        if (l == r) return l;//log2(1e5) = 15,
                             // can be considered as O(1)
    }
}
int main(){

    ios::sync_with_stdio(0),cin.tie(0);

    string s;
    cin>>n>>m>>s;
    for (int i = 1;i <= n;++i){
        if (s[i - 1] == '0') a[i] = 0;
        else a[i] = 1;
    }

    cout<<find(1,n);

    return 0;
}
