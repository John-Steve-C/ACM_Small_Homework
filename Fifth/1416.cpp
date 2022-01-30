//
// Created by Leonard C on 2021/11/17.
//
#include <bits/stdc++.h>

using namespace std;
//const int maxn = 100005;
int w, h, ans = 0, f[300][100], mp[300][100];
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, -1, 1}, cnt[300][100];
struct node{
    int x,y;
}tp,now;
queue<node> q;
void bfs(){
    while (!q.empty()){
        now = q.front(); q.pop();
        for (int i = 0; i < 4; ++i) {
            int tx = now.x + dx[i], ty = now.y+ dy[i];
            if (tx > 1 && tx < h && ty > 1 && ty < w)
                if (!f[tx][ty] && !mp[tx][ty]) {
                    f[tx][ty] = 1;
                    tp.x = tx; tp.y = ty;
                    q.push(tp);
                    cnt[tx][ty] = min(cnt[now.x][now.y] + 1, cnt[tx][ty]);
                }
        }
    }

}

int main() {

    scanf("%d%d", &w, &h);
    w = 2 * w + 1; h = 2 * h + 1;
    char ch = getchar();
//    getchar();
    for (int i = 1; i <= h; ++i) {
        for (int j = 1; j <= w; ++j) {
            ch = getchar();
            if (ch == ' ') mp[i][j] = 0;
            else mp[i][j] = 1;
        }
        ch = getchar();
    }

    memset(cnt,0x3f,sizeof(cnt));
    for (int i = 1; i <= h; ++i) {
        if (!mp[i][1]) {
            f[i][1] = f[i][2] = 1;
            cnt[i][2] = 0;
            tp.x = i; tp.y = 2; q.push(tp);
        }
        if (!mp[i][w]) {
            f[i][w] = f[i][w-1] = 1;
            cnt[i][w - 1] = 0;
            tp.x = i; tp.y = w - 1; q.push(tp);
        }
    }
    for (int j = 1; j <= w; ++j) {
        if (!mp[1][j]) {
            f[1][j] = f[2][j] = 1;
            cnt[2][j] = 0;
            tp.x = 2; tp.y = j; q.push(tp);
        }
        if (!mp[h][j]) {
            f[h][j] = f[h-1][j] = 1;
            cnt[h-1][j] = 0;
            tp.x = h - 1; tp.y = j; q.push(tp);
        }
    }

    bfs();

    for (int i = 2; i <= h - 1; ++i) {
        for (int j = 2; j <= w - 1; ++j)
            if (!mp[i][j]){
            ans = max(ans,cnt[i][j]);
        }
    }

    printf("%d", ans / 2 + 1);

    return 0;
}