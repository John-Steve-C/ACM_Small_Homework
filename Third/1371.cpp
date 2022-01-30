#include<bits/stdc++.h>
using namespace std;
const int maxn = 10010;
int n,m,a[maxn],po[maxn];
int main(){
    
    scanf("%d%d",&n,&m);
    for (int i = 1;i <= n;++i){
    	scanf("%d",&a[i]);
    	if (!po[a[i]]) po[a[i]] = i;
    }//po[i]记录数字i最早出现的位置
      
    while (m--){
    	
	    int q,f[maxn],temp[maxn],b[maxn];
	    int l=n,r=0,len=0;
	    memset(f,0,sizeof(f));
	    memset(temp,0,sizeof(temp));
	  
	    scanf("%d",&q);
	    for (int i = 1;i <= q;++i){
	  	  scanf("%d",&b[i]);
		  f[b[i]]++; //用桶，统计询问的数字 
		  l = min(l,po[b[i]]); 
		  r = max(r,po[b[i]]);
          //维护l,r两个指针，找出最大的起始范围
	    }
	    len = r - l + 1;//起始区间长度
	    
	    for (int i = l;i <= r;++i) temp[a[i]]++;
            //把询问的初始区间放到另一个桶
	    
        while (r <= n){
	    	int pre = a[l];
	    	temp[pre]--;
	    	l++; //l指针右移，更新统计次数
            
	    	if (!f[ pre ] || temp[ pre ] > 0)
			//f中没有pre,或者temp中仍然有pre,
			//说明l的移动不改变合法性 
			    len = min(len,r - l + 1);//更新 
	    	else{
	    		while (temp[pre]<=0 && f[pre] && r<=n)
	    		//temp中没有pre,f中需要pre, 
	    		    temp[ a[++r] ]++;//r右移 
	    	    }
	    }
	    printf("%d\n",len);
	}
    
    return 0;
}
