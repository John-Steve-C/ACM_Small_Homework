#include<bits/stdc++.h>
using namespace std;

const int maxn = 2010; 
int n,m,q,a[maxn],b[maxn],ans=0;
int dp[maxn][maxn];
struct tree{
	int a,b;
}t[maxn];
int cmp(tree x,tree y){
	return x.b<y.b;
}

int main()
{	
	scanf("%d%d",&n,&m);
	for (int i = 1;i <= n;++i)
	  scanf("%d",&t[i].a);
	for (int i = 1;i <= n;++i)
	  scanf("%d",&t[i].b);
	
	sort(t+1,t+1+n,cmp);
	
	for (int i = 1;i <= n;++i) //0-1±³°ü 
	  for (int j = m;j >= 1;--j){
	  	dp[i][j] = max(dp[i-1][j] , dp[i-1][j-1] + t[i].b*(j-1) + t[i].a);
	  }
	
	printf("%d",dp[n][m]);
	return 0;
}
