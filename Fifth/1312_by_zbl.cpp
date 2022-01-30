#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;
const int Max_m = 35;
const int Max_n = 1005;
const int mod = 1e9 + 7;
long long Matrix[Max_m][Max_m][Max_n];
int r[Max_n], tot[Max_n];
bool vis[Max_m], book[Max_m];
int n, m, cnt, ans;
long long poww(int a,int b){
    long long ans = 1,Base = a;
    while(b){
        if(b & 1) ans = ans * Base % mod;
        Base = Base * Base % mod;
        b >>= 1;
    }
    return ans;
}
long long get_kk(long long a,long long b){
    return ( -a * poww(b,mod - 2) % mod + mod ) % mod;
}
void work(int cur){
    memset(vis,0,sizeof (vis));
    for(int i = 1; i <= m; ++i){//第i列
        bool Have_P = 0;
        for(int j = 1; j <= m; ++j){//第j行
            if(vis[j]) continue;
            if(Matrix[j][i][cur]){
                Have_P = 1;
                vis[j] = 1;
                for(int k = j + 1; k <= m; ++k){
                    if(vis[k]) continue;
                    long long kk = get_kk(Matrix[k][i][cur], Matrix[j][i][cur]);
                    for(int l = i; l <= m; ++l)
                        Matrix[k][l][cur] = (( Matrix[k][l][cur] + Matrix[j][l][cur] * kk ) % mod + mod ) % mod;
                }
            }
        }
        if(Have_P) r[cur]++;
    }
}
int main(){
    cin >> n >> m;
    while(n--){
        cnt++;
        for(int i = 1; i <= m; ++i)
            for(int j = 1; j <= m; ++j)
                cin >> Matrix[i][j][cnt];
    }
    for(int i = 1; i <= cnt; ++i) work(i);
    r[0] = -1;
    for(int i = 1; i <= cnt; ++i){
        if(r[i] != r[i - 1]){
            tot[++ans] = i;
        }
    }
    cout << ans << endl;
    for(int i = 1; i <= ans; ++i){
        cout << tot[i] << " ";
    }
    return 0;
}