/*
1-7B（二选一） 减一运算B
Score 10
Author 郑旭玲
Organization 厦门大学

给定一个由正整数组成的非空数组，也就是一个正整数N(1≤N<10^1000)的各位数字，其中最高位数字存放在数组的首位， 且每个数组元素只存储一位数字。

请求出N-1对应的新数组并输出。

假设除了整数 0 之外，数组的首元素不会是零。
输入格式:

输入在一行中给出正整数N的各位数字，用空格隔开
输出格式:

输出N-1的各位数字，用空格隔开
输入样例：

2 8 6 6

输出样例：

2 8 6 5

Code Size Limit
16 KB
Time Limit
400 ms
Memory Limit
10 MB
Stack size limit
8192 KB
*/

#include <stdio.h>
#include <stdlib.h>

#define LEN_MAX 1000

int main()
{
    char digits=0,N[LEN_MAX]= {0},Res[LEN_MAX]= {0},CF=-1,*p=NULL,*q=NULL;
    short len_N=0,len_Res=0;
    while(((digits=(char)(getchar()))!='\n')&&(digits!=EOF))
        if((digits>='0')&&(digits<='9'))
        {
            N[len_N++]=digits;
            if((digits>'0')&&(len_N>1))
                CF=0;
        }
    if(CF&&(*N=='1'))
        if(len_N==1)
        {
            *Res='0';
            len_Res=1;
        }
        else
            len_Res=(unsigned char)(len_N-1);
    else
        len_Res=len_N;
    p=N+len_N-1,q=Res+len_Res-1;
    CF=-1;
    for(short i=0; i<len_Res; ++i)
    {
        char val=(char)((*p--)+CF);
        if(val<'0')
        {
            val+=10;
            CF=-1;
        }
        else
            CF=0;
        (*q--)=val;
    }
    for(q=Res; q<Res+len_Res; ++q)
        printf("%c ",*q);
    printf("\n");
    return 0;
}
