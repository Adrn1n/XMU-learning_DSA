/*
6-7 二叉树的非递归遍历
Score 25
Author 陈越
Organization 浙江大学

本题要求用非递归的方法实现对给定二叉树的 3 种遍历。
函数接口定义：

void InorderTraversal( BinTree BT );

void PreorderTraversal( BinTree BT );

void PostorderTraversal( BinTree BT );

其中BinTree结构定义如下：

typedef struct TNode *Position;

typedef Position BinTree;

struct TNode{

    ElementType Data;

    BinTree Left;

    BinTree Right;

    int flag;

};

要求 3 个函数分别按照访问顺序打印出结点的内容，格式为一个空格跟着一个字符。

此外，裁判程序中给出了堆栈的全套操作，可以直接调用。
裁判测试程序样例：

#include <stdio.h>

#include <stdlib.h>

typedef enum { false, true } bool;


typedef char ElementType;

typedef struct TNode *Position;

typedef Position BinTree;

struct TNode{

    ElementType Data;

    BinTree Left;

    BinTree Right;

    int flag;

};


/*------堆栈的定义-------*/
/*

typedef Position SElementType;

typedef struct SNode *PtrToSNode;

struct SNode {

    SElementType Data;

    PtrToSNode Next;

};

typedef PtrToSNode Stack;


/* 裁判实现，细节不表 */
/*

Stack CreateStack();

bool IsEmpty( Stack S );

bool Push( Stack S, SElementType X );

SElementType Pop( Stack S ); /* 删除并仅返回S的栈顶元素 */
/*

SElementType Peek( Stack S );/* 仅返回S的栈顶元素 */

/*----堆栈的定义结束-----*/
/*


BinTree CreateBinTree(); /* 裁判实现，细节不表 */
/*

void InorderTraversal( BinTree BT );

void PreorderTraversal( BinTree BT );

void PostorderTraversal( BinTree BT );


int main()

{

    BinTree BT = CreateBinTree();

    printf("Inorder:");    InorderTraversal(BT);    printf("\n");

    printf("Preorder:");   PreorderTraversal(BT);   printf("\n");

    printf("Postorder:");  PostorderTraversal(BT);  printf("\n");

    return 0;

}

/* 你的代码将被嵌在这里 */
/*

输入样例：

如图

tree.jpg (./1cc65709-9782-4788-a882-0ff567d5ad8f.jpg)
输出样例：

Inorder: D B E F A G H C I
Preorder: A B D F E C G H I
Postorder: D E F B H G I C A

Code Size Limit
16 KB
Time Limit
400 ms
Memory Limit
64 MB
*/

#include <stdio.h>
#include <stdlib.h>
typedef enum { false, true } bool;

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
    int flag;
};

