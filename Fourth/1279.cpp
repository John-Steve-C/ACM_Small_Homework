//
// Created by Leonard C on 2021/10/27.
//
#include <bits/stdc++.h>
using namespace std;
int T,dp[51],tong[26];
int main(){

    scanf("%d",&T);

    while (T--){
        int n,ans = 0,t = 0;
        string s;
        char temp[51];
        scanf("%d",&n);
        cin>>s;

        for (int i = 0;i < n;++i){
            tong[s[i] - 'a']++;
        }
        for (int i = 0;i < 26;++i){
            while (tong[i]){
                tong[i]--;
                temp[t++] = i + 'a';
            }
        }

        for (int i = 0;i < n;++i){
            if (temp[i] != s[i]) ans++;
        }
        printf("%d\n",ans);
    }

    return 0;
}