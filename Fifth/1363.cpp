#include "1363(Double Linklist).hpp"
#include <iostream>

using namespace std;

void print(MyList<int> t){
    t.p = t.head;
    for (int i = 1; i <= t.size(); ++i) {
        t.p = t.p->next;
        cout << t.p->data << ' ';
    }
    cout<<endl;
}
int main() {

    MyList<int> kkk;
    int n, m;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> m;
        kkk.push_back(m);
    }

    cout << kkk.front() << ' ' << kkk.back() << endl;

    print(kkk);

    int len = kkk.size();
    for (int i = 1; i <= len; ++i) {
        cout << "WTF" << ' ';
    }

    MyList<int> t(kkk);

    cout << endl << t.empty() << endl;

    cout << t.front() << endl;
    t.pop_back();
    t.push_front(5);

    cout << t.size() << endl;
    cout << "WTF" << ' ' << t.size() << endl;

    print(t);

    kkk.pop_front();
    kkk.link(t);
    cout << "WTF" << ' ' << kkk.size() << endl;
    print(kkk);

    kkk.erase(0);
    cout << "WTF" << ' ' << kkk.size() << endl;
    print(kkk);

    kkk.insert(0, 10);
    kkk.insert(0,11);
    cout << "WTF" << ' ' << kkk.size() << endl;
    print(kkk);

    t.clear();
    kkk.cut(3);

    print(kkk);

    cout<<kkk.size();

    kkk.clear();

    return 0;
}