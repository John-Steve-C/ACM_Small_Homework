//
// Created by Leonard C on 2021/9/30.
//正解
//
#include <bits/stdc++.h>
using namespace std;
const int maxn = 510;
int r[maxn][maxn],rb[maxn][maxn],n,m,color[maxn];
int dp[maxn][maxn],d[maxn],VISIT[maxn];
int team[maxn][2],cnt=0;
//team[i][j]表示第i个强连通分量中被分到j组中的人数(被涂成颜色1/-1的点数)
//r为原图,rb为补图
//cnt为强连通分量的数目

int dfs(int v,int c){ //u为当前点,c为颜色
    color[v] = c;
    for (int i = 1;i <= n;i++){
        if (rb[v][i]){ //用补图rb来判断，原本的0和1互换，0表示有边
//                       可以认为”不认识关系“才是边
            if (color[i] == c)
                return false;
            if (color[i] == 0 && !dfs(i,-c) )
                return false;
        }
    }
    return true;
}
int bi(){ //二分图染色
    for (int i = 1;i <= n;i++){//每个点都要做
        if (color[i] == 0){//未涂色
            if ( !dfs(i,1) ){
                return 0;
            }
        }
    }
    return 1;
}

void bianli(int k){ //遍历该连通块,统计该连通块中,不同颜色的数目
    VISIT[k] = 1;
    if (color[k] == 1)
        team[cnt][0]++;
    else
        team[cnt][1]++;

    for (int i = 1;i <= n;++i)
            if (rb[k][i] && !VISIT[i])
                bianli(i);
}

void DP(){ //dp[i][j]类似背包(选取到前i个物品,总价值为j能否凑出来)
    dp[1][ maxn + d[1] ] = dp[1][ maxn - d[1] ] = 1;
//  maxn是人数的上限，加上它可以防止数组越界
    for (int i = 1;i <= cnt - 1;++i)
        for (int j = maxn - n;j <= n + maxn;++j)
            if (dp[i][j])
                dp[i+1][j- d[i+1] ] = dp[i+1][j+ d[i+1] ] = 1;
}

int main()
{
    memset(r,0,sizeof(r));
    memset(VISIT,0,sizeof(VISIT));
    scanf("%d%d",&n,&m);
    for (int i = 1;i <= n;++i){
        for (int j = 1;j <= n;++j){
            if (i != j) rb[i][j]=1;//补图赋初值，注意i=j时还是0
        }
    }
    for (int i = 1;i <= m;++i){
        int a,b;
        scanf("%d%d",&a,&b);
        r[a][b] = r[b][a] = 1;
        rb[a][b] = rb[b][a] = 0;
    }

    if ( !bi() ){//二分图染色失败
        printf("No Answer");
        return 0;
    }
    //以上是无解的判断，对补图进行二分图染色

    for (int i = 1;i <= n;++i){ //统计强连通分量的个数cnt
        if (!VISIT[i]){ //没被遍历过的点i
            cnt++;      //就是新的强连通分量
            bianli(i);
        }
    }

    for(int i = 1;i <= cnt;i++)
        d[i]=abs(team[i][0]-team[i][1]);
    //d[i]表示第i个强连通分量中，分到不同组的人数之差的绝对值
    //也可以认为是分到不同组，对总人数差的贡献

    DP();

    for (int i = 0;i <= n;i++){//按照差值从小到大，查找答案
        if (dp[cnt][maxn+i] || dp[cnt][maxn-i]){
            cout<<i;
            break;
        }
    }

    return 0;
}