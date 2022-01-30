#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>

#define LIST_LEN 65
#define BLOCK_SIZE 500
#define BLOCK_SPLIT_THRESHOLD BLOCK_SIZE << 1
#define BLOCK_MERGE_THRESHOLD 250
//从上到下:链表的总长度,块的大小,分裂的max,合并的min

using namespace std;

template<class T, int info_len = 2>
class MemoryRiver {//一个MemoryRiver 对应一个文件
private:
    fstream file;
    string file_name;
    int sizeofT = sizeof(T);

public:
    MemoryRiver() = default;

    MemoryRiver(const string &file_name) : file_name(file_name) { initialise(); }

    void initialise(string FN = "") {
        if (FN != "") file_name = FN;
        file.open(file_name, std::fstream::in | std::fstream::out);
        if (!file) {//打开不成功说明文件不存在,并且初始化
            file.open(file_name, std::ofstream::out);
            //新建文件
            int tmp = 0;
            for (int i = 0; i < info_len; ++i)
                file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        }
        //防止连续使用文件时,重复打开导致内部数据被清空
        file.close();
    }

    //读出第n个int的值赋给tmp，1_base
    void get_info(int &tmp, int n) {
        if (n > info_len) return;
        file.open(file_name);
        file.seekg((n - 1) * sizeof(int));
        file.read(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
        return;
    }

    //将tmp写入第n个int的位置，1_base
    void write_info(int tmp, int n) {
        if (n > info_len) return;
        file.open(file_name);
        file.seekp((n - 1) * sizeof(int));
        file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
        return;
    }

    //在文件合适位置写入类对象t，并返回写入的位置索引index
    //位置索引意味着当输入正确的位置索引index，在以下三个函数中都能顺利的找到目标对象进行操作
    //位置索引index可以取为对象写入的起始位置
    int write(T &t) {
        int index;
        int num_T, del_head;//临时声明,从文件中赋值,最后写回文件中
        get_info(num_T, 1);
        get_info(del_head, 2);

        file.open(file_name);
        if (!del_head) {//没有删除过,在文件尾部加
            index = info_len * sizeof(int) + num_T * sizeofT;
            //del_head还是0(相当于上一个节点的指针)
        } else {//在释放掉的空间加
            index = del_head;
            file.seekg(del_head);
            file.read(reinterpret_cast<char *>(&del_head), sizeof(int));
        }
        file.seekp(index);
        file.write(reinterpret_cast<char *>(&t), sizeofT);
        file.close();

        //num_T 更新
        num_T++;
        write_info(num_T, 1);
        write_info(del_head, 2);//更新 del_head 的值
        return index;
    }

    //用t的值更新位置索引index对应的对象，保证调用的index都是由write函数产生
    void update(T &t, const int index) {
        file.open(file_name);
        file.seekp(index);
        file.write(reinterpret_cast<char *>(&t), sizeofT);
        file.close();
    }

    //读出位置索引index对应的T对象的值并赋值给t，保证调用的index都是由write函数产生
    void read(T &t, const int index) {
        file.open(file_name);
        file.seekg(index);
        file.read(reinterpret_cast<char *>(&t), sizeofT);
        file.close();
    }

    //删除位置索引index对应的对象(不涉及空间回收时，可忽略此函数)，保证调用的index都是由write函数产生
    void Delete(int index) {
        int del_head;
        get_info(del_head, 2);

        file.open(file_name);
        //构造一个类似链表的结构,以del_head为指针
        file.seekp(index);
        file.write(reinterpret_cast<char *>(&del_head), sizeof(int));
        del_head = index;
        //更新del_head,写入文件中
        //num_T不需要--!否则链表的位置会出错
        //所以不用读入num_T
        file.close();

        write_info(del_head, 2);
    }
};

class UllNode {
private:
    int offset, val;//val就是value,是排序的第二关键字
    //offset是节点在文件中的位置
    char str[64];//实际上存储的index,用来比对,第一关键字

public:
    friend class UllBlock;
    friend class Ull;

    UllNode() = default;