/*------堆栈的定义-------*/
typedef Position SElementType;
typedef struct SNode *PtrToSNode;
struct SNode
{
    SElementType Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;

/* 裁判实现，细节不表 */
Stack CreateStack();
bool IsEmpty( Stack S );
bool Push( Stack S, SElementType X );
SElementType Pop( Stack S ); /* 删除并仅返回S的栈顶元素 */
SElementType Peek( Stack S );/* 仅返回S的栈顶元素 */
/*----堆栈的定义结束-----*/

BinTree CreateBinTree(); /* 裁判实现，细节不表 */
void InorderTraversal( BinTree BT );
void PreorderTraversal( BinTree BT );
void PostorderTraversal( BinTree BT );

int main()
{
    BinTree BT = CreateBinTree();
    printf("Inorder:");
    InorderTraversal(BT);
    printf("\n");
    printf("Preorder:");
    PreorderTraversal(BT);
    printf("\n");
    printf("Postorder:");
    PostorderTraversal(BT);
    printf("\n");
    return 0;
}
/* 你的代码将被嵌在这里 */
void InorderTraversal( BinTree BT )
{
    if(BT)
    {
        Stack S=CreateStack();
        if(S)
        {
            for(Position p=BT;;)
                if(p->Left)
                {
                    p->flag=0;
                    if(!Push(S,p))
                    {
                        printf("ERROR\n");
                        return;
                    }
                    else
                        p=p->Left;
                }
                else
                {
                    printf(" %c",p->Data);
                    if(p->Right)
                    {
                        p->flag=1;
                        if(!Push(S,p))
                        {
                            printf("ERROR\n");
                            return;
                        }
                        else
                            p=p->Right;
                    }
                    else
                    {
                        while(1)
                            if(IsEmpty(S))
                                return;
                            else
                            {
                                p=Peek(S);
                                if(!(p->flag))
                                {
                                    printf(" %c",p->Data);
                                    if(p->Right)
                                        break;
                                }
                                Pop(S);
                            }
                        p->flag=1,p=p->Right;
                    }
                }
        }
    }
}

void PreorderTraversal( BinTree BT )
{
    if(BT)
    {
        Stack S=CreateStack();
        if(S)
        {
            for(Position p=BT;;)
            {
                printf(" %c",p->Data);
                if(p->Left)
                {
                    p->flag=0;
                    if(!Push(S,p))
                    {
                        printf("ERROR\n");
                        return;
                    }
                    else
                        p=p->Left;
                }
                else if(p->Right)
                {
                    p->flag=1;
                    if(!Push(S,p))
                    {
                        printf("ERROR\n");
                        return;
                    }
                    else
                        p=p->Right;
                }
                else
                {
                    while(1)
                        if(IsEmpty(S))
                            return;
                        else
                        {
                            p=Peek(S);
                            if(!(p->flag)&&(p->Right))
                                break;
                            Pop(S);
                        }
                    p->flag=1,p=p->Right;
                }
            }
        }
    }
}

void PostorderTraversal( BinTree BT )
{
    if(BT)
    {
        Stack S=CreateStack();
        if(S)
        {
            for(Position p=BT;;)
                if(p->Left)
                {
                    p->flag=0;
                    if(!Push(S,p))
                    {
                        printf("ERROR\n");
                        return;
                    }
                    else
                        p=p->Left;
                }
                else if(p->Right)
                {
                    p->flag=1;
                    if(!Push(S,p))
                    {
                        printf("ERROR\n");
                        return;
                    }
                    else
                        p=p->Right;
                }
                else
                {
                    printf(" %c",p->Data);
                    while(1)
                        if(IsEmpty(S))
                            return;
                        else
                        {
                            p=Peek(S);
                            if(!(p->flag)&&(p->Right))
                                break;
                            else
                                printf(" %c",p->Data);
                            Pop(S);
                        }
                    p->flag=1,p=p->Right;
                }
        }
    }
}

/* 裁判实现，细节不表 */
Stack CreateStack()
{
    Stack S=malloc(sizeof(struct SNode));
    if(S)
        S->Data=NULL,S->Next=NULL;
    return S;
}

bool IsEmpty( Stack S )
{
    if(S)
        if(S->Next)
            return false;
    return true;
}

bool Push( Stack S, SElementType X )
{
    if(S)
    {
        PtrToSNode node=malloc(sizeof(struct SNode));
        if(node)
        {
            node->Data=X,node->Next=NULL;
            PtrToSNode p=S;
            for(; p->Next; p=p->Next);
            p->Next=node;
            return true;
        }
    }
    return false;
}

SElementType Pop( Stack S )
{
    SElementType elem=NULL;
    if(S&&(!IsEmpty(S)))
    {
        PtrToSNode p=S;
        for(; (p->Next)->Next; p=p->Next);
        elem=(p->Next)->Data,free(p->Next),p->Next=NULL;
    }
    return elem;
} /* 删除并仅返回S的栈顶元素 */

SElementType Peek( Stack S )
{
    SElementType elem=NULL;
    if(S&&(!IsEmpty(S)))
    {
        PtrToSNode p=S;
        for(; p->Next; p=p->Next);
        elem=p->Data;
    }
    return elem;
}/* 仅返回S的栈顶元素 */

BinTree CreateBinTree()
{
    BinTree T=NULL;
    long long n=0;
    scanf("%lld",&n),getchar();
    if(n>0)
    {
        T=malloc(n*sizeof(struct TNode));
        if(T)
            for(BinTree p=T; p-T<n; ++p)
            {
                long long l=0,r=0;
                scanf("%c%lld%lld",&(p->Data),&l,&r),getchar();
                if(l>0)
                    p->Left=T+l-1;
                else
                    p->Left=NULL;
                if(r>0)
                    p->Right=T+r-1;
                else
                    p->Right=NULL;
            }
    }
    return T;
} /* 裁判实现，细节不表 */
