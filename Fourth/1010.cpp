//
// Created by Leonard C on 2021/11/3.
//
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n,m,a[maxn],c[maxn],qz[maxn];
int find(int l,int r,int t){
    while (l <= r){//qz[]是有序的,可以二分查找
        int mid = (l + r) >> 1;
        if (qz[mid] < t) l = mid;//注意细节，
        // l,r的调整要符合题意,不能死记硬背
        else r = mid;

        if (t > qz[mid] && t <= qz[mid + 1]) {
            cout << mid + 1 << ' ' << t - qz[mid] << endl;
            return 0;
        }

    }
    return -1;
}
int main(){

    ios::sync_with_stdio(0),cin.tie(0);

    cin>>n>>m;
    for (int i = 1;i <= n;++i){
        cin>>a[i];
        qz[i] = qz[i - 1] + a[i];
    }
    /*if (m <= 1e4)
    for (int i = 1;i <= m;++i){
        cin>>c[i];
        for (int j = 1;j <= n;++j){
            if (c[i] > qz[j - 1] && c[i] <= qz[j]){
                cout<<j<<' '<<c[i] - qz[j - 1]<<endl;
            }
        }
    }
    else{*/
        for (int i = 1;i <= m;++i){
            int t;
            cin>>t;
            find(0,n,t);//一开始的边界设定

    }


    return 0;
}