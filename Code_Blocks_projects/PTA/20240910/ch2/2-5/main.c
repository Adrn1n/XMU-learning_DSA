/*
2-5 单链表分段逆转
Score 25
Author 陈越
Organization 浙江大学

给定一个带头结点的单链表和一个整数K，要求你将链表中的每K个结点做一次逆转。例如给定单链表 1→2→3→4→5→6 和 K=3，你需要将链表改造成 3→2→1→6→5→4；如果 K=4，则应该得到 4→3→2→1→5→6。
函数接口定义：

void K_Reverse( List L, int K );

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

L是给定的带头结点的单链表，K是每段的长度。函数K_Reverse应将L中的结点按要求分段逆转。
裁判测试程序样例：

#include <stdio.h>

#include <stdlib.h>


typedef int ElementType;


typedef struct Node *PtrToNode;

struct Node {

    ElementType Data; /* 存储结点数据 */
/*

PtrToNode   Next; /* 指向下一个结点的指针 */
/*

};

typedef PtrToNode List; /* 定义单链表类型 */
/*


List ReadInput(); /* 裁判实现，细节不表 */
/*

void PrintList( List L ); /* 裁判实现，细节不表 */
/*

void K_Reverse( List L, int K );


int main()

{

    List L;

    int K;


    L = ReadInput();

    scanf("%d", &K);

    K_Reverse( L, K );

    PrintList( L );


    return 0;

}


/* 你的代码将被嵌在这里 */
/*

输入样例：

6
1 2 3 4 5 6
4

输出样例：

4 3 2 1 5 6

Code Size Limit
16 KB
Time Limit
400 ms
Memory Limit
64 MB
*/

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct Node *PtrToNode;
struct Node
{
    ElementType Data; /* 存储结点数据 */
    PtrToNode   Next; /* 指向下一个结点的指针 */
};
typedef PtrToNode List; /* 定义单链表类型 */

List ReadInput(); /* 裁判实现，细节不表 */
void PrintList( List L ); /* 裁判实现，细节不表 */
void K_Reverse( List L, int K );

int main()
{
    List L;
    int K;

    L = ReadInput();
    scanf("%d", &K);
    K_Reverse( L, K );
    PrintList( L );

    return 0;
}

/* 你的代码将被嵌在这里 */
List ReadInput()
{
    List head=malloc(sizeof(struct Node)),tail=head;
    head->Data=0,head->Next=NULL;
    ElementType cnt=0;
    scanf("%d",&cnt);
    head->Data=cnt;
    while(cnt--)
    {
        List node=malloc(sizeof(struct Node));
        scanf("%d",&(node->Data)),node->Next=NULL;
        tail->Next=node,tail=tail->Next;
    }
    return head;
}
void PrintList( List L )
{
    if(L)
    {
        L=L->Next;
        while(L)
        {
            printf("%d ",L->Data);
            L=L->Next;
        }
    }
    printf("\n");
}
//Begin
void K_Reverse( List L, int K )
{
    if(L&&(K>0))
    {
        List p=L,q=L->Next;
        while(q)
        {
            int k=K;
            while((k--)&&q)
                q=q->Next;
            if(k<0)
            {
                List f=p->Next,b=f->Next,tmp=f;
                while(b!=q)
                {
                    List ptr=b->Next;
                    b->Next=f;
                    f=b,b=ptr;
                }
                p->Next=f,tmp->Next=q;
                p=tmp;
            }
            else
                break;
        }
    }
}
