#pragma once //include guard

#undef strcspn
#undef strstr


size_t strcspn (const char *s, const char *reject);
const char *strstr (const char *haystack, const char *needle);
//char *strstr (char *haystack, const char *needle);


size_t strcspn (const char *s, const char *reject) {
	//todo
    int tong[26],l = 0;
    memset(tong,0,sizeof(tong));

    for ( ; *reject != '\0'; ++reject){
        tong[*reject - 'a']++;
    }
    for ( ; *s != '\0'; ++s){
        if (!tong[*s - 'a']){
            return l;
        }
        l++;
    }
    return l;
}

const char *strstr (const char *haystack, const char *needle) {
	//todo
    char s1[1000010],s2[1000010];    //the range!
    int l1 = 0,l2 = 0;//they are integers...
    //Do be careful while coding!

    /*for ( ; *needle != '\0'; ++needle)
        s1[l1++] = *needle;
    s1[l1] = '\0';
    needle -= l1;

    for ( ; *haystack != '\0'; ++haystack){
        s2[l2++] = *haystack;
    }
    s2[l2] = '\0';
    haystack -= l2;*/
    //There's no need to copy the string.
    l1 = strlen(needle);
    l2 = strlen(haystack);

    for (int i = 0;i <= l2 - l1;++i){//restrict the range of i!
        int f = 1;

        for (int j = 0;j < l1;++j){
            if (haystack[i + j] != needle[j]){// else (i+j) 会越界！
                // (s2[i + j] != s1[j]) is also OK.
                f = 0;
                break;
            }
        }
        if (f) return haystack + i;
        //or return &haystack[i];
    }

    return nullptr;
}


//char *strstr (char *haystack, const char *needle) {
//	return const_cast<char*>(strstr(const_cast<const char*>(haystack), needle));
//}


