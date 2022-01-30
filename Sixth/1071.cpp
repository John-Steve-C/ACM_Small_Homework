//
// Created by Leonard C on 2021/12/5.
//

#include <bits/stdc++.h>

class LinkList {
    //TODO
private:
    int siz;
    struct NODE {
        int data;
        NODE *next, *pre;
        NODE() {data = 0; next = nullptr; pre = nullptr;}//构造函数
    } *head, *rear, *p;

public:
    LinkList() {
        init();
    }

    ~LinkList() {
        clear();
//        delete head;
//        delete rear;
    }

    void init() {
        head = new NODE;
        rear = new NODE;
        head->next = rear;
        head->pre = nullptr;
        rear->next = nullptr;
        rear->pre = head;
        p = nullptr;
        siz = 0;

        return;
    }

    void clear() {
        NODE *del = head;
        for (p = head->next; p != nullptr; p = p->next) {//这样会少删除rear!
            delete del;
            del = p;
        }
        siz = 0;

        delete rear;

        return;
    }

    void push(const int &x) {//不是push_back!
        //要保证有序性,for暴力查找
        p = head->next;
        while (p->data <= x && p != rear)
            p = p->next;

        siz++;
        NODE *temp = p->pre, *t = p;
        p = new NODE;
        p->data = x;
        p->pre = temp;
        p->next = t;

        t->pre = p;
        temp->next = p;

        return;
    }

    int getKth(int x) {//query
        //Base(x) ranges from 0 to siz-1,so I add 1
        x++;
        if (x <= 0 || x > siz) return -1;
        p = head;
        for (int i = 1; i <= x; ++i) {
            p = p->next;
        }

        return p->data;
    }

    void merge(LinkList *q) {
        int i = 1, j = 1;
        NODE *cur = head;
        //一开始，我以为LinkList tmp; 不要这么写
        //因为tmp是局部变量，所以退出函数后会自动析构!
        //所以直接声明一个数组来记录data,最后修改(*this).data即可.
        //然而，这种做法也会浪费时间.不要先存到数组中，再重新赋值
        //而且以上做法会带来一些奇怪的错误.
        //最后，我发现，应该直接声明一个指针，改变节点之间的指向顺序，
        // 不需要对数据进行赋值操作
        p = head->next;
        q->p = q->head->next;
        while (i <= siz && j <= q->siz) {
            if (p->data < q->p->data) {
                i++;
                cur->next = p;
                p->pre = cur;
                cur = p;
                p = p->next; //要记得遍历啊......
            } else {
                j++;
                cur->next = q->p;
                q->p->pre = cur;
                cur = q->p;
                q->p = q->p->next;
            }
        }
        //todo:剩下的部分，还有尾指针也要处理
        if (i > siz) {
            for (; j <= q->siz; ++j, q->p = q->p->next) {
                cur->next = q->p;
                q->p->pre = cur;
                cur = q->p;
            }
            cur->next = rear;
            rear->pre = cur;
            //不是cur = rear;改完就不会RE了
        } else {
            for (; i <= siz; ++i, p = p->next) {
                cur->next = p;
                p->pre = cur;
                cur = p;
            }
            //此时p的结尾自然是rear,下列语句可省略
//            cur->next = rear;
//            rear->pre = cur;
        }

        siz += q->siz;
        q->siz = 0;
        q->head->next = q->rear;//需要这两句
        q->rear->pre = q->head;//防止通过q重新访问到之气那的节点
        //原本q的节点已经被并入p中，不需要进行clear操作.
        //事实上，上述指针的变动，可以认为就是clear
        //而在程序结束后，q的head和rear自然会被析构

        return;
    }
};

class LinkListArray {
private:
    int len;
    LinkList **lists;

public:
    LinkListArray(int n) : len(n) {
        lists = new LinkList *[n];
        for (int i = 0; i < n; ++i) lists[i] = new LinkList;
    }

    ~LinkListArray() {
        for (int i = 0; i < len; ++i) {
            delete lists[i];
        }
        delete[]lists;
    }

    void insertNumber(int n, int x) {
        lists[n]->push(x);
    }

    int queryNumber(int n, int k) {
        return lists[n]->getKth(k);
    }

    void mergeLists(int p, int q) {
        lists[p]->merge(lists[q]);
    }

};

int main() {
    int len, m;

    freopen("ans.txt", "w", stdout);
    scanf("%d%d", &len, &m);
    LinkListArray a = LinkListArray(len);
    for (int i = 0, op, s1, s2; i < m; ++i) {
        scanf("%d%d%d", &op, &s1, &s2);
        if (op == 0) {
            a.insertNumber(s1, s2);
        }
        if (op == 1) {
            printf("%d\n", a.queryNumber(s1, s2));
        }
        if (op == 2) {
            a.mergeLists(s1, s2);
        }
    }
    fclose(stdout);
    return 0;
}