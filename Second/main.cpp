//暴力枚举+暴力判断
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 1e2;
int r[501][501],n,m,f[501],t1[501],t2[501],ans=501;
void check(){
    int l1 = 0,l2 = 0,f1 = 1,f2 = 1;
    for (int i = 1;i <= n;++i){
        if (f[i]) t1[++l1] = i;
         else t2[++l2] = i;
    }

    if (l1 > 1)
        for (int i = 1;i <= l1-1;++i)
            for (int j = i+1;j <= l1;++j){
                int x = t1[i],y = t1[j];
                if (!r[x][y]) {
                    f1 = 0;
                    break;
                }
                if (!f1) break;
            }

    if (l2 > 1)
        for (int i = 1;i <= l2-1;++i)
            for (int j = i+1;j <= l2;++j){
                int x = t2[i],y = t2[j];
                if (!r[x][y]) {
                    f2 = 0;
                    break;
                }
                if (!f2) break;
            }

    if (f1 && f2) ans = min(abs(l1-l2),ans);

    return;
}
void choose(int k){

    for (int i = 1;i <= n;++i){
        if ( !f[i] ){
            f[i] = 1;
            check();
            if (k<=n/2) choose(k+1);

            f[i] = 0;
        }
    }
}

int main()
{
    memset(r,0,sizeof(r));
    scanf("%d%d",&n,&m);
    for (int i = 1;i <= m;++i){
        int a,b;
        scanf("%d%d",&a,&b);
        r[a][b] = r[b][a] = 1;
    }

    choose(1);

    if (ans == 501) cout<<"No Answer";
        else cout<<ans;

    return 0;
}