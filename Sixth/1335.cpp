//
// Created by Leonard C on 2021/12/9.
//

#include <bits/stdc++.h>

using namespace std;
int n, m;
vector<pair<string, string>> member[1001], relation[1001];
//first是继承方式,second是类/成员的名称
map<string, int> mp; //把类的名称和id对应
string ans[5] = {"Can not Fetch", "None", "Public", "Private", "Protected"};

int check(int id, const string &s2) {//类 id 中是否含有变量 s2，注意递归实现
    //0 表示 Can not fetch, 1 表示None
    //2 表示public, 3 表示private, 4 表示protected

    //todo:首先判断是否是当前类的成员
    for (int i = 0; i < member[id].size(); ++i) {
        if (member[id][i].second == s2) {
            if (member[id][i].first == "public") return 2;
            if (member[id][i].first == "private") return 3;
            if (member[id][i].first == "protected") return 4;
        }
    }
    //todo:否则就递归找基类里面的成员
    for (int j = 0; j < relation[id].size(); ++j) {
        int _id = mp.at(relation[id][j].second);
        int temp = check(_id, s2);

        if (temp == 0) return 0;//已经无法调用，直接返回
        if (temp != 1) {//能找到
            //规则判断,此时的temp即为变量的访问特性?
            //先看变量的访问权限，再看继承的方式
            if (temp == 3) return 0;
            else if (temp == 4) {
                if (relation[id][j].first == "private") return 3;//不是0！
                //继承的规则要记牢...
                else return 4;
            } else {//temp == 2,变量public
                if (relation[id][j].first == "public") return 2;
                if (relation[id][j].first == "private") return 3;
                if (relation[id][j].first == "protected") return 4;
            }
        }
    }

    //todo:最后就找不到，说明不存在
    return 1;
}


int main() {

    freopen("input.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        string s;
        int t;

        cin >> s;
        mp.insert(make_pair(s, i));
        cin >> t;
        for (int j = 1; j <= t; ++j) {
            string s1, s2;
            cin >> s1 >> s2;
            relation[i].emplace_back(make_pair(s1, s2));
        }
        cin >> t;
        for (int j = 1; j <= t; ++j) {
            string s1, s2;
            cin >> s1 >> s2;
            member[i].emplace_back(make_pair(s1, s2));
        }
    }

    cin >> m;
    while (m--) {
        string s1, s2;
        cin >> s1 >> s2;
        int id = mp.at(s1);

        cout << ans[check(id, s2)] << endl;


    }

    fclose(stdout);
    return 0;
}