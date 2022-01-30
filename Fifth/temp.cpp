#include <bits/stdc++.h>

using namespace std;
int n, m, f[52][52], ans = 0, start_x, start_y, cnt = 0;
int end_x, end_y, dir[52][52];
char mp[52][52];
int dx[8] = {0, 0, -1, 1, -1, 1, -1, 1}, dy[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
struct NODE{
    int x,y;
};
queue<>

void dfs(int x, int y, int k) {
    for (int i = 0; i < 8; ++i) {
        int tx = x + dx[i], ty = y + dy[i];

        if (tx == end_x && ty == end_y) {
            /*int tp = dir[x][y];
            if (x - dx[tp] == start_x && y - dy[tp] == start_y)
                return;*/
            check(k);
            return;
        }
        if (tx >= 1 && tx <= n && ty >= 1 && ty <= m)
            if (mp[tx][ty] == '.') {
                if (ans < k) return;

                f[tx][ty] = k;
                dir[tx][ty] = i;
                dfs(tx, ty, k + 1);

                f[tx][ty]--;
                dir[tx][ty] = 0;
            }
    }
}

void bfs(){

}

int main() {

    int m1, m2, m3, m4;
    scanf("%d%d", &n, &m);
    m1 = 1;
    m2 = n;
    m3 = 1;
    m4 = m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            cin >> mp[i][j];
            if (mp[i][j] == '*') {
                start_x = i;
                start_y = j;
                f[start_x][start_y] = 1;
            }
            if (mp[i][j] == 'X') {
                m1 = min(i,m1);
                m2 = max(i,m2);
                m3 = min(j,m3);
                m4 = max(j,m4);
            }
        }

    ans = n * m;


    end_x = m1;
    end_y = m3;

    dfs(start_x, start_y, 1);
    cnt += ans;

    end_x = m2;
    end_y = m4;
    dfs(m1, m3, 1);
    cnt += ans;

    end_x = start_x;
    end_y = start_y;
    dfs(m2, m4, 1);
    cnt += ans;

    printf("%d", cnt);

    return 0;
}