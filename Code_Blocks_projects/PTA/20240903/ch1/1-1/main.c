/*
1-1 提桶寻宝
Score 10
Author 周强
Organization 青岛大学
给你准备好一个小桶，告诉你一片广袤的天地，随手一指，挖宝去吧~

说计算机话！

 好吧，题目是这样的：

假设一个二维区域内藏有财宝，对于给定的此前寻到的财宝数量以及坐标(x,y)，按照以下规则在该位置寻回财宝，并更新财宝数量。

规则：

如果x、y均为奇数，则获得原有三分之一数量的财宝，小数部分忽略不计
如果x、y均为偶数，则获得 5 财宝
如果x、y奇偶性不同，则不获得财宝
注意：财宝数量、坐标x、坐标y都是int类型范围内的非负整数，在同一个位置可以重复寻找并获得财宝。

函数接口定义：
int getTreasure(int *pBucket, int x, int y);
其中，整型参数x、y表示坐标，指针型参数pBucket指向财宝计数的整型变量，函数根据x、y和此前的财宝数目，判断新获取的财宝并修改相应数值。返回类型为int，如果获得财宝，返回1；未获得财宝，返回0。

裁判测试程序样例：
#include <stdio.h>

int getTreasure(int *pBucket, int x, int y);

int main(){
    int bucket,total;
    bucket = total = 0;
    scanf("%d",&total);
    for (int i=0; i<total; i++) {
        int x,y;
        x = y = 0;
        scanf("%d%d", &x, &y);
        int flag = getTreasure(&bucket, x, y);
        printf("[%d]:%d\n", flag, bucket);
    }
}
/**
 你的代码将被嵌到这个位置（当然，会删除此前和此后一行的注释）
**/

/*
输入样例：
3
2 6
1 20
9 9
输出样例：
[1]:5
[0]:5
[1]:6
Code Size Limit
16 KB
Time Limit
400 ms
Memory Limit
64 MB
*/

#include <stdio.h>

int getTreasure(int *pBucket, int x, int y);

int main()
{
    int bucket,total;
    bucket = total = 0;
    scanf("%d",&total);
    for (int i=0; i<total; i++)
    {
        int x,y;
        x = y = 0;
        scanf("%d%d", &x, &y);
        int flag = getTreasure(&bucket, x, y);
        printf("[%d]:%d\n", flag, bucket);
    }
}
/**
 你的代码将被嵌到这个位置（当然，会删除此前和此后一行的注释）
**/

int getTreasure(int *pBucket, int x, int y)
{
    if((x%2)==(y%2))
    {
        if(x%2)
            *pBucket+=((*pBucket)/3);
        else
            *pBucket+=5;
        return 1;
    }
    else
        return 0;
}
