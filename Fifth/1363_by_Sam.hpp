//
// Created by Leonard C on 2021/11/21.
//

#ifndef SRC_HPP_1363_BY_SAM_HPP
#define SRC_HPP_1363_BY_SAM_HPP

template<typename ValueType>
class MyList {
private:
    struct list {
        ValueType store;
        list *next, *pre;
    } l;
    list *head, *end;
    int siz;
public:
    MyList() {
        //todo:
        head = new list;
        end = head;
        head->next = nullptr;
        head->pre = nullptr;
        siz = 0;
    }

    MyList(MyList &&obj) noexcept: siz(obj.siz) {
        //todo:
        head = obj.head;
        end = obj.end;
        list *p;
        obj.head = new list;
        obj.end = obj.head;
        obj.head->next = nullptr;
        obj.head->pre = nullptr;
        obj.siz = 0;
    }

    MyList(const MyList &obj) : siz(obj.siz) {
        //todo:
        if (obj.siz > 0) {
            list *p = obj.head->next, *q, *last;
            q = new list;
            head = q;
            q->store = obj.head->store;
            q->pre = nullptr;
            last = q;
            while (p != nullptr) {
                q = new list;
                last->next = q;
                q->pre = last;
                q->store = p->store;
                p = p->next;
                last = q;
            }
            q->next = nullptr;
            end = q;
        } else {
            head = new list;
            end = head;
            head->next = nullptr;
            head->pre = nullptr;
        }
    }

    ~MyList() {
        //todo:
        list *p = head, *q;
        while ((q = p->next) != nullptr) {
            delete p;
            p = q;
        }
        delete p;
        siz = 0;
    }

    void push_back(const ValueType &value) {
        //todo:
        siz++;
        list *p;
        p = new list;
        end->next = p;
        p->pre = end;
        p->store = value;
        p->next = nullptr;
        end = p;
    }

    void pop_back() {
        //todo:
        siz--;
        list *p = end;
        end = end->pre;
        end->next = nullptr;
        delete p;
    }

    void push_front(const ValueType &value) {
        //todo:
        list *p;
        p = new list;
        p->pre = head;
        p->store = value;
        p->next = head->next;
        if (siz != 0) {
            (head->next)->pre = p;
        } else {
            end = p;
        }
        head->next = p;
        siz++;
    }

    void pop_front() {
        //todo:
        list *p = head->next;
        if (siz != 1) {
            (p->next)->pre = head;
        } else {
            end = head;
        }
        head->next = p->next;
        delete p;
        siz--;
    }

    ValueType &front() const {
        //todo:
        return (head->next)->store;
    }

    ValueType &back() const {
        //todo:
        return end->store;
    }

    void insert(int index, const ValueType &value) {
        //todo:
        list *p = head, *q;
        for (int iter = 1; iter <= index; ++iter)
            p = p->next;
        q = new list;
        if (p == end) {
            end = q;
        } else {
            (p->next)->pre = q;
        }
        q->pre = p;
        q->store = value;
        q->next = p->next;
        p->next = q;
        siz++;
    }

    void erase(int index) {
        //todo:
        list *p = head, *q;
        for (int iter = 0; iter <= index; ++iter)
            p = p->next;
        if (p == end)
            end = end->pre;
        else (p->next)->pre = p->pre;
        (p->pre)->next = p->next;
        delete p;
        siz--;
    }

    int size() const {
        //todo:
        return siz;
    }

    bool empty() const {
        //todo:
        return (siz == 0);
    }

    void clear() {
        //todo:
        if (siz != 0) {
            list *p = head->next, *q;
            while ((q = p->next) != nullptr) {
                delete p;
                p = q;
            }
            delete p;
        }
        head->next = nullptr;
        end = head;
        siz = 0;
    }

    void link(const MyList &obj) {
        //todo:
        if (obj.empty()) return;
        list *p = end, *q = obj.head->next, *pp;
        for (int i = 1; i <= obj.siz; ++i) {
            pp = new list;
            pp->pre = p;
            pp->store = q->store;
            p->next = pp;
            p = pp;
            q = q->next;
        }
        end = pp;
        end->next = nullptr;
        siz = siz + obj.siz;
    }

    MyList cut(int index) {
        //todo:
        MyList<ValueType> ans;
        if (index == siz) return ans;
        if (index == 0) {
            std::swap(ans.head, head);
            std::swap(ans.end, end);
            std::swap(ans.siz, siz);
            return ans;
        }
        ans.siz = siz - index;
        siz = index;
        list *p = head;
        for (int iter = 0; iter <= index; ++iter)
            p = p->next;
        ans.end = end;
        ans.head->next = p;
        (p->pre)->next = nullptr;
        end = p->pre;
        end->next = nullptr;
        return ans;
    }
};

#endif //SRC_HPP_1363_BY_SAM_HPP
