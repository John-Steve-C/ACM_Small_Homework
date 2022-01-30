//
// Created by Leonard C on 2021/11/18.
//

#ifndef SRC_HPP_CALENDAR_HPP
#define SRC_HPP_CALENDAR_HPP

#include <string>
#include <iostream>

static constexpr int MONTH[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class Calendar {
public:
    int num;
    std::string s;

    bool operator>(const Calendar &b) const {
        return num > b.num;
    }

    bool operator<(const Calendar &b) const {
        return num < b.num;
    }

    bool operator>=(const Calendar &b) const {
        return num >= b.num;
    }

    bool operator<=(const Calendar &b) const {
        return num <= b.num;
    }

    bool operator==(const Calendar &b) const {
        return num == b.num;
    }

    bool operator!=(const Calendar &b) const {
        return num != b.num;
    }

    Calendar &operator++() {//前缀
        *this += 1;
        return *this;
    }

    Calendar operator++(int x) {//后缀
        Calendar temp = *this;
        ++(*this);
        return temp;
    }

    Calendar &operator--() {//前缀
        *this -= 1;
        return *this;
    }

    Calendar operator--(int x) {//后缀
        Calendar temp = *this;
        --(*this);
        return temp;
    }

    int is_leap(int x) {
        if (x % 4 == 0 && x % 100 != 0 || x % 400 == 0) return 1;
        return 0;
    }

    //加上&，可以作为左值
    Calendar &operator+=(const int &x) {//按月加,更快
        if (x < 0) return *this -= (-x);
        if (x == 0) return *this;

        int day, month, year;
        day = num % 100;
        month = (num % 10000) / 100;
        year = num / 10000;

        day += x;
        int tp = MONTH[month];
        while (day > tp) {
            if (is_leap(year) && month == 2) tp++;
            month++;
            day -= tp;
            if (month > 12) {
                month = 1;
                year++;
            }

            tp = MONTH[month];
        }

        return *this = Calendar(year, month, day);
    }

    Calendar &operator-=(const int &x) {
        if (x < 0) return *this += (-x);
        if (x == 0) return *this;

        int day, month, year;
        day = num % 100;
        month = (num % 10000) / 100;
        year = num / 10000;

        day -= x;
        int tp;
        while (day <= 0) {
            month--;
            if (month < 1) {
                month = 12;
                year--;
            }

            tp = MONTH[month];
            if (is_leap(year) && month == 2) tp++;
            day += tp;
        }

        return *this = Calendar(year, month, day);
    }

    Calendar operator+(const int &x) {
        Calendar temp = *this;
        if (x < 0) return temp -= (-x);
        temp += x;
        return temp;
    }

    Calendar operator-(const int &x) {
        Calendar temp = *this;
        if (x < 0) return temp += (-x);
        temp -= x;
        return temp;
    }

    Calendar &operator=(const Calendar &x) {
        num = x.num;
        s = x.s;
        return *this;
    }

    int operator-(const Calendar &x) {//难点!
        if (*this == x) return 0;

        int cnt = 0, f = 0;
        Calendar c1 = *this, c2 = x;
        if (*this > x)
            c1 = x, c2 = *this, f = 1;//保证c1<c2,减出来应该是负数

        int y1 = c1.num / 10000, y2 = c2.num / 10000;

        if (y2 - y1 > 1) {//先加年,把差距缩小到1
            for (int i = y1; i <= y2 - 1; ++i) {
                if (is_leap(i)) c1 += 366, cnt += 366;
                else c1 += 365, cnt += 365;
            }
        }

        int m1 = (c1.num % 10000) / 100;
        while (c1 < c2) {
            int tp = MONTH[m1];//再加月
            if (is_leap(c1.num / 10000) && m1 == 2) tp++;//记得判断闰年
            cnt += tp;
            c1 += tp;

            m1 = (c1.num % 10000) / 100;
        }
        while (c1 > c2) {//最后按天模拟
            cnt--;
            c1--;
        }

        if (f) return cnt;
        else return -cnt;
    }

    friend std::istream &operator>>(std::istream &input, Calendar &t) {
        std::string temp;
        input >> temp;
        t = Calendar(temp);

        return input;
    }

    friend std::ostream &operator<<(std::ostream &output, const Calendar t) {
        std::string temp;
        temp = t.s.substr(0, 4) + "-" + t.s.substr(4, 2) + "-" + t.s.substr(6, 2);
        output << temp;
        return output;
    }

    operator std::string() {//类型转换函数,Calendar -> string
        std::string temp = "-";
        return s.substr(0, 4) + temp + s.substr(4, 2) + temp + s.substr(6, 2);
    }

    //构造函数
    Calendar() {
        num = 0;
        s = "";
    }

    Calendar(std::string t) {
        s = t.substr(0, 4) + t.substr(5, 2) + t.substr(8, 2);

        num = 0;
        for (int i = 0; i < 8; ++i)
            num = num * 10 + s[i] - '0';
    }

    Calendar(int year, int month, int day) {

        num = year * 10000 + month * 100 + day;
        char ch[10] = "";
        std::sprintf(ch, "%08d", num);//控制长度为8,不足补0
        for (int i = 0; i < 8; ++i) {
            s += ch[i];
        }

    }

    int getday() {
        Calendar temp(1, 1, 1);
        return (*this - temp + 1) % 7;
    }
};

Calendar operator "" _C(const char *col, size_t n) {
    //不能放在class里面
    return Calendar(std::string(col));
}

#endif //SRC_HPP_CALENDAR_HPP
