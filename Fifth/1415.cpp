//
// Created by Leonard C on 2021/11/17.
//
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100005;
int n,Q,ans[maxn][3],f[maxn],cnt = 1;
vector<int> mp[maxn];
void dfs(int fa){//求树节点的dfs序和区间,用来判断祖先关系

    for (int i = 0;i < mp[fa].size();++i){
        if ( !f[ mp[fa][i] ] ){
            f[ mp[fa][i] ] = 1;
            cnt++;
            ans[ mp[fa][i] ][0] = cnt;
            ans[ mp[fa][i] ][2] = min(ans[ mp[fa][i] ][2],cnt);

            dfs( mp[fa][i] );

            ans[ mp[fa][i] ][1] = max(ans[ mp[fa][i] ][1],cnt);
        }
    }

    return ;
}
int main(){

    scanf("%d%d",&n,&Q);
    for (int i = 1;i < n;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        mp[x].push_back(y);
        mp[y].push_back(x);
        ans[i + 1][2] = maxn;
    }

    ans[1][0] = ans[1][2] = 1;
    ans[1][1] = n;
    f[1] = 1;
    dfs(1);
    while (Q--){
        int x,y;
        scanf("%d%d",&x,&y);
        if (x == y) {
            printf("No\n");
            continue;
        }
        if (ans[x][0] <= ans[y][1] && ans[x][0] >= ans[y][2])
            printf("Yes\n");
        else
            printf("No\n");

    }

    return 0;
}