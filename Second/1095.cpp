#include <bits/stdc++.h>
using namespace std;
const int maxn = 105;
struct status{
    int box_x,box_y,person_x,person_y,cnt=0;
};
int n,m,mp[maxn][maxn],x_1,x_2,x_3,y_1,y_2,y_3;
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
int ans=0x7ffffff,vis_1[maxn][maxn][4],vis_2[maxn][maxn],f=0;
//vis_1存箱子,vis_2存人

inline int judge(int x,int y){
    if (x >= 1 && x <= n && y >= 1 && y <= m && mp[x][y] != 'S')
        return 1;
    else return 0;
}

int bfs_person(status p,status box){
    status start;
    queue<status> qt;

    start.box_x = p.person_x;
    start.box_y = p.person_y;
    qt.push(start);
    f = 0;
    memset(vis_2,0,sizeof(vis_2));

    while (!qt.empty()){
        status head = qt.front(),next;
        qt.pop();

        if (head.box_x == p.box_x && head.box_y == p.box_y){//已经到达
            f = next.cnt;
            return 1;
        }
        for (int i = 0;i <= 3;++i){ //与bfs_box类似
            next = head;
            next.box_x += dx[i];
            next.box_y += dy[i];
            if (   !judge(next.box_x,next.box_y)
                || vis_2[next.box_x][next.box_y] )
                continue;

            if (next.box_x == box.box_x
             && next.box_y == box.box_y)
                continue;
            vis_2[next.box_x][next.box_y] = 1;
            next.cnt++;

            qt.push(next);
        }
    }

    return 0;
}

void bfs_box(){
    status start;
    queue<status> q;

    start.box_x = x_1,start.box_y = y_1;
    start.person_x = x_3,start.person_y = y_3;
    q.push(start);

    while (!q.empty()){
        status head = q.front(),next,pre;
        q.pop();
        if (head.box_x == x_2 && head.box_y == y_2){
            ans = head.cnt;
            return;
        }

        for (int i = 0;i <= 3;++i){
            next = head; //箱子的下一个位置
            pre = head;  //人的位置

            next.box_x += dx[i];
            next.box_y += dy[i];
            if (   !judge(next.box_x,next.box_y)
                || vis_1[next.box_x][next.box_y][i] )
                continue;

            pre.box_x -= dx[i];
            pre.box_y -= dy[i];
            if (!bfs_person(pre,head)) continue;

            vis_1[next.box_x][next.box_y][i] = 1;
            next.cnt++;
            if (f) next.cnt += f;
            next.person_x = head.box_x;
            next.person_y = head.box_y;
            q.push(next);
        }
    }

}

void read(){
    scanf("%d%d",&n,&m);
    getchar(); //读取回车
    for (int i = 1;i <= n;++i){
        for (int j = 1;j <= m;++j){
            mp[i][j] = getchar();
            if (mp[i][j] == 'P')
                x_1 = i,y_1 = j; //箱子的起始位置
            if (mp[i][j] == 'K')
                x_2 = i,y_2 = j; //箱子的目标位置
            if (mp[i][j] == 'M')
                x_3 = i,y_3 = j; //人的位置
        }
        getchar();
    }
}
void print(){
    if (ans == 0x7ffffff) printf("NO");
    else printf("%d",ans);
}
int main(){

    read();
    memset(vis_1,0,sizeof(vis_1));
    memset(vis_2,0,sizeof(vis_2));

    bfs_box();
    print();

    return 0;
}