#include<bits/stdc++.h>
using namespace std;

const int maxn = 500010; 
long long n,m,q,a[maxn],ans=0;
long long dp[maxn];
int cmp(int a,int b){
	return a<b;
}
int main()
{	
	scanf("%lld",&n);
	for (int i = 1;i <= n;++i){
		scanf("%lld",&a[i]);
	}
	sort(a+1,a+1+n,cmp);
	
	dp[1] = a[1];
	dp[2] = a[2];
	dp[3] = a[3] + a[1] + a[2];
	
	for (int i = 4;i <= n;++i){
		dp[i] = min( dp[i-2] + a[i] + a[1] + a[2]*2 , 
		             dp[i-1] + a[i] + a[1] );
	}
	
	printf("%lld",dp[n]);
	return 0;
}
