//
// Created by Leonard C on 2021/10/27.
//
#include <bits/stdc++.h>
using namespace std;
string s;
char ans[10];
int n,l,tong[26],num = 0;

void dfs(int k){
    for (int i = 0;i < l;++i){
        if (tong[i]){
            tong[i]--;
            ans[k] = i + 'a';
            if (k == l - 1){
                num++;
                if (num == n) {
                    cout<<ans;
                    exit(0);
                }
            }
            else
                dfs(k + 1);

            tong[i]++;
        }
    }
}
int main(){

    cin>>s>>n;
    l = s.length();
    for (int i = 0;i < l;++i)
        tong[s[i] - 'a']++;
    dfs(0);

    return 0;
}