/*
5-3 Knowledge
Score 20
Author 房正华
Organization 青岛工学院

每个人的学识水平化为0~9，用0~9表示其学识高低程度。众所周知，与新生婴儿讨论微积分是一个非常扯淡的事情，所以，学识不为0的人群才可以参与讨论，
现在给定一个m*n的人群，给定每个人的文化程度，每个人仅可和上下左右进行讨论，所以请你求出学术讨论组的个数。
输入格式:

用空格隔开的整数m，n(m行，n列)矩阵(1≤m，n≤100)。
输出格式:

学识组的个数。
输入样例:

在这里给出一组输入。例如：

4 10
0674800011
1034560500
0039600651
0000000098

输出样例:

在这里给出相应的输出。例如：

4

Code Size Limit
16 KB
Time Limit
1000 ms
Memory Limit
64 MB
Stack size limit
8192 KB
*/

#include <stdio.h>
#include <stdlib.h>

#define IDX_MAX 100
#define MOVE_DIMEN 2
#define MOVE_N 4

typedef short idxT;
typedef char valT;
typedef short cntT;

typedef struct queNode_
{
    void *data;
    struct queNode_ *next;
} queNode;

typedef struct queHD_
{
    queNode *tail;
} queHD;

typedef struct corT_
{
    idxT i,j;
} corT;

const idxT Moving[MOVE_DIMEN][MOVE_N]= {{0,0,-1,1},{-1,1,0,0}};

queNode *que_init()
{
    queNode *que=malloc(sizeof(queNode));
    if(que)
    {
        queHD *hd=malloc(sizeof(queHD));
        if(hd)
            hd->tail=que,que->data=hd,que->next=NULL;
        else
            free(que),que=NULL;
    }
    return que;
}

queNode *que_push(const void *const data,queNode *const que)
{
    queNode *node=NULL;
    if(que)
    {
        node=malloc(sizeof(queNode));
        if(node)
            node->data=(void *)data,node->next=NULL,(((queHD *)(que->data))->tail)->next=node,((queHD *)(que->data))->tail=node;
    }
    return node;
}

queNode *que_pop(queNode *const que)
{
    queNode *node=que;
    if(que)
        if((node=que->next))
        {
            que->next=node->next,free(node->data),free(node);
            if(!(que->next))
                ((queHD *)(que->data))->tail=que;
        }
    return node;
}

cntT que_del(queNode **const que_ptr)
{
    cntT cnt=0;
    if(que_ptr&&(*que_ptr))
    {
        while((((queHD *)((*que_ptr)->data))->tail)!=*que_ptr)
            que_pop(*que_ptr),++cnt;
        free((*que_ptr)->data),free(*que_ptr);
        *que_ptr=NULL;
    }
    return cnt;
}

cntT cnet_componN(const valT *const A,const idxT m,const idxT n)
{
    cntT cnt=0;
    if((A)&&(m>0)&&(n>0))
    {
        char Vis[m][n];
        for(char (*p)[n]=Vis; p-Vis<m; ++p)
            for(char *q=*p; q-*p<n; ++q)
                *q=0;
        corT cor= {0,0},*cor_ptr=NULL;
        for(const valT (*p)[n]=(const valT (*)[n])A; (cor.i=(idxT)(p-(const valT (*)[n])A))<m; ++p)
            for(const valT *q=*p; (cor.j=(idxT)(q-*p))<n; ++q)
                if(*q&&(!Vis[cor.i][cor.j]))
                {
                    Vis[cor.i][cor.j]=1,++cnt,cor_ptr=&cor;
                    queNode *que=que_init();
                    if(que)
                    {
                        do
                        {
                            char flag=0;
                            if(que->next)
                                cor_ptr=(que->next)->data,flag=1;
                            for(size_t i=0; i<MOVE_N; (cor_ptr->i)-=Moving[1][i],(cor_ptr->j)-=Moving[0][i],++i)
                            {
                                (cor_ptr->i)+=Moving[1][i],(cor_ptr->j)+=Moving[0][i];
                                if(((cor_ptr->i)>=0)&&((cor_ptr->i)<m)&&((cor_ptr->j)>=0)&&((cor_ptr->j)<n))
                                    if(A[(cor_ptr->i)*n+(cor_ptr->j)]&&(!Vis[cor_ptr->i][cor_ptr->j]))
                                    {
                                        corT *data=malloc(sizeof(corT));
                                        if(data)
                                        {
                                            (data->i)=(cor_ptr->i),(data->j)=(cor_ptr->j);
                                            if(que_push(data,que))
                                            {
                                                Vis[cor_ptr->i][cor_ptr->j]=1;
                                                continue;
                                            }
                                        }
                                        flag=-1;
                                        break;
                                    }
                            }
                            if(flag)
                                if((flag<0)||(!que_pop(que)))
                                {
                                    que_del(&que);
                                    return -1;
                                }
                        }
                        while((((queHD *)(que->data))->tail)!=que);
                        que_del(&que);
                    }
                    else
                        return -1;
                }
    }
    return cnt;
}

int main()
{
    idxT m=0,n=0;
    scanf("%hd%hd",&m,&n);
    if((m>0)&&(n>0)&&(m<=IDX_MAX)&&(n<=IDX_MAX))
    {
        valT A[m][n];
        for(valT (*p)[n]=A; p-A<m; ++p)
        {
            getchar();
            for(valT *q=*p; q-*p<n; ++q)
                *q=(char)(getchar()-'0');
        }
        printf("%d\n",cnet_componN(*A,m,n));
    }
    else
        printf("ERROR\n");
    return 0;
}
