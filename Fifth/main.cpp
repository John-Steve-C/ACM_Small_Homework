//
// Created by Leonard C on 2021/11/18.
//
#include <bits/stdc++.h>
#include "Calendar.hpp"

using namespace std;

int main() {

    Calendar c;
    c = Calendar("2010-01-02");
    /*cout << c.getday() << endl;
    cout << c << endl;
    cout << c.getday() << endl;
    cout << ++c << endl;
    cout << c.getday() << endl;
    cout << (c += 1) << endl;
    cout << c.getday() << endl;
    cout << (c -= 1) << endl;
    cout << c.getday() << endl;
    cout << --c << endl;*/

    cout << (c += 1) - (c -= 1) << endl;//is 0!
    cout << c - c << endl;
    cout << (c -= 1) - (c += 1) << endl;
}