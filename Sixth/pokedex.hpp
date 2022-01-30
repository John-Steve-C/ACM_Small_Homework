//
// Created by Leonard C on 2021/12/16.
//

#ifndef SRC_HPP_POKEDEX_HPP
#define SRC_HPP_POKEDEX_HPP
//可以自己定义一些全局变量、引用头文件
#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

float counter[7][7] = {{0.5, 0.5, 2,   1,   1,   1, 0.5},
                       {2,   0.5, 0.5, 1,   1,   2, 0.5},
                       {0.5, 2,   0.5, 1,   0.5, 2, 0.5},
                       {1,   2,   0.5, 1,   2,   0, 0.5},
                       {1,   1,   2,   0.5, 1,   1, 1},
                       {2,   1,   0.5, 2,   0,   1, 1},
                       {1,   1,   1,   1,   1,   1, 2}
};

class BasicException {
protected:
    //可以自己定义所需要的成员
    string message;
    //const Nt

public:
    explicit BasicException(const string &_message) {
//        strcpy(message, _message);
        //用错误信息初始化
        message = _message;
    }

    virtual const string what() const {
        //return: 错误信息字符串
        return message;
    }
};

//继承只是继承变量和其他函数,构造函数需要自己完成
class ArgumentException : public BasicException {
public:
    explicit ArgumentException(const string &_message) : BasicException(_message) {}
};

class IteratorException : public BasicException {
public:
    explicit IteratorException(const string &_message) : BasicException(_message) {}
};

//enum type{fire, water, grass, electric, flying, ground, dragon};
//这题没必要用
struct Pokemon {
    //设计你自己的宝可梦类！
    //唯一要求：一定要有名为name id的两个public成员变量，评测时需要用到
    char name[12] = "";
    int id = 0;
    bool types[7];

    bool operator<(const Pokemon &rhs) const {
        return id < rhs.id;
    }

    bool operator>(const Pokemon &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Pokemon &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Pokemon &rhs) const {
        return !(*this < rhs);
    }

    int type_to_num(const string &s) const {
        if (s == "fire") return 0;
        else if (s == "water") return 1;
        else if (s == "grass") return 2;
        else if (s == "electric") return 3;
        else if (s == "flying") return 4;
        else if (s == "ground") return 5;
        else if (s == "dragon") return 6;
        return -1;
    }

    Pokemon() {
        for (int i = 0; i < 12; ++i)
            name[i] = '\0';
        memset(types, 0, sizeof(types));
        id = 0;
    }

    Pokemon(const char *_name, const int &_id, const char *_types) {
        memset(types, 0, sizeof(types));
        id = 0;
        for (int i = 0; i < 12; ++i) name[i] = '\0';

        strcpy(name, _name);
        id = _id;
        for (int i = 0; i < strlen(name); ++i) {
            if (!isalpha(name[i])) {
                string err = "Argument Error: PM Name Invalid (" + string(name) + ")";
                throw ArgumentException(err);
            }
        }
        if (id <= 0) {
            string err = "Argument Error: PM ID Invalid (" + to_string(id) + ")";
            throw ArgumentException(err);
        }

        int len = strlen(_types);
        for (int i = 0; i < len;) {
            int j = i;
            string str = "";
            while (_types[j] != '#' && j < len) {
                str += _types[j];
                //空的string不能按位赋值,必须用加法
                ++j;
            }

            if (type_to_num(str) != -1)
                types[type_to_num(str)] = 1;
            else {
                string err = "Argument Error: PM Type Invalid (" + str + ")";
                throw ArgumentException(err);
            }
            i = j + 1;
        }
    }
};

std::set<Pokemon> Poke_list;
std::unordered_map<int, Pokemon> id_to_Poke;//用来快速查找id

class Pokedex {
private:
    /*struct cmp {
        bool operator()(const Pokemon &a, const Pokemon &b) {
            return a.id > b.id;
        }
    };原本用来重载set的比较规则(默认<)*/

    fstream file;
    string file_name;

public:
    int type_to_num(const string &s) const {
        if (s == "fire") return 0;
        else if (s == "water") return 1;
        else if (s == "grass") return 2;
        else if (s == "electric") return 3;
        else if (s == "flying") return 4;
        else if (s == "ground") return 5;
        else if (s == "dragon") return 6;
        return -1;
    }

