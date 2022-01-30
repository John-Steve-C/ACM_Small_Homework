//
// Created by Leonard C on 2021/10/5.
//
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
int n,w[maxn][maxn],mi[maxn],mp[maxn][maxn];
int f[maxn],k=0,tot=0;

void prim(){
//    memset(mi,0x7f,sizeof(mi));
    memset(f,0,sizeof(f));

    f[0] = 1;
    for (int i = 1;i <= n;++i){
        mi[i] =mp[0][i];
    }
    mi[0] = 0;

    for (int i = 1;i <= n;++i){
        k=0;
        int miin=0x7ffffff;
        for (int j = 1;j <= n;++j){ //查找边集中，未访问的最小值
            if ( !f[j] && (mi[j] < miin) )
                k = j, miin = mi[j];
        }

        tot += miin;
        f[k] = 1;
        for (int j = 1;j <= n;++j){
            if ( !f[j] )
                mi[j] = min( mp[k][j] , mi[j] );
        }

    }
}

int main(){

    cin>>n;
    for (int i = 1;i <= n;++i)
        for (int j = 1;j <= n - i + 1;++j){
            cin>>w[i][i+j-1];
            mp[i-1][i+j-1] = mp[i+j-1][i-1] = w[i][i+j-1];
    }

    prim();

    cout<<tot;

    return 0;
}