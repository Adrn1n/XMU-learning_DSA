/*
4-4 病毒感染检测
Score 15
Author 王东
Organization 贵州师范大学

人的DNA和病毒DNA均表示成由一些字母组成的字符串序列。然后检测某种病毒DNA序列是否在患者的DNA序列中出现过，如果出现过，则此人感染了该病毒，否则没有感染。例如，假设病毒的DNA序列为baa，患者1的DNA序列为aaabbba，则感染，患者2的DNA序列为babbba，则未感染。（注意，人的DNA序列是线性的，而病毒的DNA序列是环状的)
输入格式:

输入第一行中给出1个整数i(1≤i≤11)，表示待检测的病毒DNA和患者DNA的对数。
输入i行串序列，每行由两个字符串组成（字符串中不含不可见字符），两字符串之间用一个空格分隔，分别代表病毒的DNA序列和患者的DNA序列，病毒的DNA序列和患者的DNA序列长度不超过500。
输出格式:

依次逐行输出每对检测样本的结果，感染输出：YES，未感染输出：NO。
输入样例1:

1
baa bbaabbba

输出样例1:

YES

输入样例2:

2
cced cdccdcce
bcd aabccdxdxbxa

输出样例2:

YES
NO

Code Size Limit
16 KB
Time Limit
400 ms
Memory Limit
64 MB
Stack size limit
8192 KB
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_Len 500

typedef short idxT;

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

char *str_RingPatSrch(const char *const str,const char *const pat,const char *const pat_end)
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
                if(p-str>=len_pat)
                {
                    const idxT num=(idxT)(q-pat);
                    const char *ptr=p-num;
                    for(const char *tmp=pat_end-1; pat_end-tmp<=len_pat-num; --tmp)
                        if(*--ptr!=*tmp)
                        {
                            ptr=p;
                            break;
                        }
                    if(p-ptr==len_pat)
                        return (char *)ptr;
                }
                if(!*p)
                    break;
                q=NextPtr[q-pat];
                while(q&&(*q!=*p))
                    q=NextPtr[q-pat];
                if(q)
                    ++q;
                else
                    q=pat;
            }
    }
    return NULL;
}

int main()
{
    short i=0;
    scanf("%hd",&i);
    while(i--)
    {
        char V[MAX_Len+1]= {0},P[MAX_Len+1]= {0};
        scanf("%s%s",V,P);
        const char *ptr=V;
        for(; *ptr; ++ptr);
        const idxT len_V=(idxT)(ptr-V);
        char revs_V[len_V];
        for(char *tmp=revs_V; tmp-revs_V<len_V; ++tmp)
            *tmp=*--ptr;
        if(str_RingPatSrch(P,V,V+len_V)||(str_RingPatSrch(P,revs_V,revs_V+len_V)))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
