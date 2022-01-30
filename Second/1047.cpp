//
// Created by Leonard C on 2021/10/5.
//
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000005;
const int maxm = 5000005;
int num_edge=0,head[maxn*4],dis[maxn*4],vis[maxn*4];
int n,m,C,a,b;
struct Edge{
    int next,to,dis;
}edge[maxm*4];
void addedge(int from,int to,int dis){
    edge[++num_edge].next=head[from];
    edge[num_edge].to=to;
    edge[num_edge].dis=dis;
    head[from]=num_edge;
}
void dijkstra(){
    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > q;
    memset(dis,0x3f,sizeof(dis));
    dis[a]=0;
    q.push(make_pair(0,a));
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

    scanf("%d%d%d",&n,&m,&C);
    for (int i = 1;i <= m;++i){
        int f,t,v;
        scanf("%d%d%d",&f,&t,&v);
        addedge(f,t,v);
    }
    scanf("%d%d",&a,&b);

    //int l=log2(n);
    for (int i = 0;i <= n;++i) //重点：建边
        for (int j = 0;j <= 20;++j){
            int t = i ^ (1<<j);
            if (t <= n) addedge(i,t,C*(1<<j));
        }

    dijkstra();

    printf("%d",dis[b]);

    return 0;
}