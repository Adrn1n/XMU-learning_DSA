/*
6-6（拓展，基础） 求二叉树高度
Score 20
Author 陈越
Organization 浙江大学

本题要求给定二叉树的高度。
函数接口定义：

int GetHeight( BinTree BT );

其中BinTree结构定义如下：

typedef struct TNode *Position;

typedef Position BinTree;

struct TNode{

    ElementType Data;

    BinTree Left;

    BinTree Right;

};

要求函数返回给定二叉树BT的高度值。
裁判测试程序样例：

#include <stdio.h>

#include <stdlib.h>


typedef char ElementType;

typedef struct TNode *Position;

typedef Position BinTree;

struct TNode{

    ElementType Data;

    BinTree Left;

    BinTree Right;

};


BinTree CreatBinTree(); /* 实现细节忽略 */
/*

int GetHeight( BinTree BT );


int main()

{

    BinTree BT = CreatBinTree();

    printf("%d\n", GetHeight(BT));

    return 0;

}

/* 你的代码将被嵌在这里 */
/*

输出样例（对于图中给出的树）：
Image (./40.jpg)

4

Code Size Limit
16 KB
Time Limit
400 ms
Memory Limit
64 MB
*/

#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree CreatBinTree(); /* 实现细节忽略 */
int GetHeight( BinTree BT );

int main()
{
    BinTree BT = CreatBinTree();
    printf("%d\n", GetHeight(BT));
    return 0;
}
/* 你的代码将被嵌在这里 */
int GetHeight( BinTree BT )
{
    if(BT)
    {
        int l=GetHeight(BT->Left),r=GetHeight(BT->Right);
        return ((l>r)?l:r)+1;
    }
    else
        return 0;
}

BinTree CreatBinTree()
{
    BinTree T=NULL;
    long long n=0;
    scanf("%lld",&n),getchar();
    if(n>0)
    {
        T=malloc(n*sizeof(struct TNode));
        if(T)
            for(Position p=T; p-T<n; ++p)
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
} /* 实现细节忽略 */
