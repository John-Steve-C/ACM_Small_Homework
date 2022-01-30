//
// Created by Leonard C on 2021/11/21.
//

#ifndef SRC_HPP_1363_DOUBLE_LINKLIST_HPP
#define SRC_HPP_1363_DOUBLE_LINKLIST_HPP
//#include <iostream>
using namespace std;

template<typename T>
class MyList {
public:
    struct NODE {
        T data;
        NODE *next, *pre;
    } *head, *p, *rear;
    //p是用来遍历链表的指针,
    //但是在某些函数中,NODE为const,只能新开一个指针用来遍历
    //所以p实际上是不需要的
    int siz;

    void init() {//初始化,head与rear不重叠
        head = new NODE;
        rear = new NODE;
        head->pre = nullptr;
        head->next = rear;
        rear->pre = head;
        rear->next = nullptr;
        siz = 0;
        return;
    }

    NODE *find(int index) {//index从0开始
        p = head->next;
        for (int i = 1; i <= index; ++i)
            p = p->next;
        return p;
    }

    MyList() {
        init();
    }

    MyList(MyList &&obj) noexcept {//右值
        head = obj.head;
        rear = obj.rear;
        siz = obj.siz;

        obj.init();
    }

    MyList(const MyList &obj) {
        init();

        NODE *temp = obj.head;
        int len = obj.siz;
        for (int i = 1; i <= len; ++i) {
            temp = temp->next;
            push_back(temp->data);
        }
    }

    ~MyList() {
        clear();//删除数据节点
        delete head;
        delete rear;
    }

    void push_back(const T &value) {//insert a NODE before rear?
        p = new NODE;
        siz++;

        NODE *temp = rear->pre;
        p->data = value;
        p->pre = temp;
        p->next = rear;

        rear->pre = p;
        temp->next = p;
        return;
    }

    void pop_back() {//delete the last NODE before rear
        siz--;
        NODE *temp = rear->pre->pre, *to_del = rear->pre;
        temp->next = rear;
        rear->pre = temp;

        delete to_del;
        return;
    }

    void push_front(const T &value) {
        p = new NODE;
        siz++;

        NODE *temp = head->next;
        p->data = value;
        p->pre = head;
        p->next = temp;

        temp->pre = p;
        head->next = p;
        return;
    }

    void pop_front() {
        siz--;
        NODE *temp = head->next->next, *to_del = head->next;
        temp->pre = head;
        head->next = temp;

        delete to_del;
        return;
    }

    T &front() const {
        return head->next->data;
    }

    T &back() const {
        return rear->pre->data;
    }

    void insert(int index, const T &value) {//在index后添加
        p = find(index);
        siz++;

        NODE *temp;
        temp = new NODE;
        temp->data = value;
        temp->pre = p;
        temp->next = p->next;

        p->next = temp;
        temp->next->pre = temp;
        return;
    }

    void erase(int index) {//删除index
        NODE *to_del = find(index);
        siz--;

        NODE *temp = to_del->next;
        p = to_del->pre;
        p->next = temp;
        temp->pre = p;

        delete to_del;
        return;
    }

    int size() const {//the initial size is 0!
        //waste time!
        /*int cnt = 0;
        NODE *temp = head;
        while (temp != nullptr) {
            temp = temp->next;
            cnt++;
        }
        return cnt - 1;*/

        return siz;
    }

    bool empty() const {
        return (siz == 0);
    }

    void clear() {//head & rear aren't deleted.
        p = head->next;//保留第一个NODE
        NODE *t;
        siz = 0;

        while (p->next != nullptr) {//最后的NODE也不删除!
            t = p->next;
            delete p;
            p = t;
        }

        head->next = rear;
        rear->pre = head;
        return;
    }

    void link(const MyList &obj) {//=(*this) + obj
        if (obj.empty()) return;
//        rear->pre->next = obj.head->next;

        NODE *temp = obj.head;
        for (int j = 1; j <= obj.size(); ++j) {
            temp = temp->next;
            push_back(temp->data);
        }
        return;
    }

    MyList cut(int index) {//0--(index-1),(index)--(siz-1)
        MyList<T> tp;
        if (index == siz) return tp;

        /*if (!index) {//从开头就截断
            std::swap(tp.rear, rear);
            std::swap(tp.head, head);
            std::swap(tp.siz, siz);
            return tp;
        }*/

        NODE *old_rear = rear->pre;//
        NODE *new_rear = find(index - 1);
        NODE *new_head = new_rear->next;

        if (!old_rear || !new_rear || !new_head) return tp;

        old_rear->next = tp.rear;
        tp.rear->pre = old_rear;

        new_head->pre = tp.head;
        tp.head->next = new_head;

        new_rear->next = rear;
        rear->pre = new_rear;

        tp.siz = siz - index;
        siz = index;

        return tp;
    }
};

#endif //SRC_HPP_1363_DOUBLE_LINKLIST_HPP
