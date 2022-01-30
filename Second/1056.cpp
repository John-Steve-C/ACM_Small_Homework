//
// Created by Leonard C on 2021/10/7.
//
#include <bits/stdc++.h>
using namespace std;
const int maxn = 300010;
const int inf = 0x7ffffff;
int n,m,a[maxn],vis[2*maxn],dis[2*maxn],tong[200000010];
int head[2*maxn],num_edge=0; //越界！！
struct Edge
{
    int next,to,dis;
}edge[maxn*4]; //结构体表示静态邻接表,不赋初值会TLE
void addedge(int from,int to,int dis)
{
    edge[++num_edge].next=head[from];
    edge[num_edge].to=to;
    edge[num_edge].dis=dis;
    head[from]=num_edge;
}
void dijkstra(){
    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > q;
    memset(dis,0x3f,sizeof(dis));
    dis[1]=0;
    q.push(make_pair(0,1));
    while (!q.empty()){
        int u=q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u]=1;
        for (int i=head[u];i;i=edge[i].next){
            int v=edge[i].to,t=edge[i].dis;
            if (dis[v] > dis[u] + t){
                dis[v] = dis[u] + t;
                q.push(make_pair(dis[v],v));
            }
        }
    }
}

int main(){
    scanf("%d",&n);
    for (int i = 1;i <= n;++i)
        scanf("%d",&a[i]);

    if (n == 1) printf("0");
    else if (n == 2) printf("1");
    else {
        for (int i = 2;i <= n;++i)
            addedge(i-1,i,2),addedge(i,i-1,2);
        for (int i = 1;i <= n;++i){
            if (tong[a[i]+(int) 1e8] == 0) {
                tong[a[i]+(int) 1e8] = i+300000;
                addedge(i,i+300000,1);
                addedge(i+300000,i,1);
            }
            else{
                addedge(tong[a[i]+(int) 1e8],i,1);
                addedge(i,tong[a[i]+(int) 1e8],1);
            }

        }
        dijkstra();

        printf("%d",dis[n] / 2);
    }



    return 0;
}
