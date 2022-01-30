#include <bits/stdc++.h>
using namespace std;

struct NODE {//链表的结点(元素)
    int data;
    NODE *next;
}*head,*p,*rear;
//head头指针，指向"第0个空元素"。
//head->next指向第1个元素
//rear尾指针
int m;

void initialize() {//初始化链表
    head = rear = new NODE; //指针指向动态变量NODE(链表元素)
    cin >> m;
    int x;
    for (int i = 1;i <= m;++i){
        cin>>x;
        p = new NODE;
        p->data = x;
        rear->next = p;
        rear = p;
    }
    rear->next = nullptr;
}

void insert(int i, int x) {//在第i个元素后，插入元素
    p = head;
    for (int j = 1;j <= i;++j){
        p = p->next;
    }

    NODE *temp;
    temp = new NODE;
    temp->data = x;
    temp->next = p->next;
    p->next = temp;
}

int size() {
    int cnt = 0;
    p = head;
    while (p != nullptr){
        p = p->next;
        cnt++;
    }

    return cnt-1;//多计算了rear后面的nullptr,所以要-1
}

void erase(int i) {//特殊情况:i=1
    p = head;//p从第0个开始
    for (int j = 1;j <= i - 1;++j){
        p = p->next;
    }//p此时指向第i-1个元素

    NODE *to_del;
    to_del = p->next;//实际上删除的元素是p后方的元素,即为(i-1)+1=i
    p->next = to_del->next;
    delete to_del;
}

void swap() {
    int len = size();

    if (len % 2)
        len--;
    p = head->next;
    for (int i = 2;i <= len;i += 2){
        NODE *t1,*t2;
        int k;

        t1 = p;
        p = p->next;
        t2 = p;
        p = p->next;

        k = t1->data;
        t1->data = t2->data;
        t2->data = k;
    }
}

void cut(int i) {//从第i位开始，切断
//舍弃第i+1个到最后一个元素,记得要delete
    p = head;
    for (int j = 1;j <= i;++j){
        p = p->next;
    }

    NODE *del;
    del = p->next;
    while ( del != nullptr){
        p->next = del->next;
        delete del;
        del = p->next;
    }
}

int query(int i) {//查询第i个元素
    p = head;
    for (int j = 1;j <= i;++j){
        p = p->next;
    }
    return p->data;
}

void print() {
    p = head->next;//输出时要从第1个开始,而不是第0个
    while (p != nullptr){
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}

void freeMemory() {//new声明动态变量后，要删除以释放内存
    p = head;
    NODE *t;

    while (p != nullptr){
        t = p->next;
        delete p;
        p = t;
    }
}

int main() {

    int n, op, i, x;

    initialize();

    cin >> n;
    while (n--) {
        cin >> op;
        if (op == 0) {
            cin >> i >> x;
            insert(i, x);
        }
        else if (op == 1) {
            cin >> i;
            erase(i);
        }
        else if (op == 2) {
            swap();
        }
        else if (op == 3) {
            cin >> i;
            cut(i);
        }
        else if (op == 4) {
            cin >> i;
            cout << query(i) << endl;
        }
        else if (op == 5) {
            cout << size() << endl;
        }
        else {
            print();
        }
    }
    freeMemory();

    return 0;
}