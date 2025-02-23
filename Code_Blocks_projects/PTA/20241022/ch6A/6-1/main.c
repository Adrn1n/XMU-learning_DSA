/*
6-1 顺序存储的二叉树的最近的公共祖先问题
Score 25
Author DS课程组
Organization 浙江大学

设顺序存储的二叉树中有编号为 i 和 j 的两个结点，请设计算法求出它们最近的公共祖先结点的编号和值。
输入格式:

第 1 行给出正整数 n（≤1000），即顺序存储的最大容量；第 2 行给出 n 个非负整数，其间以空格分隔。其中 0 代表二叉树中的空结点（如果第 1 个结点为 0，则代表一棵空树）；第 3 行给出一对结点编号 i 和 j。

题目保证输入正确对应一棵二叉树，且 1≤i,j≤n。
输出格式:

如果 i 或 j 对应的是空结点，则输出 ERROR: T[x] is NULL，其中 x 是 i 或 j 中先发现错误的那个编号；否则在一行中输出编号为 i 和 j 的两个结点最近的公共祖先结点的编号和值，其间以 1 个空格分隔。
输入样例1：

15
4 3 5 1 10 0 7 0 2 0 9 0 0 6 8
11 4

输出样例1：

2 3

输入样例2：

15
4 3 5 1 0 0 7 0 2 0 9 0 0 6 8
12 8

输出样例2：

ERROR: T[12] is NULL

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

#define N_MAX 1000

typedef short idxT;
typedef long long valT;

idxT bin_ansrt(const idxT i)
{
    idxT ansrt=0;
    if(i>1)
    {
        for(ansrt=2; (ansrt<<1)<=i; ansrt<<=1);
        ansrt=(idxT)(((i-ansrt)>>1)+(ansrt>>1));
    }
    return ansrt;
}

int main()
{
    valT T[N_MAX]= {0};
    idxT n=0;
    scanf("%hd",&n);
    if(n>0)
    {
        for(valT *p=T; p-T<n; ++p)
            scanf("%lld",p);
        idxT i=0,j=0;
        scanf("%hd%hd",&i,&j);
        if((i>0)&&(i<=n)&&(j>0)&&(j<=n))
        {
            if(T[i-1])
                if(T[j-1])
                {
                    if(i!=j)
                    {
                        if(i>j)
                            i^=j,j^=i,i^=j;
                        if(i>1)
                        {
                            i=bin_ansrt(i);
                            while(i!=j)
                            {
                                j=bin_ansrt(j);
                                if(i>j)
                                    i^=j,j^=i,i^=j;
                            }
                        }
                    }
                    printf("%hd %lld\n",i,T[i-1]);
                }
                else
                    printf("ERROR: T[%hd] is NULL\n",j);
            else
                printf("ERROR: T[%hd] is NULL\n",i);
        }
        else
            printf("ERROR\n");
    }
    else
        printf("ERROR\n");
    return 0;
}
