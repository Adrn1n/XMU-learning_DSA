/*
2-11（拓展） 共享后缀的链表
Score 25
Author 陈越
Organization 浙江大学

有一种存储英文单词的方法，是把单词的所有字母串在一个单链表上。为了节省一点空间，如果有两个单词有同样的后缀，就让它们共享这个后缀。下图给出了单词“loading”和“being”的存储形式。本题要求你找出两个链表的公共后缀。

fig.jpg (./da14a3e3-6b79-4046-a283-ab41baf80315.jpg)
函数接口定义：

PtrToNode Suffix( List L1, List L2 );

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

L1和L2都是给定的带头结点的单链表。函数Suffix应返回L1和L2的公共后缀的起点位置。
裁判测试程序样例：

#include <stdio.h>

#include <stdlib.h>


typedef char ElementType;


typedef struct Node *PtrToNode;

struct Node {

    ElementType Data; /* 存储结点数据 */
/*

PtrToNode   Next; /* 指向下一个结点的指针 */
/*

};

typedef PtrToNode List; /* 定义单链表类型 */
/*


void ReadInput( List L1, List L2 ); /* 裁判实现，细节不表 */
/*

void PrintSublist( PtrToNode StartP ); /* 裁判实现，细节不表 */
/*

PtrToNode Suffix( List L1, List L2 );


int main()

{

    List L1, L2;

    PtrToNode P;


    L1 = (List)malloc(sizeof(struct Node));

    L2 = (List)malloc(sizeof(struct Node));

    L1->Next = L2->Next = NULL;

    ReadInput( L1, L2 );

    P = Suffix( L1, L2 );

    PrintSublist( P );


    return 0;

}


/* 你的代码将被嵌在这里 */
/*

输入样例：

如图存储的链表

fig.jpg (./da14a3e3-6b79-4046-a283-ab41baf80315.jpg)
输出样例：

ing

Code Size Limit
16 KB
Time Limit
200 ms
Memory Limit
64 MB
*/

#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct Node *PtrToNode;
struct Node
{
    ElementType Data; /* 存储结点数据 */
    PtrToNode   Next; /* 指向下一个结点的指针 */
};
typedef PtrToNode List; /* 定义单链表类型 */

void ReadInput( List L1, List L2 ); /* 裁判实现，细节不表 */
void PrintSublist( PtrToNode StartP ); /* 裁判实现，细节不表 */
PtrToNode Suffix( List L1, List L2 );

int main()
{
    List L1, L2;
    PtrToNode P;

    L1 = (List)malloc(sizeof(struct Node));
    L2 = (List)malloc(sizeof(struct Node));
    L1->Next = L2->Next = NULL;
    ReadInput( L1, L2 );
    P = Suffix( L1, L2 );
    PrintSublist( P );

    return 0;
}

/* 你的代码将被嵌在这里 */
void ReadInput( List L1, List L2 )
{
    L1->Data=0,L2->Data=0;
    List p=L1,q=L2;
    char c=0;
    while((c=(char)getchar())!='\n')
    {
        List ptr=malloc(sizeof(struct Node));
        ptr->Data=c,ptr->Next=NULL;
        ++(L1->Data),p->Next=ptr,p=ptr;
    }
    while((c=(char)getchar())!='\n')
    {
        List ptr=malloc(sizeof(struct Node));
        ptr->Data=c,ptr->Next=NULL;
        ++(L2->Data),q->Next=ptr,q=ptr;
    }
    while((c=(char)getchar())!='\n')
    {
        List ptr=malloc(sizeof(struct Node));
        ptr->Data=c,ptr->Next=NULL;
        ++(L1->Data),++(L2->Data),p->Next=ptr,q->Next=ptr,p=q=ptr;
    }
}
void PrintSublist( PtrToNode StartP )
{
    while(StartP)
        printf("%c",StartP->Data),StartP=StartP->Next;
    printf("\n");
}
PtrToNode Suffix( List L1, List L2 )
{
    List tmp_1=L1,tmp_2=L2,p=L1,q=L2;
    for(; tmp_1&&tmp_2; tmp_1=tmp_1->Next,tmp_2=tmp_2->Next);
    while(tmp_1)
        p=p->Next,tmp_1=tmp_1->Next;
    while(tmp_2)
        q=q->Next,tmp_2=tmp_2->Next;
    for(; p&&q; p=p->Next,q=q->Next)
        if(p==q)
            return p;
    return NULL;
}
