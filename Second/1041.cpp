//
// Created by Leonard C on 2021/10/8.
//
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;
int n,k,a[maxn],sum[maxn],ans=0,mina = 1e8;
struct TAG{
    int l,r,num,len;
}tag[maxn];
void scan()
{
    int cnt = 0;
    for (int i = 1;i <= n;){
        int j = i;
        for (j = i;a[j] == 1;++j) ;
        if (a[i] == 1){
            cnt++;
            for (int t = i;t <= j-1;++t){
                tag[t].num = cnt;
                tag[t].l = i;
                tag[t].r = j - 1;
                tag[t].len = (j - 1) - i + 1;
            }
            i = j;
        }
        else
            for (i = j;a[i] != 1;++i) ;
    }
}
signed main(){

    scanf("%lld%lld",&n,&k);

    for (int i = 1;i <= n;++i){
        scanf("%lld",&a[i]);
        sum[i] = sum[i-1] + a[i];
        mina = min(mina,a[i]);
    }

    if (mina == 2){
        for (int l = 1;l <= 45;++l){//45 = log2(2e13),是mina=2时,区间长度的最大值
            for (int i = 1;i <= n - l + 1;++i)
            {
                int j = i + l -1,ji = 1;
                for (int t = i;t <= j;++t)
                    ji *= a[t];
                if ( (sum[j] - sum[i-1]) * k == ji ) ans++;
            }
        }
    }
    else {
        scan();

        for (int i = 1;i <= n;++i) {
            int ji = 1,len1 = 0;

            for (int j = i; (j <= n) && (j - i + 1 - len1 <= 61); ++j) {
                if (a[j] == 1) {
                    if ((1.0 * ji / k) >= (sum[j] - sum[i - 1]) &&
                            (1.0 * ji / k) <= (sum[tag[j].r] - sum[i - 1])) {
                            ans++;
                    }
                    len1 += tag[j].len;
                    j = tag[j].r;

                }
                else {
                    ji *= a[j];
                    if ((sum[j] - sum[i - 1]) * k == ji) ans++;
                }

            }
        }
    }


    printf("%lld",ans);
    return 0;
}