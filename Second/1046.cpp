//
// Created by Leonard C on 2021/10/9.
//
#include<bits/stdc++.h>
using namespace std;
int p,m,n,k;
int mul[1010],cnt[1010];//mul[i]为第i行的积,cnt[i]为第i行已经填的数目
long long ans=1,pow2[1010];
void pre_pow(){
    pow2[0] = 1;
    for(int i = 1;i <= 1001;i++)
        pow2[i] = ( pow2[i-1] * 2 ) % p;
}
void change(){//把cnt=0的行换到第n行
    for (int i = 1;i <= n - 1;++i)
        if (cnt[i] == 0){
            swap(cnt[i],cnt[n]);
            swap(mul[i],mul[n]);
            return;
        }
}
void init(){
    for (int i = 0;i <= n;++i) mul[i] = 1,pow2[i] = 1;
    memset(cnt,0,sizeof(cnt));
    ans = 1;
}
int main(){
    int T;

    scanf("%d",&T);

    while (T--){
        int f = 0;
        scanf("%d%d%d",&n,&m,&k);
        if (n < m) {
            swap(n,m);
            f = 1;
        }

        init();

        for (int i = 1;i <= k;++i){
            int x,y,t;
            scanf("%d%d%d",&x,&y,&t);
            if (f) swap(x,y);
            cnt[x]++;
            mul[x] *= t;
        }
        scanf("%d",&p);

        if ( ((n % 2 == 0) && (m % 2 == 1)) || ((n % 2 == 1) && (m % 2 == 0)) ){
            printf("0\n");
            continue;//要放在初始化的后面
        } //奇偶性特判

        change();
        pre_pow(); //要更新p后再计算乘方

        for (int i = 1;i <= n - 1;++i){
            if (cnt[i] == m){
                if (mul[i] == 1) {
                    ans = 0;
                    break;
                }
            }
            else
                ans = (ans * pow2[m - cnt[i] -1]) % p;
                //如果写成 ans *= pow2[m - cnt[i] -1] % p;
                //那么只会对pow2进行取模,而ans不会被取模,所以会溢出
        }

        printf("%lld\n",ans%p);
    }


    return 0;
}