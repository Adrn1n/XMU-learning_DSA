/*
2-6（三选一） 约瑟夫环
Score 25
Author 李廷元
Organization 中国民用航空飞行学院

N个人围成一圈顺序编号，从1号开始按1、2、3......顺序报数，报p者退出圈外，其余的人再从1、2、3开始报数，报p的人再退出圈外，以此类推。
请按退出顺序输出每个退出人的原序号。
输入格式:

输入只有一行，包括一个整数N(1<=N<=3000)及一个整数p(1<=p<=5000)。
输出格式:

按退出顺序输出每个退出人的原序号，数据间以一个空格分隔，但行尾无空格。
输入样例:

在这里给出一组输入。例如：

7 3

输出样例:

3 6 2 7 5 1 4

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

typedef short ele_type;
typedef short idx_type;

typedef struct Node_
{
    ele_type val;
    struct Node_ *next;
} Node;

Node *Push_start(Node **ptr_start,Node **ptr_end,const ele_type val)
{
    Node *node=malloc(sizeof(Node));
    node->val=val;
    if((*ptr_start)&&(*ptr_end))
        node->next=*ptr_start,(*ptr_end)->next=node;
    else
        *ptr_end=node->next=node;
    return (*ptr_start=node);
}

int main()
{
    idx_type N=0,p=0;
    scanf("%hd",&N);
    Node *Start=NULL,*End=Start;
    for(idx_type i=N; i>0; --i)
        Push_start(&Start,&End,i);
    scanf("%hd",&p);
    return 0;
}
