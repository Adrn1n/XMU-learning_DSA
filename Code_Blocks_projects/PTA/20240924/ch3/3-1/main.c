/*
3-1（拓展，基础） 在一个数组中实现两个堆栈
Score 20
Author 陈越
Organization 浙江大学

本题要求在一个数组中实现两个堆栈。
函数接口定义：

Stack CreateStack( int MaxSize );

bool Push( Stack S, ElementType X, int Tag );

ElementType Pop( Stack S, int Tag );

其中Tag是堆栈编号，取1或2；MaxSize堆栈数组的规模；Stack结构定义如下：

typedef int Position;

struct SNode {

    ElementType *Data;

    Position Top1, Top2;

    int MaxSize;

};

typedef struct SNode *Stack;

注意：如果堆栈已满，Push函数必须输出“Stack Full”并且返回false；如果某堆栈是空的，则Pop函数必须输出“Stack Tag Empty”（其中Tag是该堆栈的编号），并且返回ERROR。
裁判测试程序样例：

#include <stdio.h>

#include <stdlib.h>


#define ERROR 1e8

typedef int ElementType;

typedef enum { push, pop, end } Operation;

typedef enum { false, true } bool;

typedef int Position;

struct SNode {

    ElementType *Data;

    Position Top1, Top2;

    int MaxSize;

};

typedef struct SNode *Stack;


Stack CreateStack( int MaxSize );

bool Push( Stack S, ElementType X, int Tag );

ElementType Pop( Stack S, int Tag );


Operation GetOp();  /* details omitted */
/*

void PrintStack( Stack S, int Tag ); /* details omitted */
/*


int main()

{

    int N, Tag, X;

    Stack S;

    int done = 0;


    scanf("%d", &N);

    S = CreateStack(N);

    while ( !done ) {

        switch( GetOp() ) {

        case push:

            scanf("%d %d", &Tag, &X);

            if (!Push(S, X, Tag)) printf("Stack %d is Full!\n", Tag);

            break;

        case pop:

            scanf("%d", &Tag);

            X = Pop(S, Tag);

            if ( X==ERROR ) printf("Stack %d is Empty!\n", Tag);

            break;

        case end:

            PrintStack(S, 1);

            PrintStack(S, 2);

            done = 1;

            break;

        }

    }

    return 0;

}


/* 你的代码将被嵌在这里 */
/*

输入样例：

5
Push 1 1
Pop 2
Push 2 11
Push 1 2
Push 2 12
Pop 1
Push 2 13
Push 2 14
Push 1 3
Pop 2
End

输出样例：

Stack 2 Empty
Stack 2 is Empty!
Stack Full
Stack 1 is Full!
Pop from Stack 1: 1
Pop from Stack 2: 13 12 11

Code Size Limit
16 KB
Time Limit
400 ms
Memory Limit
64 MB
*/

#include <stdio.h>
#include <stdlib.h>

#define ERROR 1e8
typedef int ElementType;
typedef enum { push, pop, end } Operation;
typedef enum { false, true } bool;
typedef int Position;
struct SNode
{
    ElementType *Data;
    Position Top1, Top2;
    int MaxSize;
};
typedef struct SNode *Stack;

Stack CreateStack( int MaxSize );
bool Push( Stack S, ElementType X, int Tag );
ElementType Pop( Stack S, int Tag );

Operation GetOp();  /* details omitted */
void PrintStack( Stack S, int Tag ); /* details omitted */

int main()
{
    int N, Tag, X;
    Stack S;
    int done = 0;

    scanf("%d", &N);
    S = CreateStack(N);
    while ( !done )
    {
        switch( GetOp() )
        {
        case push:
            scanf("%d %d", &Tag, &X);
            if (!Push(S, X, Tag)) printf("Stack %d is Full!\n", Tag);
            break;
        case pop:
            scanf("%d", &Tag);
            X = Pop(S, Tag);
            if ( X==ERROR ) printf("Stack %d is Empty!\n", Tag);
            break;
        case end:
            PrintStack(S, 1);
            PrintStack(S, 2);
            done = 1;
            break;
        }
    }
    return 0;
}

/* 你的代码将被嵌在这里 */
Stack CreateStack( int MaxSize )
{
    return 0;
}
bool Push( Stack S, ElementType X, int Tag )
{
    return 0;
}
ElementType Pop( Stack S, int Tag )
{
    return 0;
}

Operation GetOp()
{
    return 0;
}
void PrintStack( Stack S, int Tag )
{
}
