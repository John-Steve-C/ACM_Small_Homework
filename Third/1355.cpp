#include<iostream>
#include "Function.hpp"
using namespace std;

void generate(int seed);
int getLen();
int queryMin (int l , int r);
bool check(int index);

int main(){
    int seed,ans;//ansӦ��Ϊ��Сֵ���ڵ��±�
    cin  >> seed;
    generate(seed);

    //���������������
    int base = getLen();
    
    int l = 0, r = base - 1;
	while (l < r){
    	int mid = (l + r) >> 1;
    	
    	int t1 = queryMin(l,mid),t2 = queryMin(mid + 1,r);
    	
    	if (t1 < t2) r = mid;
    	  else l = mid + 1;
    }
    
    ans = l;
        
    check(ans);
    
    return 0;
}
