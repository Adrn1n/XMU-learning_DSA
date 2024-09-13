/*
1-4（四选二） 数组元素循环右移问题
Score 20
Author DS课程组
Organization 浙江大学
一个数组A中存有N（>0）个整数，在不允许使用另外数组的前提下，将每个整数循环向右移M（≥0）个位置，即将A中的数据由（A_0 A_1 ... A_(N−1)）变换为（A_(N−M) A_(N−1) A_0 A_1 A_(N−M−1)）（最后M个数循环移至最前面的M个位置）。如果需要考虑程序移动数据的次数尽量少，要如何设计移动的方法？

输入格式:
每个输入包含一个测试用例，第1行输入N（1≤N≤100）和M（≥0）；第2行输入N个整数，之间用空格分隔。

输出格式:
在一行中输出循环右移M位以后的整数序列，之间用空格分隔，序列结尾不能有多余空格。

输入样例:
6 2
1 2 3 4 5 6
输出样例:
5 6 1 2 3 4
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

short Swap(long long *a,long long *b)
{
    *a^=*b;
    *b^=*a;
    *a^=*b;
    return 0;
}

short Move(long long const*A,short n,short m)
{
    if(m)
        for(long long *p=(long long *)A+m; p-A<n; ++p)
        {
            long long *q=(long long *)A+(p-A)%m;
            Swap(p,q);
        }
    return 0;
}

int main()
{
    short N=0,n=0;
    long long M=0;
    scanf("%hd%lld",&N,&M);
    long long A[N];
    for(long long *p=A; p-A<N; ++p)
        scanf("%lld",p);
    M%=N;
    n=N;
    while(M)
    {
        Move(A,n,(short)M);
        short tmp=n;
        n=(short)M,M=M-((tmp-M-1)%M+1);
    }
    for(long long *p=A; p-A<N-1; ++p)
        printf("%lld ",*p);
    printf("%lld\n",A[N-1]);
    return 0;
}