    UllNode(const std::string &arg1, const int &value, const int &arg2 = 0) {
        //arg1是第一关键字,arg2同理
        strcpy(str, arg1.c_str());
        //注意转换，存储的是char[]，读入的是string
        val = value;
        offset = arg2;
    }

    bool operator<(const UllNode &x) const {//重载小于号,用于lower_bound
        if (strcmp(str, x.str) == 0) return val < x.val;
        else return strcmp(str, x.str) < 0;
    }

    bool operator>(const UllNode &x) const {
        if (strcmp(str, x.str) == 0) return val > x.val;
        else return strcmp(str, x.str) > 0;
    }

    bool operator>=(const UllNode &x) const {
        return !(*this < x);
    }

    bool operator<=(const UllNode &x) const {
        return !(*this > x);
    }

    bool operator==(const UllNode &x) const {
        return (strcmp(str, x.str) == 0) && (val == x.val);
    }

    bool operator!=(const UllNode &x) const {
        return !(*this == x);
    }

    UllNode &operator=(const UllNode &right) {
        strcpy(str, right.str);
        offset = right.offset;
        val = right.val;
        return *this;
    }
};

class UllBlock {
private:
    int nxt, pre, pos;//指针,pos是块首的位置
    int siz;//siz是块的大小
    UllNode array[(BLOCK_SIZE << 1) + 10];//最大空间要2倍

public:
    friend class Ull;

    UllBlock() {
        nxt = pre = siz = 0;
        pos = 0;
    }

    UllBlock(const int _siz, const UllNode *_array) {
        siz = _siz;
        memcpy(array, _array, _siz * sizeof(UllNode));
    }

    UllBlock &operator=(const UllBlock &right) {
        nxt = right.nxt;
        pre = right.pre;
        pos = right.pos;
        siz = right.siz;
        memcpy(array, right.array, siz * sizeof(UllNode));
        return *this;
    }

    UllNode front() {
        return array[0];
    }

    UllNode back() {//注意到,判断是否在块中,要与最后一个最大的元素比较
        if (!siz) return array[0];
        return array[siz - 1];
    }

    bool add(const UllNode &x) {//在块中新添加元素x,0说明合法
        int pos = std::lower_bound(array, array + siz, x) - array;
        //二分查找第一个不小于x的元素，返回的是指针(位置)
        if (array[pos] == x) return 1;//已经存在,不合法
        siz++;
        for (int i = siz - 1; i > pos; --i)
            array[i] = array[i - 1];//后方的元素向后移一位
        array[pos] = x;
        return siz >= (BLOCK_SIZE << 1);//判断大小是否超出限制(2倍的长度)，需要split
    }

    bool del(const UllNode &x) {//删除块中的元素x,0说明合法
        int pos = std::lower_bound(array, array + siz, x) - array;
        if (array[pos] != x) return 1;//不存在
        siz--;
        for (int i = pos; i < siz; ++i)
            array[i] = array[i + 1];//向前移动一位
        array[siz] = UllNode();
        return 0;
    }

    void search(const std::string &key, std::vector<int> &temp_array) {
        for (int i = 0; i < siz; ++i) {
            if (array[i].str == key)
                temp_array.push_back(array[i].val);
        }
    }//在当前块中查找键值位key的Node，返回一个存储val的vector
};

class Ull {//专门用来处理与文件交互的操作
private:
    const std::string file_name;
    int num, fpos;//块的个数和头指针
    //注意:把num存到了文件的头部,需要每次get/write
    MemoryRiver<UllBlock> block_list;

    inline void del_block(const int &pos) {
    }//删除第pos块

public:
    //文件读入,arg就是filename,将二者关联起来
    Ull() {
        num = 0;
        fpos = 8;
    }

    Ull(const std::string &arg) {
        block_list.initialise(arg);
        num = 0;
        fpos = 8;
    }

    ~Ull() = default;

    void find_node(const std::string &key, std::vector<int> &temp_array) {
        UllBlock tp_block;
        block_list.get_info(num, 1);
        for (int i = fpos; i; i = tp_block.nxt) {
            block_list.read(tp_block, i);
            if (key >= tp_block.front().str && key <= tp_block.back().str) {
                tp_block.search(key, temp_array);
            }
        }
    }

