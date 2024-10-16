/*
3-5（二选一A组） 八皇后问题(*)
Score 20
Author 李祥
Organization 湖北经济学院

在国际象棋中，皇后是最厉害的棋子，可以横走、直走，还可以斜走。棋手马克斯·贝瑟尔 1848 年提出著名的八皇后问题：即在 8 × 8 的棋盘上摆放八个皇后，使其不能互相攻击 —— 即任意两个皇后都不能处于同一行、同一列或同一条斜线上。例如：
题图.jpg (./f02577b2-a28e-4f3b-bbc7-93801a88a630.jpg)

现在我们把棋盘扩展到 n×n 的棋盘上摆放 n 个皇后，请问该怎么摆？

请编写程序，输入正整数 n，输出全部摆法（棋盘格子空白处显示句点“.”，皇后处显示字母“Q”，每两个字符之间空一格）。
输入格式

    正整数 n(n>0)

输出格式

    若问题有解，则输出全部摆法（每两种摆法之间空一行）。
    若问题无解，则输出 None。

要求：试探的顺序按从上到下逐行进行，其中每一行按从左到右的逐格进行，请参看输出样例2。
输入样例1

3

输出样例1

None

输入样例2

6

输出样例2

. Q . . . .
. . . Q . .
. . . . . Q
Q . . . . .
. . Q . . .
. . . . Q .

. . Q . . .
. . . . . Q
. Q . . . .
. . . . Q .
Q . . . . .
. . . Q . .

. . . Q . .
Q . . . . .
. . . . Q .
. Q . . . .
. . . . . Q
. . Q . . .

. . . . Q .
. . Q . . .
Q . . . . .
. . . . . Q
. . . Q . .
. Q . . . .

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
#include <string.h>

typedef char data_type;
typedef short idx_type;
typedef int cnt_type;
typedef char size_type;

typedef struct Node_
{
    void *data;
    struct Node_ *next;
} Node;

Node *Stack_push(Node **const Top,const void *const data,const size_type size)
{
    if(Top)
    {
        Node *node=malloc(sizeof(Node));
        node->data=malloc(size),memcpy(node->data,data,size),node->next=*Top;
        return (*Top=node);
    }
    else
        return NULL;
}

Node *Stack_pop(Node **const Top)
{
    if(Top)
    {
        if(*Top)
        {
            Node *tmp=*Top;
            *Top=tmp->next;
            free(tmp->data),free(tmp);
        }
        return *Top;
    }
    return NULL;
}

Node *Stack_del(Node **Top)
{
    while(Stack_pop(Top));
    return (*Top=NULL);
}

Node *Stack_flip(Node **Top)
{
    if(Top)
    {
        if((*Top)&&((*Top)->next))
            for(Node *p=*Top,*q=p->next; q;)
            {
                Node *tmp=q->next;
                q->next=p;
                if(p==*Top)
                    p->next=NULL;
                p=q,q=tmp;
                if(!q)
                {
                    *Top=p;
                    break;
                }
            }
        return *Top;
    }
    return NULL;
}

cnt_type print_ans(const Node *Top,const idx_type n)
{
    cnt_type cnt=0;
    while(Top)
    {
        for(data_type *p=Top->data; p-(data_type *)(Top->data)<n; ++p)
        {
            idx_type i=0;
            while(((*p)--)>0)
            {
                if(!(*p))
                    printf("Q");
                else
                    printf(". ");
                ++i;
            }
            if(i>0)
            {
                while(i++<n)
                    printf(" .");
                printf("\n");
            }
            else
                return -1;
        }
        Top=Top->next;
        if(Top)
            printf("\n");
        ++cnt;
    }
    return cnt;
}

char judge_queens_pre(const data_type *Solution,const idx_type n)
{
    if(n>0)
    {
        for(const data_type *p=Solution; p-Solution<n-1; ++p)
            if((*p==Solution[n-1])||((n-1-(p-Solution))==abs(*p-Solution[n-1])))
                return 0;
        return 1;
    }
    else
        return -1;
}

Node *solve_nQueens(Node **const Solutions,const idx_type n)
{
    *Solutions=NULL;
    data_type Table[n];
    char Used[n];
    for(idx_type i=0; i<n; ++i)
        Table[i]=Used[i]=0;
    idx_type top=0;
    do
        if((top>=0)&&(top<n))
        {
            char flag=1;
            data_type *p=Table+top;
            if((*p>=0)&&(*p<=n))
            {
                if(*p>0)
                {
                    if(Used[*p-1])
                        Used[*p-1]=0;
                    else
                        return NULL;
                }
            }
            else
                return NULL;
            for(++*p; *p<=n; ++*p)
                if(!Used[*p-1])
                    if(judge_queens_pre(Table,(idx_type)(top+1))==1)
                    {
                        if(top==n-1)
                            Stack_push(Solutions,Table,(size_type)(n*sizeof(data_type)));
                        else
                        {
                            Used[*p-1]=1;
                            ++top,flag=0;
                            break;
                        }
                    }
            if(flag)
                Table[top--]=0;
        }
        else
            return NULL;
    while(top>=0);
    Stack_flip(Solutions);
    return *Solutions;
}

int main()
{
    idx_type n=0;
    scanf("%hd",&n);
    Node *Res=NULL;
    solve_nQueens(&Res,n);
    cnt_type cnt=print_ans(Res,n);
    if(!cnt)
        printf("None\n");
    else if(cnt<0)
        printf("ERROR\n");
    Stack_del(&Res);
    return 0;
}
