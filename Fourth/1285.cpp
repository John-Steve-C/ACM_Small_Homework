//
// Created by Leonard C on 2021/10/27.
//
#include <bits/stdc++.h>
using namespace std;
int n,k,num = 0,a[100010];
int check(int l,int r){
    for (int i = l;i <= r - 1;++i)
        if (a[i] > a[i + 1]) return 0;
    return 1;
}
void merge_sort(int l,int r){
    if (l >= r - 1 || !k) return;

//    if (check(l,r)) return;

    int mid = (l + r) >> 1;

    swap(a[mid - 1],a[mid]);
    k -= 2;
    merge_sort(l,mid);
    merge_sort(mid,r);
}
int main(){

    scanf("%d%d",&n,&k);

    if (!(k % 2)) {//k must be odd
        cout<<-1;
        return 0;
    }

    for (int i = 1;i <= n;++i)
        a[i] = i;

    k--;
    merge_sort(1,n + 1);//reverse-operation

    if (k)
        cout<<-1;
    else
    for (int i = 1;i <= n;++i)
        cout<<a[i]<<' ';

    return 0;
}