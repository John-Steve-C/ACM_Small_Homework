//
// Created by Leonard C on 2021/11/18.
//

#include <bits/stdc++.h>

using namespace std;
int n, m, CNT[1001];

class MATRIX {
public:
    long long a[31][31], r = 0, len, vis[31];
    static const int MOD = 1e9 + 7;

    MATRIX(int l){
        len = l;
        r = 0;
        memset(a,0,sizeof(a));
    }

    void read() {
        for (int j = 1; j <= len; ++j)
            for (int k = 1; k <= len; ++k) {
                cin >> a[j][k];
            }
    }

    int ex_gcd(int p, int q, int &x, int &y) {//px-qy=gcd(p,q)
        if (!q) {
            x = 1;
            y = 0;
            return p;
        }
        int k = ex_gcd(q, p % q, x, y), t = x;
        x = y;
        y = t - p / q * x;
        return k;
    }

    int reverse(int p, int q) {//px mod q = 1
        int x, y;
        ex_gcd(p, q, x, y);
        return x;
    }

    long long quick_pow(int a, int b) {
        long long ans = 1, Base = a;
        while (b) {
            if (b & 1) ans = ans * Base % MOD;
            Base = Base * Base % MOD;
            b >>= 1;
        }
        return ans;
    }

    long long get_div(long long a, long long b) {//费马小定理求乘法逆元
        return (a * quick_pow(b, MOD - 2) % MOD + MOD) % MOD;
    }//保证非负性

    /* Old Edition:Failed
    void Query_Rank(int t) {
        if (t > len) return;

        int f = 0;
        if (!a[t][t]) {//保证当前行不为0
            for (int i = t + 1; i <= len; ++i) {
                if (a[i][t]) {
                    for (int j = t; j <= len; ++j)
                        swap(a[t][j], a[i][j]);
                    f = 1;
                    break;
                }
            }
        }


        for (int i = t + 1; i <= len; ++i) {//高斯消元
            int x, y;

            x = (reverse(a[i][t], MOD) + MOD) % MOD;
            y = (a[t][t] % MOD * x) % MOD;// a[t][t] / a[i][t],求系数

            for (int j = t; j <= len; ++j) {
                if (!a[i][t]) continue;
                a[i][j] = ((a[i][j] + a[t][j] * y) % MOD + MOD) % MOD;
                //保证非负性
            }

        }

        int f1 = 1;//判断是否为主元
        for (int i = t + 1; i <= len; ++i) {
            if (a[i][t]) {//左边
                f1 = 0;
                break;
            }
        }
        for (int i = 1; i <= t - 1; ++i) {
            if (a[t][i]) {//下方
                f1 = 0;
                break;
            }
        }
        if (f1) r++;

        Rank(t + 1);
    }
};*/

    void Query_Rank() {//高斯消元法,求秩,即主元个数
        memset(vis, 0, sizeof(vis));

        for (int i = 1; i <= len; ++i) {//第i列
            int is_prior = 0;
            for (int j = 1; j <= len; ++j) {//第j行
                if (vis[j]) continue;//已经处理过
                if (a[j][i]) {//==0表示不需要处理
                    is_prior = 1;
                    vis[j] = 1;
                    for (int k = j + 1; k <= len; ++k) {//
                        if (vis[k]) continue;
                        long long div = get_div(a[k][i], a[j][i]);//求出'倍数'
                        for (int l = i; l <= len; ++l)
                            a[k][l] = ((a[k][l] - a[j][l] * div) % MOD + MOD) % MOD;
                    }
                }
            }
            if (is_prior) r++;
        }
    }
};


int main() {//判断矩阵的等价->秩相等

    cin >> n >> m;
    int rt = -1, t = 0, cnt = 0;
    for (int i = 1; i <= n; ++i) {
        MATRIX temp(m);
        temp.read();

        temp.Query_Rank();
        t = temp.r;
        if (rt != t) {
            CNT[++cnt] = i;
            rt = t;
        }
    }

    cout << cnt << endl;
    for (int i = 1; i <= cnt; ++i)
        cout << CNT[i] << ' ';

    return 0;
}