// "Wrapper": src.hpp
#ifndef Wrapper_CPP_Wrapper_HPP
#define Wrapper_CPP_Wrapper_HPP

using namespace std;

class shared_ptr {
private:
    int *x, *count;//x存储数据,
    // *count表示一共有几个指针指向该位置,即被引用次数

public:
    //构造函数
    shared_ptr(int *t) {//不能乱用引用传递,这里没有*
        count = new int(1);
        x = t;
    }

    shared_ptr(const shared_ptr &q) {
        x = q.x;
        ++ *(q.count);//注意优先级---'.'是最高的
        count = q.count;//指向同一个位置
    }

    shared_ptr() {
        x = new int;
        count = new int(1);
    }

    //析构函数
    ~shared_ptr() {
        if (*count == 1) {//只剩1个指针,才需要析构
            delete x;
            delete count;
        }
        else{
            -- *count;
        }
    }

    //重载运算符
    shared_ptr &operator=(const shared_ptr &q) {
        if (this == &q) return *this;//比较地址

        -- *count;
        ++ *(q.count);
        if (*count == 0){
            delete x;
            delete count;
        }
        x = q.x;
        count = q.count;
        return *this;
    }

    //重载 *p
    int &operator*() {
        return *x;
    }

    int &operator*() const {
        return *x;
    }

    void reset() {
        if (*count == 1) return ;
        x = new int (*x);//继承该位置原本的数据
        -- *count;//原位置的引用数减少
        count = new int (1);//新位置只有一次引用
    }

    void reset(int *t) {//t为内置指针
        if (*count == 1){
            int *temp = x;
            x = t;
            delete temp;
        }
        else{
            -- *count;
            x = t;
            count = new int (1);
        }
    }

};


#endif //Wrapper_CPP_Wrapper_HPP