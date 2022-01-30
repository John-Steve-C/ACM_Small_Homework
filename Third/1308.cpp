#include<bits/stdc++.h>
using namespace std;
string A;
char a,b;
int m,n;
int main(){
	
	cin>>A;
	getchar();
	a = getchar();
	getchar();
	b = getchar();
	cin>>m;
	
	if (A == "Triangle"){
		for (int i = 1;i <= m/2+1;++i){
			for (int j = 1;j <= m;++j)
			  if (j > m/2-i+1 && j <= m/2+i) cout<<a;
			  else cout<<b;
			cout<<endl;  
		}
	}
	else 
	 if (A == "Square"){
	 	for (int i = 1;i <= m;++i){
	 		for (int j = 1;j <= m;++j)
	 		  cout<<a;
	 		cout<<endl;  
	 	}
	 }
	 else{
	 	for (int i = 1;i <= m/2+1;++i){
			for (int j = 1;j <= m;++j)
			  if (j > m/2-i+1 && j <= m/2+i) cout<<a;
			  else cout<<b;
			cout<<endl;  
		}
		for (int i = m/2;i >= 1;--i){
			for (int j = 1;j <= m;++j)
			  if (j > m/2-i+1 && j <= m/2+i) cout<<a;
			  else cout<<b;
			cout<<endl;  
		}
	 }
	
	return 0;
} 
