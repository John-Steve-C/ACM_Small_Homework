#include<bits/stdc++.h>
using namespace std;
const int maxn = 10010;
int n,m,a[maxn],po[maxn];
int main(){
    
    scanf("%d%d",&n,&m);
    for (int i = 1;i <= n;++i){
    	scanf("%d",&a[i]);
    	if (!po[a[i]]) po[a[i]] = i;
    }//po[i]��¼����i������ֵ�λ��
      
    while (m--){
    	
	    int q,f[maxn],temp[maxn],b[maxn];
	    int l=n,r=0,len=0;
	    memset(f,0,sizeof(f));
	    memset(temp,0,sizeof(temp));
	  
	    scanf("%d",&q);
	    for (int i = 1;i <= q;++i){
	  	  scanf("%d",&b[i]);
		  f[b[i]]++; //��Ͱ��ͳ��ѯ�ʵ����� 
		  l = min(l,po[b[i]]); 
		  r = max(r,po[b[i]]);
          //ά��l,r����ָ�룬�ҳ�������ʼ��Χ
	    }
	    len = r - l + 1;//��ʼ���䳤��
	    
	    for (int i = l;i <= r;++i) temp[a[i]]++;
            //��ѯ�ʵĳ�ʼ����ŵ���һ��Ͱ
	    
        while (r <= n){
	    	int pre = a[l];
	    	temp[pre]--;
	    	l++; //lָ�����ƣ�����ͳ�ƴ���
            
	    	if (!f[ pre ] || temp[ pre ] > 0)
			//f��û��pre,����temp����Ȼ��pre,
			//˵��l���ƶ����ı�Ϸ��� 
			    len = min(len,r - l + 1);//���� 
	    	else{
	    		while (temp[pre]<=0 && f[pre] && r<=n)
	    		//temp��û��pre,f����Ҫpre, 
	    		    temp[ a[++r] ]++;//r���� 
	    	    }
	    }
	    printf("%d\n",len);
	}
    
    return 0;
}
