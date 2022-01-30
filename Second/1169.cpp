//
// Created by Leonard C on 2021/10/7.
//做法：整体二分
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 1001;
const int inf = 0x7ffffff;
int n,m,d[maxn];
int c[maxn],ans[maxn];
int lowbit(int x){
    return x & (-x);
}
int check(int x){ //区间[1,x]求和
    int res = 0;
    while (x){
        res += c[x];
        x -= lowbit(x);
    }
    return res;
}
void add(int x,int val){ //单点修改
    while (x < maxn){ //注意：不是x<n(这里的n是木板数!）
                      //x应该小于区间总长度n(这里应该是maxn)
        c[x] += val;
        x += lowbit(x);
    }
}
//以上是树状数组模板
struct muban{
    int l,r,h;
}q[maxn],q1[maxn],q2[maxn]; //木板
void solve(int l,int r,int x,int y){//[l,r]是子弹区间,[x,y]是木板区间
    if (l > r || x > y) return;
    if (l == r) {
        ans[l] = y - x + 1;
        //void();
        return;
    }

    int mid = (l + r) >> 1;
    for (int i = l;i <= mid;++i){ //树状数组预处理
        if (i == m+1) add(d[i],inf);
        else add(d[i],1); //坐标d[i]处增加一颗子弹
    }

    int c1=0,c2=0;
    for (int i = x;i <= y;++i){
        int dmg = check(q[i].r)- check(q[i].l-1);
        if (q[i].h - dmg <= 0) q1[++c1] = q[i]; //q1是能击碎的组
        else q2[++c2] = q[i], q2[c2].h -= dmg;  //q2是不能的组
    }

    for (int i = l;i <= mid;i++){
        if (i == m+1) add(d[i],-inf);
        else add(d[i],-1);
    }
    for (int i = x;i <= x + c1 - 1;i++) //更新当前的所有木板q
        q[i] = q1[i-x+1];
    for (int i = x + c1;i <= y;i++)
        q[i] = q2[i-x-c1+1];

    solve(l,mid,x,x+c1-1);//递归到下一层
    solve(mid+1,r,x+c1,y);
}
int main(){

    scanf("%d%d",&n,&m);
    for (int i = 1;i <= n;++i)
        scanf("%d%d%d",&q[i].l,&q[i].r,&q[i].h);
    for (int i = 1;i <= m;++i)
        scanf("%d", &d[i]);

    solve(1,m+1,1,n);

    for (int i = 1;i <= m;++i)
        printf("%d\n",ans[i]);
    return 0;
}