    void add_node(const UllNode &node) {
        UllBlock new_block;
        block_list.get_info(num, 1);
        if (!num) {//第一次
            new_block.siz = 1;
            new_block.array[0] = node;
            new_block.pos = block_list.write(new_block);
            block_list.update(new_block, new_block.pos);
            //注意,要更新到文件里
            //以下两行代码,已经由上述的write在MemoryRiver中实现
//            num++;
//            block_list.write_info(num, 1);
        } else {
            int cnt = 0;//cnt是当前遍历到第几块
            for (int i = fpos; i; i = new_block.nxt) {
                cnt++;
                block_list.read(new_block, i);
                if (node < new_block.back() || cnt == num) {
                    new_block.add(node);
                    block_list.update(new_block, i);
                    break;
                }
            }
            if (new_block.siz > BLOCK_SPLIT_THRESHOLD)
                split_block(new_block.pos);
        }
    }

    void delete_node(const UllNode &node) {
        block_list.get_info(num, 1);
        UllBlock tp_block;
        for (int i = fpos; i; i = tp_block.nxt) {
            block_list.read(tp_block, i);
            //可能会发生跨越情况
            if (node < tp_block.front() || node > tp_block.back())
                continue;
            else {
                tp_block.del(node);
                block_list.update(tp_block, i);
                if (node > tp_block.back())
                    break;
            }
        }
        if (tp_block.siz <= BLOCK_MERGE_THRESHOLD)
            merge_block(tp_block.pos);
    }

    void split_block(const int &pos) {
        UllBlock tp_block, new_block;
        //在下方的write中已经更新
//        block_list.get_info(num, 1);
//        num++;
//        block_list.write_info(num, 1);

        block_list.read(tp_block, pos);

        int len = tp_block.siz / 2;
        new_block.siz = tp_block.siz - len;
        memcpy(new_block.array, tp_block.array + len, new_block.siz * sizeof(UllNode));
        tp_block.siz = len;

        new_block.pre = tp_block.pos;//新的块接到后面
        new_block.nxt = tp_block.nxt;
        new_block.pos = block_list.write(new_block);
        tp_block.nxt = new_block.pos;

        block_list.update(tp_block, tp_block.pos);
        block_list.update(new_block, new_block.pos);
    }

    void merge_block(const int &pos) {//把pos合并到pre
        if (pos == 8) return;//头节点
        UllBlock tp_block, pre_block, nxt_block;

//        block_list.get_info(num, 1);
//        num--;
//        block_list.write_info(num, 1);

        block_list.read(tp_block, pos);
        block_list.read(pre_block, tp_block.pre);

        if (tp_block.nxt) {//不是尾节点
            block_list.read(nxt_block, tp_block.nxt);
            nxt_block.pre = pre_block.pos;
            block_list.update(nxt_block, nxt_block.pos);
        }

        pre_block.nxt = tp_block.nxt;
        memcpy(pre_block.array + pre_block.siz, tp_block.array, tp_block.siz * sizeof(UllNode));
        pre_block.siz += tp_block.siz;

        block_list.update(pre_block, pre_block.pos);
        block_list.Delete(tp_block.pos);

        if (pre_block.siz >= BLOCK_MERGE_THRESHOLD)
            split_block(pre_block.pos);
    }

};


int main() {

    int n, num;
    string s, index;

//    freopen("test.in", "r", stdin);
//    freopen("ans.txt", "w", stdout);

    Ull list("TTT");//存储文件名
    cin >> n;
    while (n--) {
        cin >> s >> index;
        if (s == "insert") {
            cin >> num;
            list.add_node(UllNode(index, num));
        } else if (s == "delete") {
            cin >> num;
            list.delete_node(UllNode(index, num));
        } else {
            vector<int> ans;
            list.find_node(index, ans);
            if (ans.empty()) cout << "null" << endl;
            else {
                for (int i = 0; i < ans.size(); ++i)
                    cout << ans[i] << ' ';
                cout << endl;
            }
        }
    }

    return 0;
}