    Pokedex(const char *_fileName) {
        //TO DO: 构造函数，从名为_fileName的文件中读取数据（没有则创建）
//        Poke_list.clear();
//        id_to_Poke.clear();
        file_name = _fileName;
        file.open(file_name, fstream::in | fstream::out);
        if (!file) {
            file.open(file_name, std::fstream::out);
            //用out模式打开,就会创建文件
            file.close();
            return;
        } else {
//            file.seekg(0);//从头开始?
            while (file.peek() != EOF) {//peek是指针的下一位
                //todo:注意,不能用!file,eof(),因为文件数据的最后一位不是eof,这么写需要多读一位
                Pokemon new_Poke;
                file.read(reinterpret_cast<char *>(&new_Poke), sizeof(Pokemon));
                //把读进来的字符串,直接赋值为Pokemon
                //因为当初write是按照sizeof(Pokemon),以char写入的
                // 不是按照构造函数赋值
                //注意,该结构体中所有的成员都应该是定长的.不能有vector之类的动态成员
                //似乎只读了name?    eof的问题!
                //为什么文件不用异常判断?因为写入时已经保证了正确性

                if (id_to_Poke.find(new_Poke.id) == id_to_Poke.end()) {
                    Poke_list.insert(new_Poke);
                    id_to_Poke.insert(make_pair(new_Poke.id, new_Poke));
                }//防止重复加入
            }
        }
        file.close();
    }

    ~Pokedex() {
        //TO DO: 析构函数
        file.open(file_name, fstream::out);
        file.seekp(0);
        for (auto item: Poke_list) {
            //cout << "This is a test :" << item.name << endl;
            file.write(reinterpret_cast<char * >(&item), sizeof(Pokemon));
        }

        Poke_list.clear();//析构,清空!
        file.close();
    }

    bool pokeAdd(const char *name, int id, const char *types) const {
        //TO DO: 添加宝可梦
        //返回是否添加成功
        for (int i = 0; i < strlen(name); ++i) {
            if (!isalpha(name[i])) {
                string err = "Argument Error: PM Name Invalid (" + string(name) + ")";
                throw ArgumentException(err);
            }
        }
        if (id <= 0) {
            string err = "Argument Error: PM ID Invalid (" + to_string(id) + ")";
            throw ArgumentException(err);
        }

        Pokemon new_Poke;
        strcpy(new_Poke.name, name);
        new_Poke.id = id;
        int len = strlen(types);
        for (int i = 0; i < len;) {
            int j = i;
            string str = "";
            while (types[j] != '#' && j < len) {
                str += types[j];
                //空的string不能按位赋值,必须用加法
                ++j;
            }
            if (type_to_num(str) != -1)
                new_Poke.types[type_to_num(str)] = 1;
            else {
                string err = "Argument Error: PM Type Invalid (" + str + ")";
                throw ArgumentException(err);
            }
            i = j + 1;
        }

        if (id_to_Poke.find(id) != id_to_Poke.end())
            return false;
        else {
            Poke_list.insert(new_Poke);
            id_to_Poke.insert(make_pair(id, new_Poke));
            return true;
        }
    }

    bool pokeDel(int id) {
        //TO DO: 删除对应宝可梦
        //return: 返回是否删除成功
        if (id <= 0) {//首先都要判断异常
            string err = "Argument Error: PM ID Invalid (" + to_string(id) + ")";
            throw ArgumentException(err);
        }

        if (id_to_Poke.find(id) == id_to_Poke.end()) return false;

        Poke_list.erase(id_to_Poke.at(id));
        id_to_Poke.erase(id);
        return true;
    }

    std::string pokeFind(int id) const {
        //TO DO: 查询id对应的宝可梦
        //return: 如果找到，返回宝可梦的name。否则返回字符串 "None"
        if (id <= 0) {
            string err = "Argument Error: PM ID Invalid (" + to_string(id) + ")";
            throw ArgumentException(err);
        }

        if (id_to_Poke.find(id) == id_to_Poke.end())
            return "None";
        else
            return id_to_Poke.at(id).name;
    }

    std::string typeFind(const char *types) const {
        //TO DO: 查询属性包含了types中的属性的宝可梦
        //return: 如果找到，返回多行字符串。第一行为满足的宝可梦数量，
        //          接下来每一行为宝可梦的name，按id从小到大。
        //        如果找不到，返回字符串 "None"
        //注意，types可能为多种属性，同样用 # 号分隔
        int cnt = 0, len = strlen(types);
        vector<string> query, ans;

        for (int i = 0; i < len;) {
            int j = i;
            string str = "";
            while (types[j] != '#' && j < len) {
                str += types[j];
                ++j;
            }
            if (type_to_num(str) != -1)
                query.push_back(str);
            else {
//                cout << "This is an error: " << str << endl;
                string err = "Argument Error: PM Type Invalid (" + str + ")";
                throw ArgumentException(err);
            }
            i = j + 1;
        }

        for (const auto &item: Poke_list) {
            int t = 0;
            for (int k = 0; k < query.size(); ++k) {
                for (int j = 0; j < 7; ++j) {
                    if (item.types[j] && type_to_num(query[k]) == j) {
                        t++;
                    }
                }
                if (t == query.size()) {
                    cnt++;
                    ans.emplace_back(item.name);
                }
            }
        }

        if (!cnt) return "None";

        string output = to_string(cnt);//C++11内置函数
        for (int i = 0; i < ans.size(); ++i) {
            output += '\n' + ans[i];
        }
        return output;
    }

