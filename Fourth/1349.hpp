#pragma once //include guard

#undef strcmp
#undef strcpy

int strcmp(const char *s1, const char *s2);
char* strcpy(char * __restrict dest, const char * __restrict src);

int strcmp(const char *s1, const char *s2) {
	//todo
    //You'd better store them as a char[],which will be more convenient
    //You can reach the string pointer by: s1[i] or *s1
    for ( ; *s1 != '\0' && *s2 != '\0'; s1++,s2++){
        if (*s1 < *s2)
            return -1;
        if (*s1 > *s2)
            return 1;
    }
    if (*s1 != '\0')//s1 is longer
        return 1;
    if (*s2 != '\0')//s2 is longer
        return -1;

    return 0;//equal
}

char* strcpy(char * __restrict dest, const char * __restrict src) {
	//todo

    int l1 = 0,l2 = 0;
    char *t1 = dest,*temp = dest;

    for ( ; *t1 != '\0' ; ++t1) l1++;//strlen
    for ( ; *src != '\0'; ++src) l2++;

    src -= l2;

    //    l1 = strlen(dest); l2 = strlen(src);

    for (int i = 0;i <= l2;++i){//why l2? l1 is useless actually!
        //the ending '\0' also needs to be compared!
        if (&dest[i] == &src[0])//just compare their address(is OK)!
            return dest;
    }

    for (int i = 0;i <= l2;++i){
        if (&src[i] == &dest[0])
            return dest;
    }

    /*for ( ; *src != '\0'; dest++,src++)
        *dest = *src;
    *dest = '\0';//The ending of string:'\0' also needs to be copied.
*/
    for (int i = 0;i < l2; ++i)
        dest[i] = src[i];
    dest[l2] = '\0';

    return dest;
}

