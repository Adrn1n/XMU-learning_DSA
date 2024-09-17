/*
2-4 求链表的倒数第m个元素
Score 20
Author DS课程组
Organization 浙江大学

请设计时间和空间上都尽可能高效的算法，在不改变链表的前提下，求链式存储的线性表的倒数第m（>0）个元素。
函数接口定义：

ElementType Find( List L, int m );

其中List结构定义如下：

typedef struct Node *PtrToNode;

struct Node {

    ElementType Data; /* 存储结点数据 */
/*

PtrToNode   Next; /* 指向下一个结点的指针 */
/*

};

typedef PtrToNode List; /* 定义单链表类型 */
/*

L是给定的带头结点的单链表；函数Find要将L的倒数第m个元素返回，并不改变原链表。如果这样的元素不存在，则返回一个错误标志ERROR。
裁判测试程序样例：

#include <stdio.h>

#include <stdlib.h>


#define ERROR -1


typedef int ElementType;

typedef struct Node *PtrToNode;

struct Node {

    ElementType Data;

    PtrToNode   Next;

};

typedef PtrToNode List;


List Read(); /* 细节在此不表 */
/*

void Print( List L ); /* 细节在此不表 */
/*


ElementType Find( List L, int m );


int main()

{

    List L;

    int m;

    L = Read();

    scanf("%d", &m);

    printf("%d\n", Find(L,m));

    Print(L);

    return 0;

}


/* 你的代码将被嵌在这里 */
/*

输入样例：

5
1 2 4 5 6
3

输出样例：

4
1 2 4 5 6

Code Size Limit
16 KB
Time Limit
400 ms
Memory Limit
64 MB
*/

#include <stdio.h>
#include <stdlib.h>

#define ERROR -1

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node
{
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表 */

ElementType Find( List L, int m );

int main()
{
    List L;
    int m;
    L = Read();
    scanf("%d", &m);
    printf("%d\n", Find(L,m));
    Print(L);
    return 0;
}

/* 你的代码将被嵌在这里 */
List Read()
{
    return 0;
}
void Print( List L )
{
}
//Begin
ElementType Find( List L, int m )
{
    return 0;
}
