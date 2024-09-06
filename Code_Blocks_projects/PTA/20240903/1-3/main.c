/*
1-3（四选二） 最大子列和问题
Score 20
Author DS课程组
Organization 浙江大学
给定K个整数组成的序列{N_1, N_2, ..., N_K}，“连续子列”被定义为{N_i, N_(i+1), ..., N_j}，其中 1≤i≤j≤K。“最大子列和”则被定义为所有连续子列元素的和中最大者。例如给定序列{ -2, 11, -4, 13, -5, -2 }，其连续子列{ 11, -4, 13 }有最大的和20。现要求你编写程序，计算给定整数序列的最大子列和。

本题旨在测试各种不同的算法在各种数据情况下的表现。各组测试数据特点如下：

数据1：与样例等价，测试基本正确性；
数据2：10^2个随机整数；
数据3：10^3个随机整数；
数据4：10^4个随机整数；
数据5：10^5个随机整数；
输入格式:
输入第1行给出正整数K (≤100000)；第2行给出K个整数，其间以空格分隔。

输出格式:
在一行中输出最大子列和。如果序列中所有整数皆为负数，则输出0。

输入样例:
6
-2 11 -4 13 -5 -2
输出样例:
20
Code Size Limit
16 KB
Time Limit
10000 ms
Memory Limit
64 MB
Stack size limit
8192 KB
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int k=0;
    scanf("%d",&k);
    long long A[k],cur=0,res=0;
    for(long long *p=A; p-A<k; ++p)
        scanf("%lld",p);
    res=*A;
    for(long long *p=A; p-A<k; ++p)
    {
        cur+=*p;
        if(cur>0)
        {
            if(cur>res)
                res=cur;
        }
        else
            cur=0;
    }
    if(res<0)
        res=0;
    printf("%lld\n",res);
    return 0;
}
