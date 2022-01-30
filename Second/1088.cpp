#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 500;
// num表示编号，叶子为编号，非叶子为0
// tree表示该段剩余人数
int num[maxn << 2], tree[maxn << 2];
int n,m;

void build(int rt, int l, int r) { //线段树
    if (l == r) {
        tree[rt] = 1;
        num[rt] = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}

int query(int rt, int l, int r) {
    if (l == r) return num[rt];
    int mid = (l + r) >> 1;
    int t1 = query(rt << 1, l, mid), t2 = query(rt << 1 | 1, mid + 1, r);
    return max(t1,t2);//返回二者的较大值
}

void del(int rt, int l, int r, int x) { //删除[l,r]中的第x个
    if (l == r) {
        tree[rt] = 0; //标记为删除
        num[rt] = 0;
        return;
    }
    int mid = (l + r) >> 1;
    if (tree[rt << 1] >= x) { //如果删除的x比左边总人数小，
        del(rt << 1, l, mid, x); //则说明x在左半段
    } else {
        del(rt << 1 | 1, mid + 1, r, x - tree[rt << 1]);
    }
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}

int main() {
    scanf("%d%d",&n,&m);
    int cur,t;

    if (m == 1) printf("%d",n);
    else if (n == 1) printf("1");
    else {
        build(1, 1, n);
        int dir = 1; // 1表示向右，0向左
        cur = 1;     //当前点的编号

        for(int i = n;i > 1;--i) { //人数i不断减少
            if (dir) {
                if (m < i + 1 - cur) { //如果向右走m-1格，不会出界
                    cur += (m - 1);  //注意：报数和直接加法的区别
                    del(1, 1, n, cur); //则删除当前点右边m-1格的点
                } else {
                    cur += m - i; //求出,出界了多远
                    t = cur / (i - 1); //出界的倍数t
                    cur %= (i - 1); //周期性
                    if (cur == 0) { //余数边界判断
                        --t;
                        cur = i - 1;
                    }
                    if (t % 2 == 0) { //走了2k*i,来回刚好抵消
                        cur = i + 1 - cur;
                        dir = 0; //仍然可以向右
                        del(1, 1, n, cur);
                    } else { //走了奇数个i，改变方向
                        dir = 1;
                        del(1, 1, n, cur);
                    }
                }
            }

            else { //以下向左走的代码，与上方类似
                if (m < cur - 1) {
                    cur -= m;
                    del(1, 1, n, cur);
                } else {
                    cur = m - cur + 2;
                    t = cur / (i - 1);
                    cur %= (i - 1);
                    if (cur == 0) {
                        -- t;
                        cur = i - 1;
                    }
                    if (t % 2 == 0) {
                        dir = 1;
                        del(1, 1, n, cur);
                    } else {
                        cur = i + 1 - cur;
                        dir = 0;
                        del(1, 1, n, cur);
                    }
                }
            }
        }


        printf("%d", query(1, 1, n));
    }
    
    return 0;
}