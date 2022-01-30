#pragma once //include guard

#undef strtok

char *strtok(char *__restrict str, const char *__restrict delim);

//char s[1000000];
char *strtok(char *__restrict str, const char *__restrict delim) {
    //todo
    int f = 0;
    static char s[1000000];//static,在函数退出后仍然存在
    static int l;
    static int tong[26];

    if (str != nullptr) {//第一次操作
        int len = strlen(str);
        l = len;
        memset(tong, 0, sizeof(tong));
        for (int i = 0; i < strlen(delim); ++i)
            tong[(int) delim[i] - 'a']++;

        for (int i = 0; i < l; ++i) {
            if (tong[str[i] - 'a']) {
                f = 1;
                break;
            }
        }
        if (!f) return nullptr;//是否存在分隔符

        for (int i = 0; i < l; ++i) {
            s[i] = str[i];//把第一次的s1转存到s中
        }
        for (int i = 0; i < l; ++i) {
            if (tong[str[i] - 'a']) {
                s[i] = '\0';//把分隔符的位置设成'\0'
            }
        }
    }

    static char t[1000000];//一定要static,否则返回后,t会消亡,指针无法传递
    for (int i = 0; i < l; ++i) t[i] = '\0';

    int k = 0;
    for (int i = 0; i < l; ++i) {
        if (s[i] == '\0') continue;
        while (s[i] != '\0') {
            t[k++] = s[i];//把两端'\0'中间的字符串转存到t
            s[i] = '\0';//再把s中间清空
            ++i;
        }
        return t;
    }

    return nullptr;//没找到(s已经为空)
}
