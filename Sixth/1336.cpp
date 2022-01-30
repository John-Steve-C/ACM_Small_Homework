//
// Created by Leonard C on 2021/12/5.
//

#include "MemoryRiver.hpp"
#include <bits/stdc++.h>

using namespace std;

int main() {
    MemoryRiver<double,2> tp("a.txt");

//    MemoryRiver<int>;
    tp.initialise("a.txt");
    int t = 5, ans = 6;
    double temp = 2.5;
    tp.write_info(t, 6);
    tp.read(temp,2);
    t = tp.write(temp);//save index
    tp.get_info(ans, 6);
    cout << ans << endl;
    cout << tp.write(temp);
    return 0;
}