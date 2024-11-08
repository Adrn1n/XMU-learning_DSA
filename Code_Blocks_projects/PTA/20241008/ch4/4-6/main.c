/*
4-6（拓展） 匹配圆周率
Score 30
Author 陈浩川
Organization 厦门大学

使用KMP算法实现串匹配你在课堂上想必已经烂熟于心了，不过咱们先来聊一聊圆周率π。有的人猜想，无理数π的小数部分包含了宇宙中的大秘密，比如你的生日、你男朋友/女朋友的生日，甚至是你的银行卡的账号密码。将它穷尽是一件不可能的事情，但是我们可以对前面的部分进行考察。
在这个题目中，不允许使用编程语言内置的字符串匹配算法，例如C语言中的strcmp。

如果你想查找自己的π信息，可以登录网站The Pi-Search Page (http://www.angio.net/pi/)
输入格式:

输入为两行，第一行为圆周率小数部分的节选s，长度不超过106；第二行是要查找的数字串t，长度不超过106。可以假设，输入都是0~9这样的数字。
输出格式:

输出t在s中首次出现的位置。如果t未在s中出现，则输出-1，以换行结尾。
输入样例1:

821999052039574422
19990520

输出样例1:

2

输入样例2:

881994082555083527588321827035
19940825

输出样例2:

2

输入样例3:

141592653
264

输出样例3:

-1

Code Size Limit
16 KB
Time Limit
50 ms
Memory Limit
64 MB
Stack size limit
8192 KB
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N_Arr 502500

typedef int idxT;

idxT KMP_getNextPtr(const char **const NextPtr,const char *const str,const char *const str_end)
{
    idxT cnt=0;
    if(NextPtr&&str&&(*str)&&(str<str_end))
    {
        const char *Next[str_end-str];
        for(const char *p=str; *p; ++p)
            if(p==str)
                *Next=NULL,*NextPtr=NULL,++cnt;
            else
            {
                const idxT idx=(idxT)(p-str);
                const char *ptr=NextPtr[idx-1];
                while(ptr&&(*ptr!=*(p-1)))
                    ptr=Next[ptr-str];
                if(ptr)
                    Next[idx]=ptr+1;
                else
                    Next[idx]=str;
                while(ptr&&((*ptr!=*(p-1))||(*(ptr+1)==*p)))
                    ptr=Next[ptr-str];
                if(ptr)
                    ++ptr;
                else
                {
                    if(*str==*p)
                        ptr=NULL;
                    else
                        ptr=str;
                }
                NextPtr[idx]=ptr,++cnt;
            }
    }
    return cnt;
}

char *str_KMP_patSrch(const char *const str,const char *const pat,const char *const pat_end)
{
    if(str&&(*str)&&pat&&(*pat)&&(pat<pat_end))
    {
        const idxT len_pat=(idxT)(pat_end-pat);
        const char *NextPtr[len_pat];
        KMP_getNextPtr(NextPtr,pat,pat_end);
        for(const char *p=str,*q=pat;; ++p)
            if(*p&&(*q)&&(*p==*q))
                ++q;
            else
            {
                if(!*q)
                    return (char *)(p-len_pat);
                else if(!*p)
                    break;
                else
                {
                    q=NextPtr[q-pat];
                    while(q&&(*q!=*p))
                        q=NextPtr[q-pat];
                    if(q)
                        ++q;
                    else
                        q=pat;
                }
            }
    }
    return NULL;
}

int main()
{
    char s[MAX_N_Arr]= {0},t[MAX_N_Arr]= {0};
    scanf("%s%s",s,t);
    const char *p=t;
    for(; (*p)&&(p-t<MAX_N_Arr); ++p);
    p=str_KMP_patSrch(s,t,p);
    idxT idx=0;
    if(p)
        idx=(idxT)(p-s);
    else
        idx=-1;
    printf("%d\n",idx);
    return 0;
}
