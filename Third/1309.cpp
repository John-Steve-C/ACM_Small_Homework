#include<bits/stdc++.h>
using namespace std;

const int maxn = 1000010;
int m,n,a[maxn],dp[maxn],flag=0,t=0,ans=0;
int main(){
	
	scanf("%d",&n);
	for (int i = 1;i <= n;++i){
	    scanf("%d",&a[i]);
	    dp[i] = a[i];
	    if (a[i] >= 0) flag = 1;
	}
	
	if (!flag) {
		cout<<0;
		return 0;
	}
	
	for (int i = 1;i <= n;++i){
		t += a[i];
		if (t < 0) t = 0;
		else ans = max(ans,t);
	}
	
	printf("%d",ans);
	
	return 0;
} 
