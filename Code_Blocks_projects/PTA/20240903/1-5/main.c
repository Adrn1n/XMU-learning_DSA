/*
1-5（四选二） 最长对称子串
Score 20
Author 陈越
Organization 浙江大学
对给定的字符串，本题要求你输出最长对称子串的长度。例如，给定Is PAT&TAP symmetric?，最长对称子串为s PAT&TAP s，于是你应该输出11。

输入格式：
输入在一行中给出长度不超过1000的非空字符串。

输出格式：
在一行中输出最长对称子串的长度。

输入样例：
Is PAT&TAP symmetric?
输出样例：
11
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
#include <string.h>

#define MAX_LEN 1000

short LR_sym_len(const char *const Begin,const char *const End,const char *L,const char *R)
{
    short res=0;
    if((L>=Begin)&&(R<End))
    {
        if(L==R)
            --res;
        else if(L+1<R)
            return res;
        do
        {
            if(*L==*R)
            {
                res+=2;
                --L,++R;
            }
            else
                break;
        }
        while((L>=Begin)&&(R<End));
    }
    return res;
}

int main()
{
    char S[MAX_LEN+2]= {0};
    fgets(S,MAX_LEN+1,stdin);
    short res=0;
    const char *L=S,*R=L,*const End=S+strlen(S);
    while((L<=R)&&(L>=S)&&(R<End))
    {
        short cur=LR_sym_len(S,End,L,R);
        res=(cur>res)?cur:res;
        if(L==R)
            ++R;
        else
            ++L;
    }
    printf("%hd\n",res);
    return 0;
}
