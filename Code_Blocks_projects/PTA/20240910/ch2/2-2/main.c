/*
2-2（二选一A） 线性表元素的区间删除
Score 20
Author DS课程组
Organization 浙江大学

给定一个顺序存储的线性表，请设计一个函数删除所有值大于min而且小于max的元素。删除后表中剩余元素保持顺序存储，并且相对位置不能改变。
函数接口定义：

List Delete( List L, ElementType minD, ElementType maxD );

其中List结构定义如下：

typedef int Position;

typedef struct LNode *List;

struct LNode {

    ElementType Data[MAXSIZE];

    Position Last; /* 保存线性表中最后一个元素在数组中的位置 */
/*

};

L是用户传入的一个线性表，其中ElementType元素可以通过>、==、<进行比较；minD和maxD分别为待删除元素的值域的下、上界。函数Delete应将Data[]中所有值大于minD而且小于maxD的元素删除，同时保证表中剩余元素保持顺序存储，并且相对位置不变，最后返回删除后的表。
裁判测试程序样例：

#include <stdio.h>


#define MAXSIZE 20

typedef int ElementType;


typedef int Position;

typedef struct LNode *List;

struct LNode {

ElementType Data[MAXSIZE];

Position Last; /* 保存线性表中最后一个元素的位置 */
/*

};


List ReadInput(); /* 裁判实现，细节不表。元素从下标0开始存储 */
/*

void PrintList( List L ); /* 裁判实现，细节不表 */
/*

List Delete( List L, ElementType minD, ElementType maxD );


int main()

{

    List L;

    ElementType minD, maxD;

    int i;


    L = ReadInput();

    scanf("%d %d", &minD, &maxD);

    L = Delete( L, minD, maxD );

    PrintList( L );


    return 0;

}


/* 你的代码将被嵌在这里 */
/*

输入样例：

10
4 -8 2 12 1 5 9 3 3 10
0 4

输出样例：

4 -8 12 5 9 10

Code Size Limit
16 KB
Time Limit
200 ms
Memory Limit
64 MB
*/

#include <stdio.h>

#define MAXSIZE 20
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode
{
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标0开始存储 */
void PrintList( List L ); /* 裁判实现，细节不表 */
List Delete( List L, ElementType minD, ElementType maxD );

int main()
{
    List L;
    ElementType minD, maxD;
    int i;

    L = ReadInput();
    scanf("%d %d", &minD, &maxD);
    L = Delete( L, minD, maxD );
    PrintList( L );

    return 0;
}

/* 你的代码将被嵌在这里 */
#include <stdlib.h>
List ReadInput()
{
    List list=NULL;
    Position n=0;
    scanf("%d",&n);
    if(n>0)
    {
        list=malloc(sizeof(struct LNode));
        list->Last=-1;
        for(ElementType *p=(list->Data); p-(list->Data)<MAXSIZE; ++p)
            *p=0;
        for(Position i=0; i<n; ++i)
            if(i<MAXSIZE)
            {
                scanf("%d",(list->Data)+i);
                ++(list->Last);
            }
            else
            {
                getchar();
                printf("ERROR insert! Full!\n");
            }
    }
    else
        printf("ERROR insert! N is negative!\n");
    return list;
}
void PrintList( List L )
{
    if(L)
    {
        for(ElementType *p=(L->Data); p-(L->Data)<=(L->Last); ++p)
            printf("%d ",*p);
        printf("\n");
    }
    else
        printf("ERROR! Null list!\n");
}
//Begin
List Delete( List L, ElementType minD, ElementType maxD )
{
    if(L)
    {
        ElementType *p=L->Data,*q=p;
        while(q<=((L->Data)+(L->Last)))
        {
            if((*q<=minD)||(*q>=maxD))
                *p++=*q;
            ++q;
        }
        for(; p<q; ++p)
            *p=0,--(L->Last);
    }
    else
        printf("ERROR! Null list!\n");
    return L;
}
