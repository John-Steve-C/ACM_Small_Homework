#include<bits/stdc++.h>
using namespace std;
int n,m,q;
#define int long long  //long long�Ų���ը 
int ksm(int a, int b,int MOD)//����a��b�η���MODȡģ 
{
    int ans = 1, base = a;
    while(b > 0)
    {
        if(b & 1)
            ans *= base,ans%=MOD;

        base *= base,base%=MOD;
        b >>= 1;
    }
    return ans%MOD;
}
signed main()
{
	scanf("%d%d",&n,&m);

	cout<<ksm(n,m,2019);
	return 0;
}