    float attack(const char *type, int id) const {
        //TO DO: 伤害倍率计算
        //return: 返回id对应的宝可梦受到属性type的攻击的伤害倍率。
        //          如果id对应不存在宝可梦，返回 -1
        //这里type保证为单属性
        if (id <= 0) {
            string err = "Argument Error: PM ID Invalid (" + to_string(id) + ")";
            throw ArgumentException(err);
        }
        if (type_to_num(type) == -1) {
            string err = "Argument Error: PM Type Invalid (" + string(type) + ")";
            throw ArgumentException(err);
        }


        if (id_to_Poke.find(id) == id_to_Poke.end()) return -1;
        Pokemon temp = id_to_Poke.at(id);
        float ans = 1;
        for (int i = 0; i < 7; ++i) {
            if (temp.types[i])
                ans *= counter[type_to_num(type)][i];
        }
        return ans;
    }

    int catchTry() const {
        //TO DO: 全图鉴捕获尝试
        //return: 按照前文过程最后能拥有的宝可梦数量。
        int ct[7];
        set<Pokemon> is_catched;
        queue<Pokemon> q;
        memset(ct, 0, sizeof(ct));
        q.push(*Poke_list.begin());
        is_catched.insert(*Poke_list.begin());

        while (!q.empty()) {
            Pokemon temp = q.front();
            q.pop();

            for (int i = 0; i < 7; ++i) {
                if (temp.types[i])
                    ct[i] = 1;
            }
            for (int i = 0; i < 7; ++i)
                if (ct[i]) {
                    for (const auto &item: Poke_list)
                        if (is_catched.find(item) == is_catched.end()) {
                            //如果没被抓过,才要判断入队
                            float ans = 1;
                            for (int j = 0; j < 7; ++j) {
                                if (item.types[j])
                                    ans *= counter[i][j];
                            }
                            if (ans >= 2) {//克制
                                q.push(item);
                                is_catched.insert(item);
                                continue;
                            }
                        }
                }
        }

        return is_catched.size();
    }

    struct iterator {//迭代器:指针
        //可以自己定义所需要的成员
        set<Pokemon>::iterator it;//定义一个set<Pokemon>的迭代器,叫做it
        bool flag = false;//是否赋初值

        //构造函数
        iterator(set<Pokemon>::iterator t) {
            it = t;
            flag = true;
        }

        iterator &operator++() {
            //TO DO: ++迭代器
            if (!flag || it == Poke_list.end()) //越界
                throw IteratorException("Iterator Error: Invalid Iterator");
            it++;
            return *this;
        }

        iterator &operator--() {
            //TO DO: --迭代器
            if (!flag || it == Poke_list.begin())
                throw IteratorException("Iterator Error: Invalid Iterator");
            it--;
            return *this;
        }

        iterator operator++(int) {
            //TO DO: 迭代器++
            if (!flag || it == Poke_list.end())
                throw IteratorException("Iterator Error: Invalid Iterator");
            auto temp = *this;
            it++;
            return temp;
        }

        iterator operator--(int) {
            //TO DO: 迭代器--
            if (!flag || it == Poke_list.begin())
                throw IteratorException("Iterator Error: Invalid Iterator");
            auto temp = *this;
            it--;
            return temp;
        }

        iterator &operator=(const iterator &rhs) {
            //TO DO: 迭代器赋值
            it = rhs.it;
            flag = rhs.flag;
            return *this;
        }

        bool operator==(const iterator &rhs) const {
            //TO DO: 判断迭代器是否指向同一位置
            return it == rhs.it;
        }

        bool operator!=(const iterator &rhs) const {
            //TO DO: 不等号
            return it != rhs.it;
        }

        const Pokemon &operator*() const {
            //TO DO: * 运算符,注意要加const,因为值不会改变
            if (!flag || it == Poke_list.end())
                throw IteratorException("Iterator Error: Dereference Error");
            return *it;
        }

        /**
         * for the support of it->first.
         * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
         */
        const Pokemon *operator->() const {
            //TO DO: -> 运算符(* + .)
            if (!flag || it == Poke_list.end())
                throw IteratorException("Iterator Error: Dereference Error");

            const Pokemon *temp = &(*it);//找到真实的地址
            return temp;
        }
    };

    iterator begin() {
        //return: 返回指向图鉴头部的迭代器
        return Poke_list.begin();
    }

    iterator end() {
        //return: 返回指向图鉴尾部的迭代器。
        //准确的说，是“最后的一个元素”的后面，指向的内容为空，详情可以去了解标准库容器的 end()
        return Poke_list.end();
    }
};

#endif //SRC_HPP_POKEDEX_HPP
